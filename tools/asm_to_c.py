"""Wraps functions' splat assembly in a top-level asm() block so they build as C objects with identical bytes.

    cd source
    python3 tools/asm_to_c.py FUNC [FUNC...]

Writes src/<segment>/FUNC.c and adds the "c" key to the function's build.json entry. Meant for hand-written libultra and
CP0 routines that C cannot express. Run build.py afterwards: it must still say "identical"."""
import json, re, sys
from pathlib import Path

BRANCH = {"b", "beq", "bne", "beqz", "bnez", "blez", "bgtz", "bltz", "bgez", "beql", "bnel", "beqzl", "bnezl", "bc1t", "bc1f", "bc1tl", "bc1fl", "bal"}
root = Path(__file__).resolve().parent.parent
bj = root / "build.json"
text = bj.read_text()
B = json.loads(text)
for name in sys.argv[1:]:
    f = next(x for x in B["functions"] if x["name"] == name)
    out = []
    lines = (root / f["asm"]).read_text().splitlines()
    local = set(re.findall(r"^\s*(\.L\w+):", "\n".join(lines), re.M))
    for line in lines:
        s = line.strip()
        if not s or s.startswith(("nonmatching", ".size", "endlabel", "enddlabel")):
            continue
        m = re.match(r"glabel (\S+)", s)
        if m:
            out += [f".globl {m.group(1)}", f".ent {m.group(1)}", f"{m.group(1)}:"]
            continue
        w = re.match(r"/\* \w+ \w+ ([0-9A-F]{8}) \*/\s*(\w+)\s+.*?(\S+)\s*(/\*.*)?$", s)
        if w and w.group(2) in BRANCH and w.group(3) not in local:
            out.append(f".word 0x{w.group(1)} /* {w.group(2)} {w.group(3)}: target outside this function */")
            continue
        s = re.sub(r"^/\*.*?\*/\s*", "", s)
        s = re.sub(r"\s+", " ", s)
        out.append(s)
    out.append(f".end {name}")
    body = "\n".join(f'"{l}\\n"' for l in [".set noreorder", ".set noat"] + out + [".set at", ".set reorder"])
    path = root / "src" / f["seg"] / f"{name}.c"
    path.write_text(f"/* Hand-written in the original; kept as top-level asm so the bytes match exactly. */\nasm(\n{body}\n);\n")
    f["c"] = f"src/{f['seg']}/{name}.c"
    print("wrote", path.relative_to(root))
# edit the text in place so build.json keeps its layout
for name in sys.argv[1:]:
    c = next(x for x in B["functions"] if x["name"] == name)["c"]
    text = re.sub(r'("name": "%s",.*?"asm": "[^"]+")(,\s*"c": "[^"]+")?' % re.escape(name),
                  lambda m: m.group(1) + ',\n   "c": "%s"' % c, text, count=1, flags=re.S)
bj.write_text(text)
