"""Lists the decompilation's C files that the PC port's developer program compiles.

    cd source
    python3 tools/port_filelist.py --set match                   the files, one per line, sorted
    python3 tools/port_filelist.py --explain src/main/bcopy.c    how the walk reached one file
    python3 tools/port_filelist.py --surface                     what the listed files use outside the list
    python3 tools/port_filelist.py --self-test                   the negative controls, on copies of the inputs
    python3 tools/port_filelist.py --set match --output FILE --depends FILE      (for a build system)

Turnbuckle Dive, the PC port, compiles the game's own C from this decompilation's src/. Its developer program, which a
developer switch starts straight into a match (overlay 2) without the menus (overlay 1), needs only the files its
start-up reaches. This tool finds them: it starts from the functions the program calls itself (the roots, in SETS
below) and follows every name a file uses to the file that defines it, file by file. It prints the files as paths
relative to the decompilation (src/main/bcopy.c), and a summary on standard error.

How it works:
1. It reads every C file of src/ as the port's compiler sees it: with TARGET_PC, NON_MATCHING, AVOID_UB and
   F3DEX_GBI_2 defined and the macros of include/ expanded. For each function it notes the names that the function
   uses but does not declare itself: the functions it calls or takes the address of, the variables it reads or writes.
2. It finds what each name is: a function of a C file (a static one only for its own file), an old name of a function
   (a build.json symbol at a function's address), a variable (a build.json symbol, a label in asm/data/ or a C
   definition), or a function the port supplies (declared in include/port.h). A name that is none of these is an
   error: the tool names the file and line that use it, still prints the list it found, and exits with 1, because
   the list may be missing a function.
3. Data can hold function addresses: the .word entries of main's data in asm/data/, and every word of overlay 2's data
   (assets/D5FB0.bin) that is the address where a function starts. Each such word belongs to the label it lies in (an
   asm/data label in main, a build.json symbol in overlay 2's data), and a file that uses the label reaches every
   function in its data. In overlay 2's data a run of function addresses that goes on past the next label is an error,
   because a label inside a table would cut it in two.
4. The walk does not go into code the port replaces: the Nintendo SDK apart from the parts KEEP_SDK_LIBRARIES and
   KEEP_SDK_FUNCTIONS keep, and the game files in REPLACED_GAME_FILES. --surface lists the names the listed files use
   there, which the port must supply. A listed file that uses overlay 1 is an error.
5. It checks its inputs: build/game.ld (which build.py writes from build.json) must define the same symbols as
   build.json and place each C object at its function's address; each row of the table in docs/sdk_functions.md must
   name a function of main at its address; and every name in the port's choices below must be one the decompilation
   has.

Needs Python 3.8 or later and a decompilation that has been set up: build.py's first run extracts asm/data/ and
assets/ from your ROM (splat) and writes build/game.ld (without it the tool goes by build.json alone). The tool only
reads the decompilation. It writes nothing but the files named by --output and --depends, which must lie outside the
decompilation, and those only when the list is complete; --self-test works in a temporary folder.

Exit status:
    0  the list is complete: every name was found and the inputs agree
       (--explain: and the file was reached; --self-test: every control behaved as expected)
    1  a name could not be found, or a listed file uses overlay 1, so the list may be short
       (--explain: also when the file was not reached; --self-test: a control did not behave as expected)
    2  the inputs are missing or disagree, for example build/game.ld does not match build.json, a label splits a table
       of function addresses or a name in the port's choices is not in the decompilation; also a wrong command line,
       and a fault in this tool (--self-test: the tool cannot run on the decompilation itself)
"""
from __future__ import annotations

import argparse
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
from collections import defaultdict, deque
from dataclasses import dataclass, field
from pathlib import Path
from typing import Callable

# =====================================================================================================================
# The port's choices: which program, where it starts, and which code the port replaces with its own. Everything else
# the tool works out from the decompilation's own files.
# =====================================================================================================================

# The macros the port defines when it compiles a game file (td_game_code() in Turnbuckle Dive's CMakeLists.txt). The
# tool must read the code that the port's compiler reads: the PC side of every "#ifdef TARGET_PC". The port's
# settings are copied into three tools: here, and as PC_FLAGS in tools/port_check.py and tools/port_calls.py. When
# td_game_code() changes, change all three.
PC_DEFINES = ("TARGET_PC", "NON_MATCHING", "AVOID_UB", "F3DEX_GBI_2")

# Where each program starts: the game functions it calls itself, the roots of the walk.
SETS = {
    # The port's developer program, which starts a match without the menus.
    # - On the N64 the boot loop func_80013108 first makes four calls, which set up the graphics, the audio, the
    #   controllers and the table of resource sizes. The program makes the same four calls itself.
    # - func_8002B750 builds the table of wrestler names. On the N64 only the menus call it (func_800C4D70, in
    #   overlay 1), so the program calls it before the match.
    # - func_80090000_ovl2 is overlay 2's entry: the match.
    # The boot loop itself is not a root. It copies the overlays from ROM (func_80000700) and enters overlay 1
    # (func_8000082C); the port links overlay 2 in and calls its entry directly.
    "match": ("func_80001260", "func_80003120", "func_80003D20", "initializeAssetSizeTable", "func_8002B750",
              "func_80090000_ovl2"),
}

# The Nintendo SDK code that the port compiles from the decompilation, chosen by the "library" column of the table
# "The functions" in docs/sdk_functions.md. The port replaces every other SDK function with its own code or LUS's.
# - libultra's gu library (matrices, vectors, sinf and cosf, sqrtf, guRandom): LUS only declares it, and the match must
#   compute what the N64 computes, bit for bit (positions, angles, random numbers).
# - bzero and bcopy: game code calls them by name, and the port's program must not define a function under a C
#   library name, so port.h renames the game's own two port_bzero and port_bcopy. A replacement written with memset
#   could end up calling itself, because compilers turn memset(p, 0, n) back into a call to bzero.
KEEP_SDK_LIBRARIES = frozenset({"libultra (gu)"})
KEEP_SDK_FUNCTIONS = frozenset({"bzero", "bcopy"})

# Rows of that table that stay game code. func_80000A40 (library "?") sets up the SRAM handle the way Nintendo's SRAM
# sample does, but no SDK function matches it, so it counts as the game's own code.
SDK_ROWS_THAT_ARE_GAME = frozenset({"func_80000A40"})

# The game's own files that the port replaces, each named by the function of main that it holds (the file
# src/main/<name>.c). The walk stops at them as it stops at replaced SDK code. tools/port_calls.py reads this table too.
REPLACED_GAME_FILES = {
    "main": "the N64 entry point; the port has its own",
    "func_800004B8": "the first thread: starts the PI manager and the scheduler, then the boot loop's thread",
    "func_800130A0": "creates and starts the thread of the boot loop func_80013108; the port makes its calls itself",
    "rspTaskThread": "the scheduler's RSP task thread; the port hands display lists to LUS's renderer instead",
    "renderTaskThread": "the scheduler's RDP task thread, replaced like rspTaskThread",
    "func_800011D4": "waits until a frame buffer is free for renderTaskThread; LUS shows the frames",
    "func_800005AC": "removes a client from the N64 scheduler, which the port does not have; nothing calls it",
    "func_80004450": "a Controller Pak probe that calls each osPfs function once; nothing calls it",
}

# =====================================================================================================================
# A small C reader: tokens, the preprocessor and declarations. It understands the C this decompilation is written in,
# not all of C: enough to tell a name that a function uses from one that it declares.
# =====================================================================================================================


class InputError(Exception):
    """The decompilation's files are missing or disagree in a way that stops the tool (exit status 2)."""


def plural(n: int, word: str) -> str:
    """'1 file', '2 files'."""
    return f"{n} {word}{'s' * (n != 1)}"


_TOKEN = re.compile(r"""
    (?P<nl>\n)
  | (?P<splice>\\\n)
  | (?P<ws>[ \t\r\f\v]+)
  | (?P<bc>/\*.*?\*/)
  | (?P<lc>//[^\n]*)
  | (?P<str>"(?:\\.|[^"\\\n])*")
  | (?P<chr>'(?:\\.|[^'\\\n])*')
  | (?P<num>\.?\d(?:[eEpP][+-]|[\w.])*)
  | (?P<id>[A-Za-z_]\w*)
  | (?P<p>\.\.\.|<<=|>>=|->|\+\+|--|<<|>>|<=|>=|==|!=|&&|\|\||[-+*/%&|^]=|\#\#|[][(){}.,;:?~!%^&*+\-=<>|/#])
  | (?P<other>.)
""", re.S | re.X)


@dataclass
class Tok:
    kind: str   # id, num, str, chr, p (punctuation), nl (end of a line), eof
    text: str
    line: int
    pos: int = 0     # offset in the file: tells "NAME(" from "NAME (" in a #define


def lex(text: str) -> list[Tok]:
    """The tokens of a C file, with an 'nl' token at the end of each logical line (for the directives)."""
    out: list[Tok] = []
    line = 1
    for m in _TOKEN.finditer(text):
        kind = m.lastgroup
        s = m.group()
        if kind == "nl":
            out.append(Tok("nl", "\n", line, m.start()))
            line += 1
            continue
        if kind in ("splice", "bc"):
            line += s.count("\n")
            continue
        if kind in ("ws", "lc"):
            continue
        if kind == "other":
            kind = "p"
        out.append(Tok(kind, s, line, m.start()))
    out.append(Tok("nl", "\n", line, len(text)))
    return out


@dataclass
class Macro:
    params: list[str] | None   # None: an object-like macro
    variadic: bool
    body: list[Tok]


def _c_integer(text: str) -> int:
    """The value of a C integer constant such as 0x1E0, 0755 or 16u."""
    digits = text.rstrip("uUlL")
    if digits[:2] in ("0x", "0X"):
        return int(digits[2:], 16)
    if digits[:2] in ("0b", "0B"):
        return int(digits[2:], 2)
    if len(digits) > 1 and digits[0] == "0":
        return int(digits[1:], 8)
    return int(digits, 10)


def _c_divide(a: int, b: int) -> int:
    """a / b as C computes it: the quotient rounded towards zero."""
    q = abs(a) // abs(b)
    return q if (a < 0) == (b < 0) else -q


# The binary operators of an #if expression: how tightly each binds (the ternary a ? b : c binds loosest of all) and
# what it computes.
_IF_OPERATORS = {
    "||": (1, lambda a, b: int(bool(a) or bool(b))),
    "&&": (2, lambda a, b: int(bool(a) and bool(b))),
    "|": (3, lambda a, b: a | b),
    "^": (4, lambda a, b: a ^ b),
    "&": (5, lambda a, b: a & b),
    "==": (6, lambda a, b: int(a == b)),
    "!=": (6, lambda a, b: int(a != b)),
    "<": (7, lambda a, b: int(a < b)),
    "<=": (7, lambda a, b: int(a <= b)),
    ">": (7, lambda a, b: int(a > b)),
    ">=": (7, lambda a, b: int(a >= b)),
    "<<": (8, lambda a, b: a << b),
    ">>": (8, lambda a, b: a >> b),
    "+": (9, lambda a, b: a + b),
    "-": (9, lambda a, b: a - b),
    "*": (10, lambda a, b: a * b),
    "/": (10, _c_divide),
    "%": (10, lambda a, b: a - _c_divide(a, b) * b),
}


class _IfExpression:
    """Evaluates the expression of an #if or #elif line, after macro expansion, with C's operators and precedence.
    Raises ValueError, IndexError or ZeroDivisionError on an expression it cannot evaluate."""

    def __init__(self, toks: list[Tok]):
        self.toks = toks
        self.i = 0

    def value(self) -> int:
        v = self._conditional()
        if self.i != len(self.toks):
            raise ValueError(f"unexpected {self.toks[self.i].text}")
        return v

    def _peek(self) -> str:
        return self.toks[self.i].text if self.i < len(self.toks) else ""

    def _take(self, want: str | None = None) -> Tok:
        t = self.toks[self.i]
        if want is not None and t.text != want:
            raise ValueError(f"{want} expected")
        self.i += 1
        return t

    def _conditional(self) -> int:
        v = self._binary(1)
        if self._peek() == "?":
            self._take()
            a = self._conditional()
            self._take(":")
            b = self._conditional()
            v = a if v else b
        return v

    def _binary(self, level: int) -> int:
        """An expression of operators that bind at least as tightly as `level`, read from left to right."""
        v = self._unary()
        while self._peek() in _IF_OPERATORS and _IF_OPERATORS[self._peek()][0] >= level:
            precedence, compute = _IF_OPERATORS[self._take().text]
            v = compute(v, self._binary(precedence + 1))
        return v

    def _unary(self) -> int:
        t = self._take()
        if t.kind == "p" and t.text in ("!", "-", "+", "~"):
            v = self._unary()
            return {"!": int(not v), "-": -v, "+": v, "~": ~v}[t.text]
        if t.text == "(":
            v = self._conditional()
            self._take(")")
            return v
        if t.kind == "num":
            return _c_integer(t.text)
        if t.kind == "id":
            return 0     # an identifier that is not a macro counts as 0, as in C
        raise ValueError(f"unexpected {t.text}")


class Preprocessor:
    """Runs the directives of one C file: #if, #ifdef, #ifndef, #elif, #else, #endif, #define, #undef and
    #include "..." (looked up next to the file, then in include/). It returns the tokens of the code that is compiled,
    with macros expanded. System headers (#include <...>) are not read: the parser knows the few names that game files
    use from them."""

    def __init__(self, include_dir: Path, defines: tuple[str, ...], read_text: Callable[[Path], str]):
        self.include_dir = include_dir
        self.read_text = read_text
        self.base = {d: Macro(None, False, [Tok("num", "1", 0)]) for d in defines}
        # Headers that a file includes before any #define or #undef of its own: the tokens each gives and the macros
        # after it, kept for the next file, so that common.h is read once and not once per file. The key is (header,
        # the headers the file included before it), which settles the macros the header is read with.
        self.cache: dict[tuple[str, tuple[str, ...]], tuple[list[Tok], dict[str, Macro]]] = {}
        self.macros: dict[str, Macro] = {}
        self.pristine = True             # the file itself has not run a #define or #undef yet
        self.depth = 0                   # how many #include levels deep the reader is
        self.included: list[str] = []    # the headers the file itself has included so far
        self.ranges: list[tuple[str, int, int, tuple[str, tuple[str, ...]] | None]] = []

    def run(self, path: Path, rel: str) -> tuple[list[Tok], list[tuple[str, int, int, tuple | None]]]:
        """(tokens, includes). includes are the headers the file itself includes, as (header, index of its first
        token, index after its last, cache key). The key is None when the header was read after a #define or #undef
        of the file's own, so that what it declares may differ from file to file."""
        self.macros = dict(self.base)
        self.pristine = True
        self.depth = 0
        self.included = []
        self.ranges = []
        out: list[Tok] = []
        self._file(path, rel, out, set())
        return out, self.ranges

    def _file(self, path: Path, rel: str, out: list[Tok], guard: set[str]) -> None:
        """Adds to `out` the compiled tokens of one file (the C file or a header). `guard` holds the headers being
        read already, so that a header that includes itself does not loop."""
        toks = lex(self.read_text(path))
        stack: list[list[bool]] = []   # per open #if: [is the code around it compiled, was one of its branches taken]
        active = True
        pending: list[Tok] = []
        line_toks: list[Tok] = []

        def flush() -> None:
            if pending:
                out.extend(self.expand(pending, frozenset()))
                pending.clear()

        for t in toks:
            if t.kind != "nl":
                line_toks.append(t)
                continue
            if not line_toks:
                continue
            ln, line_toks = line_toks, []
            if ln[0].text == "#" and ln[0].kind == "p":
                d = ln[1].text if len(ln) > 1 else ""
                rest = ln[2:]
                where = f"{rel}:{ln[0].line}"
                if d in ("elif", "else", "endif") and not stack:
                    raise InputError(f"{where}: #{d} without #if")
                if d in ("if", "ifdef", "ifndef"):
                    if not active:
                        stack.append([False, True])
                        continue
                    if d == "ifdef":
                        cond = bool(rest) and rest[0].text in self.macros
                    elif d == "ifndef":
                        cond = not (bool(rest) and rest[0].text in self.macros)
                    else:
                        cond = self.eval_if(rest, where)
                    stack.append([active, cond])
                    active = cond
                elif d == "elif":
                    parent, taken = stack[-1]
                    cond = parent and not taken and self.eval_if(rest, where)
                    stack[-1][1] = taken or cond
                    active = cond
                elif d == "else":
                    parent, taken = stack[-1]
                    active = parent and not taken
                    stack[-1][1] = True
                elif d == "endif":
                    parent, _ = stack.pop()
                    active = parent
                elif not active:
                    continue
                elif d == "define" and rest:
                    flush()
                    self.pristine = False
                    name = rest[0].text
                    if len(rest) > 1 and rest[1].text == "(" and rest[1].pos == rest[0].pos + len(name):
                        j = 2
                        params: list[str] = []
                        variadic = False
                        while j < len(rest) and rest[j].text != ")":
                            if rest[j].text == "...":
                                variadic = True
                            elif rest[j].kind == "id":
                                params.append(rest[j].text)
                            j += 1
                        self.macros[name] = Macro(params, variadic, rest[j + 1:])
                    else:
                        self.macros[name] = Macro(None, False, rest[1:])
                elif d == "undef" and rest:
                    flush()
                    self.pristine = False
                    self.macros.pop(rest[0].text, None)
                elif d == "include" and rest and rest[0].kind == "str":
                    flush()
                    inc = rest[0].text[1:-1]
                    for cand in (path.parent / inc, self.include_dir / inc):
                        if cand.exists():
                            self._include(cand, f"include/{inc}" if cand.parent == self.include_dir else inc,
                                          out, guard)
                            break
                    else:
                        raise InputError(f"{where}: #include \"{inc}\" not found")
                # #include <...>, #pragma, #error and #line change nothing that matters here
                continue
            if active:
                pending.extend(ln)
        flush()

    def _include(self, path: Path, rel: str, out: list[Tok], guard: set[str]) -> None:
        """An #include "...": the header's tokens, from the cache when it holds them."""
        if rel in guard:
            return
        start = len(out)
        was_pristine = self.pristine
        key = (rel, tuple(self.included)) if was_pristine and self.depth == 0 else None
        if key is not None and key in self.cache:
            toks, macros = self.cache[key]
            out.extend(toks)
            self.macros = dict(macros)
        else:
            self.depth += 1
            self._file(path, rel, out, guard | {rel})
            self.depth -= 1
            if key is not None:
                self.cache[key] = (out[start:], dict(self.macros))
        # A header's own #defines do not count against the file: the key records which headers ran before.
        self.pristine = was_pristine
        if self.depth == 0:
            self.included.append(rel)
            self.ranges.append((rel, start, len(out), key))

    # -- macros -------------------------------------------------------------------------------------------------------

    def expand(self, toks: list[Tok], off: frozenset[str]) -> list[Tok]:
        """The tokens with macros expanded. `off` holds the macros being expanded already, which C does not expand
        again inside themselves."""
        out: list[Tok] = []
        i = 0
        n = len(toks)
        while i < n:
            t = toks[i]
            m = self.macros.get(t.text) if t.kind == "id" and t.text not in off else None
            if m is None:
                out.append(t)
                i += 1
                continue
            if m.params is None:
                body = [Tok(b.kind, b.text, t.line, b.pos) for b in m.body]
                out.extend(self.expand(body, off | {t.text}))
                i += 1
                continue
            if i + 1 >= n or toks[i + 1].text != "(":
                out.append(t)     # a function-like macro's name without arguments is just a name
                i += 1
                continue
            args, j = self._args(toks, i + 1)
            if args is None:
                out.append(t)
                i += 1
                continue
            body = self._substitute(m, args, t.line, off)
            out.extend(self.expand(body, off | {t.text}))
            i = j
        return out

    @staticmethod
    def _args(toks: list[Tok], i: int) -> tuple[list[list[Tok]] | None, int]:
        """The arguments of a macro call whose '(' is at toks[i], and the index after its ')'."""
        depth = 0
        args: list[list[Tok]] = [[]]
        for j in range(i, len(toks)):
            x = toks[j].text
            if toks[j].kind == "p" and x in "([{":
                depth += 1
                if depth == 1:
                    continue
            elif toks[j].kind == "p" and x in ")]}":
                depth -= 1
                if depth == 0:
                    return (args if args != [[]] else []), j + 1
            elif x == "," and depth == 1:
                args.append([])
                continue
            args[-1].append(toks[j])
        return None, len(toks)

    def _substitute(self, m: Macro, args: list[list[Tok]], line: int, off: frozenset[str]) -> list[Tok]:
        """A function-like macro's body with its parameters replaced by the arguments, and # and ## applied."""
        names = list(m.params or [])
        if m.variadic:
            names.append("__VA_ARGS__")
            if len(args) > len(m.params or []):
                head, tail = args[:len(m.params or [])], args[len(m.params or []):]
                joined: list[Tok] = []
                for k, a in enumerate(tail):
                    if k:
                        joined.append(Tok("p", ",", line))
                    joined.extend(a)
                args = head + [joined]
        amap = {p: (args[k] if k < len(args) else []) for k, p in enumerate(names)}
        body = m.body
        out: list[Tok] = []
        k = 0
        while k < len(body):
            b = body[k]
            if b.text == "#" and k + 1 < len(body) and body[k + 1].text in amap:   # #param: the argument as a string
                out.append(Tok("str", '"' + " ".join(a.text for a in amap[body[k + 1].text]) + '"', line))
                k += 2
                continue
            if b.kind == "id" and b.text in amap:
                pasted = (k + 1 < len(body) and body[k + 1].text == "##") or (k > 0 and body[k - 1].text == "##")
                raw = amap[b.text]
                out.extend(Tok(a.kind, a.text, line, a.pos) for a in (raw if pasted else self.expand(raw, off)))
            else:
                out.append(Tok(b.kind, b.text, line, b.pos))
            k += 1
        # token pasting: a ## b becomes one token
        k = 0
        res: list[Tok] = []
        while k < len(out):
            if out[k].text == "##" and res and k + 1 < len(out):
                left = res.pop()
                glued = left.text + out[k + 1].text
                res.extend(Tok(x.kind, x.text, line) for x in lex(glued)[:-1])
                k += 2
                continue
            res.append(out[k])
            k += 1
        return res

    def eval_if(self, toks: list[Tok], where: str) -> bool:
        """The condition of an #if or #elif line: defined(X) and defined X become 1 or 0, then the macros are
        expanded and the expression is evaluated as C would."""
        try:
            parts: list[Tok] = []
            i = 0
            while i < len(toks):
                t = toks[i]
                if t.text == "defined":
                    j = i + 1
                    if j < len(toks) and toks[j].text == "(":
                        name, i = toks[j + 1].text, j + 3
                    else:
                        name, i = toks[j].text, j + 1
                    parts.append(Tok("num", "1" if name in self.macros else "0", t.line))
                    continue
                parts.append(t)
                i += 1
            return bool(_IfExpression(self.expand(parts, frozenset())).value())
        except (ValueError, IndexError, ZeroDivisionError) as exc:
            raise InputError(f"{where}: cannot evaluate #if {' '.join(t.text for t in toks)}: {exc}") from None


# Names of C and of GCC that are never a global of the game.
KEYWORDS = frozenset("""
auto break case char const continue default do double else enum extern float for goto if inline int long register
restrict return short signed sizeof static struct switch typedef union unsigned void volatile while _Alignas _Alignof
_Atomic _Bool _Complex _Generic _Imaginary _Noreturn _Static_assert _Thread_local __attribute__ __attribute __asm__
__asm asm __inline__ __inline __volatile__ __volatile __const __const__ __restrict __restrict__ __signed__ __signed
__extension__ __typeof__ __typeof typeof __alignof__ __alignof __label__ __real__ __imag__ __int128 __func__
__FUNCTION__ __PRETTY_FUNCTION__ offsetof
""".split())
STORAGE = frozenset({"typedef", "extern", "static", "auto", "register", "_Thread_local"})
QUALIFIERS = frozenset({"const", "volatile", "restrict", "_Atomic", "__const", "__const__", "__restrict",
                        "__restrict__", "__volatile__", "__volatile", "inline", "__inline__", "__inline", "_Noreturn"})
BASIC_TYPES = frozenset({"void", "char", "short", "int", "long", "float", "double", "signed", "unsigned", "_Bool",
                         "_Complex", "__signed__", "__signed", "__int128", "__builtin_va_list"})
ATTRIBUTES = frozenset({"__attribute__", "__attribute"})
TYPEOF = frozenset({"__typeof__", "__typeof", "typeof"})
ASM = frozenset({"asm", "__asm__", "__asm"})
# Types that game files get from <stddef.h> and <stdint.h>, which port.h includes under TARGET_PC.
SYSTEM_TYPES = frozenset({"size_t", "ptrdiff_t", "wchar_t", "max_align_t", "intptr_t", "uintptr_t", "intmax_t",
                          "uintmax_t"})
_SYSTEM_INT = re.compile(r"u?int(_least|_fast)?(8|16|32|64)_t$")


@dataclass
class Func:
    name: str
    line: int
    static: bool
    refs: list[tuple[str, int]] = field(default_factory=list)   # the global names it uses, with their lines
    alias_of: str | None = None                                  # __attribute__((alias("..."))): the real function


@dataclass
class Unit:
    """What one C file defines and uses."""
    rel: str
    funcs: dict[str, Func] = field(default_factory=dict)
    vars: dict[str, tuple[int, bool]] = field(default_factory=dict)   # file-scope definitions: name -> (line, static)
    file_refs: list[tuple[str, int]] = field(default_factory=list)    # names used outside functions (initialisers)
    externs: set[str] = field(default_factory=set)                   # declared here, defined elsewhere


@dataclass
class Spec:
    storage: set[str]
    typedef: bool
    typed: bool


@dataclass
class Decl:
    name: str | None
    line: int
    is_func: bool
    params: list[str | None] | None


class Parser:
    """Walks the expanded tokens of one file: the declarations at file scope and, inside each function body, every
    identifier, sorted into what the function declares (locals, parameters, labels) and what it uses."""

    def __init__(self, toks: list[Tok], typedefs: set[str], enums: set[str]):
        # T: the tokens, with a few 'eof' tokens after the end so that looking ahead never runs off the list
        self.T = toks + [Tok("eof", "", toks[-1].line if toks else 0)] * 8
        self.n = len(toks)
        self.typedefs = typedefs
        self.enums = enums

    # -- helpers ------------------------------------------------------------------------------------------------------

    def close(self, i: int) -> int:
        """The index just past the bracket that closes the one at T[i]."""
        depth = 0
        T = self.T
        for j in range(i, self.n):
            if T[j].kind == "p":
                x = T[j].text
                if x in "([{":
                    depth += 1
                elif x in ")]}":
                    depth -= 1
                    if depth == 0:
                        return j + 1
        return self.n

    def is_type_name(self, x: str) -> bool:
        return x in self.typedefs or x in SYSTEM_TYPES or bool(_SYSTEM_INT.match(x))

    def skip_attributes(self, i: int, aliases: list[str] | None = None) -> int:
        """The index after any __attribute__((...)) or asm(...) at T[i]; collects alias("name") into `aliases`."""
        T = self.T
        while T[i].text in ATTRIBUTES or T[i].text in ASM:
            j = i + 1
            while T[j].text in ("volatile", "__volatile__", "goto", "inline"):
                j += 1
            if T[j].text != "(":
                return j
            end = self.close(j)
            if aliases is not None and T[i].text in ATTRIBUTES:
                for k in range(j, end):
                    if T[k].text == "alias" and T[k + 1].text == "(" and T[k + 2].kind == "str":
                        aliases.append(T[k + 2].text[1:-1])
            i = end
        return i

    # -- declarations -------------------------------------------------------------------------------------------------

    def specifiers(self, i: int) -> tuple[int, Spec]:
        """The declaration specifiers at T[i] (storage class, qualifiers, the type), and the index after them."""
        T = self.T
        spec = Spec(set(), False, False)
        while True:
            t = T[i]
            x = t.text
            if t.kind != "id":
                return i, spec
            if x in STORAGE:
                spec.storage.add(x)
                spec.typedef |= x == "typedef"
                i += 1
            elif x in QUALIFIERS or x == "__extension__":
                i += 1
            elif x in BASIC_TYPES:
                spec.typed = True
                i += 1
            elif x in ("struct", "union", "enum"):
                i = self.skip_attributes(i + 1)
                if T[i].kind == "id":
                    i += 1
                i = self.skip_attributes(i)
                if T[i].text == "{":
                    end = self.close(i)
                    self.collect_enums(i, end, x == "enum")
                    i = end
                spec.typed = True
            elif x in ATTRIBUTES:
                i = self.skip_attributes(i)
            elif x in TYPEOF or x == "_Alignas":
                i = self.close(i + 1) if T[i + 1].text == "(" else i + 1
                spec.typed = True
            elif not spec.typed and self.is_type_name(x):
                spec.typed = True
                i += 1
            else:
                return i, spec

    def collect_enums(self, i: int, end: int, is_enum: bool) -> None:
        """The enumerators of an enum body (and of enums declared inside a struct body)."""
        T = self.T
        if is_enum:
            expect = True
            depth = 0
            for k in range(i + 1, end - 1):
                x = T[k].text
                if x in ("(", "[", "{"):
                    depth += 1
                elif x in (")", "]", "}"):
                    depth -= 1
                elif x == "," and depth == 0:
                    expect = True
                elif expect and T[k].kind == "id":
                    self.enums.add(x)
                    expect = False
            return
        for k in range(i + 1, end - 1):
            if T[k].text == "enum":
                j = k + 1
                if T[j].kind == "id":
                    j += 1
                if T[j].text == "{":
                    self.collect_enums(j, self.close(j), True)

    def nested_declarator(self, i: int) -> bool:
        """At '(' in a declarator: whether it opens a declarator in brackets such as (*fp), not a parameter list."""
        T = self.T
        x = T[i + 1]
        if x.text in ("*", "^", "(") or x.text in ATTRIBUTES:
            return True
        return x.kind == "id" and x.text not in KEYWORDS and not self.is_type_name(x.text) and \
            x.text not in BASIC_TYPES and x.text not in QUALIFIERS and x.text not in STORAGE

    def declarator(self, i: int, refs: list, locals_: set[str]) -> tuple[int, Decl]:
        """One declarator at T[i] (the name with its pointers, arrays and parameters); array sizes count as uses."""
        T = self.T
        while T[i].text == "*" or T[i].text in QUALIFIERS or T[i].text in ATTRIBUTES:
            i = self.skip_attributes(i) if T[i].text in ATTRIBUTES else i + 1
        d = Decl(None, T[i].line, False, None)
        nested = False
        inner_func = False
        if T[i].text == "(" and self.nested_declarator(i):
            nested = True
            i, inner = self.declarator(i + 1, refs, locals_)
            i = self.skip_attributes(i)
            if T[i].text == ")":
                i += 1
            d.name, d.line, d.params, inner_func = inner.name, inner.line, inner.params, inner.is_func
        elif T[i].kind == "id" and T[i].text not in KEYWORDS:
            d.name, d.line = T[i].text, T[i].line
            i += 1
        first = True
        while T[i].text in ("[", "("):
            end = self.close(i)
            if T[i].text == "[":
                self.expression(i + 1, end - 1, refs, locals_)
            else:
                params = self.parameters(i + 1, end - 1)
                if not nested and first:
                    d.is_func, d.params = True, params
            i = end
            first = False
        if nested:
            d.is_func = inner_func
        return i, d

    def parameters(self, i: int, end: int) -> list[str | None]:
        """The names of the parameters between T[i] and T[end] (None for one without a name)."""
        T = self.T
        names: list[str | None] = []
        k = i
        while k < end:
            # one parameter: up to the next comma outside brackets
            j = k
            depth = 0
            while j < end:
                x = T[j].text
                if x in ("(", "[", "{"):
                    depth += 1
                elif x in (")", "]", "}"):
                    depth -= 1
                elif x == "," and depth == 0:
                    break
                j += 1
            if not (j == k + 1 and T[k].text in ("void", "...")):
                p, spec = self.specifiers(k)
                if not spec.typed and T[p].kind == "id" and T[p].text not in KEYWORDS:
                    names.append(T[p].text)   # an old-style list of names, or an implicit int
                else:
                    _, d = self.declarator(p, [], set())
                    names.append(d.name)
            k = j + 1
        return names

    def initialiser_end(self, i: int) -> int:
        """The index of the ',' or ';' that ends the initialiser starting at T[i]."""
        T = self.T
        depth = 0
        while i < self.n:
            x = T[i].text
            if T[i].kind == "p":
                if x in "([{":
                    depth += 1
                elif x in ")]}":
                    if depth == 0:
                        return i
                    depth -= 1
                elif x in (",", ";") and depth == 0:
                    return i
            i += 1
        return i

    def declaration(self, i: int, scope: str, unit: Unit | None, locals_: set[str], refs: list) -> int:
        """One declaration (or, at file scope, a function definition) starting at T[i]. Returns the index after it.
        scope is "file", "block" (inside a function) or "params" (old-style parameter declarations)."""
        T = self.T
        start = i
        i, spec = self.specifiers(i)
        while True:
            if T[i].text == ";":
                return i + 1
            i, d = self.declarator(i, refs, locals_)
            aliases: list[str] = []
            i = self.skip_attributes(i, aliases)
            if scope == "file" and d.is_func and d.name and not spec.typedef:
                if T[i].text == "{" or (T[i].kind == "id" and T[i].text not in ATTRIBUTES):
                    # a definition (old-style parameter declarations may come before the body)
                    params = set(p for p in (d.params or []) if p)
                    while T[i].text != "{" and i < self.n:
                        if T[i].text == ";":
                            i += 1
                            continue
                        i = self.declaration(i, "params", None, params, [])
                    f = Func(d.name, d.line, "static" in spec.storage)
                    i = self.body(i, params, f.refs)
                    if unit is not None:
                        unit.funcs[d.name] = f
                    return i
            if d.name:
                if spec.typedef:
                    self.typedefs.add(d.name)
                elif aliases and unit is not None:
                    f = Func(d.name, d.line, "static" in spec.storage, [(aliases[0], d.line)], aliases[0])
                    unit.funcs[d.name] = f
                elif d.is_func or "extern" in spec.storage:
                    if unit is not None:
                        unit.externs.add(d.name)
                    locals_.discard(d.name)
                elif scope == "file":
                    if unit is not None:
                        unit.vars[d.name] = (d.line, "static" in spec.storage)
                elif scope in ("block", "params"):
                    locals_.add(d.name)
            if T[i].text == "=":
                end = self.initialiser_end(i + 1)
                self.expression(i + 1, end, refs, locals_)
                i = end
            if T[i].text == ",":
                i += 1
                continue
            if T[i].text == ";":
                return i + 1
            # something this reader does not understand: skip to the end of the statement
            while i < self.n and T[i].text not in (";", "}"):
                i = self.close(i) if T[i].text in ("(", "[", "{") else i + 1
            return max(i + 1, start + 1)

    def starts_declaration(self, i: int, locals_: set[str]) -> bool:
        """Whether a statement starting at T[i] is a declaration (a type name used as a variable is not)."""
        T = self.T
        x = T[i].text
        if T[i].kind != "id":
            return False
        if x in STORAGE or x in QUALIFIERS or x in BASIC_TYPES or x in ("struct", "union", "enum", "__extension__",
                                                                        "_Alignas") or x in TYPEOF:
            return True
        if x in ATTRIBUTES:
            return True
        if self.is_type_name(x) and x not in locals_:
            return T[i + 1].text not in ("=", ".", "->", "[", "++", "--", "+=", "-=", "|=", "&=", ")", ",", ";")
        return False

    # -- statements and expressions -----------------------------------------------------------------------------------

    def body(self, i: int, locals_: set[str], refs: list) -> int:
        """A function body starting at '{'. Returns the index after its '}'."""
        T = self.T
        end = self.close(i)
        j = i + 1
        stmt = True     # at the start of a statement, where a declaration or a label can begin
        while j < end - 1:
            t = T[j]
            x = t.text
            if t.kind == "p":
                if x in ("{", "}", ";", ":"):
                    stmt = True
                    j += 1
                    continue
                if x in (".", "->"):
                    j += 2 if T[j + 1].kind == "id" else 1    # a field name, never a global
                    stmt = False
                    continue
                stmt = False
                j += 1
                continue
            if t.kind != "id":
                stmt = False
                j += 1
                continue
            if stmt:
                if x == "_Static_assert":
                    k = self.close(j + 1)
                    self.expression(j + 2, k - 1, refs, locals_)
                    j = k
                    continue
                if self.starts_declaration(j, locals_):
                    j = self.declaration(j, "block", None, locals_, refs)
                    continue
                if T[j + 1].text == ":" and x not in KEYWORDS:   # a label
                    j += 2
                    continue
            stmt = False
            if x == "goto":
                j += 2
                continue
            if x == "for" and T[j + 1].text == "(":
                if self.starts_declaration(j + 2, locals_):
                    j = self.declaration(j + 2, "block", None, locals_, refs)
                else:
                    j += 2
                continue
            j = self.identifier(j, refs, locals_)
        return end

    def expression(self, i: int, end: int, refs: list, locals_: set[str]) -> None:
        T = self.T
        while i < end:
            t = T[i]
            if t.kind == "id":
                i = self.identifier(i, refs, locals_)
            elif t.text in (".", "->") and T[i + 1].kind == "id":
                i += 2
            else:
                i += 1

    def identifier(self, j: int, refs: list, locals_: set[str]) -> int:
        """Sorts the identifier at T[j] in an expression and records it in refs when it names a global."""
        T = self.T
        x = T[j].text
        if x in ("offsetof", "__builtin_offsetof") or x in TYPEOF or x in ("_Alignof", "__alignof__", "__alignof"):
            return self.close(j + 1) if T[j + 1].text == "(" else j + 1
        if x in ATTRIBUTES:
            return self.skip_attributes(j)
        if x in ("struct", "union", "enum"):
            k = j + 1
            if T[k].kind == "id":
                k += 1
            if T[k].text == "{":
                e = self.close(k)
                self.collect_enums(k, e, x == "enum")
                return e
            return k
        if x in KEYWORDS or x in STORAGE or x in QUALIFIERS or x in BASIC_TYPES or x.startswith("__builtin_"):
            return j + 1
        if x in locals_ or x in self.enums or self.is_type_name(x):
            return j + 1
        refs.append((x, T[j].line))
        return j + 1

    def unit(self, rel: str, start: int = 0, stop: int | None = None) -> Unit:
        """What the tokens T[start:stop] define and use, read as file scope."""
        u = Unit(rel)
        T = self.T
        i = start
        stop = self.n if stop is None else stop
        while i < stop:
            x = T[i].text
            if x == ";":
                i += 1
            elif x == "_Static_assert":
                k = self.close(i + 1)
                self.expression(i + 2, k - 1, u.file_refs, set())
                i = k
            elif x in ASM:
                i = self.skip_attributes(i)
            else:
                i = self.declaration(i, "file", u, set(), u.file_refs)
        return u


# =====================================================================================================================
# The decompilation: its functions, symbols and data, and its C files read as above.
# =====================================================================================================================

@dataclass
class Target:
    # What a name turned out to be:
    #   local (defined in the same file), func (a C function), alias (an old name of one, from build.json), cdata (a
    #   variable a C file defines), data, rom (a ROM address), main-code-area, port (declared by port.h), inline (a
    #   static inline helper of a header), overlay1 / overlay1-data, code-middle (inside overlay code, not a function)
    kind: str
    file: str | None   # the C file that provides it, if any
    name: str          # the function or variable it stands for


class Decomp:
    """The decompilation's files that the tool reads, and what they say about functions, symbols and data."""

    def __init__(self, root: Path):
        self.root = root
        self.errors: list[str] = []                 # problems with the inputs, each an error line (exit status 2)
        self.files_read: set[Path] = set()          # every file read, so that --self-test can copy exactly these
        try:
            self.build = json.loads(self.read_text(root / "build.json"))
        except FileNotFoundError:
            raise InputError(f"{root}: no build.json (pass --decomp with the decompilation's folder)") from None
        except ValueError as exc:
            raise InputError(f"{self.rel(root / 'build.json')}: not valid JSON ({exc})") from None
        self.seg = {s["name"]: s for s in self.build["segments"]}
        self.func_src: dict[str, str] = {}
        self.func_seg: dict[str, str] = {}
        self.func_vram: dict[str, int] = {}
        self.at_vram: dict[int, list[str]] = defaultdict(list)
        for fn in self.build["functions"]:
            src = fn.get("c") or f"src/{fn['seg']}/{fn['name']}.c"
            self.func_src[fn["name"]] = src
            self.func_seg[fn["name"]] = fn["seg"]
            self.func_vram[fn["name"]] = fn["vram"]
            self.at_vram[fn["vram"]].append(fn["name"])
        self.file_seg: dict[str, str] = {}
        self.names_in_file: dict[str, list[str]] = defaultdict(list)
        for name, src in self.func_src.items():
            self.file_seg.setdefault(src, self.func_seg[name])
            self.names_in_file[src].append(name)
        self._class: dict[str, str] = {}
        self.symbols: dict[str, int] = dict(self.build["symbols"])
        # the code ranges of main and of each overlay (main's data follows its code)
        self.text: dict[str, tuple[int, int]] = {}
        for s in self.build["segments"]:
            if s["kind"] == "code":
                end = s["vram"] + s["end"] - s["start"]
                data = [p["vram"] for p in s.get("pieces", []) if "/data/" in p["obj"]]
                self.text[s["name"]] = (s["vram"], min(data + [end]))
        # where each function of main and overlay 2 starts: a 32-bit word in data with that value is its address
        self.starts: dict[int, str] = {}
        for name, v in self.func_vram.items():
            if self.overlay(self.func_seg[name]) in (None, 2) and self.func_seg[name] != "entry":
                self.starts.setdefault(v, name)
        self.game_ld_note = self._check_game_ld(root / "build" / "game.ld")
        self._read_sdk_table()
        self._check_choices()
        self._read_asm_data()
        self._read_overlay2_data()

    def read_text(self, path: Path, errors: str = "strict") -> str:
        """A text file (UTF-8) of the decompilation; notes it in files_read."""
        self.files_read.add(Path(os.path.abspath(path)))
        return path.read_text(encoding="utf-8", errors=errors)

    def read_bytes(self, path: Path) -> bytes:
        self.files_read.add(Path(os.path.abspath(path)))
        return path.read_bytes()

    def rel(self, path: Path) -> str:
        """A path as the messages show it: relative to the decompilation when it lies inside."""
        try:
            return path.relative_to(self.root).as_posix()
        except ValueError:
            return str(path)

    # -- areas and classes --------------------------------------------------------------------------------------------

    def overlay(self, seg: str) -> int | None:
        return self.seg[seg].get("overlay")

    def area(self, src: str) -> str:
        seg = self.file_seg.get(src)
        if seg is None:
            return "?"
        ov = self.overlay(seg)
        return "main" if ov is None else f"overlay {ov}"

    def file_class(self, src: str) -> str:
        """What the port does with a C file, by the functions it holds: "game" or "keep-SDK" (compiled), "drop-SDK"
        or "drop-game" (replaced by the port), or "overlay 1" (not in the developer program)."""
        if src not in self._class:
            self._class[src] = self._class_of(src)
        return self._class[src]

    def _class_of(self, src: str) -> str:
        if self.area(src) == "overlay 1":
            return "overlay 1"
        kinds = set()
        for n in self.names_in_file[src]:
            if n in self.sdk_lib and n not in SDK_ROWS_THAT_ARE_GAME:
                lib = self.sdk_lib[n]
                kinds.add("keep-SDK" if lib in KEEP_SDK_LIBRARIES or n in KEEP_SDK_FUNCTIONS else "drop-SDK")
            elif n in REPLACED_GAME_FILES:
                kinds.add("drop-game")
            else:
                kinds.add("game")
        if len(kinds) != 1:
            raise InputError(f"{src}: holds functions of different kinds {sorted(kinds)}")
        return kinds.pop()

    # -- inputs -------------------------------------------------------------------------------------------------------

    def _check_game_ld(self, path: Path) -> str:
        """build/game.ld is what the N64 linker reads, and build.py writes it from build.json. Checks that it agrees:
        every symbol it defines, and the address of every C object it places. Returns the line for the summary."""
        if not path.exists():
            return f"{self.rel(path)} not found; symbols from build.json only"
        text = self.read_text(path)
        ld_syms = {m.group(1): int(m.group(2), 16)
                   for m in re.finditer(r"^([A-Za-z_][\w.]*) = 0x([0-9A-Fa-f]+);$", text, re.M)}
        problems = []
        for name in sorted(set(ld_syms) | set(self.symbols)):
            a, b = self.symbols.get(name), ld_syms.get(name)
            if a != b:
                problems.append(f"{name}: build.json {a if a is None else hex(a)}, "
                                f"game.ld {b if b is None else hex(b)}")
        # placements: ". = 0xOFF; build/src/<seg>/<name>.o(.text)" inside ".<seg> 0xVRAM"
        vram = None
        placed = 0
        src_at = defaultdict(set)
        for name, src in self.func_src.items():
            src_at[self.func_vram[name]].add(src)
        for line in text.splitlines():
            m = re.match(r"\s*\.(\w+) 0x([0-9A-F]{8}) :", line)
            if m:
                vram = int(m.group(2), 16)
                continue
            m = re.match(r"\s*\. = 0x([0-9A-F]+); build/(src/\S+)\.o\(\.text\)", line)
            if m and vram is not None:
                placed += 1
                at = vram + int(m.group(1), 16)
                if m.group(2) + ".c" not in src_at.get(at, ()):
                    problems.append(f"game.ld places {m.group(2)}.c at {at:#x}, where build.json has "
                                    f"{sorted(src_at.get(at, ())) or 'no function'}")
        if problems:
            self.errors.append(f"{self.rel(path)} does not match build.json ({plural(len(problems), 'difference')}; "
                               "build.py writes it from build.json, so it is out of date):\n    "
                               + "\n    ".join(problems[:20]))
        return f"{self.rel(path)}: {len(ld_syms)} symbols and {placed} C objects checked against build.json"

    def _read_sdk_table(self) -> None:
        """The Nintendo SDK functions of main: the table "The functions" in docs/sdk_functions.md."""
        path = self.root / "docs" / "sdk_functions.md"
        if not path.exists():
            raise InputError(f"{self.rel(path)}: not found")
        self.sdk_lib: dict[str, str] = {}
        section = None
        for k, line in enumerate(self.read_text(path).splitlines(), 1):
            if line.startswith("## "):
                section = line[3:].strip()
                continue
            if section != "The functions":
                continue
            m = re.match(r"\|\s*([0-9A-F]{8})\s*\|\s*`([^`]+)`\s*\|[^|]*\|\s*([^|]*?)\s*\|", line)
            if not m:
                continue
            vram, name, lib = int(m.group(1), 16), m.group(2), m.group(3)
            if self.func_vram.get(name) != vram or self.func_seg.get(name) != "main":
                self.errors.append(f"docs/sdk_functions.md:{k}: {name} at {vram:08X} is not a main function at "
                                   "that address in build.json")
            self.sdk_lib[name] = lib
        if not self.sdk_lib:
            raise InputError(f"{self.rel(path)}: found no rows in its table 'The functions'")

    def _check_choices(self) -> None:
        """Every name in the port's choices (the top of this file) must be one the decompilation has: a misspelt name
        would quietly change the list instead of stopping the tool."""
        bad = [] if "TARGET_PC" in PC_DEFINES else ["PC_DEFINES: it must hold TARGET_PC, which every PC block tests"]
        libraries = set(self.sdk_lib.values())
        bad += [f"KEEP_SDK_LIBRARIES: {x!r} is not in the library column of docs/sdk_functions.md's table"
                for x in sorted(KEEP_SDK_LIBRARIES - libraries)]
        bad += [f"{what}: {x!r} is not a row of docs/sdk_functions.md's table"
                for what, names in (("KEEP_SDK_FUNCTIONS", KEEP_SDK_FUNCTIONS),
                                    ("SDK_ROWS_THAT_ARE_GAME", SDK_ROWS_THAT_ARE_GAME))
                for x in sorted(names - set(self.sdk_lib))]
        for name in sorted(REPLACED_GAME_FILES):
            if self.func_seg.get(name) != "main":
                bad.append(f"REPLACED_GAME_FILES: {name!r} is not a function of main in build.json (the keys are "
                           "function names, not paths)")
            elif name in self.sdk_lib and name not in SDK_ROWS_THAT_ARE_GAME:
                bad.append(f"REPLACED_GAME_FILES: {name!r} is a row of docs/sdk_functions.md's table, so it is SDK "
                           "code, not the game's")
        if bad:
            raise InputError("the port's choices at the top of tools/port_filelist.py name things the decompilation "
                             "does not have:\n    " + "\n    ".join(bad))

    def _read_asm_data(self) -> None:
        """The labels of main's data and BSS (asm/data/*.s), and the names their .word entries hold: function
        addresses in data (the libmus command table, for example)."""
        self.asm_labels: dict[str, str] = {}
        self.label_addr: dict[str, int] = {}
        self.data_points_to: dict[str, list[tuple[str, str]]] = defaultdict(list)  # label -> [(name, where)]
        files = sorted((self.root / "asm" / "data").glob("*.s"))
        if not files:
            raise InputError(f"{self.rel(self.root / 'asm' / 'data')}: no data files (build.py's first run extracts "
                             "them from your ROM; see the README)")
        for path in files:
            label = None
            rel = self.rel(path)
            for k, line in enumerate(self.read_text(path, errors="replace").splitlines(), 1):
                m = re.match(r"\s*(?:glabel|dlabel|jlabel|alabel)\s+([A-Za-z_.$][\w.$]*)", line)
                if m:
                    label = m.group(1)
                    self.asm_labels[label] = f"{rel}:{k}"
                    continue
                if re.match(r"\s*(?:enddlabel|endlabel)\b", line):
                    label = None
                    continue
                # "/* ROM VRAM WORD */ .word ..." in data, "/* VRAM */ .space ..." in BSS: the label's address
                m = re.match(r"\s*/\*\s*([0-9A-F]+)(?:\s+([0-9A-F]{8}))?", line)
                if m and label and label not in self.label_addr:
                    self.label_addr[label] = int(m.group(2) or m.group(1), 16)
                m = re.search(r"\.word\s+(.*?)\s*$", line)
                if m and label:
                    for item in m.group(1).split(","):
                        n = re.match(r"\s*([A-Za-z_][\w]*)", item)
                        if n:
                            self.data_points_to[label].append((n.group(1), f"{rel}:{k}"))
                            continue
                        n = re.match(r"\s*0x([0-9A-Fa-f]{8})\s*$", item)   # a number that is a function's address
                        if n and int(n.group(1), 16) in self.starts:
                            self.data_points_to[label].append((self.starts[int(n.group(1), 16)], f"{rel}:{k}"))

    def _read_overlay2_data(self) -> None:
        """Overlay 2's data is one block of bytes (build.json segment D5FB0, assets/D5FB0.bin). Every 32-bit word in
        it that is the start address of a function of overlay 2 or main is a function pointer, which belongs to the
        build.json symbol it lies in."""
        segs =[s for s in self.build["segments"] if s["kind"] == "raw" and s.get("overlay") == 2 and s.get("incbin")]
        starts = self.starts
        data_at = {a: n for n, a in self.label_addr.items()}
        for s in segs:
            path = self.root / s["incbin"]
            if not path.exists():
                raise InputError(f"{s['incbin']}: missing (build.py's first run extracts it from your ROM)")
            blob = self.read_bytes(path)
            base, end = s["vram"], s["vram"] + len(blob)
            labels = sorted((a, n) for n, a in self.symbols.items() if base <= a < end)
            data_at.update((a, n) for a, n in labels)
            li = 0
            prev_owner = None   # the label of the function address in the word before, if that word is one
            for off in range(0, len(blob) - 3, 4):
                w = struct.unpack_from(">I", blob, off)[0]
                if w not in starts and w not in data_at:
                    prev_owner = None
                    continue
                a = base + off
                while li + 1 < len(labels) and labels[li + 1][0] <= a:
                    li += 1
                owner = labels[li][1] if labels and labels[li][0] <= a else None
                where = f"{s['incbin']} +0x{off:X}"
                if w in starts:
                    if prev_owner is not None and owner != prev_owner:
                        self.errors.append(f"{where}: a run of function addresses goes on from {prev_owner} into "
                                           f"{owner}; one table would be read as two (check the symbols in build.json)")
                    prev_owner = owner
                    if owner:   # (a function address before the block's first symbol has no label to belong to)
                        self.data_points_to[owner].append((starts[w], where))
                    continue
                prev_owner = None
                if owner and data_at[w] != owner:
                    self.data_points_to[owner].append((data_at[w], where))   # data that points at other data

    # -- the C files --------------------------------------------------------------------------------------------------

    def read_c(self) -> None:
        """Reads every C file of build.json (overlay 1's too: its names must be known to be refused)."""
        # A byte that is not UTF-8 does not stop the C reader.
        pp = Preprocessor(self.root / "include", PC_DEFINES, lambda path: self.read_text(path, errors="replace"))
        self.units: dict[str, Unit] = {}
        self.header_funcs: dict[str, Func] = {}
        # a header read from the same macros (its cache key) -> (the typedefs, the enumerators) it declares
        seen_headers: dict[tuple, tuple[set[str], set[str]]] = {}
        for src in sorted(set(self.func_src.values())):
            if not (self.root / src).exists():
                raise InputError(f"{src}: not found (build.json names it)")
            toks, includes = pp.run(self.root / src, src)
            P = Parser(toks, set(), set())
            unit = Unit(src)
            pos = 0
            for rel, a, b, key in includes + [(None, len(toks), len(toks), None)]:
                if pos < a:
                    part = P.unit(src, pos, a)
                    unit.funcs.update(part.funcs)
                    unit.vars.update(part.vars)
                    unit.file_refs += part.file_refs
                    unit.externs |= part.externs
                if rel is None:
                    break
                if key is not None and key in seen_headers:   # the same header tokens as before: their declarations too
                    P.typedefs |= seen_headers[key][0]
                    P.enums |= seen_headers[key][1]
                else:
                    before = (set(P.typedefs), set(P.enums))
                    hu = P.unit(rel, a, b)
                    for f in hu.funcs.values():
                        self.header_funcs.setdefault(f.name, f)
                    if key is not None:
                        seen_headers[key] = (P.typedefs - before[0], P.enums - before[1])
                pos = b
            self.units[src] = unit
        # what include/port.h itself declares: the functions the port supplies (port_fatal, port_rom_read ...)
        toks, _ = pp.run(self.root / "include" / "port.h", "include/port.h")
        common = seen_headers.get(("include/common.h", ()), (set(), set()))
        pu = Parser(toks, set(common[0]), set(common[1])).unit("include/port.h")
        self.port_decls = pu.externs | set(pu.funcs)
        self._index_definitions()

    def _index_definitions(self) -> None:
        self.global_funcs: dict[str, list[str]] = defaultdict(list)
        self.global_vars: dict[str, list[str]] = defaultdict(list)
        for src, u in self.units.items():
            for f in u.funcs.values():
                if not f.static:
                    self.global_funcs[f.name].append(src)
            for v, (_, static) in u.vars.items():
                if not static:
                    self.global_vars[v].append(src)
        # port.h renames some SDK functions under TARGET_PC (#define osRecvMesg port_osRecvMesg): new name -> old
        self.renamed = {}
        hdr = self.root / "include" / "port.h"
        for m in re.finditer(r"^#define\s+(\w+)\s+((?:port|n64)_\w+)\s*$", self.read_text(hdr), re.M):
            self.renamed[m.group(2)] = m.group(1)   # port_osRecvMesg -> osRecvMesg
        back = {v: k for k, v in self.renamed.items()}
        # every function of build.json must be defined in its file under TARGET_PC (perhaps under port.h's new name)
        for name, src in self.func_src.items():
            u = self.units[src]
            if name not in u.funcs and back.get(name) not in u.funcs and self.file_class(src) in ("game", "keep-SDK"):
                self.errors.append(f"{src}: does not define {name} under TARGET_PC (build.json says it does)")

    # -- names --------------------------------------------------------------------------------------------------------

    def function_at(self, addr: int, area: str) -> str | None:
        """The function that starts at addr, as code in `area` sees memory: main plus its own overlay (main's code
        sees overlay 2, the match)."""
        want = 1 if area == "overlay 1" else 2
        for name in self.at_vram.get(addr, ()):
            ov = self.overlay(self.func_seg[name])
            if ov is None or ov == want:
                return name
        return None

    def in_text(self, addr: int, area: str) -> str | None:
        """The code segment whose code addr lies in, as code in `area` sees memory."""
        want = 1 if area == "overlay 1" else 2
        for seg, (a, b) in self.text.items():
            ov = self.overlay(seg)
            if (ov is None or ov == want) and a <= addr < b:
                return seg
        return None

    def resolve(self, name: str, src: str, redirect: dict[str, str]) -> Target | None:
        """What `name`, used in the file `src`, stands for; None when it is nothing the tool knows."""
        u = self.units[src]
        if name in u.funcs or name in u.vars:
            return Target("local", src, name)
        name = redirect.get(name, name)
        area = self.area(src)
        cands = self.global_funcs.get(name) or self.global_funcs.get(self.renamed.get(name, ""), [])
        if cands:
            mine = [c for c in cands if (self.area(c) == "overlay 1") == (area == "overlay 1")]
            if not mine:
                return Target("overlay1", cands[0], name)
            if len(mine) > 1:
                self.errors.append(f"{name} is defined in more than one file: {mine}")
            return Target("func", mine[0], name)
        if name in self.global_vars:
            mine = [c for c in self.global_vars[name] if (self.area(c) == "overlay 1") == (area == "overlay 1")]
            if not mine:
                return Target("overlay1-data", self.global_vars[name][0], name)
            return Target("cdata", mine[0], name)
        if name in self.func_src and self.area(self.func_src[name]) != "overlay 1":
            # a function of build.json that its file does not define in C: only possible for code the port replaces
            # (rspbootTextStart is RSP microcode, kept in assembly)
            return Target("func", self.func_src[name], name)
        if name in self.symbols:
            addr = self.symbols[name]
            fn = self.function_at(addr, area)
            if fn:
                return Target("alias", self.func_src[fn], fn)
            if addr < 0x80000000:
                return Target("rom", None, name)
            seg = self.in_text(addr, area)
            if seg and self.overlay(seg) is not None:
                # inside overlay code but not where a function starts: overlay 1's data and BSS share these addresses
                # with overlay 2's code
                return Target("code-middle", None, name)
            return Target("main-code-area" if seg else "data", None, name)
        if name in self.asm_labels:
            return Target("data", None, name)
        if name in self.header_funcs:
            return Target("inline", None, name)
        if name in self.port_decls:
            return Target("port", None, name)
        return None

    def pointed(self, label: str, src: str, redirect: dict[str, str],
                seen: set[str]) -> list[tuple[str, Target | None]]:
        """The functions whose addresses the data at `label` holds, also through other data it points at."""
        out: list[tuple[str, Target | None]] = []
        for name, _where in self.data_points_to.get(label, ()):
            if name in seen:
                continue
            seen.add(name)
            t = self.resolve(name, src, redirect)
            if t is not None and t.kind == "data":
                out += self.pointed(name, src, redirect, seen)
            else:
                out.append((name, t))
        return out


# =====================================================================================================================
# The walk
# =====================================================================================================================

@dataclass
class Result:
    files: list[str]                                   # the list, sorted
    leaves: dict[str, set[str]]                        # replaced file -> the names the listed files use in it
    why: dict[str, tuple[str, int, str]]               # file -> (the file that reached it, line, the name it used)
    unresolved: list[tuple[str, int, str]]
    overlay1: list[tuple[str, int, str, str]]
    other: dict[str, set[str]]                         # data, port, rom ... -> names
    tables: dict[str, set[str]] = field(default_factory=dict)   # data label -> the functions the walk took from it


def walk(d: Decomp, roots: list[str], redirect: dict[str, str]) -> Result:
    """From the roots, follows names file by file. A file is compiled whole, so every name any of its functions uses
    counts. Replaced files (SDK, REPLACED_GAME_FILES) end the walk; overlay 1 is an error."""
    why: dict[str, tuple[str, int, str]] = {}
    queue: deque[str] = deque()
    res = Result([], defaultdict(set), why, [], [], defaultdict(set), defaultdict(set))
    for r in roots:
        src = d.func_src.get(r)
        if src is None or r not in d.units[src].funcs or d.file_class(src) not in ("game", "keep-SDK"):
            raise InputError(f"root {r}: not a game function of main or overlay 2 defined in C")
        if src not in why:
            why[src] = ("root", 0, r)
            queue.append(src)
    seen = set(queue)
    while queue:
        src = queue.popleft()
        if d.file_class(src) not in ("game", "keep-SDK"):
            continue
        res.files.append(src)
        u = d.units[src]
        for name, line in [r for f in u.funcs.values() for r in f.refs] + u.file_refs:
            t = d.resolve(name, src, redirect)
            if t is None:
                res.unresolved.append((src, line, name))
                continue
            if t.kind in ("overlay1", "overlay1-data"):
                res.overlay1.append((src, line, name, t.file or ""))
                continue
            if t.kind == "code-middle":
                res.overlay1.append((src, line, name, f"0x{d.symbols[name]:08X}, inside overlay 2's code but not "
                                                      "where a function starts: overlay 1's data or BSS"))
                continue
            targets = []
            if t.file and t.kind != "local":
                targets.append((t.file, t.name, name if name == t.name else f"{name} = {t.name}"))
            if t.kind == "data":
                res.other["data"].add(name)
                for pname, pt in d.pointed(name, src, redirect, {name}):
                    if pt is None:
                        res.unresolved.append((src, line, f"{pname} (an address in the data {name})"))
                    elif pt.kind in ("overlay1", "overlay1-data"):
                        res.overlay1.append((src, line, f"{pname} (an address in the data {name})", pt.file or ""))
                    elif pt.file and pt.kind in ("func", "alias"):
                        targets.append((pt.file, pt.name, f"{name} (data holding the address of {pt.name})"))
                        res.tables[name].add(pt.name)
            elif t.kind not in ("func", "alias", "local"):
                res.other[t.kind].add(name)
            for g, gname, how in targets:
                if d.file_class(g) in ("drop-SDK", "drop-game"):
                    orig = d.renamed.get(gname)
                    res.leaves[g].add(f"{orig} (PC: {gname})" if orig else gname)
                if g not in seen:
                    seen.add(g)
                    why[g] = (src, line, how)
                    queue.append(g)
    res.files.sort()
    return res


def find_files(root: Path, roots: list[str], redirect: dict[str, str]) -> tuple[Decomp, Result]:
    """Reads the decompilation at `root` and walks from the roots. Raises InputError when the inputs stop it."""
    d = Decomp(root)
    d.read_c()
    return d, walk(d, roots, redirect)


def problems(d: Decomp, res: Result) -> tuple[int, list[str]]:
    """The error lines of a finished walk, in the order they are printed, and the exit status they give."""
    lines = [f"error: {msg}" for msg in dict.fromkeys(d.errors)]
    status = 2 if lines else 0
    for src, line, name in sorted(set(res.unresolved)):
        lines.append(f"{src}:{line}: error: '{name}' names nothing this tool knows: not a function or variable of the "
                     "decompilation (a C file, a build.json symbol, an asm/data label) and not declared by "
                     "include/port.h")
        status = status or 1
    for src, line, name, where in sorted(set(res.overlay1)):
        lines.append(f"{src}:{line}: error: '{name}' is in overlay 1 ({where}), which this program does not have")
        status = status or 1
    return status, lines


# =====================================================================================================================
# Output
# =====================================================================================================================

# How the output names the classes of files (Decomp.file_class) and the kinds of names (Target.kind).
_CLASS_WORDS = {"game": "game", "keep-SDK": "kept SDK", "drop-SDK": "Nintendo SDK code that the port replaces",
                "drop-game": "game code that the port replaces", "overlay 1": "overlay 1"}
_KIND_WORDS = {"main-code-area": "inside main's code", "cdata": "C variable", "rom": "ROM address",
               "inline": "inline helper of a header", "port": "port function"}


def summary(d: Decomp, res: Result, set_name: str, roots: list[str]) -> list[str]:
    counts: dict[tuple[str, str], int] = defaultdict(int)
    for f in res.files:
        counts[(d.area(f), d.file_class(f))] += 1
    parts = ", ".join(f"{n} {area} {_CLASS_WORDS.get(cls, cls)}" for (area, cls), n in sorted(counts.items()))
    tables = ", ".join(f"{k} ({len(v)})" for k, v in sorted(res.tables.items())) or "none"
    return [f"port_filelist: set {set_name}, {len(res.files)} files: {parts}",
            f"  roots: {', '.join(roots)}",
            f"  function addresses taken from data: {tables}",
            f"  replaced files the set calls into: {len(res.leaves)} (--surface lists them)",
            f"  {d.game_ld_note}"]


def surface(d: Decomp, res: Result) -> str:
    """--surface: what the listed files use outside the list, one tab-separated row each. 'replaced' rows name a
    replaced file and the names used in it, 'table' rows a data label whose function addresses the walk followed, and
    the other rows every name of each other kind (data, port function ...)."""
    rows = []
    for g in sorted(res.leaves):
        stem = Path(g).stem
        why = REPLACED_GAME_FILES.get(stem) or d.sdk_lib.get(stem, "")
        rows.append(f"replaced\t{g}\t{_CLASS_WORDS[d.file_class(g)]} ({why})\t{', '.join(sorted(res.leaves[g]))}")
    for k, v in sorted(res.tables.items()):
        rows.append(f"table\t{k}\t{plural(len(v), 'function')}\t{', '.join(sorted(v))}")
    for kind in sorted(res.other):
        names = sorted(res.other[kind])
        rows.append(f"{_KIND_WORDS.get(kind, kind)}\t{plural(len(names), 'name')}\t{', '.join(names)}")
    return "".join(r + "\n" for r in rows)


def explain(d: Decomp, res: Result, path: str) -> bool:
    """--explain: prints how the walk reached a file, from the file back to a root. Returns whether it was reached."""
    path = path[2:] if path.startswith("./") else path
    f = path if path.startswith("src/") else f"src/{path}"
    if f not in res.why:
        print(f"{f}: not reached", file=sys.stderr)
        return False
    chain = []
    g = f
    while g in res.why and res.why[g][0] != "root":
        frm, line, how = res.why[g]
        chain.append(f"{g}  <-  {frm}:{line} uses {how}")
        g = frm
    chain.append(f"{g}  <-  root {res.why[g][2]}")
    if f not in res.files:
        chain.append(f"(not in the list: {f} is {_CLASS_WORDS[d.file_class(f)]})")
    print("\n".join(chain))
    return True


def depends(d: Decomp) -> list[Path]:
    """--depends: the files the list depends on, for CMake's CMAKE_CONFIGURE_DEPENDS: every file the tool read (each
    C file of build.json, the headers it includes, the data, build.json, build/game.ld, docs/sdk_functions.md) and
    the tool itself. A change to any of them can change the list."""
    return sorted(p for p in d.files_read | {Path(__file__).resolve()} if p.exists())


def write_if_changed(path: Path, text: str) -> None:
    """Writes a file only when its text changes, so that a build system watching it does not run again for nothing."""
    if not path.exists() or path.read_text(encoding="utf-8") != text:
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text, encoding="utf-8")


# =====================================================================================================================
# --self-test: the negative controls
#
# Each control copies the inputs into a temporary folder, changes the copy in one way that must make the tool fail,
# runs the tool on the copy as a separate program (as a build system does) and checks how it fails. Without the tool's
# checks each change would only make the list shorter, with no error: by one file for the old name, by many for the
# tables. The self-test also checks that each change really cuts files off the list, and that the unchanged copy
# follows both tables in full. It gets the facts it compares with by reading the files itself, not through the tool's
# own readers, so that a fault there cannot hide itself: where a file uses a name (lines_using), and which functions a
# table holds (table_functions).
# =====================================================================================================================

# An old name of a function, kept as a build.json symbol at the function's address, and the file that calls the
# function by that name (tryBeginBlockReaction was func_800E2400). Removed, the call names nothing.
ALIAS_CONTROL = ("func_800E2400", "src/code_8009D7A0/func_8009DD60.c")
# A table of function addresses in overlay 2's data, and the file that calls through it. Removed, the use names nothing.
TABLE_CONTROL = ("D_800E3660", "src/code_8009D7A0/startEntityAction.c")
# A table of function addresses in overlay 2's data, and how far into it (in bytes) the control adds a label.
SPLIT_CONTROL = ("D_800E2FF0", 0x10)

# An error line that names a file and a line: "src/x.c:12: error: 'name' ..."
_LOCATED_ERROR = re.compile(r"^(?P<file>[^\s:]+):(?P<line>\d+): error: '(?P<name>[^']*)'")


def lines_using(text: str, name: str) -> set[int]:
    """The lines of a C file on which `name` stands inside braces (a function body or an initialiser), with comments
    and string literals left out. The self-test finds a file's use of a name with this plain text search, not with the
    tool's C reader, so a fault in the reader cannot hide itself. It searches each copy afresh, so an edit that moves
    the line does not break the control."""
    def blank(m: re.Match) -> str:
        return re.sub(r"[^\n]", " ", m.group())
    code = re.sub(r"/\*.*?\*/|//[^\n]*|\"(?:\\.|[^\"\\\n])*\"|'(?:\\.|[^'\\\n])*'", blank, text, flags=re.S)
    found: set[int] = set()
    depth = 0
    for number, line in enumerate(code.split("\n"), 1):
        for m in re.finditer(r"[{}]|\b" + re.escape(name) + r"\b", line):
            if m.group() == "{":
                depth += 1
            elif m.group() == "}":
                depth -= 1
            elif depth > 0:
                found.add(number)
    return found


def edit_symbols(copy: Path, remove: str | None = None, add: tuple[str, int, str] | None = None) -> None:
    """Changes the symbols of a copy in build.json and build/game.ld alike, as build.py would write them: removes the
    symbol `remove`, or adds `add` = (name, address, the symbol after which game.ld gets the new line)."""
    path = copy / "build.json"
    build = json.loads(path.read_text(encoding="utf-8"))
    ld_path = copy / "build" / "game.ld"
    ld = ld_path.read_text(encoding="utf-8") if ld_path.exists() else None
    if remove is not None:
        if remove not in build["symbols"]:
            raise InputError(f"build.json has no symbol {remove}")
        del build["symbols"][remove]
        if ld is not None:
            ld, n = re.subn(rf"^{re.escape(remove)} = 0x[0-9A-Fa-f]+;\n", "", ld, flags=re.M)
            if n != 1:
                raise InputError(f"build/game.ld defines {remove} {n} times")
    if add is not None:
        name, addr, after = add
        if name in build["symbols"]:
            raise InputError(f"build.json has a symbol {name} already")
        build["symbols"][name] = addr
        if ld is not None:
            ld, n = re.subn(rf"^({re.escape(after)} = 0x[0-9A-Fa-f]+;\n)", rf"\g<1>{name} = 0x{addr:08X};\n", ld,
                            flags=re.M)
            if n != 1:
                raise InputError(f"build/game.ld defines {after} {n} times")
    path.write_text(json.dumps(build, indent=1), encoding="utf-8")
    if ld is not None:
        ld_path.write_text(ld, encoding="utf-8")


def located_errors(copy: Path, status: int, errors: list[str], name: str, file: str) -> str | None:
    """Part of the check of the old-name and table controls: exit status 1, and every error names `name` in `file`, on
    a line where the file uses it. Returns what is wrong, or None."""
    uses = lines_using((copy / file).read_text(encoding="utf-8", errors="replace"), name)
    if not uses:
        return f"{file} does not use {name} inside a function, so the control no longer fits the decompilation"
    if status != 1:
        return f"exit status {status}, expected 1"
    if not errors:
        return "no error line"
    for e in errors:
        m = _LOCATED_ERROR.match(e)
        if not m or m.group("file") != file or m.group("name") != name or int(m.group("line")) not in uses:
            return f"expected only errors naming '{name}' at {file}:{'/'.join(map(str, sorted(uses)))}, got: {e}"
    return None


def table_functions(root: Path, label: str) -> dict[str, str]:
    """The functions whose start addresses stand in the data of `label` in overlay 2's data, as name -> C file: every
    32-bit word from the label up to the next build.json symbol that equals the address where a function of main or
    overlay 2 starts. Read here straight from build.json and the data's bytes, not with the tool's own reader."""
    build = json.loads((root / "build.json").read_text(encoding="utf-8"))
    overlay = {s["name"]: s.get("overlay") for s in build["segments"]}
    starts: dict[int, tuple[str, str]] = {}
    for fn in build["functions"]:
        if overlay[fn["seg"]] in (None, 2) and fn["seg"] != "entry":
            starts.setdefault(fn["vram"], (fn["name"], fn.get("c") or f"src/{fn['seg']}/{fn['name']}.c"))
    addr = build["symbols"].get(label)
    for s in build["segments"]:
        if addr is None or s["kind"] != "raw" or s.get("overlay") != 2 or not s.get("incbin"):
            continue
        blob = (root / s["incbin"]).read_bytes()
        base, end = s["vram"], s["vram"] + len(blob)
        if base <= addr < end:
            stop = min([a for a in build["symbols"].values() if addr < a < end] + [end])
            first = addr + (base - addr) % 4      # the tool reads the words that start a multiple of 4 from the base
            words = [struct.unpack_from(">I", blob, a - base)[0] for a in range(first, stop - 3, 4)]
            return dict(starts[w] for w in words if w in starts)
    return {}


def self_test(tree: Path) -> int:
    """Runs the negative controls on copies of the inputs in a temporary folder and prints how each behaved. Returns
    the exit status: 0 when every control behaved as expected, 1 otherwise, 2 when the tool cannot run on the
    decompilation itself. Never writes into `tree`."""
    try:
        d, res = find_files(tree, list(SETS["match"]), {})
    except InputError as exc:
        print(f"self-test: the tool cannot run on {tree}: {exc}")
        return 2
    tree_status, tree_errors = problems(d, res)
    if tree_status != 0:
        print(f"self-test: the tool fails on {tree} itself (exit status {tree_status}), and the controls need a "
              "decompilation on which it succeeds:")
        print("".join(f"    {e}\n" for e in tree_errors), end="")
        return 2
    alias, alias_file = ALIAS_CONTROL
    table, table_file = TABLE_CONTROL
    split_table, split_offset = SPLIT_CONTROL
    # What each control must cut off, found without the tool's C reader: the file of the function at the old name's
    # address (build.json), and the functions each table holds (its bytes).
    alias_target = sorted({d.func_src[n] for n in d.at_vram.get(d.symbols.get(alias, -1), ())
                           if d.overlay(d.func_seg[n]) in (None, 2)})
    tables = {name: table_functions(tree, name) for name in (table, split_table)}
    unfit = [f"build.json has no symbol {name}" for name in (alias, table, split_table) if name not in d.symbols]
    unfit += [f"{alias} is not the address of a function of main or overlay 2"] if not alias_target else []
    unfit += [f"{name} holds no function address" for name, funcs in tables.items() if not funcs]
    unfit += [f"the decompilation's own list does not have {f}" for f in alias_target if f not in res.files]
    if unfit:
        print("self-test FAILED: the controls no longer fit the decompilation: " + "; ".join(unfit))
        return 1
    label_addr = d.symbols[split_table] + split_offset
    label = f"D_{label_addr:08X}"
    crossing = f"a run of function addresses goes on from {split_table} into {label};"
    edited = "build.json and build/game.ld" if (tree / "build" / "game.ld").exists() else "build.json"

    def unchanged(copy: Path, status: int, files: list[str], errors: list[str], err: str) -> str | None:
        if status != 0 or errors:
            return f"exit status {status}, expected 0 as on the decompilation itself"
        if files != res.files:
            return f"{len(files)} files listed, which differ from the {len(res.files)} of the decompilation itself"
        line = re.search(r"function addresses taken from data: (.*)", err)
        followed = {m.group(1): int(m.group(2)) for m in re.finditer(r"(\w+) \((\d+)\)", line.group(1) if line else "")}
        for name, funcs in tables.items():
            if followed.get(name) != len(funcs):
                return (f"the summary gives {name} {followed.get(name, 'no')} functions, but its data holds the "
                        f"addresses of {len(funcs)}")
        return None

    def cut_off(files: list[str], wanted: list[str], what: str) -> str | None:
        """The list of a control must be the decompilation's own list less some files, among them one of `wanted`."""
        if not set(files) < set(res.files):
            return "the list is not the decompilation's own list less some files"
        if not set(wanted) - set(files):
            return f"{what} is still listed, so the change did not cut it off"
        return None

    def alias_removed(copy: Path, status: int, files: list[str], errors: list[str], err: str) -> str | None:
        return located_errors(copy, status, errors, alias, alias_file) or \
            cut_off(files, alias_target, f"{' and '.join(alias_target)}, which only the old name {alias} reaches,")

    def table_removed(copy: Path, status: int, files: list[str], errors: list[str], err: str) -> str | None:
        return located_errors(copy, status, errors, table, table_file) or \
            cut_off(files, sorted(set(tables[table].values())), f"every file of the {len(tables[table])} functions "
                                                                 f"in {table}")

    def split(copy: Path, status: int, files: list[str], errors: list[str], err: str) -> str | None:
        if status != 2:
            return f"exit status {status}, expected 2"
        if not errors or any(not (e.startswith("error: ") and crossing in e) for e in errors):
            return f"expected only the error '... {crossing} ...'"
        return None

    table_sizes = " and ".join(f"{name} with {len(funcs)}" for name, funcs in tables.items())
    # (what the control does and must give, how it changes the copy, the check of the result)
    controls: list[tuple[str, dict, Callable[[Path, int, list[str], list[str], str], str | None]]] = [
        (f"the copy unchanged: the same list as the decompilation itself, and the tables {table_sizes} functions "
         "followed in full", {}, unchanged),
        (f"{alias} removed from {edited}: an error at its use in {alias_file}, and "
         f"{' and '.join(alias_target)} cut off", {"remove": alias}, alias_removed),
        (f"{table} removed from {edited}: an error at its use in {table_file}, and files of its functions cut off",
         {"remove": table}, table_removed),
        (f"{label} added {split_offset:#x} bytes into the table {split_table} ({edited}): the error that a label "
         "splits a table", {"add": (label, label_addr, split_table)}, split),
    ]
    inputs = sorted(d.files_read)
    script = str(Path(__file__).resolve())
    failed = 0
    with tempfile.TemporaryDirectory(prefix="port_filelist_selftest_") as tmp:
        print(f"port_filelist self-test: the {len(inputs)} files the tool reads in {tree}, copied for each control "
              f"into {tmp}")
        copies = [Path(tmp) / f"control{number}" for number in range(1, len(controls) + 1)]
        for copy, (title, change, check) in zip(copies, controls):
            for path in inputs:
                dest = copy / path.relative_to(tree)
                dest.parent.mkdir(parents=True, exist_ok=True)
                shutil.copyfile(path, dest)
            try:
                edit_symbols(copy, **change)
            except InputError as exc:
                print(f"self-test FAILED: cannot set up the control '{title}': {exc}")
                return 1
        # The tool on each copy, as a separate program; they all run at the same time.
        runs = [subprocess.Popen([sys.executable, "-B", "-I", script, "--decomp", str(copy), "--set", "match"],
                                 cwd=copy, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
                for copy in copies]
        for copy, (title, change, check), run in zip(copies, controls, runs):
            out, err = run.communicate()
            files = out.splitlines()
            errors = [e for e in err.splitlines() if e.startswith("error: ") or _LOCATED_ERROR.match(e)]
            problem = check(copy, run.returncode, files, errors, err)
            print(f"{'ok' if problem is None else 'FAILED':6}  {title}")
            print(f"        exit status {run.returncode}, {plural(len(files), 'file')} listed")
            print("".join(f"        {e}\n" for e in errors), end="")
            if problem is not None:
                failed += 1
                print(f"        not as expected: {problem}")
                if not errors:
                    print("".join(f"        | {e}\n" for e in err.splitlines()), end="")
    print(f"self-test {'passed' if not failed else 'FAILED'}: {len(controls) - failed} of {len(controls)} controls "
          "behaved as expected")
    return 1 if failed else 0


# =====================================================================================================================
# The command line
# =====================================================================================================================

def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0],
                                 epilog="Exit status: 0 the list is complete; 1 a name could not be found, so the list "
                                        "may be short; 2 the inputs are missing or disagree, or a wrong command line. "
                                        "How the tool works: see the comment at the top of tools/port_filelist.py.")
    here = Path(__file__).resolve().parent.parent
    ap.add_argument("--decomp", type=Path, default=here, help="the decompilation's folder (default: %(default)s)")
    ap.add_argument("--set", choices=sorted(SETS), default="match", help="which program's files (default: match)")
    ap.add_argument("--output", type=Path, metavar="FILE",
                    help="write the list to FILE (only when its text changes) instead of standard output")
    ap.add_argument("--depends", type=Path, metavar="FILE",
                    help="write the files the list depends on to FILE, one absolute path per line (for CMake's "
                         "CMAKE_CONFIGURE_DEPENDS)")
    mode = ap.add_mutually_exclusive_group()
    mode.add_argument("--explain", metavar="FILE", help="print how the walk reached FILE (a src/... path)")
    mode.add_argument("--surface", action="store_true",
                      help="print the replaced code the listed files use, the data tables followed and the other "
                           "names, instead of the list")
    mode.add_argument("--self-test", action="store_true",
                      help="run the negative controls on copies of the inputs in a temporary folder")
    ap.add_argument("--root", action="append", default=[], metavar="FUNCTION",
                    help="experiment: start the walk from FUNCTION instead of the set's roots (repeatable)")
    ap.add_argument("--redirect", action="append", default=[], metavar="OLD=NEW",
                    help="experiment: read every use of the name OLD as NEW (repeatable)")
    a = ap.parse_args()
    root = a.decomp.resolve()
    if a.self_test:
        if a.root or a.redirect or a.output or a.depends:
            ap.error("--self-test takes no --root, --redirect, --output or --depends")
        return self_test(root)
    if a.explain and (a.output or a.depends):
        ap.error("--explain takes no --output or --depends")
    if any("=" not in x for x in a.redirect):
        ap.error("--redirect takes OLD=NEW")
    for option, path in (("--output", a.output), ("--depends", a.depends)):
        if path is not None and (path.resolve() == root or root in path.resolve().parents):
            ap.error(f"{option} {path}: the file must lie outside the decompilation {root}")

    roots = a.root or list(SETS[a.set])
    set_name = "custom (--root, --redirect)" if a.root or a.redirect else a.set
    try:
        d, res = find_files(root, roots, dict(x.split("=", 1) for x in a.redirect))
    except InputError as exc:
        print(f"error: {exc}", file=sys.stderr)
        return 2
    status, errors = problems(d, res)
    if a.explain:
        for line in errors:
            print(line, file=sys.stderr)
        reached = explain(d, res, a.explain)
        return status or (0 if reached else 1)

    for line in errors + summary(d, res, set_name, roots):
        print(line, file=sys.stderr)
    text = "".join(f + "\n" for f in res.files)
    if a.surface:
        sys.stdout.write(surface(d, res))
    elif not a.output:
        sys.stdout.write(text)
    if status == 0:
        if a.output:
            write_if_changed(a.output, text)
        if a.depends:
            write_if_changed(a.depends, "".join(f"{p.as_posix()}\n" for p in depends(d)))
    elif a.output or a.depends:
        print("port_filelist: --output and --depends not written, because the list is not complete", file=sys.stderr)
    return status


def stop(signum, frame) -> None:
    """Stopped from outside (kill, a timeout): leave the way Ctrl-C does, so that --self-test's temporary folder is
    still deleted."""
    raise KeyboardInterrupt


def run_main() -> int:
    """main(), with a fault in this tool turned into exit status 2, so that a build system or a check never takes it
    for the 1 of a name that could not be found."""
    signal.signal(signal.SIGTERM, stop)
    try:
        return main()
    except KeyboardInterrupt:
        print("port_filelist: stopped before it finished", file=sys.stderr)
    except Exception:
        traceback.print_exc()
        print("port_filelist: error: the error above is a fault in tools/port_filelist.py itself, or an input it "
              "cannot read", file=sys.stderr)
    return 2


if __name__ == "__main__":
    sys.exit(run_main())
