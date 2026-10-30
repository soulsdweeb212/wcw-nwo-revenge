"""Strips the noise out of a permuter result that scores 0.

    cd source
    ~/.local/share/uv/tools/decompnet/bin/python tools/reduce_match.py FUNC MATCH.c OUT.c

decomp-permuter's output compiles to the right bytes but is full of dummy locals, `if (1)` wrappers and `volatile`s. This
deletes lines and drops `volatile`, one piece at a time (in shrinking chunks), keeping a change only when the function still
scores 0 against the ROM bytes. The result is smaller and usually readable, but it is still compiler-driven code: read it, and
rename and tidy by hand, before keeping it. Needs a full build first? No: it only compiles."""
import re, sys, subprocess, json, difflib, tempfile
from pathlib import Path
from decompnet.compiler import compile_source
from decompnet.project import compiler_config, compiler_for
from decompnet import toolchains

root = Path(__file__).resolve().parent.parent
B = json.loads((root / "build.json").read_text())
name, src, out = sys.argv[1], Path(sys.argv[2]), Path(sys.argv[3])
fn = next(f for f in B["functions"] if f["name"] == name)
size = int(re.search(r"nonmatching \S+, (0x[0-9A-Fa-f]+)", (root / fn["asm"]).read_text()).group(1), 16)
cfg = compiler_config(root, {"compiler": compiler_for(B, fn["vram"])})
header = (root / "include" / "common.h").read_text()
OD = str(toolchains.binary("binutils-mips").parent / "mips-ps2-decompals-objdump")
rom = (root / B["image"]).read_bytes()[fn["rom"]:fn["rom"] + size]
tmp = Path(tempfile.mkdtemp())
(tmp / "r.bin").write_bytes(rom)


def norm(lines):
    o = []
    for l in lines:
        l = re.sub(r"^[0-9a-f]+:\s*", "", l.strip())
        m = re.match(r"(\S+)\s*(.*)", l)
        if not m: continue
        op, a = m.group(1), re.sub(r"\s*<[^>]*>", "", m.group(2))
        if op in ("lui", "jal", "j"): a = re.sub(r"0x[0-9a-f]+|\b[0-9a-f]+$", "", a)
        if op in ("b", "beq", "bne", "bnez", "beqz", "beql", "bnel", "beqzl", "bnezl", "bgez", "bgtz", "blez", "bltz", "bgezl", "bgtzl", "blezl", "bltzl", "bc1t", "bc1f", "bc1tl", "bc1fl"):
            a = re.sub(r",?\s*(0x)?[0-9a-f]+\s*$", "", a)
        if op in ("lwc1", "swc1", "lw", "sw", "lb", "lbu", "lh", "lhu", "ldc1", "sdc1", "lwl", "lwr", "swl", "swr", "sb", "sh"):
            a = re.sub(r"(-?\d+)\((?!sp)(\w+)\)", r"#(\2)", a)
        if op == "addiu" and not re.search(r"\bsp\b", a.split(",")[1] if "," in a else ""):
            a = re.sub(r",\s*-?\d+$", ",#", a)
        o.append(op + " " + a)
    return o


def dis(args, binary=False):
    t = subprocess.run([OD] + args, capture_output=True, text=True).stdout
    return [m.group(1) + ":\t" + m.group(2) for l in t.splitlines() if (m := re.match(r"\s+([0-9a-f]+):\t[0-9a-f ]+\t(.*)", l))]


def strip_pad(l):
    l = list(l)
    while l and l[-1].strip() == "nop":
        l.pop()
    return l


ORIG = strip_pad(norm(dis(["-D", "-b", "binary", "-m", "mips:4000", "-EB", str(tmp / "r.bin")])))
n = [0]


def score(text):
    m = re.match(r'\s*#include "([^"]+)"\s*\n', text)
    body = text[m.end():] if m else text
    try:
        res = compile_source(cfg, header, body, trusted=True)
    except Exception:
        return None
    if not res.ok: return None
    n[0] += 1
    p = tmp / "o.o"; p.write_bytes(res.obj)
    ours = strip_pad(norm(dis(["-d", str(p)])))
    sm = difflib.SequenceMatcher(None, ORIG, ours, autojunk=False)
    return sum(max(i2 - i1, j2 - j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != "equal")


lines = src.read_text().split("\n")
assert score("\n".join(lines)) == 0, "the input does not score 0"
text = "\n".join(lines)
text = re.sub(r"\bvolatile\s+", "", text)
if score(text) != 0:
    text = "\n".join(lines)
lines = text.split("\n")
chunk = max(1, len(lines) // 2)
while chunk >= 1:
    i, changed = 0, False
    while i < len(lines):
        trial = lines[:i] + lines[i + chunk:]
        if score("\n".join(trial)) == 0:
            lines, changed = trial, True
        else:
            i += chunk
    if not changed or chunk == 1:
        chunk //= 2
    print(f"chunk done, {len(lines)} lines left, {n[0]} compiles", flush=True)
out.write_text("\n".join(lines) + "\n")
print(f"{name}: reduced to {len(lines)} lines -> {out}")
