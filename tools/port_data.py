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
3. Each variable's N64 address comes from build.json, a label of asm/data, or the address in a D_XXXXXXXX name. The address
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
5. The address tables (TABLES, below): the own variables that the ROM starts, each described by hand down to what its
   addresses point at, checked against the ROM's data, and written as fill lines; the arrays and records they reach
   get fill lines of their own, and the data they point at swap ranges.
6. For each variable in a section that the ROM fills (main's data, overlay 2's data), the swap pattern: which bytes are
   16-, 32- or 64-bit values, which the port turns from the N64's byte order into the PC's after copying the section
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

def section_widths(sec, rows, views, labels) -> dict[int, tuple[int, int, str]]:
    """The width of every byte of a section that the ROM fills, from the block variables' types: byte offset ->
    (offset of the value it is part of, its width, the file and variable that say so). Each file's type for a variable
    covers the variable's bytes (a record reached through its inner labels covers theirs too); an open array, or a type
    smaller than the extent, repeats its element over the extent (which ends at the next variable), but not past a place
    that an address table points at (labels), where other data begins. Two readings of one byte at different widths stop
    the tool."""
    later = sorted(b for b in labels if sec[1] <= b < sec[2])
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
    all_functions = {f["vram"]: f["name"] for f in json.loads((ROOT / "build.json").read_text(encoding="utf-8"))["functions"]
                     if "vram" in f}
    functions = {a: n for a, n in all_functions.items() if n in defined}
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

    # The address tables first: the places their addresses point at begin objects too, so they bound the variables'
    # repeated patterns as labels do.
    tables = Tables(rows, views, syms, all_functions, defined)
    tables.resolve()
    # Not every label of the game's data: splat also labels fields inside a table (D_8003A4FE, 2 bytes into the name
    # tables' counts), where the table's pattern must go on.
    labels = {w for w, _, _ in tables.claims} | set(tables.objects)
    widths = {sec[0]: section_widths(sec, rows, views, labels) for sec in SECTIONS if sec[3] is not None}
    ranges = tables.add_claims(widths)
    lines = []
    # The data that the tables' addresses point at, where no block variable's extent covers it: swap-only ranges.
    blocks = sorted((r[1], r[1] + r[3]) for r in rows if r[4] == "block" and r[3])
    for sec, lo, hi in ranges:
        for blo, bhi in blocks:
            if blo <= lo < bhi:
                lo = bhi
        for blo, bhi in blocks:
            if lo < blo < hi:
                hi = blo
        if lo < hi:
            lines.append(f"td_data_{lo:08X}\t{lo:08X}\t{sec[0]}\tdata\t{hi - lo:#x}\t"
                         f"{swap_pattern(lo - sec[1], hi - lo, widths[sec[0]])}")
    for a, o in tables.objects.items():
        if o["name"].startswith("td_anon_"):
            lines.append(f"{o['name']}\t{a:08X}\t{o['section'][0]}\town\t{o['count'] * o['pcsize']:#x}\t"
                         f"{tables.fill(a)}")
    for a, n in sorted(tables.entries.items()):
        lines.append(f"{n}\t{a:08X}\tcode\tentry\t{n}\t-")
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
#     PORT                   a variable the port provides (a framebuffer);
#     UNUSED                 nothing: an entry the game never reads, whose word is not an address (tables that the
#                            game indexes from 1); PC gets NULL there.
# A 0 word is NULL whatever the target.

AUTO = "auto"
FUNC = "func"
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


class Data:
    def __init__(self, width, to_zero=False):
        self.width, self.to_zero = width, to_zero

    def __repr__(self):
        return f"Data({self.width}{', to_zero=True' if self.to_zero else ''})"


# NameEntry, the PC view of a wrestler's name entry (buildWrestlerNameRecord): id, value, a word, the name's address.
# On the N64 an entry is 0x1C bytes and also holds the addresses of the height and weight texts and two more words;
# the developer program's files read none of them, so the PC entry is NameEntry's 16 bytes.
NAME_ENTRY = [2, 1, 1, 4, Ptr(Data(1))]

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
}


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

    def __init__(self, rows, views, syms, functions, defined):
        self.rom = (ROOT / "baserom.z64").read_bytes()
        self.rows, self.views, self.functions, self.defined = rows, views, functions, defined
        self.port = {r[1]: r[0] for r in rows if r[4] == "port"}
        self.var_at = {r[1]: r[0] for r in rows if not r[4].startswith("=")}
        self.relocs, self.labels = self._read_main_data()
        self.labels |= set(syms.values())
        self.objects = {}   # N64 address -> dict(name, section, n64size, pcsize, count, elem, fields)
        self.claims = []    # (N64 address, width, why)
        self.claim_ends = {}  # N64 address -> the end of a Data(w, to_zero=True) list
        self.entries = {}   # N64 address -> function name

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
        sec = section_of(a)
        if sec is None or sec[3] is None:
            raise Fail(f"{a:#010x}: not in a section the ROM fills")
        o = sec[3] + a - sec[1]
        return int.from_bytes(self.rom[o:o + width], "big")

    def zero_end(self, a: int, width: int, where: str) -> int:
        """The end of the list of width-byte values at a, after its closing 0."""
        sec = section_of(a)
        while a + width <= sec[2]:
            a += width
            if self.word(a - width, width) == 0:
                return a
        raise Fail(f"{where}: the list has no closing 0 before the end of {sec[0]}")

    def next_label(self, a: int) -> int:
        sec = section_of(a)
        later = [b for b in (self.labels | set(self.var_at) | set(self.objects)) if a < b < sec[2]]
        return min(later, default=sec[2])

    def is_main(self, a: int) -> bool:
        return section_of(a)[0] == "main.data"

    def check_address_word(self, a: int, expect: bool, where: str):
        if not self.is_main(a):
            return
        marked = a in self.relocs
        w = self.word(a)
        # splat writes some tables as 16-bit values (the name tables), so an unmarked word is accepted when it is an
        # address in a section the ROM fills.
        if expect and not marked and w != 0 and (section_of(w) is None or section_of(w)[3] is None):
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

    def add(self, a: int, shape, name: str, where: str):
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
        sec = section_of(a)
        self.objects[a] = dict(name=name, section=sec, shape=shape, count=count, n64size=n64size, pcsize=pcsize,
                               fields=[(o4, o8, k) for (o4, k, _), (o8, _, _) in zip(n64f, pcf)])
        for k in range(count):
            for (o, kind, target) in n64f:
                at = a + k * n64size + o
                self.check_address_word(at, kind == "p", where)
                if kind != "p":
                    continue
                w = self.word(at)
                here = f"{where}[{k}]+{o:#x}"
                if target == UNUSED:
                    if section_of(w) is not None or w in self.functions:
                        raise Fail(f"{here}: an unused entry, but its word {w:#010x} is an address")
                    continue
                if w == 0:
                    continue
                if target == FUNC:
                    fn = self.functions.get(w)
                    if fn is None or fn not in self.defined:
                        raise Fail(f"{here}: {w:#010x} is not the start of a function the port compiles")
                    self.entries[w] = fn
                elif target == PORT:
                    if w not in self.port:
                        raise Fail(f"{here}: {w:#010x} is not a variable the port provides")
                elif isinstance(target, Data):
                    if section_of(w) is None or section_of(w)[3] is None:
                        raise Fail(f"{here}: {w:#010x} is not in a section the ROM fills")
                    self.claims.append((w, target.width, here))
                    if target.to_zero:
                        self.claim_ends[w] = self.zero_end(w, target.width, here)
                else:
                    self.add(w, target, self.var_at.get(w, f"td_anon_{w:08X}"), f"{here} -> {w:#010x}")

    def resolve(self):
        for name, shape in TABLES.items():
            a = next((r[1] for r in self.rows if r[0] == name), None)
            if a is None:
                raise Fail(f"TABLES describes {name}, which no file of the port uses: remove it")
            self.add(a, shape, name, name)
        # No data or object may start inside another object.
        spans = sorted((a, a + o["count"] * o["n64size"], o["name"]) for a, o in self.objects.items())
        for w, _, why in self.claims:
            for lo, hi, n in spans:
                if lo <= w < hi:
                    raise Fail(f"{why}: the data at {w:#010x} lies inside {n}")
        for (lo, hi, n), (lo2, _, n2) in zip(spans, spans[1:]):
            if lo2 < hi:
                raise Fail(f"{n2} at {lo2:#010x} starts inside {n}")

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
            sec = section_of(w)
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
        return ranges

    def fill(self, a: int) -> str:
        o = self.objects[a]
        return (f"{o['count']:x}:{o['n64size']:x}:{o['pcsize']:x}:"
                + ",".join(f"{o4:x}.{o8:x}.{k if k != 'p' else self._kind(o, o4)}" for o4, o8, k in o["fields"]))

    def _kind(self, o, off):
        elem = o["shape"].elem if isinstance(o["shape"], Arr) else o["shape"]
        for o4, k, t in shape_layout(elem, 4)[2]:
            if o4 == off:
                return "f" if t == FUNC else "z" if t == UNUSED else "p"
        raise AssertionError(off)


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
