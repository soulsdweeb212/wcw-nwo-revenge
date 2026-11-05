"""ul.py FUNC FILE.c [SYMBOL] [ctx] : score an already-preprocessed C file (no common.h, e.g. ultralib source run
through ulpp.sh) against the ROM function FUNC. Only SYMBOL's code in the object is compared (default: FUNC), so a
file holding several functions works. OPT=-O3 env var swaps -O2 for -O3 (libgultra was built -O3). Run from source/."""
import sys,re,os
src=open(os.path.join(os.getcwd(),'tools/permute_run.py')).read()
head=src[src.index('import json'):src.index('best_src=open(SRC)')]
SYM=sys.argv[3] if len(sys.argv)>3 else sys.argv[1]
ctx=int(sys.argv[4]) if len(sys.argv)>4 else 2
sys.argv=['x',sys.argv[1],sys.argv[2],'0']
exec(head)
opt=os.environ.get('OPT')
if opt:
    for a in ('cmd','flags','args'):
        if hasattr(cfg,a) and isinstance(getattr(cfg,a),list):
            setattr(cfg,a,[opt if x=='-O2' else x for x in getattr(cfg,a)])
res=compile_source(cfg,'',open(SRC).read(),trusted=True)
if not res.ok:
    print('COMPILE FAIL');print(getattr(res,'log',None) or getattr(res,'stderr',None) or res);sys.exit(1)
p=tmp+'/d.o';open(p,'wb').write(res.obj)
txt=subprocess.run([OD,'-d',p],capture_output=True,text=True).stdout
lines=[];on=False
for l in txt.splitlines():
    h=re.match(r'^[0-9a-f]+ <(\S+)>:',l)
    if h: on=(h.group(1)==SYM); continue
    m=re.match(r'\s+([0-9a-f]+):\t[0-9a-f ]+\t(.*)',l)
    if on and m: lines.append(m.group(1)+':\t'+m.group(2))
if not lines: print(f'symbol {SYM} not in object'); sys.exit(1)
ours=strip_pad(norm(lines)); orig=ORIG
sm=difflib.SequenceMatcher(None,orig,ours,autojunk=False)
sc=sum(max(i2-i1,j2-j1) for t,i1,i2,j1,j2 in sm.get_opcodes() if t!='equal')
print(f'score {sc}  rom {len(orig)} ours {len(ours)}')
vram=fn['vram']
for t,i1,i2,j1,j2 in sm.get_opcodes():
    if t=='equal' or ctx<0: continue
    print('---')
    for k in range(max(0,i1-ctx),i1): print(f'  {vram+k*4:08X} {orig[k]}')
    for k in range(max(i2-i1,j2-j1)):
        a=orig[i1+k] if i1+k<i2 else ''
        b=ours[j1+k] if j1+k<j2 else ''
        print(f'* {vram+(i1+k)*4:08X} {a:42s} | {b}' if a else f'* {" "*8} {a:42s} | {b}')
    for k in range(i2,min(len(orig),i2+ctx)): print(f'  {vram+k*4:08X} {orig[k]}')
