"""Writes port/game_vars.tsv: where the PC port puts each game variable that the port's game files use, and how it
fills the variable from the user's ROM. Turnbuckle Dive turns the file into C when it configures (its
tools/game_vars.py), so the game files link with real data and the repository holds none of the game's bytes.

    cd source
    ~/.local/share/uv/tools/decompnet/bin/python tools/port_data.py           writes port/game_vars.tsv
    ~/.local/share/uv/tools/decompnet/bin/python tools/port_data.py --check   compares instead of writing: exit 1 when
                                                                              the file is out of date

Run it after a change to the game files the port compiles, to their declarations of game variables, or to the PC
types in include/ (port_decls.h, common.h), and commit the new port/game_vars.tsv with the change. It needs pyelftools,
which decompdecomp's Python has (the same Python as build.py), and gcc ($CC to choose another; clang will not do,
because it leaves extern declarations out of the debug information).

How it works:
1. The files: tools/port_filelist.py's list for the developer program, plus VIEWER_FILES below.
2. It compiles each of them for the PC (tools/port_check.py's PC_FLAGS, which have -g) into a temporary folder, and
   reads the debug information of each object: every game variable a file declares with extern, with the file's type
   for it. The names the files use and no file defines are the game variables (functions aside).
3. Each variable's N64 address comes from build.json (its symbols, or the address in a D_XXXXXXXX name). The address
   says which N64 section holds it (SECTIONS below), and the next variable's address says how many bytes it has: its
   extent.
4. Each variable gets one of two kinds of storage on PC:
   - "block": its N64 section becomes one block of PC memory, and the variable sits in it at its N64 offset. Every
     variable whose type holds no address goes there. Its type is laid out the same on the N64 and the PC then, so code
     that reaches one variable through another's address (a label inside a record, two arrays read as one) finds the
     same bytes as on the N64.
   - "own": a variable whose type holds an address (a pointer) is bigger on PC, so it gets its own storage, as many
     bytes as its PC type. Code reaches it only by its own name (the decompilation's docs/port.md, "Shared records on
     PC").
5. For each variable in a section that the ROM fills (main's data, overlay 2's data), the swap pattern: which bytes are
   16-, 32- or 64-bit values, which the port turns from the N64's byte order into the PC's after copying the section
   from the ROM. The files' types say it. A type smaller than the variable's extent repeats over the extent, which is
   how an array declared as one value is read.

Each step checks what it relies on and stops with a message when a file breaks it: two files that read the same bytes
at different widths, a bit-field, a variable without an address or outside every section, a type bigger on the N64
than its extent.

The output, one line per variable, tab-separated, sorted by address:
    name  address  section  storage  bytes  swap
- bytes: for "block" the extent; for "own" the PC size.
- swap ("block" in a section the ROM fills, else "-"): "P:o.w,o.w..." swaps a w-byte value at each offset o, again
  every P bytes; "P:" swaps nothing (bytes only).
Address-holding variables of the sections the ROM fills ("own" there) are listed with "rom" in swap: their addresses
must become PC addresses, which a step of its own will do. Other storage: "alias" (a second name at the same address;
bytes is the first name), "port" (outside the sections: the port provides it) and "function" (an old name of a
function that some files still call; bytes is the function's name, and the port's linker gives it that second name).
"""
from __future__ import annotations

import argparse
import concurrent.futures
import json
import os
import re
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
from port_check import PC_FLAGS  # noqa: E402  the port's flags for game files

try:
    from elftools.elf.elffile import ELFFile
except ImportError:
    sys.exit("port_data.py needs pyelftools: run it with decompdecomp's Python, "
             "~/.local/share/uv/tools/decompnet/bin/python tools/port_data.py")

OUTPUT = ROOT / "port" / "game_vars.tsv"

# The asset viewer's overlay-1 files, which Turnbuckle Dive compiles besides the developer program's (its td_game).
VIEWER_FILES = ["src/code_80090000/func_80096A6C.c", "src/code_80090000/func_80096D8C.c"]

# The N64 sections that hold game variables: name, first address, end address, ROM offset of the first byte (None:
# zeroed, not loaded). From build.json's segments (main's data piece 2CA30, its BSS; overlay 2's data D5FB0) and the
# overlay table at 0x80036E30 (overlay 1's data, overlay 2's BSS). Main's BSS runs 0xA0 bytes past its end: the
# segment-1 buffer, which func_80001260 finds at D_8007FC4F's address rounded down to 16 (docs/port.md).
SECTIONS = [
    ("main.data", 0x8002BE30, 0x8003BAD0, 0x2CA30),
    ("main.bss",  0x8003BAD0, 0x8007FCE0, None),
    ("ovl1.data", 0x800C5AD0, 0x800D6D30, 0x72240),
    ("ovl2.data", 0x800E2B10, 0x800E77B0, 0xD5FB0),
    ("ovl2.bss",  0x800E77B0, 0x800FAFA0, None),
]


class Fail(Exception):
    pass


# ---- 1-2. The files and their declarations --------------------------------------------------------------------------

def file_list() -> list[str]:
    r = subprocess.run([sys.executable, "-B", str(ROOT / "tools" / "port_filelist.py"), "--set", "match"],
                       cwd=ROOT, capture_output=True, text=True)
    if r.returncode != 0:
        raise Fail("tools/port_filelist.py could not list the files:\n" + r.stderr.strip())
    return sorted(set(r.stdout.split()) | set(VIEWER_FILES))


def compile_one(cc: str, src: str, out: Path) -> str | None:
    obj = out / (src.replace("/", "@") + ".o")  # the object's name gives back its file
    r = subprocess.run([cc, *PC_FLAGS, "-O0", "-c", src, "-o", str(obj)], cwd=ROOT, capture_output=True, text=True)
    return None if r.returncode == 0 else f"{src}: {cc} failed:\n{r.stderr.strip()}"


def ref(d):
    return d.get_DIE_from_attribute("DW_AT_type") if "DW_AT_type" in d.attributes else None


def strip(d):
    while d is not None and d.tag in ("DW_TAG_typedef", "DW_TAG_const_type", "DW_TAG_volatile_type"):
        d = ref(d)
    return d


def dims(d):
    out = []
    for c in d.iter_children():
        if c.tag == "DW_TAG_subrange_type":
            a = c.attributes
            out.append(a["DW_AT_count"].value if "DW_AT_count" in a
                       else a["DW_AT_upper_bound"].value + 1 if "DW_AT_upper_bound" in a else None)
    return out


class Layout:
    """A type's scalars on one side: size, alignment and the (offset, width, kind) of each scalar, kind "i" (integer
    or float), "p" (an address) or "bits" (a bit-field). ptr is the size of an address: 8 on PC, 4 on the N64."""

    def __init__(self, ptr: int):
        self.ptr = ptr

    def of(self, d, name: str):
        """(size, align, leaves) of the type DIE d, or size None for an incomplete type (an open array's elements are
        given by of_element)."""
        d = strip(d)
        if d is None:
            raise Fail(f"{name}: a void variable")
        t = d.tag
        a = d.attributes
        if t in ("DW_TAG_base_type", "DW_TAG_enumeration_type"):
            s = a["DW_AT_byte_size"].value
            return s, s, [(0, s, "i")]
        if t == "DW_TAG_pointer_type":
            return self.ptr, self.ptr, [(0, self.ptr, "p")]
        if t in ("DW_TAG_structure_type", "DW_TAG_union_type"):
            if "DW_AT_declaration" in a:
                return None, 1, []
            union = t == "DW_TAG_union_type"
            off = size = 0
            align = 1
            leaves = []
            for c in d.iter_children():
                if c.tag != "DW_TAG_member":
                    continue
                if "DW_AT_bit_size" in c.attributes:
                    leaves.append((0, 0, "bits"))
                    continue
                ms, ma, ml = self.of(ref(c), name)
                if ms is None:  # a flexible array member
                    ms = 0
                if not union:
                    off = (off + ma - 1) // ma * ma
                leaves += [(off + o, w, k) for o, w, k in ml]
                align = max(align, ma)
                size = max(size, off + ms) if union else off + ms
                if not union:
                    off += ms
            size = (size + align - 1) // align * align
            return size, align, leaves
        if t == "DW_TAG_array_type":
            n = 1
            for x in dims(d):
                if x is None:
                    return None, 1, []
                n *= x
            es, ea, el = self.of(ref(d), name)
            if es is None:
                raise Fail(f"{name}: an array of an incomplete type")
            leaves = [(k * es + o, w, kd) for k in range(n) for o, w, kd in el] if n * len(el) <= 1 << 20 else None
            if leaves is None:
                raise Fail(f"{name}: too many scalars")
            return n * es, ea, leaves
        if t == "DW_TAG_subroutine_type":
            raise Fail(f"{name}: a function type")
        raise Fail(f"{name}: a type this tool does not know ({t})")

    def element(self, d, name: str):
        """For an open array (T x[]): (size, align, leaves) of one element; else None."""
        d = strip(d)
        if d is not None and d.tag == "DW_TAG_array_type" and dims(d) and dims(d)[0] is None:
            sub = dims(d)[1:]
            es, ea, el = self.of(ref(d), name)
            n = 1
            for x in sub:
                n *= x
            return n * es, ea, [(k * es + o, w, kd) for k in range(n) for o, w, kd in el]
        return None


def read_object(path: Path):
    """The extern variables an object declares, as {name: (PC view, N64 view)}, each view (size, element, leaves,
    open): for an open array size is None and element is one element's size. Also the names it defines, and the names
    it uses without defining them."""
    pc, n64 = Layout(8), Layout(4)
    views, defined, used = {}, set(), set()
    with open(path, "rb") as f:
        elf = ELFFile(f)
        for s in elf.get_section_by_name(".symtab").iter_symbols():
            if s["st_info"]["bind"] in ("STB_GLOBAL", "STB_WEAK"):
                (used if s["st_shndx"] == "SHN_UNDEF" else defined).add(s.name)
        for cu in elf.get_dwarf_info().iter_CUs():
            for d in cu.get_top_DIE().iter_children():
                a = d.attributes
                if d.tag != "DW_TAG_variable" or "DW_AT_declaration" not in a or "DW_AT_name" not in a:
                    continue
                name = a["DW_AT_name"].value.decode()
                ty = ref(d)
                both = []
                for lay in (pc, n64):
                    el = lay.element(ty, name)
                    if el is not None:
                        both.append((None, el[0], el[2], True))
                    else:
                        s, _, lv = lay.of(ty, name)
                        both.append((s, s, lv, False))
                views[name] = tuple(both)
    return views, defined, used


# ---- 3. Addresses and sections ----------------------------------------------------------------------------------------

def addresses() -> dict[str, int]:
    """Every name's N64 address: build.json's symbols, its functions (rspbootTextStart, the RSP's boot code, is data
    read as an array), and the labels of the data that splat extracted (asm/data/*.s: "dlabel NAME" and, on the next
    line, a comment that gives the address). A D_XXXXXXXX name not found there is at address XXXXXXXX."""
    b = json.loads((ROOT / "build.json").read_text(encoding="utf-8"))
    out = {f["name"]: f["vram"] for f in b["functions"] if "vram" in f}
    for path in sorted((ROOT / "asm" / "data").glob("*.s")):
        lines = path.read_text(encoding="utf-8").splitlines()
        for i, line in enumerate(lines[:-1]):
            m = re.match(r"\s*dlabel (\S+)", line)
            n = re.match(r"\s*/\* [0-9A-F]+ ([0-9A-F]{8}) ", lines[i + 1])
            if m and n:
                out[m.group(1)] = int(n.group(1), 16)
    out.update(b["symbols"])
    return out


def section_of(a: int):
    for s in SECTIONS:
        if s[1] <= a < s[2]:
            return s
    return None


# ---- 4-5. Storage and swap patterns ---------------------------------------------------------------------------------

def section_widths(sec, rows, views) -> dict[int, tuple[int, int, str]]:
    """The width of every byte of a section that the ROM fills, from the block variables' types: byte offset ->
    (offset of the value it is part of, its width, the file and variable that say so). Each file's type for a variable
    covers the variable's bytes (a record reached through its inner labels covers theirs too); an open array, or a type
    smaller than the extent, repeats its element over the extent. Two readings of one byte at different widths stop the
    tool."""
    width: dict[int, tuple[int, int, str]] = {}
    for name, a, s, extent, storage in rows:
        if s is not sec or storage != "block":
            continue
        for src, (pcv, _) in views[name]:
            size, elem, leaves, is_open = pcv
            if any(k == "bits" for _, _, k in leaves):
                raise Fail(f"{name}: {src} reads it through a bit-field, whose layout is the compiler's choice")
            if not elem:
                continue
            reps = max(1, -(-extent // elem)) if (is_open or size < extent) else 1
            base0 = a - sec[1]
            for k in range(reps):
                for o, w, _k in leaves:
                    at = base0 + k * elem + o
                    if k and at + w > base0 + extent:
                        break
                    for b in range(at, at + w):
                        old = width.get(b)
                        if old is not None and old[:2] != (at, w):
                            raise Fail(f"{name}: {src} reads {sec[1] + b:#x} as part of a {w}-byte value at "
                                       f"{sec[1] + at:#x}; {old[2]} reads it as part of a {old[1]}-byte value at "
                                       f"{sec[1] + old[0]:#x}")
                        width[b] = (at, w, f"{src} ({name})")
    return width


def swap_pattern(start: int, extent: int, width) -> str:
    """The swaps of one variable's extent, written as compactly as they repeat (see the module's description)."""
    vals = sorted({(at - start, w) for b, (at, w, _) in width.items() if start <= b < start + extent and w > 1})
    for p in range(1, extent + 1):
        if extent % p and p != extent:
            continue
        one = [(o, w) for o, w in vals if o < p]
        if all(o + w <= p for o, w in one) and set(vals) == {(k + o, w) for k in range(0, extent, p) for o, w in one
                                                             if k + o + w <= extent}:
            return f"{p:x}:" + ",".join(f"{o:x}.{w}" for o, w in one)
    return f"{extent:x}:" + ",".join(f"{o:x}.{w}" for o, w in vals)


def build_map(cc: str, jobs: int, out: Path) -> list[str]:
    files = file_list()
    errors = []
    with concurrent.futures.ThreadPoolExecutor(jobs) as ex:
        for e in ex.map(lambda f: compile_one(cc, f, out), files):
            if e:
                errors.append(e)
    if errors:
        raise Fail("\n\n".join(errors))
    objs = sorted(out.glob("*.o"))
    with concurrent.futures.ProcessPoolExecutor(jobs) as ex:
        results = list(ex.map(read_object, objs))
    views: dict[str, list] = {}
    defined: set[str] = set()
    used: set[str] = set()
    for obj, (v, d, u) in zip(objs, results):
        src = obj.name[:-2].replace("@", "/")
        for name, both in v.items():
            views.setdefault(name, []).append((src, both))
        defined |= d
        used |= u
    names = sorted(n for n in views if n not in defined)

    syms = addresses()
    # Old names of functions: build.json keeps a renamed function's first name as a symbol at its address, and some
    # files still call it by that name (tryBeginBlockReaction was func_800E2400). The PC link needs the same second name.
    functions = {f["vram"]: f["name"] for f in json.loads((ROOT / "build.json").read_text(encoding="utf-8"))["functions"]
                 if "vram" in f and f["name"] in defined}
    # Only names of the game's own form: build.json also puts sqrtf at nw2Sqrtf's address, and on PC sqrtf is the C
    # library's (nw2Sqrtf calls it), so that second name would replace it in the whole program.
    old_names = sorted((n, functions[syms[n]]) for n in used - defined - set(views)
                       if re.fullmatch(r"(func|D)_[0-9A-F]{8}", n)
                       and n in syms and syms[n] in functions and functions[syms[n]] != n)
    rows, problems = [], []
    for n in names:
        a = syms.get(n)
        if a is None and re.fullmatch(r"D_[0-9A-F]{8}", n):
            a = int(n[2:], 16)
        if a is None:
            problems.append(f"{n}: no address in build.json")
            continue
        holds = any(k == "p" for _, (pcv, _) in views[n] for _, _, k in pcv[2])
        sec = section_of(a)
        rows.append([n, a, sec, None, "port" if sec is None else "own" if holds else "block"])
    if problems:
        raise Fail("\n".join(problems))

    # Names that share an address are one variable: the first by name keeps the storage, the others are aliases.
    rows.sort(key=lambda r: (r[1], r[0]))
    first: dict[int, list] = {}
    for r in rows:
        if r[1] in first:
            p = first[r[1]]
            if p[4] != r[4] and "block" in (p[4], r[4]):
                p[4] = "own"  # one name holds an address: the variable does
            r[4] = "=" + p[0]
        else:
            first[r[1]] = r
    # The extent: up to the next address in the section, or its end.
    addrs = sorted(first)
    for i, a in enumerate(addrs):
        r = first[a]
        if r[2] is not None:
            nxt = next((b for b in addrs[i + 1:] if first[b][2] is r[2]), r[2][2])
            r[3] = nxt - a

    widths = {sec[0]: section_widths(sec, rows, views) for sec in SECTIONS if sec[3] is not None}
    lines = []
    for n, a, sec, extent, storage in rows:
        if storage.startswith("="):
            lines.append(f"{n}\t{a:08X}\t{sec[0] if sec else 'other'}\talias\t{storage[1:]}\t-")
            continue
        group = [x for x in rows if x[1] == a]
        vs = [v for x in group for v in views[x[0]]]
        if storage == "port":
            size = max((pcv[0] or 0) for _, (pcv, _) in vs)
            lines.append(f"{n}\t{a:08X}\tother\tport\t{size:#x}\t-")
        elif storage == "block":
            swap = swap_pattern(a - sec[1], extent, widths[sec[0]]) if sec[3] is not None else "-"
            lines.append(f"{n}\t{a:08X}\t{sec[0]}\tblock\t{extent:#x}\t{swap}")
        else:
            # As big as the biggest PC view; an open array gets as many elements as its extent holds on the N64.
            size = 0
            for src, (pcv, n64v) in vs:
                if pcv[0] is not None:
                    size = max(size, pcv[0])
                    if n64v[0] > extent:
                        problems.append(f"{n}: {src}'s type is {n64v[0]:#x} bytes on the N64, more than its extent "
                                        f"{extent:#x}")
                else:
                    size = max(size, extent // n64v[1] * pcv[1])
            lines.append(f"{n}\t{a:08X}\t{sec[0]}\town\t{size:#x}\t{'rom' if sec[3] is not None else '-'}")
    if problems:
        raise Fail("\n".join(problems))
    for n, real in old_names:
        lines.append(f"{n}\t{syms[n]:08X}\tcode\tfunction\t{real}\t-")
    return lines


HEADER = ("# Written by tools/port_data.py, which explains each column; do not edit by hand.\n"
          "# name\taddress\tsection\tstorage\tbytes\tswap\n")


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--check", action="store_true", help="compare with port/game_vars.tsv instead of writing it")
    ap.add_argument("-j", type=int, default=os.cpu_count() or 4, help="files compiled at a time")
    args = ap.parse_args()
    cc = os.environ.get("CC", "gcc")  # clang leaves extern declarations out of the debug information
    try:
        with tempfile.TemporaryDirectory() as tmp:
            lines = build_map(cc, args.j, Path(tmp))
    except Fail as e:
        print(f"port_data.py: {e}", file=sys.stderr)
        return 2
    text = HEADER + "".join(line + "\n" for line in lines)
    if args.check:
        old = OUTPUT.read_text(encoding="utf-8") if OUTPUT.exists() else ""
        if old != text:
            print("port/game_vars.tsv is out of date: run tools/port_data.py and commit it", file=sys.stderr)
            return 1
        print(f"port/game_vars.tsv is up to date ({len(lines)} variables)")
        return 0
    OUTPUT.parent.mkdir(exist_ok=True)
    if not OUTPUT.exists() or OUTPUT.read_text(encoding="utf-8") != text:
        OUTPUT.write_text(text, encoding="utf-8", newline="\n")
    print(f"port/game_vars.tsv: {len(lines)} variables")
    return 0


if __name__ == "__main__":
    sys.exit(main())
