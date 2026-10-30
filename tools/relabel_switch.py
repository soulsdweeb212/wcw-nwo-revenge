"""Relabels the `case`s of a C function's switch statements so each jump table sends every value to the body the ROM does.

    cd source
    python3 tools/relabel_switch.py FUNC [FUNC...]      (after a full build; then rebuild and run tools/check_rodata.py)

A function's code can be byte-identical while its source maps case values to the wrong bodies, because build.py uses the
ROM's table and never looks at the one the compiler made. The code fixes where each body starts, so the repair is: for every
table index, find the body at the ROM's target address and give it that case value (lowest case value + index). The
bodies and their order are not touched. A function is only rewritten when every table resolves; otherwise it says why."""
import json, re, struct, subprocess, sys
from pathlib import Path

root = Path(__file__).resolve().parent.parent
tc = Path.home() / ".local/share/decompnet/toolchains/binutils-mips"
OD = str(tc / "mips-ps2-decompals-objdump")
B = json.loads((root / "build.json").read_text())
rom = (root / B["image"]).read_bytes()


def rom_of(vram):  # the code overlays' data block (0x800E4xxx..0x800E7xxx) sits at vram - 0x8000CB60 in the ROM
    return vram - 0x8000CB60


def table_runs(obj):
    s = subprocess.run([OD, "-s", "-j", ".rodata", obj], capture_output=True, text=True).stdout
    data = bytearray()
    for line in s.splitlines():
        m = re.match(r"\s+([0-9a-f]+) ((?:[0-9a-f]{1,8} ?){1,4})", line)
        if m:
            raw = bytes.fromhex(m.group(2).replace(" ", ""))
            data[int(m.group(1), 16):int(m.group(1), 16) + len(raw)] = raw
    offs = sorted(int(m.group(1), 16) for m in re.finditer(r"^([0-9a-f]+) R_MIPS_32\s+\.text", subprocess.run(
        [OD, "-r", "-j", ".rodata", obj], capture_output=True, text=True).stdout, re.M))
    runs = []
    for o in offs:
        if runs and runs[-1][0] + 4 * len(runs[-1][1]) == o:
            runs[-1][1].append(struct.unpack(">I", bytes(data[o:o + 4]))[0])
        else:
            runs.append((o, [struct.unpack(">I", bytes(data[o:o + 4]))[0]]))
    return runs


def match_close(text, i, open_ch, close_ch):
    depth = 0
    while i < len(text):
        ch = text[i]
        if text.startswith("/*", i):
            i = text.index("*/", i) + 2; continue
        if text.startswith("//", i):
            i = text.index("\n", i); continue
        if ch in "\"'":
            q = ch; i += 1
            while text[i] != q:
                i += 2 if text[i] == "\\" else 1
        elif ch == open_ch:
            depth += 1
        elif ch == close_ch:
            depth -= 1
            if depth == 0:
                return i
        i += 1
    raise ValueError("unbalanced")


def find_switches(text):
    out = []
    for m in re.finditer(r"\bswitch\s*\(", text):
        p = match_close(text, m.end() - 1, "(", ")")
        o = text.index("{", p)
        out.append((o, match_close(text, o, "{", "}")))
    return out


def parse_groups(text, o, c):
    """Labels of this switch (at any block depth, but not those of a switch nested in it), grouped (consecutive labels
    share a body)."""
    nested = [(o2, c2) for o2, c2 in find_switches(text) if o < o2 and c2 < c]
    toks, i = [], o + 1
    while i < c:
        if text.startswith("/*", i):
            i = text.index("*/", i) + 2; continue
        span = next(((a, b) for a, b in nested if a <= i <= b), None)
        if span:
            i = span[1] + 1; continue
        m = re.compile(r"\bcase\s+([^:;{}]+?)\s*:").match(text, i) if text.startswith("case", i) else None
        if m:
            expr = re.sub(r"(?<=[0-9a-fA-F])[uUlL]+\b", "", m.group(1))
            toks.append(("case", i, m.end(), int(eval(expr, {}, {}))))
            i = m.end(); continue
        m = re.compile(r"\bdefault\s*:").match(text, i) if text.startswith("default", i) else None
        if m:
            toks.append(("default", i, m.end(), None)); i = m.end(); continue
        i += 1
    groups = []
    for k, t in enumerate(toks):
        if groups and not text[groups[-1]["last_end"]:t[1]].strip():
            groups[-1]["toks"].append(t); groups[-1]["last_end"] = t[2]
        else:
            groups.append({"toks": [t], "last_end": t[2]})
    for k, g in enumerate(groups):
        g["start"] = g["toks"][0][1]
        g["body_end"] = groups[k + 1]["toks"][0][1] if k + 1 < len(groups) else c
        g["vals"] = [t[3] for t in g["toks"] if t[0] == "case"]
        g["default"] = any(t[0] == "default" for t in g["toks"])
    return groups


def fix(name):
    f = next(x for x in B["functions"] if x["name"] == name)
    c = f.get("c") or f"src/{f['seg']}/{name}.c"
    first = next(x for x in B["functions"] if (x.get("c") or f"src/{x['seg']}/{x['name']}.c") == c)
    base, own = first["vram"], f["own"][".rodata"]
    path = root / c
    text = path.read_text()
    runs = table_runs(str(root / "build" / Path(c).with_suffix(".o")))
    switches = [(o, cl, parse_groups(text, o, cl)) for o, cl in find_switches(text)]
    used, edits = set(), []

    def consistent(groups, ours_slice):
        vals = [v for g in groups for v in g["vals"]]
        if not vals or max(vals) - min(vals) + 1 != len(ours_slice):
            return None
        v0 = min(vals)
        addr_of, ok = {}, True
        for gi, g in enumerate(groups):
            for v in g["vals"]:
                a = ours_slice[v - v0]
                if addr_of.setdefault(gi, a) != a:
                    ok = False
        unl = {ours_slice[j] for j in range(len(ours_slice)) if j + v0 not in vals}
        if ok and len(unl) <= 1 and len(set(addr_of.values())) == len(addr_of):
            return v0, addr_of, unl
        return None

    for off, ours_all in runs:
        ours_all = [base + x for x in ours_all]
        pos = 0
        while pos < len(ours_all):  # adjacent tables come out of the object as one run: peel them off in source order
            hit = None
            for si, (o, cl, groups) in enumerate(switches):
                if si in used:
                    continue
                vals = [v for g in groups for v in g["vals"]]
                if not vals:
                    continue
                n = max(vals) - min(vals) + 1
                if pos + n > len(ours_all):
                    continue
                r = consistent(groups, ours_all[pos:pos + n])
                if r:
                    hit = (si, n) + r; break
            if not hit:
                return f"{name}: no switch matches the table at +{off + 4 * pos:#x} ({len(ours_all) - pos} entries left in the run)"
            si, n, v0, addr_of, unl = hit
            ours = ours_all[pos:pos + n]
            roff = rom_of(own) + off + 4 * pos
            theirs = list(struct.unpack(f">{n}I", rom[roff:roff + 4 * n]))
            if any(not (base - 0x4000 <= a < base + 0x4000) for a in theirs):
                return f"{name}: ROM table at +{off + 4 * pos:#x} does not look like code addresses (data mapping?)"
            pos += n
            used.add(si)
            groups = switches[si][2]
            by_addr = {a: gi for gi, a in addr_of.items()}
            default_addr = next(iter(unl)) if unl else next((addr_of[gi] for gi, g in enumerate(groups) if g["default"] and gi in addr_of), None)
            new = {gi: [] for gi in range(len(groups))}
            for j, a in enumerate(theirs):
                if a in by_addr and a != default_addr:
                    new[by_addr[a]].append(v0 + j)
                elif a == default_addr:
                    continue
                elif default_addr is None:
                    default_addr = a  # the first address no body claims: where unlabelled values go
                else:
                    return f"{name}: ROM target {a:#x} (index {j}) is not the start of any body"
            for gi, g in enumerate(groups):
                if not new[gi] and not g["default"]:
                    return f"{name}: body {gi} of switch {si} would get no label"
            edits.append((switches[si], new))
    # every replacement is computed on the untouched text and applied once, last first (switches can be nested)
    reps = []
    for (o, cl, groups), new in edits:
        for gi, g in enumerate(groups):
            labels = ([("default:")] if g["default"] else []) + [f"case {v}:" for v in sorted(new[gi])]
            reps.append((g["start"], g["last_end"], " ".join(labels)))  # only the labels: bodies stay as they are
    for s, e, rep in sorted(reps, key=lambda x: -x[0]):
        text = text[:s] + rep + text[e:]
    path.write_text(text)
    return f"{name}: relabelled {len(edits)} switch(es)"


def explain(name):
    """Prints each table (C vs ROM, as offsets from the function) and each switch's groups of case values."""
    f = next(x for x in B["functions"] if x["name"] == name)
    c = f.get("c") or f"src/{f['seg']}/{name}.c"
    first = next(x for x in B["functions"] if (x.get("c") or f"src/{x['seg']}/{x['name']}.c") == c)
    base, own = first["vram"], f["own"][".rodata"]
    text = (root / c).read_text()
    for off, ours in table_runs(str(root / "build" / Path(c).with_suffix(".o"))):
        theirs = struct.unpack(f">{len(ours)}I", rom[rom_of(own) + off:rom_of(own) + off + 4 * len(ours)])
        print(f"table +{off:#x} ({len(ours)} entries)")
        print("  C  :", " ".join(f"{x:x}" for x in ours))
        print("  ROM:", " ".join(f"{x - base:x}" for x in theirs))
    for k, (o, cl) in enumerate(find_switches(text)):
        gs = parse_groups(text, o, cl)
        print(f"switch {k} (line {text[:o].count(chr(10)) + 1}):", "; ".join(
            ("default " if g["default"] else "") + ",".join(map(str, g["vals"])) for g in gs))


def lines(name, offsets):
    """Source line of the code at each offset (hex, from the function's start): compiles with -g (same code) to learn it."""
    import tempfile
    from decompnet import toolchains
    from decompnet.project import compiler_config, compiler_for
    f = next(x for x in B["functions"] if x["name"] == name)
    c = f.get("c") or f"src/{f['seg']}/{name}.c"
    first = next(x for x in B["functions"] if (x.get("c") or f"src/{x['seg']}/{x['name']}.c") == c)
    base = first["vram"]
    body = re.sub(r'^\s*#include "common.h"\s*$', "", (root / c).read_text(), count=1, flags=re.M)
    tmp = Path(tempfile.mkdtemp())
    (tmp / "u.c").write_text((root / "include" / "common.h").read_text() + "\n#line 1 \"u.c\"\n" + body)
    cfg = compiler_config(root, {"compiler": compiler_for(B, f["vram"])})
    cmd = [a.replace("{include}", str(root / "include")).replace("{src}", str(tmp / "u.c")).replace("{obj}", str(tmp / "u.o"))
           for a in cfg.cmd] + ["-g"]
    subprocess.run(cmd, check=True, capture_output=True)
    dis = subprocess.run([OD, "-dl", str(tmp / "u.o")], capture_output=True, text=True).stdout
    at, cur = {}, None
    for l in dis.splitlines():
        m = re.search(r"u\.c:(\d+)\s*$", l)
        if m:
            cur = int(m.group(1)); continue
        m = re.match(r"\s*([0-9a-f]+):\t", l)
        if m and cur is not None:
            at.setdefault(int(m.group(1), 16), cur)
    for o in offsets:
        x = int(o, 16)
        before = max((a for a in at if a <= x), default=None)
        print(f"  +{x:#x}: " + (f"line {at[x]}" if x in at else f"inside line {at[before]} (code from +{before:#x})" if before is not None else "?"))


if __name__ == "__main__":
    if sys.argv[1] == "--lines":
        lines(sys.argv[2], sys.argv[3:])
    elif sys.argv[1] == "--explain":
        for n in sys.argv[2:]:
            print("==", n); explain(n)
    else:
        for n in sys.argv[1:]:
            try:
                print(fix(n))
            except Exception as e:
                print(f"{n}: failed ({type(e).__name__}: {e})")
