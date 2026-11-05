"""uldata.py MAP.tsv OUT.json : find the ROM addresses of SDK data globals by lining up SDK source against matched ROM
functions. Run from source/ with decompdecomp's Python, after a build has extracted asm/.

MAP.tsv has one line per function: ROMNAME<tab>FILE.c<tab>[SDKNAME]<tab>[OPT], where FILE.c is an already preprocessed
SDK source (tools/ulpp.sh for ultralib) that defines SDKNAME (default ROMNAME) and OPT is -O2 or -O3 (default -O3).
The file is compiled with the game's compiler; its instructions are aligned with the ROM function's (asm/nonmatchings,
same normalisation as dh.py), and every aligned instruction pair that refers to data on both sides gives one vote
"SDK symbol S (+ its offset) is at ROM address A". Static variables are recovered from the object's symbol table.
OUT.json: {symbol: {address: [voting functions]}}; symbols with more than one address are conflicts to look at."""
import sys, os, re, json, subprocess, tempfile, difflib, glob
from pathlib import Path
from decompnet.compiler import compile_source
from decompnet.project import compiler_config, compiler_for
from decompnet import toolchains
import copy

src = open('tools/permute_run.py').read()
exec(src[src.index('def norm(lines):'):src.index('def dis(path')])
OD = str(toolchains.binary('binutils-mips').parent / 'mips-ps2-decompals-objdump')
B = json.load(open('build.json'))
fns = {f['name']: f for f in B['functions']}
ROOT = Path('.').resolve()
cfg2 = compiler_config(ROOT, {"compiler": compiler_for(B, 0x80020000)})
cfg3 = copy.deepcopy(cfg2)
for a in ('cmd', 'flags', 'args'):
    if hasattr(cfg3, a) and isinstance(getattr(cfg3, a), list):
        setattr(cfg3, a, ['-O3' if x == '-O2' else x for x in getattr(cfg3, a)])

# ROM symbol addresses: data labels splat wrote, symbol_addrs.txt, build.json symbols, function names
addr = {}
for p in glob.glob('asm/data/**/*.s', recursive=True):
    t = open(p, errors='replace').read()
    for m in re.finditer(r"dlabel (\w+)\s*\n\s*/\*\s*(?:[0-9A-F]+\s+)?([0-9A-F]{8})", t):
        addr.setdefault(m[1], int(m[2], 16))
for l in open('symbol_addrs.txt'):
    m = re.match(r"\s*(\w+)\s*=\s*(0x[0-9A-Fa-f]+)", l)
    if m: addr.setdefault(m[1], int(m[2], 16))
for k, v in B['symbols'].items(): addr.setdefault(k, v)
for f in B['functions']: addr.setdefault(f['name'], f['vram'])


def rom_side(name):
    """Normalised instructions and {index: absolute address} for the data references of the ROM function."""
    ins, refs = [], {}
    for l in open(fns[name]['asm']):
        m = re.match(r'\s*/\*\s*[0-9A-F]+\s+([0-9A-F]{8})\s+[0-9A-F]{8}\s*\*/\s+(\S+)\s*(.*)', l)
        if not m: continue
        op, args = m[2], m[3]
        r = re.search(r'%(?:hi|lo)\((\w+)(?:\s*\+\s*(0x[0-9A-Fa-f]+|\d+))?\)', args)
        if r and op != 'jal':
            base = addr.get(r[1])
            if base is None and re.fullmatch(r'D_[0-9A-F]{8}', r[1]): base = int(r[1][2:], 16)
            if base is not None: refs[len(ins)] = base + (int(r[2], 0) if r[2] else 0)
        ins.append(op)
    while ins and ins[-1] == 'nop': ins.pop()
    return ins, refs


def sdk_side(path, sym, opt):
    res = compile_source(cfg3 if opt == '-O3' else cfg2, '', open(path).read(), trusted=True)
    if not res.ok: return None
    o = tempfile.mktemp(suffix='.o'); open(o, 'wb').write(res.obj)
    # local symbols per section, to name relocations against a section (static variables)
    syms = {}
    for l in subprocess.run([OD, '-t', o], capture_output=True, text=True).stdout.splitlines():
        m = re.match(r'([0-9a-f]{8})\s+(\S+)?\s+\S*\s*(\.\w+)\s+([0-9a-f]{8})\s+(\S+)$', l.strip())
        if m and m[3] in ('.data', '.bss', '.sdata', '.sbss', '.rodata') and not m[5].startswith(('.', '$')):
            syms.setdefault(m[3], []).append((int(m[1], 16), m[5]))
    txt = subprocess.run([OD, '-dr', o], capture_output=True, text=True).stdout
    os.unlink(o)
    # MIPS ELF32 relocations are REL: the addend is in the instruction (hi16 << 16 plus the signed lo16), so take the
    # LO16 instruction's immediate together with the last HI16 immediate for the same symbol.
    ins, refs, on, last, word, hi = [], {}, False, None, 0, {}
    for l in txt.splitlines():
        h = re.match(r'^[0-9a-f]+ <(\S+)>:', l)
        if h: on = h[1] == sym; continue
        if not on: continue
        m = re.match(r'\s+([0-9a-f]+):\t([0-9a-f ]+)\t(\S+)', l)
        if m:
            ins.append(m[3]); last = len(ins) - 1; word = int(m[2].replace(' ', ''), 16); continue
        r = re.match(r'\s+[0-9a-f]+: R_MIPS_(HI16|LO16)\s+(\S+?)(?:\+0x([0-9a-f]+))?$', l)
        if r and r[1] == 'HI16':
            hi[r[2]] = word & 0xFFFF
            continue
        if r and last is not None:
            lo = word & 0xFFFF
            lo = lo - 0x10000 if lo & 0x8000 else lo
            h16 = hi.get(r[2], 0)
            s, off = r[2], ((h16 - 0x10000 if h16 & 0x8000 else h16) << 16) + lo
            if s in syms:  # section-relative: find the static it falls in
                cand = [(v, n) for v, n in syms[s] if v <= off]
                if not cand: continue
                v, n = max(cand)
                s, off = n, off - v
            elif s.startswith('.'):
                continue
            refs[last] = (s, off)
    while ins and ins[-1] == 'nop': ins.pop()
    return ins, refs


def main():
    votes = {}
    for line in open(sys.argv[1]):
        line = line.rstrip('\n')
        if not line or line.startswith('#'): continue
        parts = line.split('\t') + ['', '', '']
        rom, path, sym, opt = parts[0], parts[1], parts[2] or parts[0], parts[3] or '-O3'
        sd = sdk_side(path, sym, opt)
        if not sd or not sd[0]:
            print('no code for', rom, sym, path, file=sys.stderr); continue
        ri, rr = rom_side(rom)
        si, sr = sd
        sm = difflib.SequenceMatcher(None, ri, si, autojunk=False)
        for t, i1, i2, j1, j2 in sm.get_opcodes():
            if t != 'equal': continue
            for k in range(i2 - i1):
                if i1 + k in rr and j1 + k in sr:
                    s, off = sr[j1 + k]
                    if s in fns or s == sym: continue  # function addresses (pointers to functions)
                    a = rr[i1 + k] - off
                    votes.setdefault(s, {}).setdefault(f'{a:08X}', set()).add(rom)
    json.dump({s: {a: sorted(v) for a, v in d.items()} for s, d in sorted(votes.items())}, open(sys.argv[2], 'w'), indent=1)
    conf = [s for s, d in votes.items() if len(d) > 1]
    print(f'{len(votes)} symbols, {len(conf)} with more than one address: {conf[:30]}')


if __name__ == '__main__':
    main()
