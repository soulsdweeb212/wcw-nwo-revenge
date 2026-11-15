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
1. The files: tools/port_filelist.py's boot set (all the game runs from its boot: the menus and the match), plus
   VIEWER_FILES below.
2. It compiles each of them for the PC (tools/port_check.py's PC_FLAGS, which have -g) into a temporary folder, and
   reads the debug information of each object: every game variable a file declares with extern, with the file's type
   for it. The names the files use and no file defines are the game variables (functions aside).
3. Each variable's N64 address comes from build.json, a label of asm/data, or the address in a D_XXXXXXXX name. The
   address says which N64 section holds it (SECTIONS below; an address in the overlays' area names a variable of the
   overlay whose files use it), and the next variable's address says how many bytes it has: its extent.
4. Each variable gets one of two kinds of storage on PC:
   - "block": its N64 section becomes one block of PC memory, and the variable sits in it at its N64 offset. Every
     variable whose type holds no address goes there. Its type is laid out the same on the N64 and the PC then, so code
     that reaches one variable through another's address (a label inside a record, two arrays read as one) finds the
     same bytes as on the N64.
   - "own": a variable whose type holds an address (a pointer) is bigger on PC, so it gets its own storage, as many
     bytes as its PC type. Code reaches it only by its own name (the decompilation's docs/port.md, "Shared records on
     PC").
5. The address tables (TABLES, below): the own variables that the ROM starts, each described by hand down to what its
   addresses point at, checked against the ROM's data, and written as fill lines; the arrays and records they reach
   get fill lines of their own, and the data they point at swap ranges.
6. The display lists in the ROM's data (DISPLAY_LISTS, section 7 below): each gets a PC copy of 16-byte commands
   ("gfx" lines), and the vertices they load the widths of a vertex.
7. For each variable in a section that the ROM fills (main's data, the overlays' data), the swap pattern: which bytes
   are 16-, 32- or 64-bit values, which the port turns from the N64's byte order into the PC's after copying the section
   from the ROM. The files' types say it. A type smaller than the variable's extent repeats over it (but not past a
   place an address table points at), which is how an array declared as one value is read.

Each step checks what it relies on and stops with a message when a file breaks it: two files that read the same bytes
at different widths, a bit-field, a variable without an address or outside every section, a type bigger on the N64
than its extent.

The output, one line per variable, tab-separated, sorted by address: name, address, section, storage, bytes and the
swap or fill column. docs/port.md ("The game's variables on PC") explains each storage and column.
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
# zeroed, not loaded), and the overlay they belong to (0: main). From build.json's segments (main's data piece 2CA30,
# its BSS; overlay 2's data D5FB0) and the overlay table at 0x80036E30 (overlay 1's data and BSS, overlay 2's BSS: the
# ranges the loader func_80000700 zeroes). Main's BSS runs 0xA0 bytes past its end: the segment-1 buffer, which
# func_80001260 finds at D_8007FC4F's address rounded down to 16 (docs/port.md).
# The two overlays share addresses: overlay 1's BSS lies where overlay 2's code, data and BSS lie. Only one overlay is
# loaded at a time, and loading one fills or zeroes all of its sections, so on the N64 nothing passes from one to the
# other there. An address in that range is a variable of overlay 1 for overlay 1's files and of overlay 2 for overlay
# 2's (OVERLAY_DIRS); the port keeps all of them in one area of PC memory by N64 address, as the N64 does, and each
# overlay's load fills its own sections.
SECTIONS = [
    ("main.data", 0x8002BE30, 0x8003BAD0, 0x2CA30, 0),
    ("main.bss",  0x8003BAD0, 0x8007FCE0, None, 0),
    ("ovl1.data", 0x800C5AD0, 0x800D6D30, 0x72240, 1),
    ("ovl1.bss",  0x800D6D30, 0x800EA350, None, 1),
    ("ovl2.data", 0x800E2B10, 0x800E77B0, 0xD5FB0, 2),
    ("ovl2.bss",  0x800E77B0, 0x800FAFA0, None, 2),
]
# Where the overlays' memory lies, from overlay 1's code to overlay 2's BSS.
OVERLAY_AREA = (0x80090000, 0x800FAFA0)


class Fail(Exception):
    pass


# ---- 1-2. The files and their declarations --------------------------------------------------------------------------

def file_list(file_set: str) -> list[str]:
    r = subprocess.run([sys.executable, "-B", str(ROOT / "tools" / "port_filelist.py"), "--set", file_set],
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


# Integer types as wide as an address, which the PC code uses where the N64's 32-bit word holds an address (or a
# number or an address, port.h's IdOrAddr, MenuKey and ResKey): 4 bytes on the N64 and 8 on PC, and they count as
# addresses, so a variable that holds one gets storage of its own.
POINTER_WIDE = {"uintptr_t", "intptr_t", "uptr", "IdOrAddr", "MenuKey", "ResKey"}


class Layout:
    """A type's scalars on one side: size, alignment and the (offset, width, kind) of each scalar, kind "i" (integer
    or float), "p" (an address) or "bits" (a bit-field). ptr is the size of an address: 8 on PC, 4 on the N64."""

    def __init__(self, ptr: int):
        self.ptr = ptr

    def of(self, d, name: str):
        """(size, align, leaves) of the type DIE d, or size None for an incomplete type (an open array's elements are
        given by of_element)."""
        n = d
        while n is not None and n.tag in ("DW_TAG_typedef", "DW_TAG_const_type", "DW_TAG_volatile_type"):
            if n.tag == "DW_TAG_typedef" and n.attributes["DW_AT_name"].value.decode() in POINTER_WIDE:
                return self.ptr, self.ptr, [(0, self.ptr, "p")]
            n = ref(n)
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


def section_of(a: int, overlay: int):
    """The section that holds address a for a file of `overlay` (0: main, 1, 2); None outside every section. A main
    file has no section in the overlays' area: which overlay it would mean depends on the moment."""
    for s in SECTIONS:
        if s[1] <= a < s[2] and s[4] in (0, overlay):
            return s
    return None


def rom_section_of(a: int):
    """The section the ROM fills that holds address a, or None. These never overlap (overlay 1's data lies on overlay
    2's code, overlay 2's data on overlay 1's BSS), so the address alone says which."""
    for s in SECTIONS:
        if s[1] <= a < s[2] and s[3] is not None:
            return s
    return None


def file_overlay(src: str, segments: dict[str, int]) -> int:
    """The overlay of a game file (0: main), from its folder: src/<segment>/name.c."""
    return segments.get(Path(src).parts[1], 0) if len(Path(src).parts) > 2 else 0


# ---- 4-5. Storage and swap patterns ---------------------------------------------------------------------------------

def section_widths(sec, rows, views_of, labels) -> dict[int, tuple[int, int, str]]:
    """The width of every byte of a section that the ROM fills, from the block variables' types: byte offset ->
    (offset of the value it is part of, its width, the file and variable that say so). Each file's type for a variable
    covers the variable's bytes (a record reached through its inner labels covers theirs too); an open array, or a type
    smaller than the extent, repeats its element over the extent (which ends at the next variable), but not past a place
    that an address table points at (labels), where other data begins. Two readings of one byte at different widths stop
    the tool."""
    later = sorted(b for b in labels if sec[1] <= b < sec[2])
    width: dict[int, tuple[int, int, str]] = {}
    for name, a, s, extent, storage, ovl in rows:
        if s is not sec or storage != "block":
            continue
        for src, (pcv, _) in views_of(name, ovl):
            size, elem, leaves, is_open = pcv
            if any(k == "bits" for _, _, k in leaves):
                raise Fail(f"{name}: {src} reads it through a bit-field, whose layout is the compiler's choice")
            if not elem:
                continue
            stop = min(next((b for b in later if b > a), sec[2]) - a, extent)
            reps = max(1, -(-stop // elem)) if (is_open or size < stop) else 1
            base0 = a - sec[1]
            for k in range(reps):
                for o, w, _k in leaves:
                    at = base0 + k * elem + o
                    if k and at + w > base0 + stop:
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


def build_map(cc: str, jobs: int, out: Path, file_set: str) -> list[str]:
    files = file_list(file_set)
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
    used: dict[str, set[str]] = {}  # name -> the files that use it without defining it
    for obj, (v, d, u) in zip(objs, results):
        src = obj.name[:-2].replace("@", "/")
        for name, both in v.items():
            views.setdefault(name, []).append((src, both))
        defined |= d
        for name in u:
            used.setdefault(name, set()).add(src)
    names = sorted(n for n in views if n not in defined)

    syms = addresses()
    build = json.loads((ROOT / "build.json").read_text(encoding="utf-8"))
    seg_overlay = {sg["name"]: sg.get("overlay") or 0 for sg in build["segments"]}
    src_overlay = {src: file_overlay(src, seg_overlay) for src in {o.name[:-2].replace("@", "/") for o in objs}}

    def views_of(name: str, overlay: int) -> list:
        """The files' views of a variable that count for a section of `overlay`: those of main's files and that
        overlay's (all of them for a section of main)."""
        return [v for v in views[name] if overlay == 0 or src_overlay[v[0]] in (0, overlay)]

    # Old names of functions: build.json keeps a renamed function's first name as a symbol at its address, and some
    # files still call it by that name (tryBeginBlockReaction was func_800E2400). The PC link needs the same second name.
    # The two overlays' functions share addresses (func_80090000 and func_80090000_ovl2), so the functions are kept by
    # overlay: an address names a function of main or of the overlay of the code that holds it.
    all_functions: dict[int, dict[int, str]] = {0: {}, 1: {}, 2: {}}
    for f in build["functions"]:
        if "vram" in f:
            all_functions[seg_overlay[f["seg"]]].setdefault(f["vram"], f["name"])

    def function_at(a: int, overlay: int, only_defined: bool) -> str | None:
        for o in (overlay, 0):
            n = all_functions[o].get(a)
            if n is not None and (n in defined or not only_defined):
                return n
        return None
    # Only names of the game's own form: build.json also puts sqrtf at nw2Sqrtf's address, and on PC sqrtf is the C
    # library's (nw2Sqrtf calls it), so that second name would replace it in the whole program. The function an old
    # name means is the one at its address in the overlay of the files that use it.
    old: dict[str, set[str]] = {}
    for n, srcs in used.items():
        if n in defined or n in views or not re.fullmatch(r"(func|D)_[0-9A-F]{8}", n) or n not in syms:
            continue
        for src in srcs:
            real = function_at(syms[n], src_overlay[src], True)
            if real is not None and real != n:
                old.setdefault(n, set()).add(real)
    clash = [f"{n}: an old name of {' and of '.join(sorted(r))}, in different overlays" for n, r in old.items()
             if len(r) > 1]
    if clash:
        raise Fail("\n".join(clash))
    old_names = sorted((n, next(iter(r))) for n, r in old.items())
    # One row per variable: [name, address, section, extent, storage, overlay]. A name in the overlays' area gets a row
    # for each overlay whose files use it, in that overlay's section (D_800E6B60 is an s32 of overlay 1's BSS and an
    # f64 of overlay 2's data). A name that only the PC has, for a variable of one overlay whose N64 name the other
    # overlay also uses, ends in _ovl1 or _ovl2 (D_800E6BA0_ovl1).
    rows, problems = [], []
    for n in names:
        m = re.fullmatch(r"(D_[0-9A-F]{8})_ovl([12])", n)
        a = syms.get(m.group(1) if m else n)
        if a is None and re.fullmatch(r"D_[0-9A-F]{8}", m.group(1) if m else n):
            a = int((m.group(1) if m else n)[2:], 16)
        if a is None:
            problems.append(f"{n}: no address in build.json")
            continue
        users = {src_overlay[src] for src, _ in views[n]}
        if OVERLAY_AREA[0] <= a < OVERLAY_AREA[1]:
            if 0 in users:
                problems.append(f"{n}: a main file uses it, but it lies in the overlays' area ({a:#010x}), where what "
                                "it means depends on the overlay loaded")
                continue
            overlays = sorted(users) if not m else [int(m.group(2))]
            if m and users != set(overlays):
                problems.append(f"{n}: a name of overlay {m.group(2)} only, used by another overlay's files")
                continue
        else:
            overlays = [0]
        for ovl in overlays:
            holds = any(k == "p" for _, (pcv, _) in views_of(n, ovl) for _, _, k in pcv[2])
            sec = section_of(a, ovl)
            rows.append([n, a, sec, None, "port" if sec is None else "own" if holds else "block", ovl])
    if problems:
        raise Fail("\n".join(problems))
    # A name with rows in both overlays must be plain bytes in both: the PC has one storage per name.
    for n in {r[0] for r in rows if r[5]}:
        both = [r for r in rows if r[0] == n]
        if len(both) > 1 and any(r[4] != "block" for r in both):
            raise Fail(f"{n}: both overlays use it, and one holds an address there; give one overlay's variable a "
                       f"name of its own on PC ({n}_ovl1 or {n}_ovl2, declared in include/port_decls.h)")

    # Names that share an address in one section are one variable: the first by name keeps the storage, the others are
    # aliases.
    rows.sort(key=lambda r: (r[1], r[0], r[5]))
    first: dict[tuple, list] = {}
    for r in rows:
        key = (r[1], r[2][0] if r[2] else None)
        if key in first:
            p = first[key]
            if p[0] == r[0]:
                continue
            if p[4] != r[4] and "block" in (p[4], r[4]):
                p[4] = "own"  # one name holds an address: the variable does
            r[4] = "=" + p[0]
        else:
            first[key] = r
    # The extent: up to the next address in the section, or its end.
    keys = sorted(first)
    for i, key in enumerate(keys):
        r = first[key]
        if r[2] is not None:
            nxt = next((b[0] for b in keys[i + 1:] if first[b][2] is r[2]), r[2][2])
            r[3] = nxt - key[0]

    # The address tables first: the places their addresses point at begin objects too, so they bound the variables'
    # repeated patterns as labels do.
    tables = Tables(rows, views, syms, function_at, {f["name"] for f in build["functions"]})
    # The boot set holds every file that uses a table of TABLES or a list of DISPLAY_LISTS; a smaller set (the
    # match's) may use none of overlay 1's.
    tables.resolve(every_name=file_set == "boot")
    tables.walk_display_lists(every_name=file_set == "boot")
    # Not every label of the game's data: splat also labels fields inside a table (D_8003A4FE, 2 bytes into the name
    # tables' counts), where the table's pattern must go on.
    labels = ({w for w, _, _ in tables.claims} | set(tables.objects) | set(tables.gfx)
              | {w for w, _, _ in tables.vertices})
    # A display list's bytes get no width from the files' types: the PC draws its PC copy (gfx storage).
    in_gfx = {(g["section"][0], b) for a, g in tables.gfx.items() for b in (a, *g["entries"])}
    wrows = [r for r in rows if r[2] is None or (r[2][0], r[1]) not in in_gfx]
    widths = {sec[0]: section_widths(sec, wrows, views_of, labels) for sec in SECTIONS if sec[3] is not None}
    ranges = tables.add_claims(widths)
    lines = []
    # The data that the tables' addresses point at, where no block variable's extent covers it: swap-only ranges.
    # Ranges that overlap (two addresses into one run of data without a label between them) become one, so that each
    # byte is turned once; the bytes of block variables are left out, as their own lines turn them, except a display
    # list's, whose block line is not written (the PC draws its copy).
    blocks = sorted((r[1], r[1] + r[3], r[2][0]) for r in rows
                    if r[4] == "block" and r[3] and (r[2][0], r[1]) not in in_gfx)
    merged: list[list] = []
    for sec, lo, hi in sorted(ranges, key=lambda x: (x[0][1], x[1])):
        if merged and merged[-1][0] is sec and lo < merged[-1][2]:
            merged[-1][2] = max(merged[-1][2], hi)
        else:
            merged.append([sec, lo, hi])
    for sec, lo, hi in merged:
        pieces = [(lo, hi)]
        for blo, bhi, bsec in blocks:
            if bsec == sec[0]:
                pieces = [(x, y) for a, b in pieces for x, y in ((a, min(b, blo)), (max(a, bhi), b)) if x < y]
        for x, y in pieces:
            lines.append(f"td_data_{x:08X}\t{x:08X}\t{sec[0]}\tdata\t{y - x:#x}\t"
                         f"{swap_pattern(x - sec[1], y - x, widths[sec[0]])}")
    for a, o in tables.objects.items():
        if o["name"].startswith("td_anon_"):
            lines.append(f"{o['name']}\t{a:08X}\t{o['section'][0]}\town\t{o['count'] * o['pcsize']:#x}\t"
                         f"{tables.fill(a)}")
    for a, n in sorted(tables.entries.items()):
        lines.append(f"{n}\t{a:08X}\tcode\tentry\t{n}\t-")
    gfx_names = set()
    for a, g in sorted(tables.gfx.items()):
        lines.append(f"{g['name']}\t{a:08X}\t{g['section'][0]}\tgfx\t{g['count'] * 16:#x}\t{g['count']:x}")
        gfx_names.add((g["section"][0], a))
        for b, n in sorted(g["entries"].items()):
            # an entry point: the PC copy's command of the same number
            lines.append(f"{n}\t{b:08X}\t{g['section'][0]}\tgfxentry\t{g['name']}\t{(b - a) // 8 * 16:x}")
            gfx_names.add((g["section"][0], b))
    for n, a, sec, extent, storage, ovl in rows:
        if sec is not None and (sec[0], a) in gfx_names and not storage.startswith("="):
            continue  # a display list: its gfx line above
        if storage.startswith("="):
            lines.append(f"{n}\t{a:08X}\t{sec[0] if sec else 'other'}\talias\t{storage[1:]}\t-")
            continue
        group = [x for x in rows if x[1] == a and x[2] is sec]
        vs = [v for x in group for v in views_of(x[0], ovl)]
        if storage == "port":
            size = max((pcv[0] or 0) for _, (pcv, _) in vs)
            lines.append(f"{n}\t{a:08X}\tother\tport\t{size:#x}\t-")
        elif storage == "block":
            swap = swap_pattern(a - sec[1], extent, widths[sec[0]]) if sec[3] is not None else "-"
            lines.append(f"{n}\t{a:08X}\t{sec[0]}\tblock\t{extent:#x}\t{swap}")
        elif sec[3] is not None:
            # An address table the N64 starts from the ROM: as TABLES describes it, and at least as big as each file's
            # PC type for it.
            o = tables.objects.get(a)
            if o is None:
                problems.append(f"{n}: holds addresses and the ROM starts it; describe its shape in TABLES")
                continue
            size = o["count"] * o["pcsize"]
            for src, (pcv, _) in vs:
                if pcv[0] is not None and pcv[0] > size:
                    problems.append(f"{n}: {src}'s type is {pcv[0]:#x} bytes on PC, more than TABLES gives it "
                                    f"({size:#x})")
            lines.append(f"{n}\t{a:08X}\t{sec[0]}\town\t{size:#x}\t{tables.fill(a)}")
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
                    if extent < n64v[1]:
                        # A label the files use lies inside the first element (D_800E8234 in D_800E8230's first
                        # menu): the variable would get no storage, and the label would not follow it on PC.
                        inside = sorted(x[0] for x in rows if a < x[1] < a + n64v[1] and x[2] is sec)
                        problems.append(f"{n}: {src} reads it as an array of {n64v[1]:#x}-byte elements, but its "
                                        f"extent is {extent:#x}: a file uses a label inside it ({', '.join(inside)}), "
                                        "which on PC must be a field access")
                    size = max(size, extent // n64v[1] * pcv[1])
            lines.append(f"{n}\t{a:08X}\t{sec[0]}\town\t{size:#x}\t-")
    if problems:
        raise Fail("\n".join(problems))
    for n, real in old_names:
        lines.append(f"{n}\t{syms[n]:08X}\tcode\tfunction\t{real}\t-")
    return sorted(lines, key=lambda line: (line.split("\t")[2] == "code", line.split("\t")[1], line))



# ---- 6. Address tables ------------------------------------------------------------------------------------------------
# The variables that hold addresses and that the N64 starts from the ROM. Each address must become a PC address when the
# port fills them, and the PC layout of each must be known, so each is described here by hand: its shape, down to what
# its addresses point at. The tool checks every description against the ROM's data (see Tables) and every file's PC
# type for the variable, and writes the fill into the map.
#
# A shape is one of:
#   an int 1, 2, 4 or 8      a value of that many bytes;
#   [shape, shape, ...]      a struct of those fields, aligned as C aligns them on each machine;
#   Arr(count, shape)        an array; count AUTO means "as many addresses as the data holds there": in main's data,
#                            the run of words that splat marked as addresses or that are 0 (a list's closing NULL),
#                            up to the next label (an array of single addresses only);
#   Ptr(target)              an address (4 bytes on the N64, 8 on PC) of:
#     Data(w)                data that holds no address, read as w-byte values (1: bytes; also for textures and
#                            palettes, which stay in the N64's byte order); it keeps its N64 offset in its section's
#                            block, and is turned into the PC's byte order as w-byte values up to the next label;
#     Data(w, to_zero=True)  the same, for a list that ends with a 0 value: up to the next label or, where that 0
#                            lies past it, up to and with the 0;
#     a shape                one object of that shape (an Arr for an array of them), which gets storage of its own;
#     FUNC                   a function: the PC function of that N64 address;
#     GFX                    a display list (section 7): the address of its PC copy;
#     VTX                    vertices (section 7), up to the next label: they keep their N64 offset in the block and
#                            are turned into the PC's byte order field by field;
#     IdOr(target)           a word that holds a number (0 or more as an s32: an id; or -1) or the address of target
#                            (negative as an s32), which the code tells apart by the sign: on PC a pointer-wide field
#                            with the number (-1 as all ones), or the PC address (port.h's IdOrAddr);
#     PORT                   a variable the port provides (a framebuffer);
#     UNUSED                 nothing: an entry the game never reads, whose word is not an address (tables that the
#                            game indexes from 1); PC gets NULL there.
# A 0 word is NULL whatever the target.

AUTO = "auto"
FUNC = "func"
GFX = "gfx"
VTX = "vtx"
PORT = "port"
UNUSED = "unused"


class Arr:
    def __init__(self, count, elem):
        self.count, self.elem = count, elem

    def __repr__(self):
        return f"Arr({self.count}, {self.elem!r})"


class Ptr:
    def __init__(self, target):
        self.target = target

    def __repr__(self):
        return f"Ptr({self.target!r})"


class IdOr:
    def __init__(self, target):
        self.target = target

    def __repr__(self):
        return f"IdOr({self.target!r})"


class Data:
    def __init__(self, width, to_zero=False):
        self.width, self.to_zero = width, to_zero

    def __repr__(self):
        return f"Data({self.width}{', to_zero=True' if self.to_zero else ''})"


# A wrestler's name entry (common.h's Nw2NameEntry): id, value, a byte, a word, the addresses of the name, height and
# weight texts, two bytes, a u16 and a word: 0x1C bytes on the N64, 0x28 on PC.
NAME_ENTRY = [2, 1, 1, 4, Ptr(Data(1)), Ptr(Data(1)), Ptr(Data(1)), 1, 1, 2, 4]

# common.h's Nw2MenuDef: an element's description, 0x16 bytes of 16-bit values and bytes (no address).
MENU_DEF = [2, 2, 2, 1, 1, 1, 1, 2, 2, 1, 1, 2, 2, 2]
# The menus' camera paths (D_800D2530; func_800B7F3C, func_800B807C, func_800B7C9C, func_800B7C20): each record
# names six curves (the six values func_800B8368 takes), each the address of its keys and their count, then two
# u16 ids (from, to); a key is an f32 value, an s16 time and an s16. The counts of each record's curves, from the ROM:
MENU_CAM_KEY = [4, 2, 2]
MENU_CAM_COUNTS = ((1, 1, 1, 1, 1, 1), (4, 4, 4, 4, 4, 4), (5, 5, 5, 5, 5, 5), (5, 5, 5, 5, 5, 5),
    (5, 5, 5, 5, 5, 5), (5, 5, 5, 5, 5, 5), (5, 5, 5, 5, 5, 5), (1, 1, 1, 1, 1, 1), (4, 4, 4, 4, 4, 4),
    (4, 4, 4, 4, 4, 4), (1, 1, 1, 1, 1, 1), (1, 1, 1, 1, 1, 1), (1, 1, 1, 1, 1, 1), (1, 1, 1, 1, 1, 1),
    (1, 1, 1, 1, 1, 1), (1, 1, 1, 1, 1, 1), (1, 1, 1, 1, 1, 1), (1, 1, 1, 1, 1, 1), (1, 1, 1, 1, 1, 1),
    (4, 7, 5, 6, 4, 4), (11, 11, 11, 11, 11, 4), (5, 5, 5, 4, 4, 4), (5, 5, 5, 4, 4, 4), (5, 5, 5, 4, 4, 4),
    (5, 5, 5, 4, 4, 4), (5, 5, 5, 4, 4, 4), (5, 5, 5, 4, 4, 4), (5, 5, 5, 4, 4, 4), (5, 5, 5, 4, 4, 4),
    (5, 5, 5, 4, 4, 4), (5, 5, 5, 4, 4, 4), (5, 5, 5, 4, 4, 4), (5, 5, 5, 4, 4, 4), (5, 5, 5, 4, 4, 4),
    (5, 5, 5, 4, 4, 4), (5, 5, 5, 4, 4, 4), (5, 5, 5, 4, 4, 4), (5, 5, 5, 4, 4, 4), (5, 5, 5, 4, 4, 4),
    (5, 5, 5, 4, 4, 4), (5, 5, 5, 4, 4, 4), (5, 5, 5, 4, 4, 4), (5, 5, 5, 4, 4, 4), (5, 5, 5, 4, 4, 4),
    (5, 5, 5, 4, 4, 4), (1, 1, 1, 1, 1, 1), (1, 1, 1, 1, 1, 1), (1, 1, 1, 1, 1, 1), (4, 4, 4, 4, 4, 4),
    (4, 4, 4, 4, 4, 4), (1, 1, 1, 1, 1, 1), (4, 4, 4, 4, 4, 4), (4, 4, 4, 4, 4, 4), (4, 4, 4, 4, 4, 4),
    (1, 1, 1, 1, 1, 1), (4, 10, 8, 9, 10, 4), (1, 1, 1, 1, 1, 1), (4, 4, 4, 4, 4, 4), (1, 1, 1, 1, 1, 1),
    (4, 4, 4, 4, 4, 4), (4, 4, 4, 4, 4, 4), (4, 4, 4, 4, 4, 4), (4, 4, 4, 4, 4, 4), (4, 4, 4, 4, 4, 4),
    (1, 1, 1, 1, 1, 1), (4, 4, 4, 4, 4, 4), (4, 4, 4, 4, 4, 4), (4, 4, 4, 4, 4, 4), (5, 4, 5, 4, 4, 4),
    (1, 1, 1, 1, 1, 1), (4, 4, 4, 4, 4, 4), (4, 4, 4, 4, 4, 4), (4, 4, 4, 4, 4, 4), (4, 4, 4, 4, 4, 4),
    (4, 4, 4, 4, 4, 4), (4, 4, 4, 4, 4, 4), (4, 4, 4, 4, 4, 4), (4, 4, 4, 4, 4, 4), (1, 1, 1, 1, 1, 1),
    (4, 4, 4, 4, 4, 4), (4, 4, 4, 4, 4, 4), (4, 4, 4, 4, 4, 4), (4, 4, 4, 4, 4, 4), (4, 4, 4, 4, 4, 4),
    (4, 4, 4, 4, 4, 4), (4, 4, 4, 4, 4, 4), (4, 4, 4, 4, 4, 4), (4, 4, 4, 4, 4, 4), (4, 4, 4, 4, 4, 4),
    (4, 4, 4, 4, 4, 4), (4, 4, 4, 4, 4, 4), (4, 4, 4, 4, 4, 4), (4, 4, 4, 4, 4, 4), (4, 4, 4, 4, 4, 4),
    (4, 4, 4, 4, 4, 4), (4, 4, 4, 4, 4, 4), (4, 4, 4, 4, 4, 4), (4, 4, 4, 4, 4, 4), (4, 4, 4, 4, 4, 4),
    (4, 4, 4, 4, 4, 4), (4, 4, 4, 4, 4, 4), (4, 4, 4, 4, 4, 4), (1, 1, 1, 1, 1, 1), (9, 9, 9, 4, 9, 4),
    (1, 1, 1, 1, 1, 1))

# The menus' encounter scenes (common.h's Nw2EncScene; func_80093DAC, func_800940D8, func_800945E0, func_80095884):
# 0x34 bytes, with the addresses of the scene's parts (each a list of 16-bit values and byte pairs, turned as 16-bit
# values), its spots, its title pieces (common.h's Nw2EncTitle) and five phase lists of 16-bit values. The counts
# of each scene's parts and title pieces (the closing piece counted), from the ROM; scenes 7 and 8 share their parts.
ENC_TITLE = [2, 1, 1, 2, 2, 2, 2]


def ENC_SCENE(parts, title):
    return [2, 2, 2, 2, Ptr(Arr(parts, Ptr(Data(2)))), Ptr(Data(2)), Ptr(Arr(title, ENC_TITLE)), 2, 2, 2, 2,
            Arr(5, Ptr(Data(2))), 4]


TABLES = {
    # main's data
    "D_8002EEB0": Arr(3, Ptr(PORT)),                                  # the three framebuffers
    "nw2ResourceCacheHead": Ptr(Data(1)),                              # the resource cache's first entry: 0 at start
    "D_80031060": Arr(10, Ptr(Data(2))),                               # sound ids, by group (func_8000E4FC)
    "D_800317F0": Arr(52, Ptr(Data(2))),                               # 52 tables of s16 (func_8000BDD0)
    "D_80031998": Arr(10, Ptr(Data(2))),                               # 10 tables of u16, by bank (func_8000BDD0)
    "D_80032B44": Arr(10, Ptr(Arr(AUTO, Ptr(Arr(AUTO, Ptr(Data(2))))))),  # bank -> index -> list of s16 tables
    "D_800360F0": Arr(5, Ptr(Arr(AUTO, Ptr(Arr(AUTO, Ptr(Data(2))))))),   # the same shape, u16 (func_8000C1B8)
    "D_80036710": Arr(10, Ptr(Arr(AUTO, Ptr(Data(2))))),               # group -> id -> u16 pairs (func_8000B630)
    "D_80036C74": Arr(6, Ptr(Data(2))),                                # s16/u16 arrays that func_80007020 reads
    "D_80036C94": Arr(6, Ptr(Data(2))),
    "D_80036CB4": Arr(6, Ptr(Data(2))),
    "D_80036CCC": Arr(6, Ptr(Data(2))),
    "D_80036CE4": Arr(6, Ptr(Data(2))),
    "D_80038A64": Arr(10, Ptr(Data(2))),                               # resource ids per character group (u16)
    "D_80038AAC": Ptr(Data(1)),                                        # the save buffer (func_800BB2A0): 0 at start
    "D_8003A484": Arr(5, [1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 2, Ptr(Data(1))]),  # the cups (common.h's Nw2Cup)
    "D_8003A4F8": Arr(13, [Ptr(Arr(AUTO, Ptr(NAME_ENTRY))), 2, 2]),   # the 13 name tables: entries, count, id
    "D_8003A594": Ptr(Data(1)),                                        # the name records' buffer: 0 at start
    "D_8003A59C": NAME_ENTRY,                                          # the entry for an unknown id
    # overlay 2's data
    "D_800E2B84": Arr(6, Ptr(Data(1))),                                # s8 tables
    "D_800E2BB4": Arr(6, Ptr(Data(1))),
    "D_800E2BD4": Arr(6, Ptr(Data(1))),
    # s16 tables (func_80096FE8 reads them with lh), indexed from 1. Each list ends with a 0, which the game reads up
    # to: the last list, at 0x800E2CE8, ends with the value 0x2AF and that 0 in the table's own first word (unused as
    # an address), so its values run past D_800E2CF4's label.
    "D_800E2CF4": [Ptr(UNUSED), Arr(10, Ptr(Data(2, to_zero=True)))],
    "D_800E2D58": [Ptr(UNUSED), Arr(10, Ptr(Data(1)))],               # byte tables, indexed from 1
    "D_800E2E80": Arr(6, Ptr(Data(1))),                                # textures for display lists: stay big-endian
    "D_800E2FF0": Arr(146, Ptr(FUNC)),                                 # handlers (func_8009D8D0)
    "D_800E3660": Arr(62, Ptr(FUNC)),                                  # handlers (startEntityAction)
    # overlay 1's data
    # The menus' shapes (func_8009F9A0, func_800A0420): a display list or 0, its vertices, their count and three s16.
    # Entries share vertices (0x800C9EC8 with 4, 5 and 12), and func_800A73AC reads 64 from one, so the vertices of
    # each go up to the next place a label or another entry names.
    "D_800CB7B8": Arr(37, [Ptr(GFX), Ptr(VTX), 2, 2, 2, 2]),
    # The pictures' shapes (func_800936DC, func_80092DE0): a display list, its vertices, their count, a picture index
    # and four bytes. func_80092B20 and func_800927B0 read records 6 to 9, which the N64 reaches by labels inside the
    # table (D_800C6568 ...); on PC they index it.
    "D_800C6508": Arr(12, [Ptr(GFX), Ptr(VTX), 2, 2, 1, 1, 1, 1]),
    "D_800C93E8": Arr(19, Ptr(Data(1))),                               # texts of message ids 0x122 to 0x134
    "D_800C9708": Arr(3, [Ptr(Data(1)), 2, 2, 2, 2]),                 # reaction texts (emitReactionSprite99B68)
    # The credits' lines (func_8009B66C, func_800BCDF4): text, a value, a kind and a delay; the last has no text.
    "D_800D34C8": Arr(152, [Ptr(Data(1)), 2, 1, 1]),
    # The menus' scene records (common.h's Nw2MenuScene; func_800C1370, func_800C15A0, func_800C194C, func_800BF9B8):
    # a kind and a byte, five 16-bit values, then four words that each hold 0, a number or the address of a list of
    # 16-bit values (func_800BF65C's keys). 77: the last has kind 0xFF, and D_800D5744 follows.
    "D_800D4ED8": Arr(77, [1, 1, 2, 2, 2, 2, 2] + [Ptr(IdOr(Data(2)))] * 4),
    "D_800D4E40": Arr(19, [Ptr(Data(2)), 2, 2]),                       # the scenes' camera tracks (Nw2MenuSceneTrack)
    # The scenes' picture sets (common.h's Nw2MenuShot; func_800C0680): four addresses of 16-bit lists, then values.
    "D_800D4930": Arr(27, [Ptr(Data(2))] * 4 + [2] * 6 + [1] * 4),
    "D_800D5990": Arr(16, Ptr(Data(2))),                               # point lists (func_800C2370, func_800C2704)
    "D_800D5DA0": Arr(32, Ptr(Data(2))),
    "D_800C8E84": [ENC_SCENE(n, t) for n, t in ((29, 4), (11, 3), (9, 2), (25, 3), (15, 2), (11, 3), (20, 1), (14, 1),
                                                 (14, 1), (0, 1))],
    # The menus' element lists (common.h's Nw2MenuItems; func_8009F9A0): the address of the menu's n descriptions,
    # then bytes, n at +5. Menus 13 and 14, 16 and 17, 22 and 23 share their descriptions.
    "D_800CC8EC": [[Ptr(Arr(n, MENU_DEF)), 1, 1, 1, 1, 1, 1, 1, 1]
                   for n in (2, 5, 6, 6, 5, 2, 2, 3, 3, 17, 4, 24, 15, 11, 11, 21, 14, 14, 5, 12, 10, 1, 1, 1)],
    # The camera paths: 105 records, then the closing one, whose 0 address the code walks to.
    "D_800D2530": [[Ptr([[Ptr(Arr(n, MENU_CAM_KEY)), 4] for n in ns]), 2, 2] for ns in MENU_CAM_COUNTS]
                  + [[Ptr(UNUSED), 2, 2]],
}


# ---- 7. Display lists in the ROM's data ------------------------------------------------------------------------------
# Overlay 1's data holds display lists ready-made: N64 commands, two big-endian 32-bit words each, which the code hands
# to the graphics chip by their address (a G_DL command, DL_ADDR on PC). The PC draws commands of two 64-bit words
# (port.h's Gfx), so the port builds a PC copy of each list when it loads the section ("gfx" storage): the same
# commands, each word widened, and each address in them turned into the PC address of what it names (the next list,
# the vertices, the texture). DISPLAY_LISTS names the lists that code uses; the lists they call or branch to are
# found by walking them (td_gfx_ and their address when no file names them). The data the commands load gets its
# width: vertices (VTX_FIELDS) and the viewport turn into the PC's byte order, textures and palettes stay as they are
# (LUS reads them in the N64's byte order).
DISPLAY_LISTS = [
    "D_80038D80",  # main's data
    "D_800C5B90", "D_800C5C50", "D_800C5D10", "D_800C5D58", "D_800C5D90", "D_800C5EC0",
    "D_800C9098", "D_800C9538", "D_800C95B8", "D_800C95F0", "D_800C9620", "D_800C9678", "D_800C9C70",
    "D_800D5768",
]

# The commands a list may hold (F3DEX2's numbers): "addr" for those whose second word is an address the port turns
# into a PC address (G_VTX, G_DL, G_SETTIMG, G_MOVEMEM), "plain" for the others, whose words are copied.
GBI_OPS = {op: "addr" for op in (0x01, 0xDE, 0xFD, 0xDC)}
GBI_OPS.update({op: "plain" for op in (
    0x02,                               # G_MODIFYVTX (a field of a loaded vertex)
    0x05, 0x06, 0x07,                   # G_TRI1, G_TRI2, G_QUAD
    0xD7, 0xD8, 0xD9, 0xDB, 0xDF,       # G_TEXTURE, G_POPMTX, G_GEOMETRYMODE, G_MOVEWORD (not a segment), G_ENDDL
    0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9,  # RDPHALF_1, SETOTHERMODE_L/H, TEXRECT(FLIP), the syncs
    0xED, 0xEE, 0xEF, 0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC,
)})

# A vertex (16 bytes): x, y, z, a flag, s and t as 16-bit values, then four bytes of colour or normal.
VTX_FIELDS = [(0, 2), (2, 2), (4, 2), (6, 2), (8, 2), (10, 2), (12, 1), (13, 1), (14, 1), (15, 1)]


def shape_layout(shape, ptr: int):
    """(size, align, fields) of a shape on one machine; fields are (offset, kind, target): kind 1/2/4/8, or "p" with
    the Ptr's target."""
    if isinstance(shape, int):
        return shape, shape, [(0, shape, None)]
    if isinstance(shape, Ptr):
        return ptr, ptr, [(0, "p", shape.target)]
    if isinstance(shape, Arr):
        es, ea, ef = shape_layout(shape.elem, ptr)
        return es * shape.count, ea, [(k * es + o, kd, t) for k in range(shape.count) for o, kd, t in ef]
    off, align, fields = 0, 1, []
    for f in shape:
        fs, fa, ff = shape_layout(f, ptr)
        off = (off + fa - 1) // fa * fa
        fields += [(off + o, kd, t) for o, kd, t in ff]
        off += fs
        align = max(align, fa)
    return (off + align - 1) // align * align, align, fields


class Tables:
    """Resolves TABLES against the ROM: the objects (each table, and each array or record its addresses point at that
    holds addresses itself), the data its addresses point at, and the functions they name. Checks, and stops with a
    message when one fails: in main's data, a word is an address exactly where splat marked it as one (asm/data/*.s);
    in overlay 2's data, which splat did not mark, every address word is 0 or an address the shape allows; an address of
    data or of an object must not land inside another object; a function address must start a function the port
    compiles; two readings of a byte must agree on its width. (splat writes the name tables as 16-bit values, so an
    unmarked word in main's data passes when it is an address in a section the ROM fills.)"""

    def __init__(self, rows, views, syms, function_at, function_names):
        self.rom = (ROOT / "baserom.z64").read_bytes()
        self.rows, self.views, self.function_at = rows, views, function_at
        self.port = {r[1]: r[0] for r in rows if r[4] == "port"}
        # The variables by section and address: overlay 1's and overlay 2's can share an address.
        self.var_at = {(r[2][0], r[1]): r[0] for r in rows if r[2] is not None and not r[4].startswith("=")}
        self.relocs, self.labels = self._read_main_data()
        # A function's start is no label of data: overlay 2's functions lie where overlay 1's data lies.
        self.labels |= {a for n, a in syms.items() if n not in function_names}
        self.objects = {}   # N64 address -> dict(name, section, n64size, pcsize, count, elem, fields)
        self.claims = []    # (N64 address, width, why)
        self.claim_ends = {}  # N64 address -> the end of a Data(w, to_zero=True) list
        self.entries = {}   # N64 address -> function name
        self.gfx = {}       # N64 address -> dict(name, section, count): a display list in the ROM's data (DISPLAY_LISTS)
        self.vertices = []  # (N64 address, count, why): vertices that a display list loads (count None: a table's
                            # VTX, up to the next label)
        self.gfx_todo = []  # (N64 address, name, overlay, why): display lists that a table's GFX addresses name

    def _read_main_data(self):
        relocs, labels = {}, set()
        for path in sorted((ROOT / "asm" / "data").glob("*.s")):
            lines = path.read_text(encoding="utf-8").splitlines()
            for i, line in enumerate(lines):
                m = re.match(r"\s*/\* [0-9A-F]+ ([0-9A-F]{8}) [0-9A-F]{8} \*/ \.word ([A-Za-z_]\w*)", line)
                if m:
                    relocs[int(m.group(1), 16)] = m.group(2)
                m = re.match(r"\s*dlabel (\S+)", line)
                n = re.match(r"\s*/\* [0-9A-F]+ ([0-9A-F]{8}) ", lines[i + 1]) if m and i + 1 < len(lines) else None
                if n:
                    labels.add(int(n.group(1), 16))
        return relocs, labels

    def word(self, a: int, width: int = 4) -> int:
        sec = rom_section_of(a)
        if sec is None or sec[3] is None:
            raise Fail(f"{a:#010x}: not in a section the ROM fills")
        o = sec[3] + a - sec[1]
        return int.from_bytes(self.rom[o:o + width], "big")

    def zero_end(self, a: int, width: int, where: str) -> int:
        """The end of the list of width-byte values at a, after its closing 0."""
        sec = rom_section_of(a)
        while a + width <= sec[2]:
            a += width
            if self.word(a - width, width) == 0:
                return a
        raise Fail(f"{where}: the list has no closing 0 before the end of {sec[0]}")

    def next_label(self, a: int) -> int:
        sec = rom_section_of(a)
        mine = {b for s, b in self.var_at if s == sec[0]}
        later = [b for b in (self.labels | mine | set(self.objects)) if a < b < sec[2]]
        return min(later, default=sec[2])

    def is_main(self, a: int) -> bool:
        return rom_section_of(a)[0] == "main.data"

    def check_address_word(self, a: int, expect: bool, where: str):
        if not self.is_main(a):
            return
        marked = a in self.relocs
        w = self.word(a)
        # splat writes some tables as 16-bit values (the name tables), so an unmarked word is accepted when it is an
        # address in a section the ROM fills.
        if expect and not marked and w != 0 and (section_of(w, 0) is None or section_of(w, 0)[3] is None):
            raise Fail(f"{where}: the shape has an address at {a:#010x}, but the word there ({w:#010x}) is neither "
                       f"marked as one by splat nor an address in a section the ROM fills")
        if not expect and marked:
            raise Fail(f"{where}: splat marked the word at {a:#010x} as the address {self.relocs[a]}, but the shape "
                       f"has a value there")

    def auto_count(self, a: int, where: str) -> int:
        if not self.is_main(a):
            raise Fail(f"{where}: AUTO counts only work in main's data, where splat marked the addresses")
        end = self.next_label(a)
        n = 0
        # Addresses and 0 words (NULL): many lists end with a NULL that the game walks to (func_8000C91C counts the
        # entries of D_80032B44's lists so), so it must be in the PC array too.
        while a + 4 * n < end and (a + 4 * n in self.relocs or self.word(a + 4 * n) == 0):
            n += 1
        if n == 0 or a not in self.relocs:
            raise Fail(f"{where}: no address at {a:#010x}")
        return n

    def add(self, a: int, shape, name: str, where: str, ovl: int):
        """Adds the object at a (in a section of overlay ovl, or of main) and everything its addresses reach, which
        the code of overlay ovl reads: an address names main's memory or that overlay's."""
        if isinstance(shape, Arr) and shape.count == AUTO:
            shape = Arr(self.auto_count(a, where), shape.elem)
        if a in self.objects:
            o = self.objects[a]
            if repr(o["shape"]) != repr(shape):
                raise Fail(f"{where}: {a:#010x} is reached as {shape!r} and as {o['shape']!r}")
            return
        elem = shape.elem if isinstance(shape, Arr) else shape
        count = shape.count if isinstance(shape, Arr) else 1
        n64size, _, n64f = shape_layout(elem, 4)
        pcsize, _, pcf = shape_layout(elem, 8)
        sec = section_of(a, ovl)
        if sec is None or sec[3] is None:
            raise Fail(f"{where}: {a:#010x} is not in a section the ROM fills for overlay {ovl}'s code")
        self.objects[a] = dict(name=name, section=sec, shape=shape, count=count, n64size=n64size, pcsize=pcsize,
                               fields=[(o4, o8, k) for (o4, k, _), (o8, _, _) in zip(n64f, pcf)])
        for k in range(count):
            for (o, kind, target) in n64f:
                at = a + k * n64size + o
                # an IdOr's number: 0 or more as an s32, or -1 (none)
                number = (kind == "p" and isinstance(target, IdOr)
                          and (not self.word(at) & 0x80000000 or self.word(at) == 0xFFFFFFFF))
                self.check_address_word(at, kind == "p" and not number, where)
                if kind != "p" or number:
                    continue
                if isinstance(target, IdOr):
                    target = target.target
                w = self.word(at)
                here = f"{where}[{k}]+{o:#x}"
                if target == UNUSED:
                    if section_of(w, ovl) is not None or self.function_at(w, ovl, False) is not None:
                        raise Fail(f"{here}: an unused entry, but its word {w:#010x} is an address")
                    continue
                if w == 0:
                    continue
                if target == FUNC:
                    fn = self.function_at(w, ovl, True)
                    if fn is None:
                        raise Fail(f"{here}: {w:#010x} is not the start of a function the port compiles")
                    self.entries[w] = fn
                elif target == GFX:
                    tsec = section_of(w, ovl)
                    self.gfx_todo.append((w, self.var_at.get((tsec[0] if tsec else None, w), f"td_gfx_{w:08X}"),
                                          ovl, here))
                elif target == VTX:
                    if section_of(w, ovl) is None or section_of(w, ovl)[3] is None:
                        raise Fail(f"{here}: {w:#010x} is not in a section the ROM fills")
                    self.vertices.append((w, None, here))
                elif target == PORT:
                    if w not in self.port:
                        raise Fail(f"{here}: {w:#010x} is not a variable the port provides")
                elif isinstance(target, Data):
                    if section_of(w, ovl) is None or section_of(w, ovl)[3] is None:
                        raise Fail(f"{here}: {w:#010x} is not in a section the ROM fills")
                    self.claims.append((w, target.width, here))
                    if target.to_zero:
                        self.claim_ends[w] = self.zero_end(w, target.width, here)
                else:
                    tsec = section_of(w, ovl)
                    self.add(w, target, self.var_at.get((tsec[0] if tsec else None, w), f"td_anon_{w:08X}"),
                             f"{here} -> {w:#010x}", ovl)

    def resolve(self, every_name: bool):
        """Adds each table of TABLES. every_name: each must be used by a file of the set."""
        for name, shape in TABLES.items():
            r = next((r for r in self.rows if r[0] == name), None)
            if r is None:
                if every_name:
                    raise Fail(f"TABLES describes {name}, which no file of the port uses: remove it")
                continue
            self.add(r[1], shape, name, name, r[5])
        # No data or object may start inside another object.
        spans = sorted((a, a + o["count"] * o["n64size"], o["name"]) for a, o in self.objects.items())
        for w, _, why in self.claims:
            for lo, hi, n in spans:
                if lo <= w < hi:
                    raise Fail(f"{why}: the data at {w:#010x} lies inside {n}")
        for (lo, hi, n), (lo2, _, n2) in zip(spans, spans[1:]):
            if lo2 < hi:
                raise Fail(f"{n2} at {lo2:#010x} starts inside {n}")

    def walk_display_lists(self, every_name: bool):
        """Reads each display list of DISPLAY_LISTS from the ROM, and every list one of them calls or branches to,
        command by command up to its end (G_ENDDL, or a G_DL that branches without return). Each becomes a gfx object;
        the data its commands load (vertices, textures, the viewport) gets claims of its width. Stops on a command this
        tool does not know, an address that is not in a section the ROM fills for the list's overlay, or a segment
        address (Fast3D reads those only with bit 0 set, which the N64's do not have). every_name: each name of
        DISPLAY_LISTS must be used by a file of the set."""
        todo, walked = [], {}
        for name in DISPLAY_LISTS:
            r = next((r for r in self.rows if r[0] == name), None)
            if r is None:
                if every_name:
                    raise Fail(f"DISPLAY_LISTS names {name}, which no file of the port uses: remove it")
                continue
            todo.append((r[1], name, r[5]))
        todo += [(a, name, ovl) for a, name, ovl, _ in self.gfx_todo]
        while todo:
            a, name, ovl = todo.pop()
            if a in walked:
                continue
            sec = section_of(a, ovl)
            if sec is None or sec[3] is None:
                raise Fail(f"{name}: the display list at {a:#010x} is not in a section the ROM fills")
            n, at = 0, a
            while True:
                if at + 8 > sec[2]:
                    raise Fail(f"{name}: the display list at {a:#010x} runs past the end of {sec[0]}")
                w0, w1 = self.word(at), self.word(at + 4)
                op, n, at = w0 >> 24, n + 1, at + 8
                where = f"{name}+{at - 8 - a:#x}"
                if op not in GBI_OPS:
                    raise Fail(f"{where}: {w0:08X} {w1:08X} is not a command this tool knows (GBI_OPS)")
                kind = GBI_OPS[op]
                if kind == "addr" or (op == 0xDB and (w0 >> 16) & 0xFF == 0x06):
                    if op != 0xDB and w1 >> 24 not in (0x00, 0x80) or op == 0xDB:
                        raise Fail(f"{where}: {w0:08X} {w1:08X}: a segment address or a segment's base, which the "
                                   "port does not convert")
                    t = w1 | 0x80000000
                    ts = section_of(t, ovl)
                    if ts is None or ts[3] is None:
                        raise Fail(f"{where}: {w0:08X} {w1:08X}: {t:#010x} is not in a section the ROM fills")
                    if op == 0x01:  # G_VTX: n vertices of 16 bytes
                        self.vertices.append((t, (w0 >> 12) & 0xFF, where))
                    elif op == 0xDE:  # G_DL: another list
                        tsec = section_of(t, ovl)
                        todo.append((t, self.var_at.get((tsec[0], t), f"td_gfx_{t:08X}"), ovl))
                    elif op == 0xFD:  # G_SETTIMG: a texture or palette, which stays in the N64's byte order
                        self.claims.append((t, 1, where))
                    elif op == 0xDC and (w0 & 0xFF) == 0x08:  # G_MOVEMEM of the viewport: eight s16
                        self.claims.append((t, 2, where))
                        self.claim_ends[t] = t + 16
                    else:
                        raise Fail(f"{where}: {w0:08X} {w1:08X}: data of a command this tool does not describe")
                if op == 0xDF or (op == 0xDE and (w0 >> 16) & 0xFF == 1):
                    break
            walked[a] = dict(name=name, section=sec, end=at)
        # Lists that overlap are one list with more than one entry point (D_800C5D48 is the last two commands of
        # D_800C5D10): one gfx object from the first of them, whose other starts are its entries.
        for a in sorted(walked):
            w = walked[a]
            host = next((g for b, g in self.gfx.items() if g["section"] is w["section"] and b <= a < g["end"]), None)
            if host is None:
                self.gfx[a] = dict(name=w["name"], section=w["section"], end=w["end"], entries={})
            else:
                host["end"] = max(host["end"], w["end"])
                host["entries"][a] = w["name"]
        for a, g in self.gfx.items():
            g["count"] = (g["end"] - a) // 8
        spans = sorted([(a, a + g["count"] * 8, g["name"]) for a, g in self.gfx.items()]
                       + [(a, a + o["count"] * o["n64size"], o["name"]) for a, o in self.objects.items()])
        for (lo, hi, n), (lo2, _, n2) in zip(spans, spans[1:]):
            if lo2 < hi:
                raise Fail(f"{n2} at {lo2:#010x} starts inside {n}")
        for w, _, why in self.claims:
            for lo, hi, n in spans:
                if lo <= w < hi:
                    raise Fail(f"{why}: the data at {w:#010x} lies inside {n}")

    def add_claims(self, widths):
        """Puts the widths of the data the addresses point at into the sections' width maps; returns the swap-only
        ranges (section, start, end) of claimed bytes, each from its address to the next label."""
        ranges = []
        seen: dict[int, tuple[int, str]] = {}
        for w, width, why in sorted(set(self.claims)):
            # Many addresses can name the same data (D_80036594 twelve times): one range, so it is swapped once.
            if w in seen:
                if seen[w][0] != width:
                    raise Fail(f"{why}: reads {w:#x} as {width}-byte values; {seen[w][1]} as {seen[w][0]}-byte values")
                continue
            seen[w] = (width, why)
            sec = rom_section_of(w)
            end = max(self.claim_ends.get(w, 0), self.next_label(w))
            wm = widths[sec[0]]
            if width > 1:
                for at in range(w - sec[1], end - sec[1] - width + 1, width):
                    for b in range(at, at + width):
                        old = wm.get(b)
                        if old is not None and old[:2] != (at, width):
                            raise Fail(f"{why}: reads {sec[1] + b:#x} as part of a {width}-byte value at "
                                       f"{sec[1] + at:#x}; {old[2]} reads it as part of a {old[1]}-byte value at "
                                       f"{sec[1] + old[0]:#x}")
                        wm[b] = (at, width, why)
            else:
                for b in range(w - sec[1], end - sec[1]):
                    old = wm.get(b)
                    if old is not None and old[1] > 1:
                        raise Fail(f"{why}: reads {sec[1] + b:#x} as bytes; {old[2]} reads it as part of a "
                                   f"{old[1]}-byte value")
            ranges.append((sec, w, end))
        # Vertices: x, y, z, a flag, s and t are 16-bit values, the colour four bytes; each list of them is its own
        # range, as long as the commands that load it say (the longest of them).
        longest: dict[int, tuple[int, str]] = {}
        starts = ({v for v, _, _ in self.vertices} | set(self.gfx) | {c for c, _, _ in self.claims})
        for w, n, why in self.vertices:
            if n is None:
                n = (min([b for b in starts if w < b < self.next_label(w)], default=self.next_label(w)) - w) // 16
            if n > longest.get(w, (0, ""))[0]:
                longest[w] = (n, why)
        for w, (n, why) in sorted(longest.items()):
            sec = rom_section_of(w)
            wm = widths[sec[0]]
            for k in range(n):
                for o, width in VTX_FIELDS:
                    at = w - sec[1] + 16 * k + o
                    for b in range(at, at + width):
                        old = wm.get(b)
                        if old is not None and old[:2] != (at, width):
                            raise Fail(f"{why}: loads {sec[1] + b:#x} as part of a vertex ({width}-byte value at "
                                       f"{sec[1] + at:#x}); {old[2]} reads it as part of a {old[1]}-byte value at "
                                       f"{sec[1] + old[0]:#x}")
                        wm[b] = (at, width, why)
            ranges.append((sec, w, w + 16 * n))
        return ranges

    def fill(self, a: int) -> str:
        o = self.objects[a]
        return (f"{o['count']:x}:{o['n64size']:x}:{o['pcsize']:x}:"
                + ",".join(f"{o4:x}.{o8:x}.{k if k != 'p' else self._kind(o, o4)}" for o4, o8, k in o["fields"]))

    def _kind(self, o, off):
        elem = o["shape"].elem if isinstance(o["shape"], Arr) else o["shape"]
        for o4, k, t in shape_layout(elem, 4)[2]:
            if o4 == off:
                return "f" if t == FUNC else "z" if t == UNUSED else "k" if isinstance(t, IdOr) else "p"
        raise AssertionError(off)


HEADER = ("# Written by tools/port_data.py, which explains each column; do not edit by hand.\n"
          "# name\taddress\tsection\tstorage\tbytes\tswap\n")


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--check", action="store_true", help="compare with port/game_vars.tsv instead of writing it")
    ap.add_argument("-j", type=int, default=os.cpu_count() or 4, help="files compiled at a time")
    # Another of port_filelist.py's sets, for a test of this tool: the map must be written from the boot set.
    ap.add_argument("--set", default="boot", help=argparse.SUPPRESS)
    args = ap.parse_args()
    cc = os.environ.get("CC", "gcc")  # clang leaves extern declarations out of the debug information
    try:
        with tempfile.TemporaryDirectory() as tmp:
            lines = build_map(cc, args.j, Path(tmp), args.set)
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
