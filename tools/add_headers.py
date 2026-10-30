"""Adds a standard @header comment at the very top of every C file under src/, one block per function in the file.

    cd source
    python3 tools/add_headers.py [--dry-run]

Names, addresses and sizes come from symbol_addrs.txt, each segment's ROM start and vram from splat.yaml, and which
functions a file holds from build.json (several consecutive functions can share one "c" entry). A second run replaces
the existing blocks in place. A file whose function is not in symbol_addrs.txt is skipped with a warning. Only the
header blocks are written: the rest of each file is left byte for byte as it was. --dry-run prints each header that
would change and writes nothing."""
import argparse, json, re, sys
from pathlib import Path

import yaml

ROOT = Path(__file__).resolve().parent.parent
SYMBOL = re.compile(r"\s*(\S+)\s*=\s*(0x[0-9A-Fa-f]+);\s*//.*\bsize:(0x[0-9A-Fa-f]+)")
HEADERS = re.compile(r"\A(?:/\* @header\n(?: \*.*\n)*? \*/\n)+")


def load_symbols():
    symbols = {}
    for line in (ROOT / "symbol_addrs.txt").read_text(encoding="utf-8").splitlines():
        m = SYMBOL.match(line)
        if m and "type:func" in line:
            symbols[m[1]] = (int(m[2], 16), int(m[3], 16))
    return symbols


def load_segments():
    doc = yaml.safe_load((ROOT / "splat.yaml").read_text(encoding="utf-8"))
    return {s["name"]: (s["start"], s["vram"]) for s in doc["segments"] if isinstance(s, dict) and "name" in s and "vram" in s}


def functions_by_file():
    """Source path -> function names in address order. A function with no "c" uses src/<seg>/<name>.c, as build.py does."""
    build = json.loads((ROOT / "build.json").read_text(encoding="utf-8"))
    files = {}
    for fn in sorted(build["functions"], key=lambda f: f["vram"]):
        path = fn.get("c") or f"src/{fn['seg']}/{fn['name']}.c"
        if (ROOT / path).exists():
            files.setdefault(path, []).append(fn["name"])
    return files


def header_for(name, vram, size, segment, seg_rom, seg_vram):
    original = f"func_{vram:08X}"
    title = name if name == original else f"{name}  (originally {original})"
    rom = vram - seg_vram + seg_rom
    asm = f"asm/nonmatchings/{segment}/{name}.s"  # (the .s files carry the current name, not the func_ one)
    text = (f"/* @header\n * {title}\n * VRAM 0x{vram:08X} | ROM 0x{rom:X} | size 0x{size:X}\n"
            f" * asm: {asm}\n */\n")
    return text, asm


def main():
    parser = argparse.ArgumentParser(description="Add @header comments to src/**/*.c")
    parser.add_argument("--dry-run", action="store_true", help="print what would change without writing")
    args = parser.parse_args()

    symbols, segments, files = load_symbols(), load_segments(), functions_by_file()
    counts = {"added": 0, "updated": 0, "unchanged": 0, "skipped": 0}
    warnings, missing_asm = [], []

    for path in sorted(p for p in (ROOT / "src").rglob("*.c")):
        rel = path.relative_to(ROOT).as_posix()
        segment = path.parent.name
        names = files.get(rel, [path.stem])
        unknown = [n for n in names if n not in symbols]
        if unknown or segment not in segments:
            why = f"{', '.join(unknown)} not in symbol_addrs.txt" if unknown else f"segment {segment} not in splat.yaml"
            warnings.append(f"{rel}: {why}; skipped")
            counts["skipped"] += 1
            continue

        seg_rom, seg_vram = segments[segment]
        blocks = []
        for name in names:
            vram, size = symbols[name]
            block, asm = header_for(name, vram, size, segment, seg_rom, seg_vram)
            blocks.append(block)
            if not (ROOT / asm).exists():
                missing_asm.append(asm)
        header = "".join(blocks)

        with open(path, encoding="utf-8", newline="") as f:
            text = f.read()
        old = HEADERS.match(text)
        new = header + (text[old.end():] if old else text)
        if new == text:
            counts["unchanged"] += 1
            continue
        counts["updated" if old else "added"] += 1
        if args.dry_run:
            print(f"--- {rel}: would {'update' if old else 'add'}\n{header}", end="")
        else:
            with open(path, "w", encoding="utf-8", newline="") as f:
                f.write(new)

    verb = "would be " if args.dry_run else ""
    print(", ".join(f"{count} files {verb}{what}" for what, count in counts.items()))
    for warning in warnings:
        print(f"warning: {warning}", file=sys.stderr)
    if missing_asm:
        print(f"warning: {len(missing_asm)} headers name an asm file that does not exist, e.g. {missing_asm[0]}", file=sys.stderr)


if __name__ == "__main__":
    main()
