"""Re-indents the C files under src/ (or the files given) with 4 spaces per level. Only leading whitespace changes.

    cd source
    python3 tools/indent_c.py [--check] [--diff] [paths...]

No path means every .c file under src/. --check writes nothing and lists the files that would change (exit 1 if any);
--diff prints a unified diff instead of writing.

Style (the one most of src/ already used):
- 4 spaces per brace level; a body without braces (`if (x)`, `else`, `for`, `while` or `do` ending its line) is one
  level deeper than its header, and an `else` lines up with its `if`.
- `case` and `default` line up with their `switch`; the statements under them are one level deeper.
- A goto label alone on its line starts in column 0 (one with a statement after it on the line is indented as code).
- A `case` lines up with its `switch` even when it sits inside a nested block of the switch body; in `case 0: {` the
  block's statements are one level deeper than the case and its `}` lines up with it.
- A brace-less body that starts on its header's line (`else switch (x) {`, `if (a) for (...)`) adds no level.
- A call of a macro defined in the file whose body ends in `}` or `;` counts as a whole statement, so the line after
  `else RESET(0)` is not taken for a continuation.
- Preprocessor lines start in column 0. The continuation lines of a line ending in a backslash (macro bodies, strings)
  are left exactly as they were.
- A line that continues a statement (inside parentheses, or after an operator) keeps its offset from the statement's
  first line, so arguments aligned under a `(` stay aligned; one with no offset gets 4 spaces.
- The lines of a block comment move by the same amount as the line it starts on.

Whitespace at the start of a line never changes what GCC compiles (a backslash-continued string literal is the one place
it would, and those lines are never touched), so the build stays identical. Every file is checked: each line must be
unchanged apart from its leading whitespace, or the file is skipped with a message."""
import argparse, difflib, re, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
WIDTH = 4
TOKEN = re.compile(r"""
    (?P<ws>[ \t]+)
  | (?P<lcomment>//.*)
  | (?P<bcomment>/\*)
  | (?P<str>"(?:[^"\\]|\\.)*(?:"|\\?$))
  | (?P<chr>'(?:[^'\\]|\\.)*(?:'|$))
  | (?P<word>[A-Za-z_]\w*)
  | (?P<num>\.?[0-9](?:[eEpP][+-]|[\w.])*)
  | (?P<punct>->|\+\+|--|<<=|>>=|<<|>>|<=|>=|==|!=|&&|\|\||[-+*/%&|^]=|\.\.\.|\S)
""", re.X)
HEADERS = {"if", "while", "for", "switch"}


class Indenter:
    """Tracks brace frames and brace-less bodies token by token; each line's indent comes from the state at its start."""

    def __init__(self, stmt_macros=()):
        self.stmt_macros = set(stmt_macros)  # macros whose use is a complete statement
        self.macro_stmt = False  # reading the arguments of one of those
        self.swallow_semi = False  # a `;` right after such a use is an empty statement
        self.lineno = 0
        self.case_line = None  # (line, level) of the last `case` line, for a `{` opened on it
        self.frames = [{"base": 0, "open": 0, "switch": False, "stmt": True, "header": None, "saved": [], "mid": False}]
        self.oneshots = []      # (kind, level, inline) of the brace-less headers whose body is the current statement;
                                # inline: the body started on the header's line, so it adds no level
        self.paren = 0          # depth of ( and [ outside a header
        self.header = None      # (kind, level) of an if/while/for/switch whose parentheses are being read
        self.hparen = 0
        self.pending = None     # (kind, level, line): header done, its body not started yet
        self.mid = False        # inside a statement
        self.ntok = 0           # tokens in the current statement
        self.prev = None        # previous token
        self.else_targets = []  # (level, oneshots) of the ifs whose bodies just ended, innermost last
        self.after_do = False   # a do body just ended, so `while (...)` is its tail
        self.first = None       # first token of the current statement
        self.stmt_orig = self.stmt_new = 0
        self.in_comment = False
        self.comment_delta = 0
        self.continued = False

    # ---- lines -----------------------------------------------------------------------------------------------------
    def line(self, text):
        self.lineno += 1
        if self.continued:  # macro body or string continuation: untouched
            self.continued = text.endswith("\\")
            return text
        if self.in_comment:
            out = shift(text, self.comment_delta)
            self.scan(text)
            return out
        stripped = text.lstrip(" \t")
        if not stripped:
            return ""
        orig = len(text) - len(stripped)
        if stripped.startswith("#"):
            self.continued = text.endswith("\\")
            return stripped
        new = self.indent_for(stripped, orig)
        self.comment_delta = new - orig
        self.scan(stripped)
        self.continued = text.endswith("\\") and not self.in_comment
        return " " * new + stripped

    def indent_for(self, s, orig):
        toks = first_tokens(s, 3)
        first = toks[0] if toks else ""
        f = self.frames[-1]
        if first == "}":
            return WIDTH * f["open"]
        if (self.paren or self.header or self.mid) and not (first == "{" and not self.paren):
            off = orig - self.stmt_orig
            return self.stmt_new + (off if off > 0 else WIDTH)
        if first == "else" and self.else_targets:
            return self.start(self.else_targets[-1][0], orig)
        if first == "{" and self.pending:
            return self.start(self.pending[1], orig)
        lvl = self.level() + (1 if self.pending else 0)
        if first in ("case", "default"):
            sw = next((fr for fr in reversed(self.frames) if fr["switch"]), None)
            if sw:
                self.case_line = (self.lineno, sw["open"])
                return self.start(sw["open"], orig)
        if len(toks) == 2 and toks[1] == ":" and re.fullmatch(r"[A-Za-z_]\w*", first) and first != "default":
            return self.start(0, orig)
        return self.start(lvl, orig)

    def start(self, lvl, orig):
        self.stmt_orig, self.stmt_new = orig, WIDTH * lvl
        return self.stmt_new

    def scan(self, s):
        i = 0
        while i < len(s):
            if self.in_comment:
                j = s.find("*/", i)
                if j < 0:
                    return
                self.in_comment = False
                i = j + 2
                continue
            m = TOKEN.match(s, i)
            i = m.end()
            if m.lastgroup == "bcomment":
                self.in_comment = True
            elif m.lastgroup not in ("ws", "lcomment"):
                self.token(m.lastgroup, m.group())

    # ---- tokens ----------------------------------------------------------------------------------------------------
    def level(self):
        return self.frames[-1]["base"] + sum(1 for o in self.oneshots if not o[2])

    def if_targets(self):
        return [(o[1], self.oneshots[:k]) for k, o in enumerate(self.oneshots) if o[0] == "if"]

    def statement_done(self):
        self.else_targets = self.if_targets()
        self.after_do = any(o[0] == "do" for o in self.oneshots)
        self.end_statement()

    def end_statement(self):
        self.mid, self.ntok, self.oneshots = False, 0, []

    def token(self, kind, tok):
        prev, self.prev = self.prev, tok
        if self.header is not None:
            if tok in ("(", "["):
                self.hparen += 1
            elif tok in (")", "]"):
                self.hparen -= 1
                if self.hparen == 0:
                    self.pending, self.header = self.header + (self.lineno,), None
                    if self.pending[0] == "dowhile":
                        self.pending = None
            return
        if self.pending:
            p, self.pending = self.pending, None
            if tok == "{":
                return self.open_brace(p, prev)
            if not (tok == "if" and p[0] == "else"):
                self.oneshots.append((p[0], p[1], p[2] == self.lineno))  # brace-less body
        swallow, self.swallow_semi = self.swallow_semi, False
        if swallow and tok == ";":
            return
        if self.paren:
            if tok in ("(", "["):
                self.paren += 1
            elif tok in (")", "]"):
                self.paren -= 1
                if self.paren == 0 and self.macro_stmt:
                    self.macro_stmt = False
                    self.statement_done()
                    self.swallow_semi = True
            return
        after_do, self.after_do = self.after_do, False
        targets, self.else_targets = self.else_targets, []
        if not self.mid:
            if tok in HEADERS:
                self.header, self.hparen = ("dowhile" if tok == "while" and after_do else tok, self.level()), 0
                return
            if tok == "else" and targets:
                lvl, self.oneshots = targets[-1]
                self.pending = ("else", lvl, self.lineno)
                return
            if tok in ("else", "do"):
                self.pending = (tok, self.level(), self.lineno)
                return
            if tok in self.stmt_macros:
                self.macro_stmt = True
        if tok == "{":
            return self.open_brace(None, prev)
        if tok == "}":
            if len(self.frames) == 1:
                return
            fr = self.frames.pop()
            self.oneshots, self.mid = fr["saved"], fr["mid"]
            if fr["stmt"]:
                hdr = fr["header"]
                self.else_targets = self.if_targets() + ([(hdr[1], list(self.oneshots))] if hdr and hdr[0] == "if" else [])
                self.after_do = bool(hdr and hdr[0] == "do")
                self.end_statement()
            return
        if tok == ";":
            self.statement_done()
            return
        if tok == "," and not self.frames[-1]["stmt"]:
            self.end_statement()  # next element of an initializer or enum
            return
        if tok == ":" and (self.ntok == 1 and kind == "punct" and re.fullmatch(r"[A-Za-z_]\w*", prev or "")
                           or self.first in ("case", "default")):
            self.end_statement()  # label or case
            return
        if tok in ("(", "["):
            self.paren += 1
        if not self.mid:
            self.first = tok
        self.mid = True
        self.ntok += 1

    def open_brace(self, hdr, prev):
        lvl = hdr[1] if hdr else self.level()
        if not hdr and self.case_line and self.case_line[0] == self.lineno:
            lvl = self.case_line[1]  # `case 0: {`: the block's `}` lines up with the case
        stmt = bool(hdr) or not self.mid or prev == ")"  # a block, or a function body; else an initializer/struct
        self.frames.append({"base": lvl + 1, "open": lvl, "switch": bool(hdr and hdr[0] == "switch"), "stmt": stmt,
                            "header": hdr, "saved": self.oneshots, "mid": self.mid and not stmt})
        self.oneshots, self.mid, self.ntok = [], False, 0


def first_tokens(s, n):
    out = []
    for m in TOKEN.finditer(s):
        if m.lastgroup in ("lcomment", "bcomment"):
            break
        if m.lastgroup != "ws":
            out.append(m.group())
            if len(out) == n:
                break
    return out


def shift(text, delta):
    stripped = text.lstrip(" \t")
    if not stripped:
        return ""
    return " " * max(0, len(text) - len(stripped) + delta) + stripped


def statement_macros(text):
    """Names of the macros defined in `text` whose body ends in `}` or `;`: a use of one is a whole statement."""
    out = set()
    joined = re.sub(r"\\\n", " ", text)
    for m in re.finditer(r"^[ \t]*#[ \t]*define[ \t]+([A-Za-z_]\w*)(\([^)]*\))?(.*)$", joined, re.M):
        body = re.sub(r"/\*.*?\*/|//.*", "", m[3]).strip()
        if body.endswith(("}", ";")):
            out.add(m[1])
    return out


def reindent(text):
    ind = Indenter(statement_macros(text))
    lines = text.split("\n")
    out = [ind.line(l) for l in lines]
    for a, b in zip(lines, out):
        if a.lstrip(" \t") != b.lstrip(" \t"):
            raise ValueError(f"line content changed: {a!r} -> {b!r}")
    if len(ind.frames) != 1:
        raise ValueError("unbalanced braces")
    return "\n".join(out)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("paths", nargs="*")
    ap.add_argument("--check", action="store_true", help="list the files that would change, write nothing")
    ap.add_argument("--diff", action="store_true", help="print a unified diff, write nothing")
    args = ap.parse_args()
    files = [Path(p) for p in args.paths] or sorted((ROOT / "src").rglob("*.c"))
    changed = 0
    for path in files:
        old = path.read_text(encoding="utf-8")
        try:
            new = reindent(old)
        except ValueError as e:
            print(f"{path}: skipped, {e}", file=sys.stderr)
            continue
        if new == old:
            continue
        changed += 1
        if args.diff:
            sys.stdout.writelines(difflib.unified_diff(old.splitlines(True), new.splitlines(True), str(path), str(path)))
        elif args.check:
            print(path)
        else:
            path.write_text(new, encoding="utf-8")
    verb = "would change" if args.check or args.diff else "changed"
    print(f"{changed} of {len(files)} files {verb}", file=sys.stderr)
    return 1 if args.check and changed else 0


if __name__ == "__main__":
    sys.exit(main())
