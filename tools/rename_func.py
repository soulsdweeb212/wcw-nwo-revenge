"""Renames functions everywhere the tree names them.

    cd source
    python3 tools/rename_func.py [--dry-run] OLD NEW [OLD NEW ...]
    python3 tools/rename_func.py [--dry-run] --file MAP.tsv      (lines "OLD<tab>NEW", # comments allowed)

For each pair it changes the line in symbol_addrs.txt, the function's "name", "asm" and "c" in build.json, moves
src/<seg>/OLD.c to src/<seg>/NEW.c (git mv) when the file is named after the function, and replaces OLD as a whole
word in every file under src/ and include/ and in README.md, nonmatching/*.md, objdiff.json and
tools/list_nonmatching.py. It refuses a NEW name that
is already a function or symbol. Afterwards it reruns tools/add_headers.py and deletes asm/, so the next build.py
extracts the assembly again (splat) with the new names. Run python3 build.py afterwards; it must still say
identical."""
import argparse, json, re, shutil, subprocess, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
TEXT_GLOBS = ["src/**/*.c", "src/**/*.h", "include/**/*.h", "README.md", "nonmatching/*.md", "objdiff.json",
              "tools/list_nonmatching.py"]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("--file")
    ap.add_argument("pairs", nargs="*")
    a = ap.parse_args()
    pairs = []
    if a.file:
        for line in Path(a.file).read_text(encoding="utf-8").splitlines():
            line = line.split("#", 1)[0].strip()
            if line:
                old, new = line.split()[:2]
                pairs.append((old, new))
    if len(a.pairs) % 2:
        sys.exit("give OLD NEW pairs")
    pairs += list(zip(a.pairs[::2], a.pairs[1::2]))
    build_path = ROOT / "build.json"
    build = json.loads(build_path.read_text(encoding="utf-8"))
    names = {f["name"]: f for f in build["functions"]}
    taken = set(names) | set(build["symbols"])
    olds = [o for o, _ in pairs]
    news = [n for _, n in pairs]
    for old, new in pairs:
        if old not in names:
            sys.exit(f"{old} is not a function in build.json")
        if not re.fullmatch(r"[A-Za-z_]\w*", new):
            sys.exit(f"{new} is not a C identifier")
        if new in taken and new not in olds:
            sys.exit(f"{new} is already a name in build.json")
    if len(set(news)) != len(news) or len(set(olds)) != len(olds):
        sys.exit("a name appears twice")
    mapping = dict(pairs)
    word = re.compile(r"\b(" + "|".join(map(re.escape, sorted(olds, key=len, reverse=True))) + r")\b")

    # symbol_addrs.txt
    sym_path = ROOT / "symbol_addrs.txt"
    sym = sym_path.read_text(encoding="utf-8")
    sym2 = re.sub(r"^(\s*)(\w+)(\s*=)", lambda m: m[1] + mapping.get(m[2], m[2]) + m[3], sym, flags=re.M)
    # build.json
    moves = []
    for f in build["functions"]:
        if f["name"] in mapping:
            old, new = f["name"], mapping[f["name"]]
            f["name"] = new
            f["asm"] = re.sub(rf"/{re.escape(old)}\.s$", f"/{new}.s", f["asm"])
            c = f.get("c")
            if not c and (ROOT / f"src/{f['seg']}/{old}.c").exists():  # no "c": build.py uses src/<seg>/<name>.c
                moves.append((f"src/{f['seg']}/{old}.c", f"src/{f['seg']}/{new}.c"))
            elif c and Path(c).stem == old:
                newc = str(Path(c).with_name(new + ".c"))
                moves.append((c, newc))
                for g in build["functions"]:  # every function sharing this file
                    if g.get("c") == c:
                        g["c"] = newc
    # text files
    edits = {}
    for g in TEXT_GLOBS:
        for p in ROOT.glob(g):
            t = p.read_text(encoding="utf-8")
            t2 = word.sub(lambda m: mapping[m[1]], t)
            if t2 != t:
                edits[p] = t2
    print(f"{len(pairs)} renames: symbol_addrs {'changed' if sym2 != sym else 'unchanged'}, "
          f"{len(moves)} files moved, {len(edits)} files edited")
    if a.dry_run:
        for p in sorted(edits):
            print("  edit", p.relative_to(ROOT))
        for o, n in moves:
            print("  move", o, "->", n)
        return
    sym_path.write_text(sym2, encoding="utf-8")
    build_path.write_text(json.dumps(build, indent=1), encoding="utf-8")  # (the file has no trailing newline)
    for p, t in edits.items():
        p.write_text(t, encoding="utf-8")
    for o, n in moves:
        subprocess.run(["git", "mv", o, n], cwd=ROOT, check=True)
    subprocess.run([sys.executable, "tools/add_headers.py"], cwd=ROOT, check=True, stdout=subprocess.DEVNULL)
    shutil.rmtree(ROOT / "asm", ignore_errors=True)
    print("done; run python3 build.py (it re-extracts asm/)")


if __name__ == "__main__":
    main()
