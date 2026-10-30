"""Checks that the .rodata the compiler generates for C functions (jump tables, float/double constants) is what the ROM has.

    cd source
    python3 tools/check_rodata.py          (run after a full build; needs build/src/**/*.o)

build.py places a C function's own .rodata (the "own" entry in build.json) without writing it into the ROM: the ROM's
bytes are used, so a wrong constant or a jump table that sends a case to the wrong body still gives an *identical* ROM.
This script rebuilds the expected bytes from each object (jump-table entries are .text-relative relocations: it adds the
function's address) and looks for them in baserom.z64. A function listed here as NOT FOUND has C whose switch (or
constants) differs from the original even though its code is byte-identical: relabel the cases (the table says which
body each case value must reach) or fix the constant. Trailing alignment padding is ignored."""
import json, re, struct, subprocess
from pathlib import Path

root = Path(__file__).resolve().parent.parent
tc = Path.home() / ".local/share/decompnet/toolchains/binutils-mips"
OD = str(tc / "mips-ps2-decompals-objdump")
B = json.loads((root / "build.json").read_text())
rom = (root / B["image"]).read_bytes()
by_src = {}
for f in B["functions"]:
    c = f.get("c") or f"src/{f['seg']}/{f['name']}.c"
    if (root / c).exists():
        by_src.setdefault(c, []).append(f)
ok, bad = 0, []
for f in B["functions"]:
    if not (f.get("own") or {}).get(".rodata"):
        continue
    c = f.get("c") or f"src/{f['seg']}/{f['name']}.c"
    obj = root / "build" / Path(c).with_suffix(".o")
    base = by_src[c][0]["vram"]
    dump = subprocess.run([OD, "-s", "-j", ".rodata", str(obj)], capture_output=True, text=True).stdout
    data = bytearray()
    for line in dump.splitlines():
        m = re.match(r"\s+([0-9a-f]+) ((?:[0-9a-f]{1,8} ?){1,4})", line)
        if m:
            raw = bytes.fromhex(m.group(2).replace(" ", ""))
            data[int(m.group(1), 16):int(m.group(1), 16) + len(raw)] = raw
    relocs = subprocess.run([OD, "-r", "-j", ".rodata", str(obj)], capture_output=True, text=True).stdout
    skip = False
    for line in relocs.splitlines():
        m = re.match(r"([0-9a-f]+) (R_MIPS_\w+)\s+(\S+)", line)
        if m:
            off = int(m.group(1), 16)
            if m.group(2) == "R_MIPS_32" and m.group(3) == ".text":
                data[off:off + 4] = struct.pack(">I", (base + struct.unpack(">I", bytes(data[off:off + 4]))[0]) & 0xFFFFFFFF)
            else:
                skip = True
    core = bytes(data).rstrip(b"\0")
    if skip or not core:
        continue
    if core in rom:
        ok += 1
    else:
        bad.append((f["name"], len(data)))
print(f"{ok} functions' .rodata found in the ROM, {len(bad)} not found")
for name, size in bad:
    print(f"  NOT FOUND: {name} ({size} bytes)")
