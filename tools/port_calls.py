"""Finds the calls in the PC port's game files that would behave differently on a 64-bit PC than on the N64.

What it is for
--------------
Turnbuckle Dive, the PC port, compiles the game's own C files: for its developer program, the set that
tools/port_filelist.py --set match lists. A call works only if the caller and the called function agree on where each
argument travels.
- On the N64 (KMC GCC 2.7.2 with -mips3 -mgp32 -mfp32: the O32 calling convention) pointers, integers and floats are
  all 32 bits. The first four argument words travel in the registers $a0 to $a3, except that the first two arguments
  travel in $f12 and $f14 when they are floats and only floats come before them. A result comes back in $v0.
- So a call can go through a declaration that differs from the function's definition (an s32 where the function takes
  a pointer, or an s32 holding a float's bits where it takes an f32) and still do what the original did. The
  decompilation keeps such declarations, because the N64 code it must match depends on them.
- On a 64-bit PC (x86-64 with the System V convention, as on Linux) pointers are 64 bits, integers and pointers travel
  in rdi, rsi, rdx, rcx, r8 and r9, and floats in xmm0 to xmm7. The same call can then cut a pointer to 32 bits, or
  hand the function a different number.
This tool finds every call in the set whose caller sees the called function differently from its definition, in a way
that changes what happens on such a PC, and rates the effect.

How it works
------------
1. It takes the file set from tools/port_filelist.py --set match, or from the list given with --files-from.
2. It has clang read every C file of the main program and of overlay 2 the way the port compiles them (PC_FLAGS
   below), and reads each file's syntax tree (clang's JSON AST): the function definitions, with the type of each
   parameter and how the function uses it; every call, with the types the caller sees; the extern variables.
3. For each call made in the set it finds the definition the call reaches: a static function of the caller's own file
   first, then the global function of that name, then a function's other name: an __attribute__((alias)), or a name
   that build.json's "symbols" puts at a function's address (the N64 link resolves those through build/game.ld). A
   call through a table of function addresses in overlay 2's data (D_800E3660[i]()) reaches every function the table
   holds, and each is rated against the type the call uses.
4. For each argument it works out, on both machines, which register or stack slot the caller writes and which one the
   definition reads, and it compares the integer widths and the result. Each difference becomes a finding with a class
   and an effect (CLASSES and EFFECTS below). A call's effect is that of its worst finding.
5. It also flags an integer that the caller's PC declaration turns into a float by value where the N64 passed the
   integer itself. On the PC a game file's own declaration often stands behind #ifndef TARGET_PC, so the caller sees
   include/port_decls.h's float parameter, and C converts the integer's value: an s32 that holds 100.0f's bits
   (0x42C80000) arrives as 1120403456.0f. To know what the N64 passed, clang reads each reported file a second time as
   the N64 compiler does (N64_FLAGS below: TARGET_PC undefined), and each call is paired with the same call there. The
   argument is flagged when that view does not convert it to a float too: the declaration KMC GCC reads has an integer
   there, or no prototype. A conversion the N64 makes as well (its declaration has a float there) is the original
   game's own, and is not flagged; nor is a literal 0, which is 0.0f either way. A call written only for the PC (in an
   #ifdef TARGET_PC block, with no N64 call to pair it with) is flagged when the integer is a float's storage read
   through an integer pointer (*(s32 *)&f), or an extern variable that another file declares as a float, or an
   integer constant of 2^24 or more (a float's bits, like 0x3F800000 for 1.0f). Other forms in such a call, such as an
   s32 local or an integer-typed table that holds a float's bits, are not seen; a call written only for the PC should
   pass the f32 itself.
6. A call to a function outside the set must reach code that the port replaces (the choices at the top of
   tools/port_filelist.py, read from its text): Nintendo SDK code listed in docs/sdk_functions.md, which the port
   replaces with a stand-in, or one of the game files it replaces with its own version. Any other function outside the
   set means that the set is incomplete, and the tool stops. Such a call is rated SDK or replaced, apart from a finding
   on the caller's own side of an SDK call (see EFFECTS), which counts as for any other call.
7. It prints every call rated crash or wrong value that the --allow file does not list, then a summary by class and
   effect. --tsv writes every flagged call, and --externs the extern variables that the set's files declare with more
   than one type (a pointer in one file and an integer in another, or different widths).

Usage, from source/ (Python 3.8 or later with only its standard library, and clang; checked with clang 18):
    python3 tools/port_calls.py                             every call rated crash or wrong value, and the summary
    python3 tools/port_calls.py --tsv /tmp/calls.tsv --externs /tmp/externs.tsv
    python3 tools/port_calls.py --allow FILE                FILE lists the calls that wait for a later step
    python3 tools/port_calls.py --files-from LIST           the file set from LIST (one path per line)
    python3 tools/port_calls.py --only src/main/func_8000BDD0.c    report only the calls made in these files
                                                            (all after one --only; a second --only replaces the first)
It writes nothing but the --tsv and --externs files, which must lie outside the decompilation.

Exit status: 0 when no call is rated crash or wrong value, apart from those the --allow file lists; 1 when one is; 2
when it cannot run (no clang, no file set, an incomplete file set, a file clang gives no syntax tree for, a malformed
allow file, a fault in this tool, a reported file whose N64 view clang gives no syntax tree for).
"""
from __future__ import annotations

import argparse
import ast
import bisect
import json
import os
import re
import shutil
import struct
import subprocess
import sys
import traceback
from collections import Counter, defaultdict
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path

# ---- The port's flags for game files ------------------------------------------------------------------------------
# PC_FLAGS mirror td_game_code() in turnbuckle-dive/CMakeLists.txt, in the order CMake writes them into
# compile_commands.json: its compile definitions, its include directory (clang runs in the decompilation's folder), -g
# from the Debug build type, -std=gnu17 from C_STANDARD 17 with C_EXTENSIONS ON, then its compile options. The port's
# settings are copied into three tools: here, as PC_FLAGS in tools/port_check.py, and as PC_DEFINES in
# tools/port_filelist.py. When td_game_code() changes, change all three.
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

# The PC the calls are checked for: 64-bit x86 with the System V calling convention.
CLANG_TARGET = "--target=x86_64-linux-gnu"
# The N64 view: the text KMC GCC reads (build.json's compiler command defines nothing, so TARGET_PC is undefined and
# every game file's own declarations count), read by clang for 32-bit big-endian MIPS, as C89 with GCC's extensions
# (GCC 2.7.2's dialect, in which a call to an undeclared function declares it). The game's matched code mixes pointers
# and integers freely, which clang 18 would refuse; these flags make it accept that, as GCC 2.7.2 does. Only the
# conversions clang applies to each call's arguments are read from this view (step 5 at the top of this file).
N64_TARGET = "--target=mips-linux-gnu"
N64_FLAGS = ["-Iinclude", "-std=gnu89", "-w", "-Wno-int-conversion", "-Wno-incompatible-function-pointer-types",
             "-Wno-implicit-function-declaration", "-Wno-implicit-int"]
# Check the code and dump its syntax tree as JSON, without stopping after a number of errors.
DUMP_FLAGS = ["-fsyntax-only", "-ferror-limit=0", "-fno-color-diagnostics", "-Xclang", "-ast-dump=json"]

# Effects. A call's effect is the worst of its findings', unless the called function lies outside the set (SDK,
# replaced) or clang could not build the call (not rated). Crash and wrong value block: exit status 1.
# - crash: a pointer is cut to 32 bits, or the function reads a pointer from a place that holds something else.
# - wrong value: the function gets, or the caller gets back, a different number than on the N64.
# - clang-only: an integer argument wider than its parameter. GCC at any optimisation and clang at -O0 narrow it in the
#   called function, as the N64 code does; clang at -O1 and above counts on the caller to have narrowed it.
# - harmless: the two sides differ, but the PC does what the N64 does.
# - SDK: the called function is Nintendo SDK code that the port replaces with a stand-in, whose types decide. The
#   decompilation's C of an SDK function often declares a pointer parameter as s32, as the N64 code it matches allows,
#   where the stand-in takes the pointer; so a finding about the function's own types does not count. A finding on the
#   caller's side does (caller_side below): the caller passes an integer where the function reads a pointer, reads a
#   pointer result as an integer, or leaves out an argument. Such a call is rated crash or wrong value like any other.
# - replaced: the called function is game code that the port replaces with its own version, which decides.
# - not rated: clang reported an error inside the call (the compile check covers it).
CRASH, WRONG, CLANG_ONLY, HARMLESS = "crash", "wrong value", "clang-only", "harmless"
SDK, REPLACED, NOT_RATED = "SDK", "replaced", "not rated"
EFFECTS = (CRASH, WRONG, CLANG_ONLY, HARMLESS, SDK, REPLACED, NOT_RATED)
SEVERITY = {CRASH: 4, WRONG: 3, CLANG_ONLY: 2, HARMLESS: 1, NOT_RATED: 0}
BLOCKING = (CRASH, WRONG)

# Classes of findings; docs/port.md's section on this tool explains each letter.
CLASSES = {
    "A1": "pointer into an integer parameter",
    "A2": "integer where a pointer is read",
    "B": "pointer and integer results mixed up",
    "C1": "float and integer mixed up",
    "C2": "64-bit argument after the N64's pad",
    "D": "argument missing",
    "E": "result of a void function used",
    "F1": "integer wider than the parameter",
    "F2": "narrow result read at full width",
    "G": "function pointer made from integers",
    "H": "struct passed by value",
    "O": "other difference",
    "Z": "difference without effect",
    "X": "compile error in the call",
}


def caller_side(finding: tuple, d: dict) -> bool:
    """Whether a finding is the caller's own fault, whatever types the called function has: an integer passed where
    the function reads a pointer (A2), a missing argument (D), or a pointer result read as an integer (B)."""
    return finding[0] in ("A2", "D") or (finding[0] == "B" and d["ret_class"][0] == "p")


def plural(n: int, word: str) -> str:
    """'1 file', '2 files'."""
    return f"{n} {word}{'s' * (n != 1)}"


class Failure(Exception):
    """A reason the tool cannot run (exit status 2)."""


# ---------------------------------------------------------------------------------------------------------------------
# C types as clang prints them, sorted into the few kinds that decide how a value travels.
# ---------------------------------------------------------------------------------------------------------------------
_QUALIFIERS = re.compile(r"\b(?:const|volatile|restrict|__restrict|_Atomic)\b")
_ANONYMOUS = re.compile(r"\((?:unnamed|anonymous) [^)]*\)")   # "struct (unnamed struct at include/x.h:3:9)"
_ATTRIBUTE = re.compile(r"\s*__attribute__\(\(.*\)\)\s*$")
_INTEGERS = {"char": (1, "s"), "signed char": (1, "s"), "unsigned char": (1, "u"), "_Bool": (1, "u"),
             "short": (2, "s"), "unsigned short": (2, "u"), "int": (4, "s"), "unsigned int": (4, "u")}
KIND_WORDS = {"p": "a pointer", "f": "a float", "d": "a double", "i": "an integer of 4 bytes or less",
              "q": "a 64-bit integer", "L": "a long", "s": "a struct", "v": "void", "?": "a value of unknown type"}


def _clean(t: str) -> str:
    return re.sub(r"\s+", " ", _QUALIFIERS.sub("", t)).strip()


def type_class(t: str | None, typedefs: dict) -> tuple:
    """(kind, bytes, sign) of a type. The kinds are the keys of KIND_WORDS: p pointer (arrays and functions are passed
    as pointers), f float, d double, i integer of 4 bytes or less, q long long (8 bytes on both machines), L long (4
    bytes on the N64, 8 on the PC), s struct or union passed by value, v void, ? anything else."""
    if not t:
        return ("?", 0, "")
    t = _clean(t)
    for _ in range(10):                               # follow typedefs: s32 -> int
        if t not in typedefs or typedefs[t] == t:
            break
        t = _clean(typedefs[t])
    bare = _ANONYMOUS.sub("", t)
    if "*" in bare or "[" in bare or "(" in bare:
        return ("p", 8, "u")
    if bare in ("float", "double", "long double", "void"):
        return {"float": ("f", 4, ""), "void": ("v", 0, "")}.get(bare, ("d", 8, ""))
    if re.match(r"(?:struct|union)\b", bare):
        return ("s", 0, "")
    if bare.startswith("enum "):
        return ("i", 4, "u")
    if bare in ("long long", "unsigned long long", "long", "unsigned long"):
        return ("q" if "long long" in bare else "L", 8, "u" if bare.startswith("unsigned") else "s")
    if bare in _INTEGERS:
        return ("i",) + _INTEGERS[bare]
    return ("?", 0, bare)


def split_function_type(t: str) -> tuple:
    """'RET (PARAMS)', or a pointer to one ('RET (*)(PARAMS)'), as (RET, PARAMS); PARAMS is None for other types."""
    t = _ATTRIBUTE.sub("", t.strip())
    if not t.endswith(")"):
        return t, None
    depth = 0
    for i in range(len(t) - 1, -1, -1):
        depth += {")": 1, "(": -1}.get(t[i], 0)
        if depth == 0:
            ret = t[:i].strip()
            return (ret[:-3].strip() if ret.endswith("(*)") else ret), t[i + 1:-1]
    return t, None


def split_parameters(text: str | None) -> list | None:
    """A function type's parameter types: None when it has no prototype ("()"), [] for "(void)"."""
    if text is None or not text.strip():
        return None
    if text.strip() == "void":
        return []
    out, depth, cur = [], 0, ""
    for ch in text:
        depth += {"(": 1, "[": 1, ")": -1, "]": -1}.get(ch, 0)
        if ch == "," and depth == 0:
            out.append(cur.strip())
            cur = ""
        else:
            cur += ch
    return out + [cur.strip()]


def declaration(t: str, name: str) -> str:
    """'Wrestler *' and 'w' as 'Wrestler *w'; 's32' and 'x' as 's32 x'."""
    return f"{t}{name}" if t.endswith("*") else f"{t} {name}".strip()


# ---------------------------------------------------------------------------------------------------------------------
# Reading one file's syntax tree. This part runs in worker processes, one file at a time.
# ---------------------------------------------------------------------------------------------------------------------
def _discards(parent: str, index: int, count: int) -> bool:
    """True when the child at index of a node of kind parent is a statement, whose value nobody uses."""
    if parent in ("CompoundStmt", "DefaultStmt", "LabelStmt"):
        return True
    if parent == "CaseStmt":
        return index == count - 1
    if parent in ("IfStmt", "WhileStmt", "SwitchStmt"):
        return index > 0
    if parent == "DoStmt":
        return index == 0
    if parent == "ForStmt":                     # children: init, condition variable, condition, increment, body
        return index in (0, 3, 4)
    return False


def _qual(node: dict) -> str:
    return (node.get("type") or {}).get("qualType", "")


def _desugared(node: dict) -> str:
    t = node.get("type") or {}
    return t.get("desugaredQualType") or t.get("qualType", "")


def _children(node: dict) -> list:
    return [c for c in node.get("inner", ()) if isinstance(c, dict)]


def _under(node: dict, kinds: tuple) -> dict:
    """The expression under any number of nodes of the given kinds (implicit casts, parentheses)."""
    while node.get("kind") in kinds and node.get("inner"):
        node = node["inner"][0]
    return node


def _constant(node: dict):
    """('zero' | 'int' | 'float', value) for a literal under casts, parentheses and a unary minus; else None."""
    negative = False
    while node.get("kind") in ("ImplicitCastExpr", "CStyleCastExpr", "ParenExpr", "UnaryOperator") \
            and node.get("inner"):
        if node["kind"] == "UnaryOperator":
            if node.get("opcode") not in ("-", "+"):
                return None
            negative ^= node.get("opcode") == "-"
        node = node["inner"][0]
    if node.get("kind") in ("IntegerLiteral", "CharacterLiteral"):
        v = -int(node["value"]) if negative else int(node["value"])
        return ("zero" if v == 0 else "int", v)
    if node.get("kind") == "FloatingLiteral":
        return ("float", -float(node["value"]) if negative else float(node["value"]))
    return None


def _cast_pointers(node: dict) -> list:
    """For an expression that reads memory through a pointer (*p, p[i]), the types the pointer had before the C casts
    the caller wrote on it, as clang prints them: ['f32 *'] for *(s32 *)&f. facts() then tells whether one of them
    points to floats: the value read is then a float's bits."""
    node = _under(node, ("ParenExpr",))
    if not ((node.get("kind") == "UnaryOperator" and node.get("opcode") == "*")
            or node.get("kind") == "ArraySubscriptExpr") or not node.get("inner"):
        return []
    pointer, cast_seen, out = node["inner"][0], False, []
    while pointer.get("kind") in ("ImplicitCastExpr", "CStyleCastExpr", "ParenExpr") and pointer.get("inner"):
        cast_seen = cast_seen or pointer.get("kind") == "CStyleCastExpr"
        pointer = pointer["inner"][0]
        if cast_seen:
            out.append(_desugared(pointer))
    return out


def _variable(node: dict) -> str | None:
    """The variable an expression reads, directly or as an element of it (x, x[i]); else None."""
    node = _under(node, ("ParenExpr", "ImplicitCastExpr"))
    if node.get("kind") == "ArraySubscriptExpr" and node.get("inner"):
        node = _under(node["inner"][0], ("ParenExpr", "ImplicitCastExpr"))
    if node.get("kind") != "DeclRefExpr":
        return None
    ref = node.get("referencedDecl") or {}
    return ref.get("name") if ref.get("kind") == "VarDecl" else None


def _has_error(node: dict) -> bool:
    """True if clang could not build part of this expression: it leaves a RecoveryExpr where the error was."""
    stack = [node]
    while stack:
        n = stack.pop()
        if n.get("kind") == "RecoveryExpr" or _qual(n) == "<dependent type>":
            return True
        stack.extend(_children(n))
    return False


def _function_reference(node: dict):
    """(name, cast type) when the expression names a function, through implicit casts, parentheses and C casts (cast
    type: the outermost C cast's type, or None); else None."""
    cast = None
    while node:
        kind = node.get("kind")
        if kind == "DeclRefExpr":
            ref = node.get("referencedDecl") or {}
            return (ref.get("name"), cast) if ref.get("kind") == "FunctionDecl" else None
        if kind == "CStyleCastExpr":
            cast = cast or _qual(node)
        elif kind not in ("ImplicitCastExpr", "ParenExpr"):
            return None
        node = node["inner"][0] if node.get("inner") else None
    return None


def _chain_entry(node: dict, i: int) -> tuple:
    """What node does with the value of its child i, for the chain that result_findings reads: ("paren",) for a node
    that passes the value on unchanged, ("cast", cast kind, type), ("binary", operator, i, the other operand's
    constant or None), ("unary", operator), or ("other", kind)."""
    kind = node.get("kind")
    if kind == "ParenExpr" or (kind == "BinaryOperator" and node.get("opcode") == "," and i == 1) or \
            (kind == "ConditionalOperator" and i > 0):
        return ("paren",)
    if kind in ("ImplicitCastExpr", "CStyleCastExpr"):
        return ("cast", node.get("castKind"), _desugared(node))
    if kind == "BinaryOperator":
        children = _children(node)
        return ("binary", node.get("opcode"), i, _constant(children[1 - i]) if len(children) == 2 else None)
    if kind == "UnaryOperator":
        return ("unary", node.get("opcode"))
    return ("other", kind)


def _use_tag(use) -> str:
    """How a function uses one of its parameters, in a word or two, from the expression the parameter appears in."""
    if use == "argument":
        return "passed on"
    if not isinstance(use, tuple):
        return "other"
    if use[0] in ("implicit cast", "cast") and use[1] == "IntegralToPointer":
        return "cast to a pointer"
    if use[0] == "binary":
        if use[1] == "=":
            return "stored" if use[2] == 1 else "assigned"
        if use[1] in ("==", "!=", "<", ">", "<=", ">="):
            return "compared"
        return "tested" if use[1] in ("&&", "||") else "arithmetic"
    return {"return": "returned", "init": "copied", "unary": "arithmetic", "subscript": "index",
            "condition": "tested"}.get(use[0], "other")


class AstReader:
    """Collects what the checker needs from one file's clang JSON AST: the function definitions in the file, the calls
    they make, the extern variables the file declares, and its typedefs (to tell what s32 or u64 stands for)."""

    def __init__(self, rel: str, source: bytes):
        self.rel = rel
        self.source = source
        self.line_starts = [0] + [m.end() for m in re.finditer(rb"\n", source)]
        self.typedefs: dict = {}
        self.definitions: list = []
        self.calls: list = []
        self.externs: list = []
        self.param_index: dict = {}       # id of a ParmVarDecl -> (definition, parameter number)

    # -- Locations. Clang gives each a byte offset in its file; one without "includedFrom" lies in the file itself.
    @staticmethod
    def _offset(loc) -> int | None:
        if not loc:
            return None
        loc = loc.get("expansionLoc", loc)         # in a macro: where the macro is used
        if "offset" not in loc or "includedFrom" in loc:
            return None
        return loc["offset"]

    def _line(self, node: dict, key: str = "loc") -> int | None:
        """The line of a node's location (key "loc"), or of where its source range begins (key "range")."""
        loc = (node.get("range") or {}).get("begin") if key == "range" else node.get("loc")
        offset = self._offset(loc)
        return None if offset is None else bisect.bisect_right(self.line_starts, offset)

    def _text(self, node: dict) -> str:
        r = node.get("range") or {}
        b, e = self._offset(r.get("begin")), self._offset(r.get("end"))
        if b is None or e is None:
            return ""
        end = r["end"].get("expansionLoc", r["end"])
        return " ".join(self.source[b:e + end.get("tokLen", 0)].decode("latin-1").split())[:160]

    # -- The file's top level.
    def read(self, tree: dict) -> None:
        for node in tree.get("inner", ()):
            if node.get("kind") == "TypedefDecl":
                self.typedefs[node.get("name")] = _desugared(node)
            if self._line(node) is None:
                continue                            # declared in a header, or by clang itself
            if node.get("kind") == "FunctionDecl":
                self._function(node)
            elif node.get("kind") == "VarDecl" and node.get("storageClass") == "extern":
                self.externs.append({"name": node.get("name"), "type": _qual(node), "line": self._line(node)})

    def _function(self, node: dict) -> None:
        inner = node.get("inner", ())
        parms = [c for c in inner if c.get("kind") == "ParmVarDecl"]
        body = next((c for c in inner if c.get("kind") == "CompoundStmt"), None)
        alias = next((c.get("aliasee") for c in inner if c.get("kind") == "AliasAttr"), None)
        if body is None and alias is None:
            return                                  # a declaration: each call keeps the type it saw
        d = {"name": node.get("name"), "file": self.rel, "line": self._line(node), "type": _qual(node),
             "static": node.get("storageClass") == "static", "alias": alias, "variadic": bool(node.get("variadic")),
             "params": [(_qual(p), _desugared(p), p.get("name") or "") for p in parms],
             "reads": [0] * len(parms), "uses": [Counter() for _ in parms]}
        self.definitions.append(d)
        if body is not None:
            for i, p in enumerate(parms):
                self.param_index[p.get("id")] = (d, i)
            self._walk(body, d["name"], {"discarded": False, "use": None})

    # -- Function bodies. ctx says whether the node's value is discarded and how its parent uses it.
    def _walk(self, node: dict, caller: str, ctx: dict) -> None:
        kind = node.get("kind")
        if kind == "CallExpr":
            self._call(node, caller, ctx)
        elif kind == "RecoveryExpr":
            self._failed_call(node, caller)
        elif kind == "DeclRefExpr":
            ref = node.get("referencedDecl") or {}
            if ref.get("kind") == "ParmVarDecl" and ref.get("id") in self.param_index:
                d, i = self.param_index[ref["id"]]
                d["reads"][i] += 1
                d["uses"][i][_use_tag(ctx["use"])] += 1
        elif kind == "VarDecl" and node.get("storageClass") == "extern":
            self.externs.append({"name": node.get("name"), "type": _qual(node), "line": self._line(node)})
        elif kind == "TypedefDecl":
            self.typedefs[node.get("name")] = _desugared(node)
        children = _children(node)
        for i, child in enumerate(children):
            self._walk(child, caller, self._child_context(node, i, len(children), ctx))

    @staticmethod
    def _child_context(node: dict, i: int, count: int, ctx: dict) -> dict:
        """The context of child i of node: whether its value is discarded, how node uses it ("use"), and the chain of
        what the nodes above do with it, nearest first (for result_findings' low_bits_use)."""
        out = AstReader._use_context(node, i, count, ctx)
        out["chain"] = (_chain_entry(node, i),) + ctx.get("chain", ())[:7]
        return out

    @staticmethod
    def _use_context(node: dict, i: int, count: int, ctx: dict) -> dict:
        kind, same = node.get("kind"), dict(ctx)
        if kind == "ParenExpr":
            return same
        if kind == "ImplicitCastExpr":
            cast = node.get("castKind")
            return same if cast in ("LValueToRValue", "NoOp") else \
                {"discarded": ctx["discarded"], "use": ("implicit cast", cast, _desugared(node))}
        if kind == "CStyleCastExpr":
            return {"discarded": _desugared(node) == "void", "use": ("cast", node.get("castKind"), _desugared(node))}
        if kind == "BinaryOperator" and node.get("opcode") == ",":
            return {"discarded": True, "use": None} if i == 0 else same
        if kind == "ConditionalOperator":
            return {"discarded": False, "use": ("condition",)} if i == 0 else same
        use = {"BinaryOperator": ("binary", node.get("opcode"), i), "UnaryOperator": ("unary", node.get("opcode")),
               "ReturnStmt": ("return",), "VarDecl": ("init", _desugared(node)),
               "ArraySubscriptExpr": ("subscript",)}.get(kind)
        if kind == "CallExpr":
            use = None if i == 0 else "argument"
        return {"discarded": _discards(kind, i, count), "use": use}

    def _argument(self, a: dict) -> dict:
        """One argument: its type as passed, the type written before implicit conversions, those conversions, a
        literal value, a cast the caller wrote, its text, and whether clang could build it."""
        conversions, e = [], a
        while e.get("kind") == "ImplicitCastExpr" and e.get("inner"):
            if e.get("castKind") != "LValueToRValue":
                conversions.append(e.get("castKind"))
            e = e["inner"][0]
        written = _under(e, ("ParenExpr",))
        cast = None
        if written.get("kind") == "CStyleCastExpr" and written.get("inner"):
            cast = (written.get("castKind"), _desugared(written["inner"][0]))
        return {"passed": _desugared(a), "written": _desugared(e), "conversions": conversions,
                "constant": _constant(a), "cast": cast, "text": self._text(a), "error": _has_error(a),
                "cast_pointers": _cast_pointers(e), "variable": _variable(e)}

    def _call(self, node: dict, caller: str, ctx: dict) -> None:
        inner, line = node.get("inner", ()), self._line(node, "range")
        if not inner or line is None:
            return
        ref = _function_reference(inner[0])
        c = {"caller": caller, "line": line, "discarded": ctx["discarded"], "use": ctx["use"],
             "chain": ctx.get("chain", ()), "args": [self._argument(a) for a in inner[1:]], "text": self._text(node),
             "callee": None}
        if ref is None:                                   # through a function pointer
            c.update(how="indirect", view=_desugared(inner[0]), table=self._table_read(inner[0]),
                     base=self._first_name(inner[0]))
        elif ref[1]:                                      # through a C cast of the function's name
            c.update(how="cast", callee=ref[0], view=ref[1])
        else:                                             # the type of the declaration the call sees
            c.update(how="direct", callee=ref[0], view=_qual(_under(inner[0], ("ImplicitCastExpr", "ParenExpr"))))
        c["error"] = any(a["error"] for a in c["args"]) or _has_error(inner[0])
        self.calls.append(c)

    def _failed_call(self, node: dict, caller: str) -> None:
        """A call clang could not build (too few arguments, for example) is a RecoveryExpr that holds the function
        and the arguments. It is kept as a call that cannot be rated."""
        inner, line = node.get("inner", ()), self._line(node, "range")
        ref = _function_reference(inner[0]) if inner else None
        if ref is not None and line is not None:
            self.calls.append({"caller": caller, "line": line, "how": "direct", "callee": ref[0], "view": "",
                               "discarded": True, "use": None, "args": [], "text": self._text(node), "error": True})

    @staticmethod
    def _first_name(node: dict) -> str | None:
        stack = [node]
        while stack:
            n = stack.pop()
            if n.get("kind") == "DeclRefExpr":
                return (n.get("referencedDecl") or {}).get("name")
            stack.extend(reversed(_children(n)))
        return None

    def _table_read(self, callee: dict) -> str | None:
        """For a call through a function pointer: why that pointer cannot be right on the PC, if it is made from an
        integer, or read through a pointer to integers (u8 *, s32 *: on the N64 a table of 4-byte entries, which a
        64-bit pointer does not fit); else None."""
        stack = [callee]
        while stack:
            n = stack.pop()
            inner = _children(n)
            if n.get("kind") in ("ImplicitCastExpr", "CStyleCastExpr") and inner:
                to, frm = _desugared(n), _desugared(inner[0])
                if "(*" in to and n.get("castKind") == "IntegralToPointer":
                    return f"makes the function pointer from the integer {self._text(inner[0])} ({frm})"
                if "(**)" in to and n.get("castKind") == "BitCast" and frm.endswith("*") \
                        and type_class(frm[:-1], self.typedefs)[0] in "iqL":
                    return f"reads the function pointer through a {frm}, at {self._text(inner[0])}"
            stack.extend(inner)
        return None

    # -- The result, with every type sorted into its kind.
    def facts(self) -> dict:
        td = self.typedefs
        for d in self.definitions:
            ret, plist = split_function_type(d["type"])
            d.update(ret=ret, ret_class=type_class(ret, td), uses=[dict(u) for u in d["uses"]],
                     knr=split_parameters(plist) is None and len(d["params"]) > 0,
                     param_classes=[type_class(desugared, td) for _, desugared, _ in d["params"]])
        for c in self.calls:
            ret, plist = split_function_type(c["view"])
            c["view_ret_class"] = type_class(ret, td) if plist is not None else ("i", 4, "s")
            for a in c["args"]:
                a["class"] = type_class(a["passed"], td)
                a["float_storage"] = any(t.endswith("*") and type_class(t[:-1], td)[0] in "fd"
                                         for t in a.pop("cast_pointers"))
            use = c["use"]
            c["use_class"] = type_class(use[2], td) if isinstance(use, tuple) and len(use) > 2 \
                and isinstance(use[2], str) else None
            c["chain"] = [(e[0], e[1], type_class(e[2], td)) if e[0] == "cast" else e for e in c.get("chain", ())]
        for v in self.externs:
            v["view"] = extern_view(v["type"], td)
        return {"file": self.rel, "definitions": self.definitions, "calls": self.calls, "externs": self.externs}


def extern_view(qual: str, typedefs: dict) -> str:
    """An extern variable's type in a form in which two files' declarations can be compared: typedefs resolved to the
    fixed-size names (s32, u8 ...), array sizes dropped, 'struct:NAME' for a struct, 'fnptr/...' for a function
    pointer."""
    scalar = {"signed char": "s8", "char": "s8", "unsigned char": "u8", "short": "s16", "unsigned short": "u16",
              "int": "s32", "unsigned int": "u32", "long long": "s64", "unsigned long long": "u64", "float": "f32",
              "double": "f64", "long": "long", "unsigned long": "ulong", "_Bool": "u8"}
    shape = re.compile(r"^(.*?)\s*((?:\*|\s)*)((?:\[[^\]]*\])*)$")    # base type, stars, array brackets
    t = _clean(qual)
    if re.search(r"\(\s*\*", _ANONYMOUS.sub("", t)):
        return "fnptr/" + t
    m = shape.match(t)
    base, stars, arrays = m.group(1).strip(), m.group(2).replace(" ", ""), re.sub(r"\[[^\]]*\]", "[]", m.group(3))
    for _ in range(8):
        if base not in typedefs:
            break
        target = _clean(typedefs[base])
        if re.match(r"(?:struct|union) \((?:unnamed|anonymous) ", target):
            base = "struct:" + base               # a typedef of an unnamed struct: the typedef's name tells it apart
            break
        mm = shape.match(target)
        base = mm.group(1).strip()
        stars = mm.group(2).replace(" ", "") + stars
        arrays += re.sub(r"\[[^\]]*\]", "[]", mm.group(3))
    if _ANONYMOUS.search(base):                    # an unnamed struct: where it is written tells it apart
        base = "struct:anonymous@" + base.split(" at ")[-1].rstrip(")")
    base = scalar.get(base, base)
    if re.match(r"(?:struct|union) ", base):
        base = "struct:" + base.split(" ", 1)[1]
    return base + stars + arrays


def read_file(job: tuple) -> dict:
    """Runs clang on one file and returns its facts (each worker process runs this). With n64 set, clang also reads
    the file's N64 view, and each call's arguments get what the N64 view does with them (pair_with_n64)."""
    clang, root, rel, n64 = job
    sys.setrecursionlimit(20000)
    source = (Path(root) / rel).read_bytes()
    # Run in the decompilation's folder on the relative path, as the PC_FLAGS' -Iinclude needs; clang then names
    # files by relative paths too (in "struct (unnamed struct at src/x.c:8:8)", for example).
    tree, stderr = _syntax_tree(clang, root, rel, [CLANG_TARGET, *PC_FLAGS])
    if tree is None:
        return {"file": rel, "failed": stderr[-1500:] or "no syntax tree"}
    reader = AstReader(rel, source)
    reader.read(tree)
    facts = reader.facts()
    facts["errors"] = re.findall(r"^" + re.escape(rel) + r":(\d+):\d+: error: (.*)$", stderr, re.M)
    if n64:
        n64_tree, n64_stderr = _syntax_tree(clang, root, rel, [N64_TARGET, *N64_FLAGS])
        if n64_tree is None:
            facts["n64_failed"] = n64_stderr[-1500:] or "no syntax tree"
        else:
            n64_reader = AstReader(rel, source)
            n64_reader.read(n64_tree)
            facts["n64_unpaired"] = pair_with_n64(facts["calls"], n64_reader.facts()["calls"])
    return facts


def _syntax_tree(clang: str, root: str, rel: str, flags: list) -> tuple:
    """(clang's JSON syntax tree of one file, or None, and clang's messages)."""
    proc = subprocess.run([clang, *flags, *DUMP_FLAGS, rel], cwd=root, capture_output=True)
    stderr = proc.stderr.decode("utf-8", "replace")
    try:
        return json.loads(proc.stdout), stderr
    except ValueError:
        return None, stderr


def pair_with_n64(calls: list, n64_calls: list) -> int:
    """Gives each call of the PC view the N64 view's facts of its arguments: for each argument, whether the N64 view
    converts it from an integer to a float, and its kind there (KIND_WORDS). A call is paired with the N64 call to the
    same function from the same function on the same line (in the order they come on that line); a call with no such
    partner, as in an #ifdef TARGET_PC block, is paired by its place among the calls to that function from that
    function, when both views make the same number of them. Otherwise, and for an argument the N64 call does not
    have, the facts are None. Returns the number of PC calls left without a partner."""
    on_line, in_function = defaultdict(list), defaultdict(list)
    for c in n64_calls:
        on_line[(c["caller"], c["callee"], c["line"])].append(c)
        in_function[(c["caller"], c["callee"])].append(c)
    pc_on_line, pc_in_function = defaultdict(int), defaultdict(int)
    pc_count = Counter((c["caller"], c["callee"]) for c in calls)
    unpaired = 0
    for c in calls:
        key, line_key = (c["caller"], c["callee"]), (c["caller"], c["callee"], c["line"])
        k, n = pc_on_line[line_key], pc_in_function[key]
        pc_on_line[line_key] += 1
        pc_in_function[key] += 1
        partner = None
        if k < len(on_line.get(line_key, ())):
            partner = on_line[line_key][k]
        elif len(in_function.get(key, ())) == pc_count[key]:
            partner = in_function[key][n]
        unpaired += partner is None
        for i, a in enumerate(c["args"]):
            b = partner["args"][i] if partner is not None and i < len(partner["args"]) else None
            a["n64"] = None if b is None or b["error"] else \
                {"to_float": "IntegralToFloating" in b["conversions"], "kind": b["class"][0], "passed": b["passed"]}
    return unpaired


# ---------------------------------------------------------------------------------------------------------------------
# The two calling conventions. Each model gives, for a list of value kinds in order, the place each one travels in.
# ---------------------------------------------------------------------------------------------------------------------
def o32_places(kinds: list) -> list:
    """The N64 (O32): argument words of 4 bytes; an 8-byte value (double, long long) starts on an even word. The first
    four words travel in $a0-$a3, the rest on the stack, except that the first two arguments travel in $f12 and $f14
    when they are floats or doubles and only floats or doubles come before them. A struct is not modelled (None)."""
    places, word, floats_only = [], 0, True
    for index, (kind, _, _) in enumerate(kinds):
        size = 8 if kind in "dq" else 4
        if size == 8 and word % 2:
            word += 1
        if kind in "fd" and index < 2 and floats_only:
            places.append(("$f", 12 + 2 * index))
        elif kind in "s?":
            places.append(None)
        else:
            places.append(("$a", word) if word < 4 else ("N64 stack", word))
        floats_only = floats_only and kind in "fd"
        word += size // 4
    return places


def sysv_places(kinds: list) -> list:
    """The PC (x86-64 System V): integers and pointers in the next of six integer registers, floats and doubles in the
    next of eight xmm registers, the rest on the stack in order. A struct is not modelled (None)."""
    places, gpr, xmm, stack = [], 0, 0, 0
    for kind, _, _ in kinds:
        if kind in "ipqL" and gpr < 6:
            places.append(("gpr", gpr))
            gpr += 1
        elif kind in "fd" and xmm < 8:
            places.append(("xmm", xmm))
            xmm += 1
        elif kind in "ipqLfd":
            places.append(("PC stack", stack))
            stack += 1
        else:
            places.append(None)
    return places


def sources(args: list, params: list, model) -> list:
    """For each parameter: the number of the argument the caller wrote where the function reads the parameter, None
    when no argument went there, '?' when that place is not modelled."""
    written = {place: i for i, place in enumerate(model(args)) if place is not None}
    return ["?" if place is None else written.get(place) for place in model(params)]


def compare(args: list, params: list, constants: list) -> list:
    """The parameters whose value can differ on the PC from the N64, as (parameter number, code, words)."""
    n64, pc = sources(args, params, o32_places), sources(args, params, sysv_places)
    out = []
    for j, p in enumerate(params):
        a64, apc = n64[j], pc[j]
        if a64 == "?" or apc == "?":
            out.append((j, "struct", "a struct passed by value travels differently"))
        elif a64 is None and apc is None:
            if j < len(args):
                out.append((j, "register file", f"argument {j + 1} is {KIND_WORDS[args[j][0]]}, and on both machines "
                                                "it travels in another kind of register than the function reads"))
            else:
                out.append((j, "missing", "gets no argument"))
        elif apc != a64:
            if apc is None:
                words = f"the N64 reads argument {a64 + 1}; the PC reads a register that no argument was put in"
            elif a64 is None:
                words = f"the N64 reads a register that no argument was put in; the PC reads argument {apc + 1}"
            else:
                words = f"the N64 reads argument {a64 + 1}; the PC reads argument {apc + 1}"
            out.append((j, "moved", words))
        else:
            a, kinds = args[a64], args[a64][0] + p[0]
            if kinds == "ip":
                c = constants[a64]
                out.append((j, "null" if c and c[0] == "zero" else "pointer from integer", ""))
            elif kinds == "pi":
                out.append((j, "integer from pointer", ""))
            elif kinds in ("iq", "qi", "iL", "qL"):
                out.append((j, "width", f"the caller passes {KIND_WORDS[a[0]]}, the function reads {KIND_WORDS[p[0]]}"))
            elif a[0] == p[0] == "i":
                if a[1] > p[1]:
                    out.append((j, "narrow", f"the caller passes a {a[1]}-byte integer"))
                elif a[1] == p[1] < 4 and a[2] != p[2]:
                    out.append((j, "narrow", "the caller passes it with the other signedness"))
            elif a[0] != p[0] and kinds not in ("Li", "Lq"):
                out.append((j, "bits", f"the caller passes {KIND_WORDS[a[0]]}, the function reads {KIND_WORDS[p[0]]} "
                                       "from the same place"))
    return out


def promote(kind: tuple) -> tuple:
    """A parameter of an old-style (K&R) definition receives its argument promoted: a float as a double, a narrow
    integer as an int."""
    if kind[0] == "f":
        return ("d", 8, "")
    return ("i", 4, "s") if kind[0] == "i" and kind[1] < 4 else kind


# ---------------------------------------------------------------------------------------------------------------------
# Rating a call.
# ---------------------------------------------------------------------------------------------------------------------
def float_conversion(i: int, a: dict, callee: str, float_externs: dict) -> str | None:
    """Why argument i (facts a) reaches the function as another number on the PC than on the N64, when the caller's PC
    declaration converts it from an integer to a float (step 5 at the top of this file); else None. float_externs
    names the extern variables that a file of the set declares as a float, with one such declaration's place."""
    if "IntegralToFloating" not in a["conversions"]:
        return None
    k, n64 = a["constant"], a.get("n64")
    if k and k[0] == "zero":
        return None                                       # 0 and 0.0f have the same bits
    if n64 is not None and n64["to_float"]:
        return None                                       # the N64's declaration converts it too
    if k and k[0] == "int" and (n64 is not None or abs(k[1]) >= 1 << 24):
        # A constant of 2^24 or more is a float's bits: the N64 code passed 0x3F800000 for 1.0f through an s32.
        bits = struct.unpack(">f", (k[1] & 0xFFFFFFFF).to_bytes(4, "big"))[0]
        return (f"argument {i + 1} is the integer {k[1]:#x}, which the declaration turns into the float "
                f"{float(k[1]):.0f}; as a float's bits it is {bits:g}")
    what = f"argument {i + 1} ({a['text'][:40]})"
    if n64 is not None:
        n64_words = f"passes {KIND_WORDS[n64['kind']]} ({n64['passed']})"
        if n64["kind"] in "iqL":
            n64_words = "passes the integer's bits, which the function reads as a float"
        return (f"{what} is an integer ({a['written']}), which the caller's PC declaration of {callee} converts to a "
                f"float by value; the declaration the N64 compiler reads has no float there, so the N64 {n64_words}")
    if a["float_storage"]:
        return (f"{what} reads a float's storage as an integer ({a['written']}), and the caller's declaration "
                "converts that integer to a float by value")
    if a["variable"] in float_externs:
        return (f"{what} reads {a['variable']} as an integer ({a['written']}), but {float_externs[a['variable']]} "
                "declares it as a float, so it holds a float's bits, which the caller's declaration converts to a "
                "float by value")
    return None


def call_findings(call: dict, d: dict, float_externs: dict | None = None) -> list:
    """The differences between a call and the definition it reaches, as (class, effect, words): the parameters in
    order, then the result. float_externs: see float_conversion."""
    float_externs = float_externs or {}
    if call["error"]:
        return [("X", NOT_RATED, "clang reported an error inside this call, so the call cannot be read")]
    params = [promote(k) for k in d["param_classes"]] if d["knr"] else d["param_classes"]
    args = [a["class"] for a in call["args"]]
    out = []
    for j, code, words in compare(args, params, [a["constant"] for a in call["args"]]):
        t, _, name = d["params"][j]
        what = f"parameter {j + 1} ({declaration(t, name)})"
        i = sources(args, params, sysv_places)[j]          # the argument the PC function reads it from
        arg = f"argument {i + 1} ({call['args'][i]['text'][:40]})" if isinstance(i, int) else ""
        if d["reads"][j] == 0:
            out.append(("Z", HARMLESS, f"{what} is never read"))
        elif code == "null":
            if sysv_places(params)[j][0] == "gpr":
                out.append(("Z", HARMLESS, f"{what} gets a literal 0 in a register: the PC sees NULL"))
            else:
                out.append(("A2", CRASH, f"{what} gets a literal 0 on the stack, which leaves the pointer's upper "
                                         "half unset"))
        elif code == "pointer from integer":
            a = call["args"][i]
            if "PointerToIntegral" in a["conversions"]:
                source = "a pointer that the caller's declaration turns into an integer"
            elif a["cast"] and a["cast"][0] == "PointerToIntegral":
                source = "a pointer that the caller casts to an integer"
            elif a["constant"] and isinstance(a["constant"][1], int):
                source = f"the integer constant {a['constant'][1]:#x}"
            else:
                source = f"a 32-bit {a['written']}"
            out.append(("A2", CRASH, f"{what} is a pointer, but {arg} is {source}: the function gets a 32-bit value "
                                     "as a 64-bit pointer"))
        elif code == "integer from pointer":
            a = call["args"][i]
            if a["cast"] and a["cast"][0] == "IntegralToPointer" and type_class(a["cast"][1], {})[0] in "iqL":
                out.append(("Z", HARMLESS, f"{arg} is an integer cast to a pointer, and {what} reads it back as an "
                                           "integer"))
            else:
                uses = sorted(u for u in d["uses"][j] if u != "other")
                out.append(("A1", CRASH, f"{arg} is a pointer ({a['written']}); {what} keeps only its low 32 bits"
                                         + (f" (the function's uses: {', '.join(uses)})" if uses else "")))
        elif code in ("moved", "register file"):
            pointer = params[j][0] == "p"
            if any(k[0] in "fd" for k in args + params):
                cls = "C1"
            else:
                cls = "C2" if any(k[0] == "q" for k in params) else "O"
            out.append((cls, CRASH if pointer else WRONG, f"{what}: {words}"))
        elif code == "missing":
            out.append(("D", CRASH if params[j][0] == "p" else WRONG, f"{what} {words}"))
        elif code == "narrow":
            out.append(("F1", CLANG_ONLY, f"{what}: {words}"))
        elif code == "struct":
            out.append(("H", WRONG, f"{what}: {words}"))
        else:
            out.append(("O", WRONG, f"{what}: {words}"))
    for i, a in enumerate(call["args"]):
        words = float_conversion(i, a, d["name"], float_externs)
        if words:
            out.append(("C1", WRONG, words))
    out += result_findings(call, d)
    extra = len(args) - len(params)
    if extra > 0 and not d["variadic"] and not out:
        out.append(("Z", HARMLESS, f"{extra} more argument{'s' if extra > 1 else ''} than the function reads"))
    return out


def result_findings(call: dict, d: dict) -> list:
    """The finding for the call's result, if the caller uses it and reads it differently from the definition."""
    seen, defined = call["view_ret_class"], d["ret_class"]
    if call["discarded"] or seen == defined or seen[0] == "v":
        return []
    seen_type = split_function_type(call["view"])[0] or "int"
    if defined[0] == "v":
        return [("E", WRONG, f"the caller uses the result, but {d['name']} returns nothing (void)")]
    if seen[0] in "iqL" and defined[0] == "p":
        return [("B", CRASH, f"the function returns a pointer ({d['ret']}); the caller reads it as {seen_type}")]
    if seen[0] == "p" and defined[0] in "iqL":
        return [("B", CRASH, f"the function returns {d['ret']}; the caller reads it as a pointer ({seen_type})")]
    if seen[0] == defined[0] == "i":
        if defined[1] < seen[1] or (defined[1] == seen[1] < 4 and defined[2] != seen[2]):
            how = low_bits_use(call.get("chain", ()), defined[1])
            if how:
                return [("F2", HARMLESS, f"the {d['ret']} result is read as {seen_type} and {how}")]
            return [("F2", WRONG, f"the {d['ret']} result is read as {seen_type} and used at full width: GCC (at any "
                                  "optimisation) and clang at -O1 and above leave the register's upper bits unset")]
        return []
    return [("O", WRONG, f"the function returns {d['ret']}; the caller reads {seen_type}")]


def low_bits_use(chain: list, size: int) -> str | None:
    """How the caller uses a result of `size` bytes that it reads as a wider integer, if only the result's low bytes
    can matter; else None. The chain says what each expression above the call does with its value, nearest first.
    The low bits of +, -, *, &, |, ^, ~ and unary - depend only on the low bits of their operands, so the value can
    pass through them; it then counts when it is converted to an integer of `size` bytes or fewer, masked with a
    constant within those bytes, or shifted left so far that only those bytes are left in a 32-bit int."""
    bits, first = 8 * size, True
    for entry in chain:
        kind = entry[0]
        if kind == "paren" or (kind == "cast" and entry[1] in ("NoOp", "LValueToRValue")):
            continue
        if kind == "cast" and entry[1] == "IntegralCast" and entry[2][0] == "i":
            if entry[2][1] <= size:
                return "converted back at once" if first else f"only its low {bits} bits are used"
            first = False      # (an int of 4 bytes or less: the low bits stay where they are)
            continue
        if kind == "binary" and entry[1] in ("+", "-", "*", "|", "^", "&"):
            other = entry[3]
            if entry[1] == "&" and other and other[0] in ("zero", "int") and 0 <= other[1] < 1 << bits:
                return f"only its low {bits} bits are used"
            first = False
            continue
        if kind == "binary" and entry[1] == "<<" and entry[2] == 0 and entry[3] and entry[3][0] == "int" \
                and entry[3][1] >= 32 - bits:
            return f"only its low {bits} bits are used"
        if kind == "unary" and entry[1] in ("-", "~", "+"):
            first = False
            continue
        return None
    return None


# ---------------------------------------------------------------------------------------------------------------------
# The decompilation's files: which C files to read, which functions are SDK code, and the functions' other names.
# ---------------------------------------------------------------------------------------------------------------------
class Decomp:
    """What the checker reads from the decompilation besides the C: build.json's functions and their other names, the
    code the port replaces (Nintendo SDK code and game files), and the tables of function addresses in overlay 2's
    data."""

    def __init__(self, root: Path):
        self.root = root
        for need in ("build.json", "src", "include", "docs/sdk_functions.md"):
            if not (root / need).exists():
                raise Failure(f"{root / need} not found: --decomp must name the decompilation's folder")
        try:
            self.build = json.loads((root / "build.json").read_text(encoding="utf-8"))
        except ValueError as e:
            raise Failure(f"{root / 'build.json'}: not valid JSON ({e})") from None
        self.symbols = self.build.get("symbols", {})              # other names -> address
        self.at_address = defaultdict(list)                        # address -> function names
        self.function_file = {}                                    # function name -> its C file
        for f in self.build["functions"]:
            self.at_address[f["vram"]].append(f["name"])
            self.function_file[f["name"]] = f.get("c") or f"src/{f['seg']}/{f['name']}.c"
        self.tables: dict = {}
        self.sdk_files, self.replaced_files = self._replaced()

    def definition_files(self) -> list:
        """The C files of the main program and of overlay 2: every function the set can call is defined in one."""
        out = []
        for seg in self.build["segments"]:
            folder = self.root / "src" / seg["name"]
            if seg.get("kind") == "code" and seg.get("overlay") in (None, 2) and folder.is_dir():
                out += sorted(f"src/{seg['name']}/{p.name}" for p in folder.glob("*.c"))
        return out

    def _replaced(self) -> tuple:
        """(the files of the Nintendo SDK code that the port replaces, the game files it replaces), from the table in
        docs/sdk_functions.md and the port's choices in tools/port_filelist.py, as that tool sorts them."""
        text = (self.root / "docs" / "sdk_functions.md").read_text(encoding="utf-8")
        table = text.split("\n## The functions", 1)[-1].split("\n## ", 1)[0]
        library = {m.group(1): m.group(2) for m in
                   re.finditer(r"^\|\s*[0-9A-F]{8}\s*\|\s*`([^`]+)`\s*\|[^|]*\|\s*([^|]*?)\s*\|", table, re.M)}
        if not library:
            raise Failure("docs/sdk_functions.md: its table 'The functions' was not found")
        choices = port_choices(self.root)
        sdk = {self.function_file[n] for n, lib in library.items()
               if n in self.function_file and n not in choices["SDK_ROWS_THAT_ARE_GAME"]
               and lib not in choices["KEEP_SDK_LIBRARIES"] and n not in choices["KEEP_SDK_FUNCTIONS"]}
        game = {self.function_file[n] for n in choices["REPLACED_GAME_FILES"] if n in self.function_file}
        return sdk, game

    def table_members(self, label: str) -> list:
        """The functions whose start addresses stand in the data of `label`, when it is a table of function addresses
        in overlay 2's data (D_800E3660): every 32-bit word from the label up to the next build.json symbol that is
        the address where a function of main or overlay 2 starts. [] for any other name."""
        if label not in self.tables:
            self.tables[label] = self._read_table(label)
        return self.tables[label]

    def _read_table(self, label: str) -> list:
        addr = self.symbols.get(label)
        if addr is None:
            return []
        overlay = {s["name"]: s.get("overlay") for s in self.build["segments"]}
        starts = {}
        for f in self.build["functions"]:
            if overlay.get(f["seg"]) in (None, 2) and f["seg"] != "entry":
                starts.setdefault(f["vram"], f["name"])
        for s in self.build["segments"]:
            if s.get("kind") != "raw" or s.get("overlay") != 2 or not s.get("incbin"):
                continue
            path = self.root / s["incbin"]
            base, end = s["vram"], s["vram"] + s["end"] - s["start"]
            if base <= addr < end:
                if not path.is_file():
                    raise Failure(f"{path}: not found, and {label}'s table of function addresses lies in it "
                                  "(build.py's first run extracts it from your ROM)")
                blob = path.read_bytes()
                stop = min([a for a in self.symbols.values() if addr < a < end] + [end])
                first = addr + (base - addr) % 4
                words = [struct.unpack_from(">I", blob, a - base)[0] for a in range(first, stop - 3, 4)]
                return sorted({starts[w] for w in words if w in starts})
        return []


def port_choices(root: Path) -> dict:
    """The port's choices of the code it replaces, which tools/port_filelist.py keeps at its top (REPLACED_GAME_FILES,
    KEEP_SDK_LIBRARIES, KEEP_SDK_FUNCTIONS, SDK_ROWS_THAT_ARE_GAME), read from its text with Python's own parser, so
    that they stay in one place. (The tool is not imported: that would write a __pycache__ folder into tools/.)"""
    script = root / "tools" / "port_filelist.py"
    if not script.is_file():
        raise Failure(f"{script} not found: it holds the port's choices of the code it replaces")
    wanted = ("REPLACED_GAME_FILES", "KEEP_SDK_LIBRARIES", "KEEP_SDK_FUNCTIONS", "SDK_ROWS_THAT_ARE_GAME")
    found = {}
    for node in ast.parse(script.read_text(encoding="utf-8")).body:
        names = [t.id for t in getattr(node, "targets", ()) if isinstance(t, ast.Name)]
        if isinstance(node, ast.Assign) and names and names[0] in wanted:
            value = node.value
            if isinstance(value, ast.Call) and getattr(value.func, "id", "") == "frozenset" and value.args:
                value = value.args[0]                       # frozenset({...}): the set inside
            try:
                found[names[0]] = set(ast.literal_eval(value))
            except ValueError:
                raise Failure(f"{script}: {names[0]} is not a plain table of names") from None
    missing = [w for w in wanted if w not in found]
    if missing:
        raise Failure(f"{script}: {', '.join(missing)} not found")
    return found


def read_file_set(root: Path, files_from: Path | None) -> list:
    """The developer program's files, as paths from the decompilation's folder (src/main/x.c)."""
    if files_from is not None:
        if not files_from.is_file():
            raise Failure(f"{files_from}: no such file")
        lines, source = files_from.read_text(encoding="utf-8").splitlines(), str(files_from)
    else:
        script = root / "tools" / "port_filelist.py"
        if not script.is_file():
            raise Failure("tools/port_filelist.py not found: give the file set with --files-from")
        proc = subprocess.run([sys.executable, "-B", str(script), "--set", "match"], cwd=root, capture_output=True,
                              text=True)
        if proc.returncode != 0:
            raise Failure(f"tools/port_filelist.py --set match failed (exit {proc.returncode}):\n{proc.stderr}")
        lines, source = proc.stdout.splitlines(), "tools/port_filelist.py"
    files = []
    for line in lines:
        s = line.strip()
        if s and not s.startswith("#"):
            rel = s if s.startswith("src/") else f"src/{s}"
            if not (root / rel).is_file():
                raise Failure(f"{source}: {s}: no such file in {root / 'src'}")
            files.append(rel)
    if not files:
        raise Failure(f"{source}: the file set is empty")
    return sorted(set(files))


class Definitions:
    """Finds the definition a call reaches, the way the N64 link does."""

    def __init__(self, facts: list, decomp: Decomp, file_set: set):
        self.decomp = decomp
        self.in_file = defaultdict(dict)                   # file -> name -> definition
        self.global_defs = defaultdict(list)                # name -> the definitions that are not static
        for f in facts:
            for d in f["definitions"]:
                self.in_file[d["file"]][d["name"]] = d
                if not d["static"]:
                    self.global_defs[d["name"]].append(d)
        for ds in self.global_defs.values():                 # two global definitions: the one in the set wins
            ds.sort(key=lambda d: (d["file"] not in file_set, d["file"]))
        self.ambiguous = {n: [d["file"] for d in ds] for n, ds in self.global_defs.items() if len(ds) > 1}
        self.float_externs = {}                             # extern variables a file of the set declares as a float
        for f in sorted(facts, key=lambda f: f["file"]):
            for v in f["externs"] if f["file"] in file_set else ():
                if v["view"].replace("[]", "") in ("f32", "f64"):
                    self.float_externs.setdefault(v["name"], f"{f['file']}:{v['line']}")

    def resolve(self, name: str, file: str) -> tuple:
        """(definition, how it was found) for a name used in file; (None, None) if it has no C definition."""
        d = self.in_file[file].get(name) or next(iter(self.global_defs.get(name, ())), None)
        how = "name"
        if d is None and name in self.decomp.symbols:      # another name at a function's address (build.json)
            for other in self.decomp.at_address.get(self.decomp.symbols[name], ()):
                if other != name and self.global_defs.get(other):
                    d, how = self.global_defs[other][0], f"build.json puts {name} at {other}'s address"
                    break
        for _ in range(4):                                  # __attribute__((alias("other"))), in the same file
            if d is None or not d["alias"]:
                break
            d, how = self.in_file[d["file"]].get(d["alias"]), f"{d['name']} is an alias of {d['alias']}"
        return (d, how) if d is not None else (None, None)


# ---------------------------------------------------------------------------------------------------------------------
# The reports.
# ---------------------------------------------------------------------------------------------------------------------
def signature(ret: str, name: str, params: list | None) -> str:
    """A function's declaration as C writes it: 'void f(s32 a)', 'void f(void)', or 'void f()' with no prototype."""
    inside = "" if params is None else ", ".join(params) or "void"
    return declaration(ret, name) + f"({inside})"


def build_rows(facts: list, defs: Definitions, file_set: set, report: set, stats: Counter) -> list:
    """One row for each flagged call made in the report's files. Stops (Failure) when a call reaches a function that
    lies outside the set and that the port does not replace: the set is then incomplete."""
    rows, outside = [], []
    replaced = defs.decomp.sdk_files | defs.decomp.replaced_files
    for f in facts:
        if f["file"] not in report:
            continue
        for c in f["calls"]:
            row = {"location": f"{f['file']}:{c['line']}", "file": f["file"], "line": c["line"], "caller": c["caller"],
                   "call": c["text"]}
            stats["calls"] += 1
            targets = [(c["callee"], None)]
            if c["how"] == "indirect":
                stats["through a function pointer"] += 1
                if c["table"]:
                    rows.append(dict(row, callee=f"indirect:{c['base']}", cls="G", effect=CRASH, view=c["view"],
                                     reason=f"the call {c['table']}: a PC function pointer is 8 bytes"))
                # a call through a table of function addresses reaches each function the table holds
                targets = [(name, c["base"]) for name in defs.decomp.table_members(c["base"] or "")]
                stats["functions reached through a table"] += len(targets)
            for callee, table in targets:
                d, how = defs.resolve(callee, f["file"])
                if d is None:
                    stats[f"no C definition: {callee}"] += 1
                    continue
                if table is None:
                    stats["reach a C definition"] += 1
                if d["file"] not in file_set and d["file"] not in replaced:
                    outside.append(f"{row['location']}: {callee} is defined in {d['file']}")
                    continue
                new = rate_call(c, d, how, callee, table, file_set, defs)
                if new is not None:
                    rows.append(dict(row, **new))
    if outside:
        raise Failure(f"the file set is incomplete: {plural(len(outside), 'call')} reach functions outside it that the "
                      "port does not replace (the port's choices at the top of tools/port_filelist.py name what it "
                      "replaces):\n" + "\n".join(f"    {x}" for x in outside[:20])
                      + ("\n    ..." if len(outside) > 20 else ""))
    rows.sort(key=lambda r: (r["file"], r["line"], r["callee"]))
    return rows


def rate_call(c: dict, d: dict, how: str, callee: str, table: str | None, file_set: set, defs: Definitions) -> dict:
    """The row of one call to the definition d (callee: the name it is called by; table: the table of function
    addresses the call goes through, if any), or None when the call is not flagged."""
    findings = call_findings(c, d, defs.float_externs)
    if not findings:
        return None
    worst = max(findings, key=lambda x: SEVERITY[x[1]])
    effect = worst[1]
    notes = [how] if how != "name" else []
    if table:
        notes.append(f"a call through the table {table}, which holds the address of {d['name']}, as {c['view']}")
    elif c["how"] == "cast":
        notes.append(f"called through a cast to {c['view']}")
    if d["knr"]:
        notes.append("an old-style definition, which receives its arguments promoted")
    if d["file"] not in file_set and effect != NOT_RATED:
        own = [x for x in findings if caller_side(x, d) and x[1] in BLOCKING]
        if d["file"] in defs.decomp.sdk_files and own:
            worst = max(own, key=lambda x: SEVERITY[x[1]])
            effect = worst[1]
            notes.append(f"the port replaces {d['file']}, Nintendo SDK code, with a stand-in; the {worst[0]} finding "
                         "is on the caller's side, so it holds whatever types the stand-in takes")
        else:
            effect = SDK if d["file"] in defs.decomp.sdk_files else REPLACED
            notes.append(f"the port replaces {d['file']}; as compiled it would be {worst[1]}")
    ret, plist = split_function_type(c["view"])
    return {"callee": callee, "cls": worst[0], "effect": effect,
            "view": signature(ret, callee, split_parameters(plist)) if c["view"] else "",
            "definition": signature(d["ret"], d["name"], [declaration(t, n) for t, _, n in d["params"]]),
            "defined_at": f"{d['file']}:{d['line']}",
            "reason": "; ".join(x[2] for x in findings) + (f" ({'; '.join(notes)})" if notes else "")}


EXTERN_KINDS = {
    "pointer and integer views": "crash: a 64-bit pointer read or written through a 32-bit view",
    "struct and other views": "layout: the offsets move if the struct holds a pointer",
    "different struct views": "layout: the offsets move if a struct holds a pointer",
    "different widths": "byte order: a narrower view reads other bytes on a little-endian PC",
    "same width": "harmless: signedness, f32 and s32 views of the same bits, array or scalar",
}


def extern_rows(facts: list, file_set: set) -> tuple:
    """The extern variables that the set's files declare with more than one type; and how many they declare."""
    seen = defaultdict(list)
    for f in facts:
        if f["file"] in file_set:
            for v in f["externs"]:
                seen[v["name"]].append((f"{f['file']}:{v['line']}", v["view"]))
    rows = []
    for name, decls in seen.items():
        views = Counter(view for _, view in decls)
        if len(views) < 2:
            continue
        widths = {width_class(view) for view in views}
        if "pointer" in widths and len(widths) > 1:
            kind = "pointer and integer views"
        elif "struct" in widths:
            kind = "struct and other views" if len(widths) > 1 else "different struct views"
        else:
            kind = "different widths" if len(widths) > 1 else "same width"
        example = {}
        for where, view in decls:
            example.setdefault(view, where)
        rows.append({"symbol": name, "kind": kind, "effect": EXTERN_KINDS[kind],
                     "files": len({where.rsplit(":", 1)[0] for where, _ in decls}),
                     "views": "; ".join(f"{v} x{n} (e.g. {example[v]})" for v, n in views.most_common())})
    rows.sort(key=lambda r: (list(EXTERN_KINDS).index(r["kind"]), -r["files"], r["symbol"]))
    return rows, len(seen)


def width_class(view: str) -> str:
    """What decides whether two views of a variable agree on the PC: pointer, struct, or the element's width."""
    v = view.replace("[]", "")
    if v.endswith("*") or v.startswith("fnptr/"):
        return "pointer"
    if v.startswith("struct:"):
        return "struct"
    return {"s8": "1", "u8": "1", "s16": "2", "u16": "2", "s32": "4", "u32": "4", "f32": "4", "s64": "8", "u64": "8",
            "f64": "8"}.get(v, v)


def read_allow(path: Path) -> dict:
    """The allow file: one call per line, FILE:LINE, the callee and the reason, separated by tabs; # starts a comment
    line. Returns (location, callee) -> (line number in the allow file, reason)."""
    if not path.is_file():
        raise Failure(f"{path}: no such allow file")
    allow = {}
    for n, line in enumerate(path.read_text(encoding="utf-8").splitlines(), 1):
        if not line.strip() or line.startswith("#"):
            continue
        parts = [p.strip() for p in line.split("\t", 2)]
        if len(parts) != 3 or not parts[2] or not re.match(r"\S+:\d+$", parts[0]):
            raise Failure(f"{path}:{n}: expected FILE:LINE, the callee and a reason, separated by tabs")
        loc = parts[0] if parts[0].startswith("src/") else f"src/{parts[0]}"
        allow[(loc, parts[1])] = (n, parts[2])
    return allow


def write_tsv(path: Path, columns: list, rows: list) -> None:
    with open(path, "w", encoding="utf-8", newline="\n") as out:
        out.write("\t".join(title for title, _ in columns) + "\n")
        for r in rows:
            out.write("\t".join(str(r.get(key, "")).replace("\t", " ") for _, key in columns) + "\n")


def summary_table(rows: list) -> list:
    """Flagged calls by class (rows) and effect (columns)."""
    table = Counter((r["cls"], r["effect"]) for r in rows)
    width = max(len(f"{k} {v}") for k, v in CLASSES.items()) + 1
    lines = ["  " + "class".ljust(width) + "".join(e.rjust(len(e) + 1) for e in EFFECTS) + " total"]
    for cls, words in CLASSES.items():
        counts = [table[(cls, e)] for e in EFFECTS]
        if sum(counts):
            lines.append("  " + f"{cls} {words}".ljust(width)
                         + "".join(str(n or "").rjust(len(e) + 1) for n, e in zip(counts, EFFECTS))
                         + str(sum(counts)).rjust(6))
    return lines


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0],
                                 epilog="Exit status: 0 no call is rated crash or wrong value, apart from those the "
                                        "allow file lists; 1 one is; 2 the tool cannot run. The effects, the classes "
                                        "and how the tool works: see the comment at the top of tools/port_calls.py "
                                        "and docs/port.md.")
    ap.add_argument("--decomp", type=Path, default=Path(__file__).resolve().parent.parent,
                    help="the decompilation's folder (default: %(default)s)")
    ap.add_argument("--files-from", type=Path, metavar="LIST",
                    help="read the file set from LIST, one path per line, instead of from tools/port_filelist.py")
    ap.add_argument("--only", nargs="+", default=[], metavar="FILE", help="report only the calls made in these files")
    ap.add_argument("--allow", type=Path, metavar="FILE",
                    help="calls rated crash or wrong value that wait for a later step: FILE:LINE, callee, reason")
    ap.add_argument("--tsv", type=Path, metavar="FILE", help="write every flagged call to FILE")
    ap.add_argument("--externs", type=Path, metavar="FILE",
                    help="write the extern variables declared with more than one type to FILE")
    ap.add_argument("--quiet", action="store_true", help="print the summary only, not each blocking call")
    ap.add_argument("--clang", default="clang", help="the clang to run (default: %(default)s)")
    ap.add_argument("--jobs", type=int, default=os.cpu_count() or 1,
                    help="clang processes at a time (default: %(default)s)")
    a = ap.parse_args()
    try:
        return run(a)
    except Failure as e:
        print(f"port_calls: error: {e}", file=sys.stderr)
    except KeyboardInterrupt:
        print("port_calls: stopped before it finished", file=sys.stderr)
    except Exception:  # a fault in this tool: exit status 2, not the 1 of a blocking call
        traceback.print_exc()
        print("port_calls: error: the error above is a fault in tools/port_calls.py itself, or an input it cannot "
              "read", file=sys.stderr)
    return 2


def run(a) -> int:
    root = a.decomp.resolve()
    for option, path in (("--tsv", a.tsv), ("--externs", a.externs)):
        if path is not None and (path.resolve() == root or root in path.resolve().parents):
            raise Failure(f"{option} {path}: the file must lie outside the decompilation {root}")
    decomp = Decomp(root)
    clang = shutil.which(a.clang)
    if clang is None:
        raise Failure(f"{a.clang}: not found (name another with --clang)")
    allow = read_allow(a.allow) if a.allow else {}
    file_set = read_file_set(root, a.files_from)
    report = set()
    for p in a.only:                         # src/main/x.c, ./src/main/x.c, main/x.c or an absolute path
        rel = Path(p)
        if rel.is_absolute():
            if root not in rel.resolve().parents:
                raise Failure(f"--only: {p} is not in {root}")
            rel = rel.resolve().relative_to(root)
        report.add(rel.as_posix() if rel.as_posix().startswith("src/") else f"src/{rel.as_posix()}")
    report = report or set(file_set)
    if report - set(file_set):
        raise Failure("--only: not in the file set: " + ", ".join(sorted(report - set(file_set))))

    files = sorted(set(decomp.definition_files()) | set(file_set))
    with ProcessPoolExecutor(max_workers=max(1, a.jobs)) as pool:
        facts = list(pool.map(read_file, [(clang, str(root), f, f in report) for f in files], chunksize=8))
    failed = [f for f in facts if "failed" in f]
    if failed:
        raise Failure("clang gave no syntax tree for " + ", ".join(f["file"] for f in failed) + ":\n"
                      + failed[0]["failed"])
    failed = [f for f in facts if "n64_failed" in f]
    if failed:
        raise Failure("clang gave no syntax tree for the N64 view (N64_FLAGS) of "
                      + ", ".join(f["file"] for f in failed) + ":\n" + failed[0]["n64_failed"])

    defs = Definitions(facts, decomp, set(file_set))
    stats = Counter()
    rows = build_rows(facts, defs, set(file_set), report, stats)
    externs, declared = extern_rows(facts, set(file_set))
    used = set()
    for r in rows:
        key = (r["location"], r["callee"])
        if key in allow and r["effect"] in BLOCKING:
            r["allowed"] = allow[key][1]
            used.add(key)
    blocking = [r for r in rows if r["effect"] in BLOCKING and not r.get("allowed")]

    if a.tsv:
        write_tsv(a.tsv, [("location", "location"), ("caller", "caller"), ("callee", "callee"), ("class", "cls"),
                          ("effect", "effect"), ("caller's view", "view"), ("definition", "definition"),
                          ("defined at", "defined_at"), ("reason", "reason"), ("allowed", "allowed"),
                          ("call", "call")], rows)
    if a.externs:
        write_tsv(a.externs, [("symbol", "symbol"), ("kind", "kind"), ("effect on the PC", "effect"),
                              ("files", "files"), ("types (count, example)", "views")], externs)

    if not a.quiet:
        for r in blocking:
            print(f"{r['location']}: {r['effect']}: {r['callee']} ({r['cls']} {CLASSES[r['cls']]}): {r['reason']}")
    nodef = sorted((k.split(": ", 1)[1], n) for k, n in stats.items() if k.startswith("no C definition: "))
    by_effect = Counter(r["effect"] for r in rows)
    print(f"port_calls: {plural(len(report), 'file')}" + (f" of the set's {len(file_set)}" if a.only else "")
          + f" ({len(files)} read for definitions); {stats['calls']} calls: to a function with a C definition "
          f"{stats['reach a C definition']}, through a function pointer {stats['through a function pointer']} (they "
          f"reach {stats['functions reached through a table']} functions through tables), to a function with no C "
          f"definition {sum(n for _, n in nodef)}")
    print(f"  {len(rows)} calls flagged (a call through a table once for each function it reaches): "
          + ", ".join(f"{e} {by_effect[e]}" for e in EFFECTS))
    print("\n".join(summary_table(rows)))
    if nodef:
        print("  functions with no C definition (port.h helpers, port functions): "
              + ", ".join(f"{name} {n}" for name, n in nodef))
    unpaired = sum(f.get("n64_unpaired", 0) for f in facts if f["file"] in report)
    print(f"  calls with no partner in the N64 view (written only for the PC): {unpaired}")
    errors = sum(len(f["errors"]) for f in facts if f["file"] in report)
    if errors:
        print(f"  clang errors in these files: {errors} (a call that clang could not build is 'not rated')")
    if defs.ambiguous:
        print("  names with more than one global definition (the one in the set is used): "
              + "; ".join(f"{n}: {', '.join(fs)}" for n, fs in sorted(defs.ambiguous.items())))
    kinds = Counter(r["kind"] for r in externs)
    print(f"  extern variables declared in the set: {declared}; with more than one type: {len(externs)} ("
          + ", ".join(f"{k} {kinds[k]}" for k in EXTERN_KINDS) + ")")
    if a.allow:
        # An entry that matches no blocking call is reported (a call fixed, or moved to another line by an edit).
        stale = [(n, loc, callee) for (loc, callee), (n, _) in allow.items()
                 if (loc, callee) not in used and loc.rsplit(":", 1)[0] in report]
        print(f"  allowed by {a.allow}: {sum(1 for r in rows if r.get('allowed'))} calls; its entries that match no "
              f"blocking call: {len(stale)}")
        for n, loc, callee in sorted(stale):
            print(f"{a.allow}:{n}: no call rated crash or wrong value at {loc} to {callee}", file=sys.stderr)
    print(f"  blocking (crash or wrong value, not allowed): {len(blocking)}")
    return 1 if blocking else 0


if __name__ == "__main__":
    sys.exit(main())
