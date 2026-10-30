"""Rewrites a function's asm file after its real end has been found past a segment boundary.

    cd source
    ~/.local/share/uv/tools/decompnet/bin/python tools/extend_function.py FUNC SIZE

splat stopped some functions at a segment end, leaving the rest in a raw blob (see nonmatching/README.md). This disassembles
FUNC from the ROM for SIZE bytes in the same format splat writes, naming call and jump-table targets from symbol_addrs.txt and
pairing %hi/%lo only where the symbol is known. Instructions it can't express exactly are written as .word, so the bytes never
change. It writes only that function's .s; moving the segment end in build.json and splat.yaml is a separate step."""
import json, re, struct, sys
from pathlib import Path

import rabbitizer

ROOT = Path(__file__).resolve().parent.parent
FUNC, SIZE = sys.argv[1], int(sys.argv[2], 0)
build = json.loads((ROOT / "build.json").read_text())
fn = next(f for f in build["functions"] if f["name"] == FUNC)
rom = (ROOT / build["image"]).read_bytes()
names = {}
for line in (ROOT / "symbol_addrs.txt").read_text().splitlines():
    m = re.match(r"\s*(\S+)\s*=\s*(0x[0-9A-Fa-f]+);", line)
    if m:
        names[int(m[2], 16)] = m[1]

words = [struct.unpack(">I", rom[fn["rom"] + i:fn["rom"] + i + 4])[0] for i in range(0, SIZE, 4)]
insns = [rabbitizer.Instruction(w, vram=fn["vram"] + i * 4) for i, w in enumerate(words)]
end = fn["vram"] + SIZE
labels = set()


def target_of(insn):
    if insn.uniqueId == rabbitizer.InstrId.cpu_j:
        return insn.getInstrIndexAsVram()
    return insn.getBranchVramGeneric() if insn.isBranch() else None


for insn in insns:
    target = target_of(insn)
    if target is not None and fn["vram"] <= target < end:
        labels.add(target)

out = [f"nonmatching {FUNC}, 0x{SIZE:X}", "", f"glabel {FUNC}"]
for i, (word, insn) in enumerate(zip(words, insns)):
    vram = fn["vram"] + i * 4
    if vram in labels:
        out.append(f"  .L{vram:08X}:")
    text = insn.disassemble(extraLJust=10)
    target = target_of(insn)
    if target is not None:
        if target in labels:
            text = re.sub(r"(\. \+ 4 \+ \(.*\)|\S+)$", f".L{target:08X}", text)
        else:
            text = f".word      0x{word:08X}"
    elif insn.uniqueId == rabbitizer.InstrId.cpu_jal:
        text = f".word      0x{word:08X}"   # /* jal target */ kept as a comment below
        text += f"  /* jal {names.get(insn.getInstrIndexAsVram(), hex(insn.getInstrIndexAsVram()))} */"
    prefix = " " if i and (insns[i - 1].hasDelaySlot()) else ""
    out.append(f"    /* {fn['rom'] + i * 4:X} {vram:08X} {word:08X} */  {prefix}{text}")
out += [f"endlabel {FUNC}", ""]
(ROOT / fn["asm"]).write_text("\n".join(out))
print(f"{FUNC}: {len(words)} instructions, {len(labels)} labels")
