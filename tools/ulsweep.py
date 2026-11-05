"""ulsweep.py OUT.json [VERSIONS] : compile every ultralib C file (ULTRALIB env var) for each libgultra_rom version
(default "I J K"), split the objects into functions and score each against every main-segment ROM function of a
similar size (same normalisation as dh.py). Writes, per ROM function, the best candidates. Run from source/."""
import sys,os,re,json,subprocess,tempfile,difflib,glob
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor
from decompnet.compiler import compile_source
from decompnet.project import compiler_config, compiler_for
src=open('tools/permute_run.py').read()
FUNCS=src[src.index('def norm(lines):'):src.index('tmp=tempfile.mkdtemp()')]
from decompnet import toolchains
OD=str(toolchains.binary('binutils-mips').parent/'mips-ps2-decompals-objdump')
exec(FUNCS)
def strip_pad(l):
    l=list(l)
    while l and l[-1].strip()=='nop': l.pop()
    return l
OUT=sys.argv[1]; VERS=(sys.argv[2] if len(sys.argv)>2 else 'I J K').split()
U=os.environ['ULTRALIB']; ROOT=Path('.').resolve()
B=json.load(open('build.json'))
main=sorted([f for f in B['functions'] if f['seg']=='main'],key=lambda f:f['vram'])
rom=open(B['image'],'rb').read()
tmp=tempfile.mkdtemp()
roms={}
for f in main:
    size=int(re.search(r'nonmatching \S+, (0x[0-9A-Fa-f]+)',open(f['asm']).read()).group(1),16)
    p=f'{tmp}/r.bin'; open(p,'wb').write(rom[f['rom']:f['rom']+size])
    roms[f['name']]=strip_pad(norm(dis(p,True)))
cfg=compiler_config(ROOT,{"compiler":compiler_for(B,main[0]['vram'])})
cfgs={'-O2':cfg}
import copy
c3=copy.deepcopy(cfg)
for a in ('cmd','flags','args'):
    if hasattr(c3,a) and isinstance(getattr(c3,a),list): setattr(c3,a,['-O3' if x=='-O2' else x for x in getattr(c3,a)])
cfgs['-O3']=c3
files=sorted(glob.glob(f'{U}/src/**/*.c',recursive=True))
def work(job):
    path,v,opt=job
    rel=os.path.relpath(path,f'{U}/src')
    pp=subprocess.run(['bash','tools/ulpp.sh',rel,v],capture_output=True,text=True)
    if pp.returncode or not pp.stdout.strip(): return []
    try: res=compile_source(cfgs[opt],'',pp.stdout,trusted=True)
    except Exception: return []
    if not res.ok: return []
    o=f'{tmp}/{abs(hash(job))}.o'; open(o,'wb').write(res.obj)
    txt=subprocess.run([OD,'-d',o],capture_output=True,text=True).stdout
    fs={};cur=None
    for l in txt.splitlines():
        h=re.match(r'^[0-9a-f]+ <(\S+)>:',l)
        if h: cur=h.group(1); fs[cur]=[]; continue
        m=re.match(r'\s+([0-9a-f]+):\t[0-9a-f ]+\t(.*)',l)
        if cur and m: fs[cur].append(m.group(1)+':\t'+m.group(2))
    return [(rel,v,opt,n,strip_pad(norm(ls))) for n,ls in fs.items() if ls]
jobs=[(p,v,o) for p in files for v in VERS for o in cfgs]
with ThreadPoolExecutor(5) as ex: comp=[c for r in ex.map(work,jobs) for c in r]
print(len(comp),'compiled functions',file=sys.stderr)
seen={}
for rel,v,opt,n,ins in comp:  # identical code across versions/opts: keep one, remember where
    k=(rel,n,tuple(ins)); seen.setdefault(k,[]).append(f'{v}{opt}')
uniq=[(rel,n,list(ins),vs) for (rel,n,ins),vs in seen.items()]
def best(name):
    r=roms[name]; out=[]
    for rel,n,ins,vs in uniq:
        if not (0.6*len(r)<=len(ins)<=1.6*len(r)+2): continue
        sm=difflib.SequenceMatcher(None,r,ins,autojunk=False)
        if sm.real_quick_ratio()<0.6 or sm.quick_ratio()<0.6: continue
        sc=sum(max(i2-i1,j2-j1) for t,i1,i2,j1,j2 in sm.get_opcodes() if t!='equal')
        out.append((sc,round(sc/max(len(r),len(ins)),3),n,rel,vs))
    out.sort(); return out[:4]
with ThreadPoolExecutor(5) as ex: res=dict(zip(roms,ex.map(best,roms)))
json.dump({n:{'vram':f"{f['vram']:08X}",'len':len(roms[n]),'cands':res[n]} for n,f in zip(roms,main)},open(OUT,'w'),indent=1)
