"""Proves, one file at a time, that a TARGET_PC edit is safe: the N64 build still reads and compiles exactly what it
did, and the PC port can compile the file. Several people can check their own files at the same time this way,
without build.py, which only one person may run at a time (it writes build/).

    cd source
    python3 tools/port_check.py FILE...            the files given: paths under src/ or include/
    python3 tools/port_check.py --changed          every file under src/ or include/ that git reports changed against
                                                   HEAD (modified, new or deleted)
    python3 tools/port_check.py --set match -j 8   checks 3 and 4 for every file tools/port_filelist.py lists for the
                                                   developer program; with --files-from LIST, for the files LIST names
    python3 tools/port_check.py --files-from LIST  the files LIST names, one path per line

    -j N    checks N files at a time (default 1)
    -v      prints the details under every failed check (the lines that differ, the compilers' messages), and the
            notes of a check that passed with notes
    --keep DIR   keeps the work files (both versions of the files, the objects, the preprocessed text and the
            compilers' messages) in DIR, which must be outside the source tree, instead of a temporary folder that is
            deleted at the end
    --against-build   compiles each C file as check 2 does and compares the object with build.py's own in build/
            (after build.py's trim of the code section's end padding): the proof that check 2 compiles as build.py does

HEAD is git's last commit, the state that build.py last proved identical. Every file gets four checks:
1. N64 view. The text the N64 compiler reads, which never defines TARGET_PC: each "#ifdef TARGET_PC" block is dropped
   and its #else branch kept, each "#ifndef TARGET_PC" block is kept, and the directive lines themselves are dropped.
   It must equal the same view of HEAD's version byte for byte: then every change sits inside TARGET_PC blocks. Only
   plain tests of TARGET_PC are accepted (#ifdef, #ifndef, #if defined(TARGET_PC), #if !defined(TARGET_PC)); #elif and
   other conditions on TARGET_PC are refused with a message, because the view could not follow them. Then KMC GCC's
   own preprocessor (-E in place of -c in build.py's command) must read the file without an error and give the same
   text as for HEAD's version, apart from line breaks and spaces: the N64's preprocessor reads some text in a skipped
   block differently (a quote that does not close on its line stops it, for example). A header is preprocessed after
   common.h, as game files include it. A new file fails, because HEAD has nothing to compare it with, and so does a
   deleted file, because the N64 build would lose it: only build.py can prove those. For a header this is the only
   N64 check. include/port_decls.h is PC-only (common.h includes it inside TARGET_PC), so its N64 view is empty; for
   it the check proves instead that common.h's PC view includes it, and that no file under src/ or include/ includes it
   outside a TARGET_PC block.
2. N64 object (C files). The file and HEAD's version, each with its own include/, are compiled by KMC GCC 2.7.2 the way
   build.py compiles them: decompdecomp's toolchain and command, build.json's flags and compiler_ranges. Both objects
   must hold the same code, relocations, data and symbols (sections the link throws away, such as .comment, aside).
3. PC compile (C files). A real compile (-c) with gcc and with clang (clang with -ferror-limit=0, so it counts every
   error) and exactly the flags the port gives game files (PC_FLAGS below): no errors. A second compile adds -Wall
   -Wextra: no warning that HEAD's version of the file does not also have. Where HEAD's version still has errors in
   that compile, a compiler skips some of its warnings there, so a new warning on a line that HEAD's version also has
   is a note, not a failure.
4. No asm (C files). No asm, __asm__ or __asm in the file's preprocessed PC text (gcc -E and clang -E). A compile
   cannot catch MIPS assembly: x86 assemblers accept some MIPS instructions as other instructions.

Output: one line per file and check, "pass", "FAIL", or "n/a" where a check does not apply, then a summary.
Exit status: 0 when every check passed, 1 when a check failed, 2 when the tool could not run or was stopped; it then
says why (no git repository, a compiler or decompdecomp missing, a path outside src/ and include/,
tools/port_filelist.py failing, a fault in this tool).

Needs Python 3.8 or later and nothing outside its standard library; checks 1 and 2 run decompdecomp's own Python, as
build.py does, to get the KMC GCC command. It writes nothing into the source tree: every file it makes goes to a
temporary folder (or the --keep folder).
"""
from __future__ import annotations

import argparse
import collections
import concurrent.futures
import difflib
import fnmatch
import json
import os
import re
import shutil
import signal
import struct
import subprocess
import sys
import tempfile
import traceback
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent

# ---- The port's flags for game files ------------------------------------------------------------------------------
# PC_FLAGS mirror td_game_code() in turnbuckle-dive/CMakeLists.txt, in the order CMake writes them into
# compile_commands.json: its compile definitions, its include directory, -g from the Debug build type (the debug
# preset), -std=gnu17 from C_STANDARD 17 with C_EXTENSIONS ON, then its compile options. The port's settings are
# copied into three tools: here, as PC_FLAGS in tools/port_calls.py, and as PC_DEFINES in tools/port_filelist.py.
# When td_game_code() changes, change all three.
PC_FLAGS = [
    "-DAVOID_UB", "-DF3DEX_GBI_2", "-DNON_MATCHING", "-DTARGET_PC",
    "-Iinclude",
    "-g",
    "-std=gnu17",
    "-fno-strict-aliasing", "-fwrapv", "-fsigned-char", "-ffp-contract=off", "-fno-builtin-sinf", "-fno-builtin-cosf",
    "-Werror=implicit-function-declaration", "-Werror=int-conversion", "-Werror=pointer-to-int-cast",
    "-Werror=int-to-pointer-cast",
]
# ---- end of the port's flags --------------------------------------------------------------------------------------

# How each compiler prints its messages: one line each, without colours or source excerpts, so they can be read here.
# -ferror-limit=0: clang otherwise stops after 20 errors in a file and the count comes out too low.
MESSAGE_FLAGS = {
    "gcc": ["-fdiagnostics-plain-output"],
    "clang": ["-fno-caret-diagnostics", "-fno-color-diagnostics", "-ferror-limit=0"],
}
# The warnings compile (-Wall -Wextra) also turns the errors that the port's flags and the compilers' own defaults make
# of pointer and declaration problems back into warnings. HEAD's version often does not compile yet, and a compiler
# that stops at an error skips the later passes that warn; this way both versions go through them. A file without such
# errors compiles exactly as it would without these flags.
DEMOTE_FLAGS = {
    "gcc": ["-Wno-error=implicit-function-declaration", "-Wno-error=int-conversion", "-Wno-error=pointer-to-int-cast",
            "-Wno-error=int-to-pointer-cast", "-Wno-error=implicit-int", "-Wno-error=incompatible-pointer-types"],
    "clang": ["-Wno-error=implicit-function-declaration", "-Wno-error=int-conversion", "-Wno-error=pointer-to-int-cast",
              "-Wno-error=int-to-pointer-cast", "-Wno-error=implicit-int", "-Wno-error=incompatible-pointer-types",
              "-Wno-error=incompatible-function-pointer-types"],
}
COMPILERS = ("gcc", "clang")

# The sections build.py's link throws away (DISCARD in build.py): nothing in them reaches the ROM.
DISCARDED = (".reginfo", ".MIPS.abiflags", ".MIPS.options", ".pdr", ".comment", ".mdebug*", ".gnu.attributes",
             ".note*", ".gptab.*")
ASM_WORDS = ("asm", "__asm__", "__asm")
CHECK_NAMES = {1: "N64 view", 2: "N64 object", 3: "PC compile", 4: "no asm"}
PASS, FAIL, NA = "pass", "FAIL", "n/a"
MAX_DETAILS = 30  # lines of details printed per check with -v


class CannotRun(Exception):
    """Something the tool needs is missing, so it cannot check anything (exit status 2)."""


class Result:
    """The outcome of one check of one file: its status, a one-line summary, the -v details and counts for the
    summary at the end."""

    def __init__(self, check: int, status: str, text: str, details: list[str] | None = None,
                 stats: dict | None = None):
        self.check, self.status, self.text = check, status, text
        self.details, self.stats = details or [], stats or {}


def run(argv: list[str], cwd: Path, env: dict | None = None, timeout: int = 300,
        stdin: bytes | None = None) -> tuple[int | None, str]:
    """Runs a program; returns its exit status and everything it printed. A program that cannot be started, or does
    not finish in time, gives the status None and a message instead."""
    try:
        res = subprocess.run(argv, cwd=cwd, env=env, input=stdin, stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                             timeout=timeout)
    except OSError as e:
        return None, f"{argv[0]}: cannot be started ({e.strerror})"
    except subprocess.TimeoutExpired:
        return None, f"{argv[0]}: no result after {timeout} seconds"
    return res.returncode, res.stdout.decode("utf-8", "replace")


def plural(n: int, word: str) -> str:
    return f"{n} {word}{'s' * (n != 1)}"


def short(text: str, width: int = 70) -> str:
    """A line of source shortened for a message."""
    text = text.strip()
    return text if len(text) <= width else text[:width - 3] + "..."


# ---- git: HEAD's version of the files -----------------------------------------------------------------------------

def git(*args: str, stdin: bytes | None = None) -> bytes:
    """Runs a git command that only reads (--no-optional-locks: not even git status's index refresh is written)."""
    try:
        res = subprocess.run(["git", "--no-optional-locks", *args], cwd=ROOT, input=stdin, capture_output=True)
    except OSError as e:
        raise CannotRun(f"git cannot be started ({e.strerror})") from None
    if res.returncode != 0:
        raise CannotRun(f"git {' '.join(args)}: {res.stderr.decode('utf-8', 'replace').strip()}")
    return res.stdout


class Head:
    """HEAD's commit: its files under src/ and include/ and its build.json, read with git (which changes nothing)."""

    def __init__(self):
        top = git("rev-parse", "--show-toplevel").decode().strip()
        if Path(top).resolve() != ROOT:
            raise CannotRun(f"{ROOT} is not the top folder of its git repository ({top} is)")
        self.commit = git("rev-parse", "--short", "HEAD").decode().strip()
        self.blob = {}  # path -> blob id
        for entry in git("ls-tree", "-r", "-z", "HEAD", "--", "src", "include", "build.json").split(b"\0"):
            if entry:
                meta, path = entry.split(b"\t", 1)
                if meta.split()[1] == b"blob":
                    self.blob[path.decode("utf-8", "surrogateescape")] = meta.split()[2].decode()
        self.data: dict[str, bytes] = {}

    def load(self, paths) -> None:
        """Reads HEAD's version of the paths HEAD has, all with one git command."""
        todo = sorted({p for p in paths if p in self.blob and p not in self.data})
        if not todo:
            return
        out = git("cat-file", "--batch", stdin="".join(self.blob[p] + "\n" for p in todo).encode())
        pos = 0
        for p in todo:  # each answer: "<id> blob <size>\n<bytes>\n"
            nl = out.index(b"\n", pos)
            size = int(out[pos:nl].split()[2])
            self.data[p] = out[nl + 1:nl + 1 + size]
            pos = nl + 1 + size + 1

    def get(self, path: str) -> bytes | None:
        """HEAD's version of the file (load() it first), or None when HEAD does not have it."""
        return self.data.get(path)


def changed_files() -> list[str]:
    """The files under src/ and include/ that git reports changed against HEAD: modified, added, deleted, and new
    files git does not track yet."""
    tracked = git("diff", "--name-only", "-z", "HEAD", "--", "src", "include").split(b"\0")
    new = git("ls-files", "-z", "--others", "--exclude-standard", "--", "src", "include").split(b"\0")
    return sorted({p.decode("utf-8", "surrogateescape") for p in tracked + new if p})


# ---- Check 1: the N64 view ----------------------------------------------------------------------------------------

class ViewError(Exception):
    """A file uses TARGET_PC in a way the N64 view cannot follow (or its conditionals do not balance)."""

    def __init__(self, line: int, message: str):
        super().__init__(f"line {line}: {message}")
        self.line, self.message = line, message


class Directive:
    """One preprocessor directive: the physical lines it spans, whether its # starts its line (only blanks before
    it), its name (if, ifdef, define...) and the words after the name, with comments taken out."""

    def __init__(self, first: int, at_line_start: bool):
        self.first, self.last, self.at_line_start = first, first, at_line_start
        self.text: list[str] = []
        self.name, self.words, self.shown = "", [], ""


def find_directives(text: str) -> list[Directive]:
    """The directives of a C file, found the way a C preprocessor finds them.

    The N64's preprocessor (KMC GCC 2.7.2's cpp) and GCC agree on all of this; checked by hand, it is what makes the
    view safe: a "#else" inside a comment, or after a quote that never closes on its line, is not a directive, and a
    comment that runs over several lines makes a directive run on to where it closes.
    - A backslash at the end of a line joins it to the next one, everywhere.
    - Comments (/* */ and //) count as blanks; text in quotes is not looked into, and a quote ends with its line.
    - A # is a directive when nothing but blanks and comments came before it since the last line break outside a
      comment. The directive ends at the next line break outside a comment."""
    # join backslash-newlines, remembering each character's physical line
    chars, lines = [], []
    line, i, n = 1, 0, len(text)
    while i < n:
        if text[i] == "\\" and text.startswith("\n", i + 1):
            i += 2
            line += 1
            continue
        chars.append(text[i])
        lines.append(line)
        if text[i] == "\n":
            line += 1
        i += 1
    s = "".join(chars)
    found: list[Directive] = []
    cur: Directive | None = None
    state = "code"  # code, block (comment), line (comment), string, char
    no_token = True  # nothing but blanks and comments since the last line break outside a comment
    blank = True  # nothing at all but blanks since then, so a # here starts its physical line
    j, n = 0, len(s)
    while j < n:
        c = s[j]
        nxt = s[j + 1] if j + 1 < n else ""
        if state == "block":
            if c == "*" and nxt == "/":
                state = "code"
                j += 2
            else:
                j += 1
            continue
        if state in ("string", "char"):
            if c == "\\" and nxt and nxt != "\n":
                if cur:
                    cur.text.append(c + nxt)
                j += 2
                continue
            if c != "\n":
                if cur:
                    cur.text.append(c)
                if c == ('"' if state == "string" else "'"):
                    state = "code"
                j += 1
                continue
            state = "code"  # a quote that does not close ends with its line
        if state == "line":
            if c != "\n":
                j += 1
                continue
            state = "code"
        # outside comments and quotes
        if c == "\n":
            if cur:
                cur.last = lines[j]
                found.append(cur)
                cur = None
            no_token = blank = True
        elif c == "/" and nxt in ("*", "/"):
            state = "block" if nxt == "*" else "line"
            blank = False
            if cur:
                cur.text.append(" ")
            j += 2
            continue
        elif c in " \t\f\v\r":
            if cur:
                cur.text.append(c)
        elif c == "#" and no_token and cur is None:
            cur = Directive(lines[j], blank)
            no_token = blank = False
        else:
            no_token = blank = False
            if cur:
                cur.text.append(c)
            if c in "\"'":
                state = "string" if c == '"' else "char"
        j += 1
    if cur:
        cur.last = lines[-1]
        found.append(cur)
    for d in found:
        m = re.match(r"\s*([A-Za-z_]\w*)?(.*)", "".join(d.text), re.S)
        d.name = m.group(1) or ""
        d.words = re.findall(r"[A-Za-z_]\w*|\d\w*|\S", m.group(2))
        d.shown = f"#{d.name} {' '.join(m.group(2).split())}".strip()  # as written, for messages
    return found


def pc_test(d: Directive) -> str | None:
    """'on' for a plain test that TARGET_PC is defined (#ifdef TARGET_PC, #if defined(TARGET_PC)), 'off' for a plain
    test that it is not; None when the directive does not name TARGET_PC. Any other use raises ViewError."""
    if "TARGET_PC" not in d.words:
        return None
    w = d.words
    if d.name in ("ifdef", "ifndef") and w == ["TARGET_PC"]:
        kind = "on" if d.name == "ifdef" else "off"
    elif d.name == "if" and w in (["defined", "(", "TARGET_PC", ")"], ["defined", "TARGET_PC"]):
        kind = "on"
    elif d.name == "if" and w in (["!", "defined", "(", "TARGET_PC", ")"], ["!", "defined", "TARGET_PC"]):
        kind = "off"
    elif d.name in ("elif", "elifdef", "elifndef"):
        raise ViewError(d.first, f"#{d.name} that tests TARGET_PC: use a plain #ifdef TARGET_PC block instead")
    elif d.name in ("if", "ifdef", "ifndef"):
        raise ViewError(d.first, f"{d.shown}: not one of the accepted tests of TARGET_PC; only #ifdef TARGET_PC, "
                                 "#ifndef TARGET_PC, #if defined(TARGET_PC) and #if !defined(TARGET_PC) are accepted")
    elif d.name in ("define", "undef"):
        raise ViewError(d.first, f"#{d.name} that names TARGET_PC: only the PC build defines it")
    else:
        return None
    if not d.at_line_start:
        raise ViewError(d.first, "a TARGET_PC directive must start its line (a comment comes before its #)")
    return kind


def n64_view(data: bytes, pc: bool = False) -> tuple[bytes, list[int]]:
    """The file as the N64 compiler reads it, TARGET_PC being undefined there: the PC branch of every TARGET_PC test
    dropped, the other branch kept, the TARGET_PC directives' own lines dropped; every other line exactly as it is.
    Returns the view and, for each of its lines, the line's number in the file. With pc=True, the PC view instead: the
    branches the PC compiler reads, TARGET_PC being defined (only check_pc_only_header asks for it)."""
    text = data.decode("latin-1")  # one character per byte: any bytes, given back exactly
    parts = text.split("\n")
    lines = [p + "\n" for p in parts[:-1]] + ([parts[-1]] if parts[-1] else [])
    drop = [False] * (len(lines) + 2)
    stack: list[list] = []  # open conditionals: ["pc", keep this branch, line, #else seen] or ["other"]
    pos = 1  # the first line not yet given a fate

    def visible() -> bool:
        return all(f[1] for f in stack if f[0] == "pc")

    def fill(upto: int, dropped: bool) -> None:  # lines pos..upto-1 get the current fate
        nonlocal pos
        for k in range(pos, upto):
            drop[k] = dropped
        pos = max(pos, upto)

    for d in find_directives(text):
        fill(d.first, not visible())
        own = False  # the directive belongs to a TARGET_PC conditional, so its lines go
        if d.name in ("if", "ifdef", "ifndef"):
            kind = pc_test(d)
            if kind:
                stack.append(["pc", kind == ("on" if pc else "off"), d.first, False])
                own = True
            else:
                stack.append(["other"])
        elif d.name in ("elif", "elifdef", "elifndef"):
            if not stack:
                raise ViewError(d.first, f"#{d.name} without #if")
            if stack[-1][0] == "pc":
                raise ViewError(d.first, f"#{d.name} in a TARGET_PC conditional (opened at line {stack[-1][2]}): "
                                         "the view cannot follow it; use #else, or a separate #if block")
            pc_test(d)
        elif d.name in ("else", "endif"):
            if not stack:
                raise ViewError(d.first, f"#{d.name} without #if")
            top = stack[-1]
            if top[0] == "pc":
                if d.words:
                    raise ViewError(d.first, f"text after #{d.name} of a TARGET_PC conditional: put it in a comment")
                if not d.at_line_start:
                    raise ViewError(d.first, "a TARGET_PC directive must start its line (a comment comes before #)")
                if d.name == "else":
                    if top[3]:
                        raise ViewError(d.first, f"a second #else in the TARGET_PC conditional of line {top[2]}")
                    top[1], top[3] = not top[1], True
                own = True
            if d.name == "endif":
                stack.pop()
        else:
            pc_test(d)
        dropped = True if own else not visible()
        fill(d.last + 1, dropped)
    if stack:
        raise ViewError(stack[-1][2] if stack[-1][0] == "pc" else len(lines), "a conditional is not closed by #endif")
    fill(len(lines) + 1, False)
    kept = [k for k in range(1, len(lines) + 1) if not drop[k]]
    return "".join(lines[k - 1] for k in kept).encode("latin-1"), kept


def line_changes(old: bytes, new: bytes) -> tuple[int, int]:
    """How many lines an edit adds and removes."""
    a, b = old.split(b"\n"), new.split(b"\n")
    added = removed = 0
    for tag, i1, i2, j1, j2 in difflib.SequenceMatcher(None, a, b, autojunk=False).get_opcodes():
        if tag != "equal":
            removed += i2 - i1
            added += j2 - j1
    return added, removed


# Headers that only the PC build reads, each with the file that includes it inside a TARGET_PC block: common.h
# includes port_decls.h as the last line of its TARGET_PC section. The N64 never reads such a header, so its N64 view
# is empty, whatever it holds; check 1 proves instead that the including file's PC view includes it and that no file's
# N64 view does.
PC_ONLY_HEADERS = {"include/port_decls.h": "include/common.h"}


def check_pc_only_header(rel: str) -> Result:
    """Check 1 for a PC-only header: the file that PC_ONLY_HEADERS names includes it inside a TARGET_PC block (an
    #include directive in its PC view, found the way a preprocessor finds directives, so not one inside a comment,
    and not inside any other conditional, such as #if 0, which the PC view keeps), and no file under src/ or include/
    includes it outside a TARGET_PC block. The including file has no include guard, so the directive must be outside
    every conditional of its PC view."""
    name = rel.rsplit("/", 1)[-1].encode()
    pattern = re.compile(rb'^[ \t]*#[ \t]*include[ \t]*["<]([^">]*/)?' + re.escape(name) + rb'[">]', re.M)
    includer = PC_ONLY_HEADERS[rel]
    try:
        pc_view, _ = n64_view((ROOT / includer).read_bytes(), pc=True)
    except (OSError, ViewError) as e:
        return Result(1, FAIL, f"{includer}: {e}")
    named = re.compile(r'["<]([^">]*/)?' + re.escape(name.decode()) + r'[">]')
    depth, found = 0, False  # depth: the other conditionals (not TARGET_PC ones) open around a directive
    for d in find_directives(pc_view.decode("latin-1")):
        if d.name in ("if", "ifdef", "ifndef"):
            depth += 1
        elif d.name == "endif":
            depth -= 1
        elif d.name == "include" and depth == 0 and named.search(d.shown):
            found = True
    if not found:
        return Result(1, FAIL, f"a PC-only header, but {includer} does not include it inside TARGET_PC, outside any "
                               "other conditional: the PC build might not read it")
    for path in sorted(list((ROOT / "src").rglob("*.[ch]")) + list((ROOT / "include").rglob("*.h"))):
        data = path.read_bytes()
        if name not in data:
            continue
        try:
            view, kept = n64_view(data)
        except ViewError as e:
            return Result(1, FAIL, f"{path.relative_to(ROOT)}, line {e.line}: {e.message}")
        m = pattern.search(view)
        if m:
            line = kept[view[:m.start()].count(b"\n")]
            return Result(1, FAIL, f"a PC-only header, but {path.relative_to(ROOT)}:{line} includes it outside "
                                   "TARGET_PC: the N64 build would read it")
    return Result(1, PASS, f"a PC-only header ({includer} includes it inside TARGET_PC): its N64 view is empty, and "
                           "no file includes it outside TARGET_PC")


def check_view(ctx: Context | None, rel: str, head: bytes | None, work: bytes | None) -> Result:
    """Check 1: the N64 view, then (with ctx, for a C file or a header) KMC GCC's own preprocessed text."""
    if work is None:
        return Result(1, FAIL, "the file is deleted, but HEAD has it: the N64 build would lose it")
    if rel in PC_ONLY_HEADERS:
        return check_pc_only_header(rel)
    try:
        view, kept = n64_view(work)
    except ViewError as e:
        return Result(1, FAIL, f"line {e.line}: {e.message}")
    if head is None:
        return Result(1, FAIL, "a new file: HEAD has no version of it to compare with; only build.py can prove it")
    try:
        head_view, head_kept = n64_view(head)
    except ViewError as e:
        return Result(1, FAIL, f"HEAD's version, line {e.line}: {e.message}")
    if view == head_view:
        if work == head:
            return Result(1, PASS, "the file is the same as HEAD's")
        added, removed = line_changes(head, work)
        what = f"the edit adds {added} and removes {removed} lines, all of them PC-only or TARGET_PC directives"
        if ctx is None or not rel.endswith((".c", ".h")):
            return Result(1, PASS, f"the N64 view equals HEAD's; {what}")
        problem = check_kmc_text(ctx, rel, head)
        if problem is not None:
            return problem
        return Result(1, PASS, f"the N64 view equals HEAD's, and so does KMC GCC's preprocessed text; {what}")
    a, b = head_view.decode("latin-1").split("\n"), view.decode("latin-1").split("\n")
    details, first = [], None
    for tag, i1, i2, j1, j2 in difflib.SequenceMatcher(None, a, b, autojunk=False).get_opcodes():
        if tag == "equal":
            continue
        at = kept[j1] if j1 < len(kept) else (kept[-1] + 1 if kept else 1)
        was = head_kept[i1] if i1 < len(head_kept) else (head_kept[-1] + 1 if head_kept else 1)
        if first is None:
            what = {"insert": f"added: {short(b[j1])!r}", "delete": f"removed: {short(a[i1])!r}",
                    "replace": f"changed: {short(b[j1])!r}, was {short(a[i1])!r}"}[tag]
            first = f"the N64 view differs from HEAD's at line {at} (HEAD's line {was}): an N64 line {what}"
        details += [f"HEAD's line {head_kept[i]}: - {a[i]}" for i in range(i1, i2) if i < len(head_kept)]
        details += [f"line {kept[j]}: + {b[j]}" for j in range(j1, j2) if j < len(kept)]
    return Result(1, FAIL, first, details)


# A line marker of the preprocessor's output: # 12 "src/main/x.c" (and flags), or #line 12 "..."
CPP_LINE_MARKER = re.compile(r'^#\s*(?:line\s+)?\d+\s+"')


def kmc_preprocess(ctx: Context, tree: Path, rel: str) -> tuple[list[str] | None, str]:
    """KMC GCC's preprocessed text of tree/rel as a list of words (its line markers dropped, spaces and line breaks
    reduced to word boundaries), and the preprocessor's messages; None when it stops with an error. The command is
    build.py's with -E in place of -c. A header is preprocessed through a small C file in the work folder that
    includes common.h and then the header."""
    command = ctx.kmc_command("work" if tree == ctx.work_tree else "head", rel) or \
        ctx.default_command["work" if tree == ctx.work_tree else "head"]
    src = rel
    if rel.endswith(".h"):
        src = f"build/port_check/{rel}.c"
        header = Path(rel).relative_to("include").as_posix()
        ctx.write(tree, src, f'#include "common.h"\n#include "{header}"\n'.encode())
    out = f"build/{rel}.i"
    (tree / out).parent.mkdir(parents=True, exist_ok=True)
    if (tree / out).exists():
        (tree / out).unlink()
    argv = ["-E" if a == "-c" else a.replace("{src}", src).replace("{obj}", out).replace("{include}", "include")
            for a in command]
    status, log = run(argv, cwd=tree, env=ctx.env)
    if status != 0 or not (tree / out).exists():
        return None, log or f"exit status {status}"
    text = (tree / out).read_bytes().decode("latin-1")
    return " ".join(line for line in text.split("\n") if not CPP_LINE_MARKER.match(line)).split(), log


def check_kmc_text(ctx: Context, rel: str, head: bytes) -> Result | None:
    """The second half of check 1: KMC GCC's preprocessor must read this version without an error and give the same
    words as for HEAD's version. Returns the failure, or None. The view above follows today's C rules, and the N64's
    preprocessor (GCC 2.7.2's) reads a few things differently: a quote that does not close on its line stops it even
    in a skipped block, and a directive inside the arguments of a macro call is not a directive to it."""
    if rel.startswith("src/"):
        ctx.write(ctx.head_tree, rel, head)
    new, new_log = kmc_preprocess(ctx, ctx.work_tree, rel)
    if new is None:
        lines = new_log.strip().splitlines()
        located = [x for x in lines if re.search(r":\d+: ", x)]
        first = next((x for x in located if ": warning: " not in x), located[0] if located else lines[0] if lines
                     else "")
        return Result(1, FAIL, f"KMC GCC's preprocessor stops on this version: {first.strip()}", lines)
    old, old_log = kmc_preprocess(ctx, ctx.head_tree, rel)
    if old is None:
        return Result(1, FAIL, "KMC GCC's preprocessor stops on HEAD's version", old_log.strip().splitlines())
    if new == old:
        return None
    k = next((k for k in range(min(len(new), len(old))) if new[k] != old[k]), min(len(new), len(old)))
    near = " ".join(new[max(0, k - 6):k + 6])
    was = " ".join(old[max(0, k - 6):k + 6])
    warnings = [x for x in new_log.strip().splitlines() if x.strip()]
    return Result(1, FAIL, f"the N64 view equals HEAD's, but KMC GCC's preprocessed text does not, at word {k + 1}: "
                           f"{short(near, 60)!r}, HEAD's {short(was, 60)!r}",
                  [f"this version: ... {near} ...", f"HEAD's: ... {was} ..."] + warnings)


# ---- Check 2: the N64 object --------------------------------------------------------------------------------------

class Section:
    """One section header of an ELF object."""

    def __init__(self, index: int, fields: tuple):
        self.index = index
        (self.name_off, self.type, self.flags, self.addr, self.offset, self.size, self.link, self.info, self.align,
         self.entsize) = fields
        self.name = ""


class Elf:
    """A 32-bit ELF object (the KMC GCC objects are big-endian MIPS), read as far as this tool compares it."""

    def __init__(self, data: bytes):
        if len(data) < 52 or data[:4] != b"\x7fELF" or data[4] != 1:
            raise ValueError("not a 32-bit ELF object")
        self.data = data
        self.order = e = ">" if data[5] == 2 else "<"
        self.shoff = struct.unpack_from(e + "I", data, 0x20)[0]
        self.shentsize, count, names = struct.unpack_from(e + "HHH", data, 0x2E)
        self.sections = [Section(i, struct.unpack_from(e + "10I", data, self.shoff + i * self.shentsize))
                         for i in range(count)]
        table = self.raw(self.sections[names]) if names < count else b""
        for s in self.sections:
            s.name = table[s.name_off:table.index(b"\0", s.name_off)].decode("latin-1") if table else ""
        self.symbols = []  # (name, value, size, type, bind, other, section index)
        for s in self.sections:
            if s.type == 2:  # SHT_SYMTAB
                strings = self.raw(self.sections[s.link])
                raw = self.raw(s)
                for k in range(0, len(raw) - 15, 16):
                    name, value, size, info, other, shndx = struct.unpack_from(e + "IIIBBH", raw, k)
                    text = strings[name:strings.index(b"\0", name)].decode("latin-1")
                    self.symbols.append((text, value, size, info & 0xF, info >> 4, other & 3, shndx))
        self.relocs = {}  # section index -> [(offset, type, symbol index, addend)]
        for s in self.sections:
            if s.type in (9, 4):  # SHT_REL, SHT_RELA
                raw, step = self.raw(s), 8 if s.type == 9 else 12
                out = self.relocs.setdefault(s.info, [])
                for k in range(0, len(raw) - step + 1, step):
                    offset, info = struct.unpack_from(e + "II", raw, k)
                    addend = struct.unpack_from(e + "i", raw, k + 8)[0] if step == 12 else None
                    out.append((offset, info & 0xFF, info >> 8, addend))

    def raw(self, s: Section) -> bytes:
        return b"" if s.type == 8 else self.data[s.offset:s.offset + s.size]  # (SHT_NOBITS has no bytes)

    def where(self, shndx: int) -> str:
        if shndx == 0:
            return "undefined"
        if shndx >= 0xFF00:
            return {0xFFF1: "absolute", 0xFFF2: "common"}.get(shndx, f"special 0x{shndx:X}")
        return self.sections[shndx].name if shndx < len(self.sections) else f"section {shndx}"

    def symbol_at(self, shndx: int, offset: int) -> str:
        """The function or label an offset in a section falls in, as name+0xNN."""
        best = None
        for name, value, size, kind, bind, other, sx in self.symbols:
            if sx == shndx and name and kind not in (3, 4) and value <= offset and (best is None or value >= best[1]):
                best = (name, value)
        return f"{best[0]}+0x{offset - best[1]:X}" if best else f"0x{offset:X}"


def rom_sections(elf: Elf) -> dict[str, Section]:
    """The object's sections that build.py's link can put into the ROM: loaded ones it does not throw away."""
    return {s.name: s for s in elf.sections
            if s.flags & 2 and not any(fnmatch.fnmatchcase(s.name, p) for p in DISCARDED)}  # SHF_ALLOC


def relocations(elf: Elf, s: Section) -> list[tuple]:
    """The relocations on a section as (offset, type, target, addend); the target is a symbol's name, or for a
    section symbol the section's name, so two objects can be compared by them."""
    got = []
    for offset, kind, sym, addend in elf.relocs.get(s.index, []):
        target = "?"
        if sym < len(elf.symbols):
            name, shndx = elf.symbols[sym][0], elf.symbols[sym][6]
            target = name if name else f"section {elf.where(shndx)}"
        got.append((offset, kind, target, addend))
    return got


def symbol_table(elf: Elf) -> list[tuple]:
    """Every symbol but the file and section ones, as (name, value, size, type, binding, visibility, section)."""
    return sorted((name, value, size, kind, bind, other, elf.where(shndx))
                  for name, value, size, kind, bind, other, shndx in elf.symbols[1:] if kind not in (3, 4))


def object_differences(old: bytes, new: bytes, old_name: str = "HEAD's") -> tuple[list[str], list[str]]:
    """How two MIPS objects differ in what reaches the ROM: the kept sections (kind, size, alignment, bytes), the
    relocations on them, and the symbols. Returns the differences, and the names of other sections that differ (which
    the link throws away). old_name names the first object in the messages."""
    a, b = Elf(old), Elf(new)
    sa, sb = rom_sections(a), rom_sections(b)
    out = []
    for name in sorted(set(sa) | set(sb)):
        x, y = sa.get(name), sb.get(name)
        if x is None or y is None:
            out.append(f"section {name} is only in {'this' if x is None else old_name} object")
            continue
        if (x.type, x.flags, x.size, x.align) != (y.type, y.flags, y.size, y.align):
            out.append(f"section {name}: size 0x{y.size:X} ({old_name} 0x{x.size:X}), type {y.type}/{x.type}, "
                       f"flags 0x{y.flags:X}/0x{x.flags:X}, alignment {y.align}/{x.align}")
        rx, ry = a.raw(x), b.raw(y)
        if rx != ry:
            at = next((k for k in range(min(len(rx), len(ry))) if rx[k] != ry[k]), min(len(rx), len(ry)))
            k = at - at % 4  # the word (a MIPS instruction) the first difference is in
            out.append(f"section {name} differs at {b.symbol_at(y.index, k)} (offset 0x{k:X}): word "
                       f"{ry[k:k + 4].hex() or '-'} where {old_name} object has {rx[k:k + 4].hex() or '-'}")
        la, lb = relocations(a, x), relocations(b, y)
        if la != lb:
            k = next((k for k in range(min(len(la), len(lb))) if la[k] != lb[k]), min(len(la), len(lb)))
            ra, rb = (la[k] if k < len(la) else None), (lb[k] if k < len(lb) else None)
            out.append(f"relocations of {name} differ: "
                       f"{f'type {rb[1]} to {rb[2]} at 0x{rb[0]:X}' if rb else 'none'} where {old_name} object has "
                       f"{f'type {ra[1]} to {ra[2]} at 0x{ra[0]:X}' if ra else 'none'}")
    ya, yb = symbol_table(a), symbol_table(b)
    for s in sorted(set(yb) - set(ya))[:3]:
        out.append(f"symbol {s[0]} (value 0x{s[1]:X}, size 0x{s[2]:X}, in {s[6]}) is not in {old_name} object")
    for s in sorted(set(ya) - set(yb))[:3]:
        out.append(f"symbol {s[0]} (value 0x{s[1]:X}, size 0x{s[2]:X}, in {s[6]}) of {old_name} object is missing")
    names_a, names_b = {s.name: s for s in a.sections}, {s.name: s for s in b.sections}
    other = sorted(n for n in set(names_a) | set(names_b) if n and n not in sa and n not in sb
                   and (n not in names_a or n not in names_b or a.raw(names_a[n]) != b.raw(names_b[n])))
    return out, other


MARKERS = ("gcc2_compiled.", "__gnu_compiled_c", "__gnu_compiled_cplusplus")


def function_extents(elf: Elf) -> dict[str, tuple[int, int, int]]:
    """name -> (section index, offset, size) of every function in an object: decompdecomp's _function_symbols
    (decompnet/elfobj.py), which build.py's trim uses, rewritten without pyelftools. A function is a symbol of type
    FUNC with a size; for old assemblers that write neither, a symbol in a code section runs to the next one, without
    the zero padding after it but with the delay slot of a last jump."""
    out: dict[str, tuple[int, int, int]] = {}
    loose: dict[int, list[tuple[int, str]]] = {}
    for name, value, size, kind, bind, other, shndx in elf.symbols:
        if not name or not (0 < shndx < 0xFF00) or kind in (3, 4):  # (section and file symbols)
            continue
        if kind == 2 and size > 0:  # STT_FUNC
            out[name] = (shndx, value, size)
        elif size == 0 and name not in MARKERS and name[0] not in ".$" and elf.sections[shndx].flags & 4:
            loose.setdefault(shndx, []).append((value, name))
    for shndx, syms in loose.items():
        section = elf.sections[shndx]
        data = elf.raw(section)
        starts = sorted({off for off, _ in syms} | {off for sx, off, _ in out.values() if sx == shndx})
        for off, name in syms:
            if name in out:
                continue
            nxt = next((x for x in starts if x > off), section.size)
            end = nxt
            while end - 4 >= off + 4 and data[end - 4:end] == b"\0\0\0\0":
                end -= 4
            if end < nxt and end - 4 >= off:  # keep the delay slot of a final jr or branch
                word = int.from_bytes(data[end - 4:end], "big" if elf.order == ">" else "little")
                if word == 0x03E00008 or (word >> 26) in (1, 2, 3, 4, 5, 6, 7) or (word & 0xFC00003F) == 8:
                    end += 4
            if end > off:
                out[name] = (shndx, off, end - off)
    return out


def build_trim(data: bytes) -> tuple[bytes, list[str]]:
    """The object as build.py's trim() leaves it, and what it cut. Old assemblers pad a code section to 16 bytes;
    build.py shrinks the section to where its last function ends when everything after that is zero (nops) and no
    relocation points there, because each function is placed at its own address and the padding would run into the
    next one."""
    elf = Elf(data)
    ends: dict[int, int] = {}
    for shndx, off, size in function_extents(elf).values():
        ends[shndx] = max(ends.get(shndx, 0), off + size)
    out, cut = bytearray(data), []
    for shndx, end in ends.items():
        section = elf.sections[shndx]
        tail = elf.raw(section)[end:]
        relocated = any(r[0] >= end for r in elf.relocs.get(shndx, []))
        if end < section.size and not tail.strip(b"\0") and not relocated:
            struct.pack_into(elf.order + "I", out, elf.shoff + shndx * elf.shentsize + 20, end)
            cut.append(f"{section.name} 0x{section.size:X} -> 0x{end:X} ({len(tail)} zero bytes)")
    return bytes(out), cut


def decompdecomp_python() -> str | None:
    """The Python that decompdecomp is installed in, found as build.py finds it (decompdecomps_python there): the one
    the `decomp` command starts, else where `uv tool install` puts it."""
    command = shutil.which("decomp") or next((str(p) for p in (Path.home() / ".local/bin/decomp",) if p.exists()),
                                             None)
    try:
        text = Path(command).read_text(encoding="utf-8", errors="replace")[:4096] if command else ""
    except OSError:
        text = ""
    found = re.search(r"^#!\s*(\S*python[\d.]*)\s*$", text, re.M) or re.search(r"(/\S+/python[\d.]*)\b", text)
    if found and Path(found.group(1)).exists():
        return found.group(1)
    fallback = Path.home() / ".local/share/uv/tools/decompnet/bin/python"
    return str(fallback) if fallback.exists() else None


# Asks decompdecomp for the compile command build.py would use for a function at each address: compiler_for picks
# build.json's compiler or a compiler_ranges entry, compiler_config turns it into the command (build_objects in
# build.py does the same).
KMC_HELPER = """
import json, sys
from pathlib import Path
from decompnet.project import compiler_config, compiler_for
root, config = Path(sys.argv[1]), json.loads(Path(sys.argv[2]).read_text(encoding="utf-8"))
print(json.dumps([compiler_config(root, {"compiler": compiler_for(config, v)}).cmd for v in json.loads(sys.argv[3])]))
"""


def build_addresses(config: dict, exists) -> dict[str, int]:
    """build.py's vram_of: for each C file build.py compiles, the address its compiler is chosen by (the last function
    the file holds, as build.py's dictionary keeps it). exists(path) says whether the file is there."""
    out = {}
    for fn in config["functions"]:
        path = fn.get("c") or f"src/{fn['seg']}/{fn['name']}.c"
        if exists(path):
            out[path] = fn["vram"]
    return out


def kmc_commands(config_path: Path, addresses: list[int | None]) -> dict[int | None, list[str]]:
    """The compile command (with build.py's {src}, {obj} and {include} placeholders) for each address; for None,
    build.json's own compiler, which every address outside its compiler_ranges gets."""
    python = decompdecomp_python()
    if not python:
        raise CannotRun("check 2 needs decompdecomp (its KMC GCC and its Python, which build.py also runs with); "
                        "it is not installed")
    status, out = run([python, "-I", "-B", "-c", KMC_HELPER, str(ROOT), str(config_path), json.dumps(addresses)],
                      cwd=ROOT)
    if status != 0:
        raise CannotRun(f"decompdecomp could not give the KMC GCC command:\n{out.strip()}")
    commands = json.loads(out.strip().splitlines()[-1])
    for cmd in commands:
        if not Path(cmd[0]).exists():
            raise CannotRun(f"the N64 compiler {cmd[0]} is missing; build.py installs it (decompdecomp's toolchain)")
    return dict(zip(addresses, commands))


def kmc_compile(ctx: Context, tree: Path, rel: str, command: list[str]) -> tuple[bytes | None, str]:
    """Compiles tree/rel exactly as build.py does: the same command, run from the top of the tree, with the same
    relative names (src/<folder>/<name>.c, -Iinclude, build/src/<folder>/<name>.o), so the object names the same
    source file."""
    obj = f"build/{Path(rel).with_suffix('.o').as_posix()}"
    (tree / obj).parent.mkdir(parents=True, exist_ok=True)
    if (tree / obj).exists():
        (tree / obj).unlink()
    argv = [a.replace("{src}", rel).replace("{obj}", obj).replace("{include}", "include") for a in command]
    status, out = run(argv, cwd=tree, env=ctx.env)
    if status != 0 or not (tree / obj).exists():
        return None, out or f"exit status {status}"
    return (tree / obj).read_bytes(), out


def check_object(ctx: Context, rel: str, head: bytes | None, work: bytes | None) -> Result:
    work_cmd = ctx.kmc_command("work", rel)
    if ctx.against_build:
        return against_build(ctx, rel, work, work_cmd)
    head_cmd = ctx.kmc_command("head", rel) if head is not None else None
    if work_cmd is None and head_cmd is None:
        return Result(2, NA, "build.py does not compile this file (no function in build.json names it)")
    if work is None:
        return Result(2, FAIL, "the file is deleted, but build.py compiled it at HEAD")
    if work_cmd is None:
        return Result(2, FAIL, "build.py compiled this file at HEAD but would not now (build.json changed)")
    if head_cmd is None:
        return Result(2, FAIL, "build.py would compile this file, but HEAD has no version of it to compare with")
    if work == head and not ctx.include_changed and work_cmd == head_cmd:
        return Result(2, PASS, "the file, include/ and the compile command are the same as HEAD's")
    ctx.write(ctx.head_tree, rel, head)
    old, old_log = kmc_compile(ctx, ctx.head_tree, rel, head_cmd)
    new, new_log = kmc_compile(ctx, ctx.work_tree, rel, work_cmd)
    if new is None:
        return Result(2, FAIL, "KMC GCC cannot compile this version", new_log.strip().splitlines())
    if old is None:
        return Result(2, FAIL, "KMC GCC cannot compile HEAD's version", old_log.strip().splitlines())
    if old == new:
        return Result(2, PASS, "the object is the same as HEAD's, byte for byte")
    diffs, other = object_differences(old, new)
    if diffs:
        return Result(2, FAIL, diffs[0], diffs)
    return Result(2, PASS, "same code, relocations, data and symbols as HEAD's object (the objects differ only in "
                           f"{', '.join(other) or 'their layout'}, which the link throws away)")


def against_build(ctx: Context, rel: str, work: bytes | None, cmd: list[str] | None) -> Result:
    """--against-build: the object check 2 compiles, against the one build.py made in build/."""
    if work is None or cmd is None:
        return Result(2, NA, "build.py does not compile this file" if work is not None else "the file is deleted")
    built = ROOT / "build" / Path(rel).with_suffix(".o")
    if not built.exists():
        return Result(2, FAIL, f"{built.relative_to(ROOT)} is missing: build.py has not built it")
    new, log = kmc_compile(ctx, ctx.work_tree, rel, cmd)
    if new is None:
        return Result(2, FAIL, "KMC GCC cannot compile this file", log.strip().splitlines())
    trimmed, cut = build_trim(new)
    what = f"build.py's trim cut {'; '.join(cut)}" if cut else "build.py's trim cuts nothing here"
    if trimmed == built.read_bytes():
        return Result(2, PASS, f"the same as {built.relative_to(ROOT)} byte for byte once {what}")
    stale = " (build/'s object is older than the file: build.py has not run since it changed)" \
        if built.stat().st_mtime < (ROOT / rel).stat().st_mtime else ""
    diffs, other = object_differences(built.read_bytes(), trimmed, "build/'s")
    return Result(2, FAIL, f"differs from {built.relative_to(ROOT)}{stale}: "
                           f"{diffs[0] if diffs else 'in ' + ', '.join(other)}", diffs + other)


# ---- Check 3: the PC compile --------------------------------------------------------------------------------------

MESSAGE = re.compile(r"^(?P<file>[^:\n]+?)(?::(?P<line>\d+))?(?::(?P<col>\d+))?: "
                     r"(?P<kind>(?i:warning|error|fatal error)): (?P<text>.*)$", re.M)


def messages(output: str) -> list[tuple[str, int, str, str]]:
    """The errors and warnings in a compiler's output: (file, line, 'error' or 'warning', text). Notes and the
    "In function" lines are left out."""
    out = []
    for m in MESSAGE.finditer(output):
        kind = "warning" if m.group("kind").lower() == "warning" else "error"
        out.append((m.group("file"), int(m.group("line") or 0), kind, m.group("text")))
    return out


def pc_compile(ctx: Context, cc: str, tree: Path, rel: str, warnings: bool, tag: str) -> tuple[int | None, str]:
    """One real compile (-c) of tree/rel with the port's flags, into the work folder. warnings: the -Wall -Wextra
    compile, with the errors turned back into warnings (DEMOTE_FLAGS)."""
    extra = ["-Wall", "-Wextra", *DEMOTE_FLAGS[cc]] if warnings else []
    obj = ctx.tmp / "pc" / cc / f"{rel}.{tag}.o"
    obj.parent.mkdir(parents=True, exist_ok=True)
    status, out = run([ctx.cc[cc], *PC_FLAGS, *MESSAGE_FLAGS[cc], *extra, "-c", rel, "-o", str(obj)], cwd=tree,
                      env=ctx.env)
    obj.with_suffix(".txt").write_text(out, encoding="utf-8")  # the compiler's messages, for --keep
    return status, out


def message_keys(found: list[tuple[str, int, str, str]], tree: Path, wanted: str = "warning",
                 bare: bool = False) -> collections.Counter:
    """Messages of one kind as keys that do not depend on line numbers, which an edit shifts: the file, the message
    and the text of the line it points at. bare: without the option at the end ([-Wint-conversion]), which differs
    between an error and the same message turned back into a warning."""
    texts: dict[str, list[str]] = {}
    keys = collections.Counter()
    for file, line, kind, text in found:
        if kind != wanted:
            continue
        if bare:
            text = re.sub(r"\s*\[-W[^\]]*\]$", "", text)
        if file not in texts:
            try:
                texts[file] = (tree / file).read_bytes().decode("latin-1").split("\n")
            except OSError:
                texts[file] = []
        src = texts[file][line - 1].strip() if 0 < line <= len(texts[file]) else ""
        keys[(file, text, src)] += 1
    return keys


def check_pc(ctx: Context, rel: str, head: bytes | None, work: bytes | None) -> Result:
    if work is None:
        return Result(3, NA, "the file is deleted")
    stats, details, problems, error_keys = {}, [], [], {}
    for cc in COMPILERS:
        status, out = pc_compile(ctx, cc, ctx.work_tree, rel, False, "port")
        errors = [m for m in messages(out) if m[2] == "error"]
        error_keys[cc] = message_keys(errors, ctx.work_tree, "error", bare=True)
        stats[f"{cc}_errors"] = len(errors)
        stats[f"{cc}_failed"] = status != 0 or bool(errors)
        if errors:
            problems.append(f"{cc} {plural(len(errors), 'error')}")
            details += [f"{cc}: {f}:{ln}: {t}" for f, ln, k, t in errors]
        elif status != 0:
            problems.append(f"{cc} exit status {status}")
            details += [f"{cc}: {line}" for line in out.strip().splitlines()[-10:]]
    same = head is not None and head == work and not ctx.include_changed
    if head is not None and not same:
        ctx.write(ctx.head_tree, rel, head)
    new_total, note_total, counts = 0, 0, []
    for cc in COMPILERS:
        _, out = pc_compile(ctx, cc, ctx.work_tree, rel, True, "wall")
        now = message_keys(messages(out), ctx.work_tree)
        stats[f"{cc}_warnings"] = sum(now.values())
        notes = collections.Counter()
        if same:
            new = collections.Counter()
        else:
            before, head_broken = collections.Counter(), False
            if head is not None:
                _, old_out = pc_compile(ctx, cc, ctx.head_tree, rel, True, "head-wall")
                before = message_keys(messages(old_out), ctx.head_tree)
                head_broken = any(kind == "error" for _, _, kind, _ in messages(old_out))
            new = now - before
            # an error of the port's compile comes back here as a warning (DEMOTE_FLAGS): it is counted once, above
            demoted = error_keys[cc].copy()
            for key in list(new):
                bare = (key[0], re.sub(r"\s*\[-W[^\]]*\]$", "", key[1]), key[2])
                gone = min(new[key], demoted[bare])
                new[key] -= gone
                demoted[bare] -= gone
            new += collections.Counter()  # (drops the keys counted down to 0)
            if head_broken:
                # HEAD's version still has errors in this compile, and a compiler that meets an error skips some of
                # its later warnings (clang drops -Wreturn-type and the uninitialised-variable warnings, for example).
                # A new warning on a line that HEAD's version also has may be one of those, so it is a note.
                old_lines = {}
                for key in list(new):
                    if key[0] not in old_lines:
                        try:
                            old_lines[key[0]] = {x.strip() for x in
                                                 (ctx.head_tree / key[0]).read_bytes().decode("latin-1").split("\n")}
                        except OSError:
                            old_lines[key[0]] = set()
                    if key[2] in old_lines[key[0]]:
                        notes[key] = new.pop(key)
        stats[f"{cc}_new"] = sum(new.values())
        new_total += sum(new.values())
        note_total += sum(notes.values())
        counts.append(f"{cc} {sum(now.values())}")
        details += [f"{cc}: new warning: {f}: {t} (at: {short(src, 60)})" for (f, t, src), k in sorted(new.items())]
        details += [f"{cc}: note: a warning HEAD's version could not show, on a line it also has: {f}: {t} "
                    f"(at: {short(src, 60)})" for (f, t, src), k in sorted(notes.items())]
    stats["notes"] = note_total
    if new_total:
        problems.append(f"{plural(new_total, 'new warning')} under -Wall -Wextra")
    if problems:
        return Result(3, FAIL, "; ".join(problems), details, stats)
    why = "the file and include/ are the same as HEAD's" if same else \
        "none that HEAD's version lacks" if head is not None else "a new file"
    noted = f"; {plural(note_total, 'note')}: warnings on lines HEAD's version also has, which its compile could not " \
            "show because it has errors (-v lists them)" if note_total else ""
    return Result(3, PASS, f"0 errors with gcc and clang; -Wall -Wextra warnings: {', '.join(counts)}, {why}{noted}",
                  details, stats)


# ---- Check 4: no asm ----------------------------------------------------------------------------------------------

LINE_MARKER = re.compile(r'#\s*(?:line\s+)?(\d+)\s+"((?:[^"\\]|\\.)*)"')
TOKEN = re.compile(r'"(?:[^"\\\n]|\\.)*"?|\'(?:[^\'\\\n]|\\.)*\'?|[A-Za-z_]\w*')


def asm_uses(text: str) -> list[tuple[str, int, str]]:
    """Where asm, __asm__ or __asm appears in a compiler's -E output, outside quotes: (file, line, word), for the
    decomp's own files (the C file and include/; their names are relative). System headers, which the compiler names
    by absolute paths, are left out: the C library uses __asm__ to name symbols in declarations, which is not code."""
    hits, where, line = [], "", 0
    for raw in text.split("\n"):
        if raw.startswith("#"):
            m = LINE_MARKER.match(raw)
            if m:
                where, line = m.group(2), int(m.group(1))
                continue
        elif "asm" in raw and where and not os.path.isabs(where) and not where.startswith("<"):
            hits += [(where, line, tok) for tok in TOKEN.findall(raw) if tok in ASM_WORDS]
        line += 1
    return hits


def check_asm(ctx: Context, rel: str, work: bytes | None) -> Result:
    if work is None:
        return Result(4, NA, "the file is deleted")
    hits = set()
    for cc in COMPILERS:
        out = ctx.tmp / "pc" / cc / f"{rel}.i"
        out.parent.mkdir(parents=True, exist_ok=True)
        status, log = run([ctx.cc[cc], *PC_FLAGS, *MESSAGE_FLAGS[cc], "-E", rel, "-o", str(out)], cwd=ctx.work_tree,
                          env=ctx.env)
        if status != 0:
            return Result(4, FAIL, f"{cc} -E cannot preprocess the file", log.strip().splitlines())
        hits.update(asm_uses(out.read_bytes().decode("latin-1")))
    if hits:
        found = sorted(hits, key=lambda h: (h[0], h[1]))
        first = found[0]
        more = f" and {len(found) - 1} more" if len(found) > 1 else ""
        return Result(4, FAIL, f"{first[2]} at {first[0]}:{first[1]}{more}",
                      [f"{w} at {f}:{n}" for f, n, w in found], {"asm": len(found)})
    return Result(4, PASS, "no asm, __asm__ or __asm in the preprocessed PC text (gcc -E, clang -E)")


# ---- Running the checks -------------------------------------------------------------------------------------------

class Context:
    """What every file's checks share: the work folder with the two trees (this version's and HEAD's files under the
    same relative names, so both compile alike), HEAD, the compilers and the KMC GCC commands."""

    def __init__(self, tmp: Path, head: Head, checks: set, against_build: bool, gcc: str, clang: str):
        self.tmp, self.head, self.checks, self.against_build = tmp, head, checks, against_build
        self.work_tree, self.head_tree = tmp / "work", tmp / "head"
        self.cc = {"gcc": gcc, "clang": clang}
        (tmp / "t").mkdir(parents=True, exist_ok=True)
        # English messages with plain quotes; the compilers' temporary files go to the work folder
        self.env = dict(os.environ, LC_ALL="C", TMPDIR=str(tmp / "t"))
        self.include_changed = False
        self.commands = {"work": {}, "head": {}}  # tree -> C file -> KMC command
        self.default_command = {"work": [], "head": []}  # tree -> build.json's own KMC command (headers, check 1)

    def write(self, tree: Path, rel: str, data: bytes) -> None:
        path = tree / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        if not path.exists() or path.read_bytes() != data:
            path.write_bytes(data)

    def kmc_command(self, tree: str, rel: str) -> list[str] | None:
        return self.commands[tree].get(rel)


def tool_version(cc: str, exe: str) -> str:
    status, out = run([exe, "--version"], cwd=ROOT)
    if status != 0:
        raise CannotRun(f"checks 3 and 4 need {cc}: {out.strip() or exe + ' does not run'}")
    m = re.search(r"\b(\d+\.\d+(?:\.\d+)?)\b", out.splitlines()[0] if out else "")
    return f"{cc} {m.group(1) if m else '?'}"


def prepare(ctx: Context, files: list[str]) -> None:
    """Fills the two trees' include/ folders, notes whether include/ changed since HEAD, and gets build.py's KMC GCC
    command for each C file (checks 1 and 2), and build.json's own command for a header (check 1)."""
    head, work_tree, head_tree = ctx.head, ctx.work_tree, ctx.head_tree
    head_include = [p for p in head.blob if p.startswith("include/")]
    head.load(head_include + files + ["build.json"])
    shutil.copytree(ROOT / "include", work_tree / "include")
    for p in head_include:
        ctx.write(head_tree, p, head.get(p))
    work_include = sorted(p.relative_to(ROOT).as_posix() for p in (ROOT / "include").rglob("*") if p.is_file())
    ctx.include_changed = work_include != sorted(head_include) or any(
        (ROOT / p).read_bytes() != head.get(p) for p in work_include)
    # Check 1 needs KMC GCC only for a file that differs from HEAD's version (a C file or a header), check 2 for every
    # C file.
    differs = [f for f in files if f.endswith((".c", ".h")) and (ROOT / f).is_file() and head.get(f) is not None
               and (ROOT / f).read_bytes() != head.get(f)]
    if not (2 in ctx.checks or (1 in ctx.checks and differs)):
        return
    c_files = [f for f in files if f.startswith("src/") and f.endswith(".c")]
    try:
        work_config = json.loads((ROOT / "build.json").read_text(encoding="utf-8"))
        head_config = json.loads(head.get("build.json").decode("utf-8")) if head.get("build.json") else None
    except (OSError, ValueError) as e:
        raise CannotRun(f"checks 1 and 2 need build.json, which cannot be read: {e}") from None
    trees = {"work": (ROOT / "build.json", build_addresses(work_config, lambda p: (ROOT / p).exists()))}
    if not ctx.against_build and head_config is not None:
        ctx.write(head_tree, "build.json", head.get("build.json"))
        trees["head"] = (head_tree / "build.json", build_addresses(head_config, lambda p: p in head.blob))
    for tree, (config, addresses) in trees.items():
        wanted = sorted({addresses[f] for f in c_files if f in addresses})
        if not wanted and not (1 in ctx.checks and differs):
            continue
        commands = kmc_commands(config, wanted + [None])  # None: build.json's own compiler, for check 1's headers
        ctx.commands[tree] = {f: commands[addresses[f]] for f in c_files if f in addresses}
        ctx.default_command[tree] = commands[None]


def check_file(ctx: Context, rel: str) -> list[Result]:
    """Every check asked for, on one file."""
    try:
        work = (ROOT / rel).read_bytes()
    except FileNotFoundError:
        work = None
    head = ctx.head.get(rel)
    if work is not None:
        ctx.write(ctx.work_tree, rel, work)
    is_c = rel.startswith("src/") and rel.endswith(".c")
    why = "a header: the C files that include it are compiled (--set match), not the header alone" \
        if rel.endswith(".h") else "not a C file"
    results = []
    if 1 in ctx.checks:
        results.append(check_view(ctx, rel, head, work))
    if 2 in ctx.checks:
        results.append(check_object(ctx, rel, head, work) if is_c else
                       Result(2, NA, "a header: check 1 is its N64 check" if rel.endswith(".h") else why))
    if 3 in ctx.checks:
        results.append(check_pc(ctx, rel, head, work) if is_c else Result(3, NA, why))
    if 4 in ctx.checks:
        results.append(check_asm(ctx, rel, work) if is_c else Result(4, NA, why))
    return results


def tree_path(arg: str, head: Head) -> str:
    """A file argument as a path relative to the source folder; it must lie under src/ or include/."""
    p = Path(arg)
    for candidate in ([p] if p.is_absolute() else [Path.cwd() / p, ROOT / p]):
        try:
            rel = candidate.resolve().relative_to(ROOT).as_posix()
        except ValueError:
            continue
        if rel.split("/")[0] in ("src", "include") and ((ROOT / rel).is_file() or rel in head.blob):
            return rel
    raise CannotRun(f"{arg}: not a file under {ROOT / 'src'} or {ROOT / 'include'} (now or at HEAD)")


def match_set(files_from: str | None) -> list[str]:
    """The developer program's files: the --files-from list, else what tools/port_filelist.py --set match prints."""
    if files_from:
        return read_list(files_from)
    script = ROOT / "tools" / "port_filelist.py"
    if not script.exists():
        raise CannotRun("--set match needs tools/port_filelist.py, which is not there yet: give the list with "
                        "--files-from LIST")
    res = subprocess.run([sys.executable, "-B", str(script), "--set", "match"], cwd=ROOT, capture_output=True)
    if res.returncode != 0:
        raise CannotRun(f"tools/port_filelist.py --set match failed (exit status {res.returncode}):\n"
                        f"{res.stderr.decode('utf-8', 'replace').strip()}")
    return [line.strip() for line in res.stdout.decode("utf-8").splitlines() if line.strip()]


def read_list(path: str) -> list[str]:
    try:
        text = Path(path).read_text(encoding="utf-8")
    except OSError as e:
        raise CannotRun(f"{path}: {e.strerror}") from None
    return [line.strip() for line in text.splitlines() if line.strip() and not line.lstrip().startswith("#")]


def summary(results: dict[str, list[Result]], checks: list[int]) -> list[str]:
    """One line per check: how many files passed, failed or had nothing to check, and for checks 3 and 4 the totals
    of errors, warnings and asm."""
    lines = []
    for n in checks:
        got = [r for rs in results.values() for r in rs if r.check == n]
        count = collections.Counter(r.status for r in got)
        text = ", ".join(f"{count[s]} {s}" for s in (PASS, FAIL, NA) if count[s])
        if n == 3 and any(r.status != NA for r in got):
            parts = []
            for cc in COMPILERS:
                errors = sum(r.stats.get(f"{cc}_errors", 0) for r in got)
                failed = sum(1 for r in got if r.stats.get(f"{cc}_failed"))
                parts.append(f"{cc} {plural(errors, 'error')} in {plural(failed, 'file')}")
            new = sum(r.stats.get(f"{cc}_new", 0) for r in got for cc in COMPILERS)
            warned = ", ".join(f"{cc} {sum(r.stats.get(f'{cc}_warnings', 0) for r in got)}" for cc in COMPILERS)
            text += f"; {', '.join(parts)}; {plural(new, 'new warning')}; -Wall -Wextra warnings in all: {warned}"
        if n == 4:
            bad = [f for f, rs in results.items() for r in rs if r.check == 4 and r.status == FAIL]
            if bad:
                text += ": " + ", ".join(bad[:10]) + (f" and {len(bad) - 10} more" if len(bad) > 10 else "")
        lines.append(f"  check {n} {CHECK_NAMES[n]:<10} {text}")
    return lines


def stop(signum, frame) -> None:
    """Stopped from outside (kill, a timeout): leave the way Ctrl-C does, so the temporary folder is still deleted."""
    raise KeyboardInterrupt


def main(argv: list[str] | None = None) -> int:
    ap = argparse.ArgumentParser(prog="port_check.py", description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("files", nargs="*", help="files under src/ or include/")
    ap.add_argument("--changed", action="store_true", help="every file under src/ or include/ changed against HEAD")
    ap.add_argument("--set", choices=["match"], help="checks 3 and 4 for every file of the developer program")
    ap.add_argument("--files-from", metavar="LIST", help="the files named in LIST, one path per line")
    ap.add_argument("--against-build", action="store_true", help="compare check 2's objects with build/'s")
    ap.add_argument("-j", "--jobs", type=int, default=1, metavar="N", help="files checked at a time (default 1)")
    ap.add_argument("-v", "--verbose", action="store_true", help="print the details of failed checks")
    ap.add_argument("--keep", metavar="DIR", help="keep the work files in DIR (outside the source tree)")
    ap.add_argument("--gcc", default="gcc", help="the gcc to use (default: gcc)")
    ap.add_argument("--clang", default="clang", help="the clang to use (default: clang)")
    a = ap.parse_args(argv)
    sources = sum(bool(x) for x in (a.files, a.changed, a.set, a.files_from and not a.set))
    if sources != 1:
        ap.error("give files, or one of --changed, --set match, --files-from LIST")
    if a.set and a.against_build:
        ap.error("--against-build compares check 2's objects; --set match runs checks 3 and 4 only")
    if a.jobs < 1:
        ap.error("-j needs a number of 1 or more")
    signal.signal(signal.SIGTERM, stop)
    try:
        return check_all(a)
    except CannotRun as e:
        print(f"port_check: cannot run: {e}", file=sys.stderr)
    except KeyboardInterrupt:
        print("port_check: stopped before it finished", file=sys.stderr)
    except Exception:  # a fault in this tool: exit status 2, not the 1 of a failed check
        traceback.print_exc()
        print("port_check: cannot run: the error above is a fault in port_check.py itself", file=sys.stderr)
    return 2


def check_all(a: argparse.Namespace) -> int:
    """Chooses the files and the checks, then runs them in a temporary folder (or the --keep folder)."""
    head = Head()
    if a.set:
        names, checks = match_set(a.files_from), [3, 4]
    else:
        names = changed_files() if a.changed else read_list(a.files_from) if a.files_from else a.files
        checks = [2] if a.against_build else [1, 2, 3, 4]
    files = list(dict.fromkeys(tree_path(f, head) for f in names))
    if not files:
        print("port_check: no files to check" + (": nothing under src/ or include/ differs from HEAD" if a.changed
                                                  else ": the list is empty"))
        return 0
    if (3 in checks or 4 in checks) and any(f.startswith("src/") and f.endswith(".c") for f in files):
        versions = [tool_version(cc, exe) for cc, exe in (("gcc", a.gcc), ("clang", a.clang))]
    else:
        versions = []  # (checks 3 and 4 have no C file to compile)
    if a.keep:
        tmp = Path(a.keep).resolve()
        if tmp == ROOT or ROOT in tmp.parents:
            raise CannotRun(f"--keep {a.keep}: the folder must be outside the source tree {ROOT}")
        if tmp.exists() and any(tmp.iterdir()):
            raise CannotRun(f"--keep {a.keep}: the folder must be new or empty")
        tmp.mkdir(parents=True, exist_ok=True)
        return check_in(a, head, files, checks, versions, tmp)
    with tempfile.TemporaryDirectory(prefix="port_check-") as folder:
        return check_in(a, head, files, checks, versions, Path(folder))


def check_in(a: argparse.Namespace, head: Head, files: list[str], checks: list[int], versions: list[str],
             tmp: Path) -> int:
    """Runs the checks with tmp as the work folder, prints a line per file and check and the summary, and returns the
    exit status."""
    ctx = Context(tmp, head, set(checks), a.against_build, a.gcc, a.clang)
    prepare(ctx, files)
    what = "check 2 against build/" if a.against_build else \
        "checks " + " and ".join(str(n) for n in checks) if len(checks) < 4 else "checks 1 to 4"
    tools = f" ({', '.join(versions)})" if versions else ""
    print(f"port_check: {plural(len(files), 'file')}, {what}, against HEAD {head.commit}{tools}"
          f"{'; include/ differs from HEAD' if ctx.include_changed else ''}", flush=True)
    results: dict[str, list[Result]] = {}
    pool = concurrent.futures.ThreadPoolExecutor(max_workers=a.jobs)
    futures = [(rel, pool.submit(check_file, ctx, rel)) for rel in files]
    try:
        for rel, future in futures:  # printed in the order given, each file as soon as it and those before are done
            results[rel] = future.result()
            for r in results[rel]:
                print(f"{r.status:<4} {r.check} {CHECK_NAMES[r.check]:<10} {rel}: {r.text}")
                if a.verbose and (r.status == FAIL or r.stats.get("notes")):
                    for line in r.details[:MAX_DETAILS]:
                        print(f"       {line}")
                    if len(r.details) > MAX_DETAILS:
                        print(f"       ... and {len(r.details) - MAX_DETAILS} more lines (--keep DIR keeps the logs)")
            sys.stdout.flush()
    finally:  # when stopped: the files not started yet are dropped, the ones running finish (a few compiles each)
        for _, future in futures:
            future.cancel()
        pool.shutdown(wait=True)
    failed = sum(1 for rs in results.values() for r in rs if r.status == FAIL)
    print(f"summary: {plural(len(files), 'file')}")
    print("\n".join(summary(results, checks)))
    if failed:
        print(f"result: {plural(failed, 'check')} failed")
    else:
        print("result: every check passed")
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
