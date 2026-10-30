"""Random-walks variants of a near-miss function's C with decomp-permuter's generator and keeps the closest.

    cd source
    ~/.local/share/uv/tools/decompnet/bin/python tools/permute_run.py FUNC DRAFT.c MINUTES [WORKERS]

FUNC is a function name from build.json, DRAFT.c a C file that defines it (as src/<segment>/FUNC.c would). Each variant is
compiled with the project's own compiler command and scored by how many instructions differ from the original ROM bytes
(relocation targets and branch offsets are ignored). The best is written to build/permuter/perm_FUNC.best.c, and a score
of 0 to perm_FUNC.MATCH.c: copy that to src/<segment>/FUNC.c and run `build.py` to confirm, as the score is only a guide.
The permuter rewrites the C aggressively and does not always keep its meaning, so read a "best" before using it.
Nothing under src/ is touched. Needs decomp-permuter (`decomp setup`)."""
import json,re,subprocess,sys,time,random,difflib,tempfile,os
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor
from decompnet.compiler import compile_source
from decompnet.project import compiler_config, compiler_for

FUNC,SRC,MIN=sys.argv[1],sys.argv[2],float(sys.argv[3]); W=int(sys.argv[4]) if len(sys.argv)>4 else 4
ROOT=Path('.').resolve(); S=ROOT/'build'/'permuter'; S.mkdir(parents=True,exist_ok=True)
B=json.load(open('build.json'))
fn=next(f for f in B['functions'] if f['name']==FUNC)
import decompnet
from decompnet import toolchains
TC=Path.home()/'.local'/'share'/'decompnet'/'toolchains'
OD=str(toolchains.binary('binutils-mips').parent/'mips-ps2-decompals-objdump')
PD=str(TC/'decomp-permuter')
GEN=str(Path(decompnet.__file__).parent/'permuter_gen.py')
size=int(re.search(r'nonmatching \S+, (0x[0-9A-Fa-f]+)',open(fn['asm']).read()).group(1),16)
rom=open(B['image'],'rb').read()[fn['rom']:fn['rom']+size]
header=open('include/common.h').read()
cfg=compiler_config(ROOT,{"compiler":compiler_for(B,fn['vram'])})

def norm(lines):
    out=[]
    for l in lines:
        l=re.sub(r'^[0-9a-f]+:\s*','',l.strip())
        m=re.match(r'(\S+)\s*(.*)',l)
        if not m: continue
        op,args=m.group(1),m.group(2)
        args=re.sub(r'\s*<[^>]*>','',args)
        if op in('lui','jal','j'): args=re.sub(r'0x[0-9a-f]+|\b[0-9a-f]+$','',args)
        if op in('b','beq','bne','bnez','beqz','beql','bnel','beqzl','bnezl','bgez','bgtz','blez','bltz','bgezl','bgtzl','blezl','bltzl','bc1t','bc1f','bc1tl','bc1fl'):
            args=re.sub(r',?\s*(0x)?[0-9a-f]+\s*$','',args)
        if op in('lwc1','swc1','lw','sw','lb','lbu','lh','lhu','sb','sh','ldc1','sdc1','lwl','lwr','swl','swr'):
            args=re.sub(r'(-?\d+)\((?!sp)(\w+)\)',r'#(\2)',args)
        if op=='addiu' and not re.search(r'\bsp\b',args.split(',')[1] if ',' in args else ''):
            args=re.sub(r',\s*-?\d+$',',#',args)
        out.append(op+' '+args)
    return out
def dis(path,binary=False):
    cmd=[OD,'-D','-b','binary','-m','mips:4000','-EB',path] if binary else [OD,'-d',path]
    txt=subprocess.run(cmd,capture_output=True,text=True).stdout
    return [m.group(1)+':\t'+m.group(2) for l in txt.splitlines() if (m:=re.match(r'\s+([0-9a-f]+):\t[0-9a-f ]+\t(.*)',l))]
tmp=tempfile.mkdtemp(); open(tmp+'/orig.bin','wb').write(rom)
def strip_pad(l):  # alignment nops at the end of a function: the ROM's size includes them, the linker supplies ours
    l=list(l)
    while l and l[-1].strip()=='nop': l.pop()
    return l
ORIG=strip_pad(norm(dis(tmp+'/orig.bin',True)))

def score(src,tag='0'):
    m=re.match(r'\s*(?:/\* @header\n(?: \*.*\n)*? \*/\n)*#include "([^"]+)"\s*\n',src)
    body=src[m.end():] if m else src
    try: res=compile_source(cfg,header,body,trusted=True)
    except Exception: return None
    if not res.ok: return None
    p=f'{tmp}/v{tag}.o'; open(p,'wb').write(res.obj)
    ours=strip_pad(norm(dis(p)))
    sm=difflib.SequenceMatcher(None,ORIG,ours,autojunk=False)
    return sum(max(i2-i1,j2-j1) for t,i1,i2,j1,j2 in sm.get_opcodes() if t!='equal')

best_src=open(SRC).read(); best=score(best_src,'base')
print(f'{FUNC}: {len(ORIG)} original instructions; start score {best}',flush=True)
gen=subprocess.Popen([PD+'/venv/bin/python','-I',GEN,PD],stdin=subprocess.PIPE,stdout=subprocess.PIPE,text=True,bufsize=1)
def variants(src,seed,count):
    gen.stdin.write(json.dumps({"header":header,"source":src,"function":FUNC,"family":"gcc","seed":seed,"count":count})+"\n"); gen.stdin.flush()
    out=[]
    while True:
        r=json.loads(gen.stdout.readline())
        if r.get('done'): return out
        if 'variant' in r: out.append(r['variant'])
        if 'error' in r: print('generator error:',r['error'][:200],flush=True); return out
rng=random.Random(); t0=time.time(); tried=0; ok=0; pool=ThreadPoolExecutor(W)
cur_src,cur=best_src,best; rounds=0
while time.time()-t0<MIN*60 and best!=0:
    rounds+=1
    vs=variants(cur_src,rng.randrange(10**9),60)
    scores=list(pool.map(lambda a:score(a[1],str(a[0])),enumerate(vs)))
    for v,s in zip(vs,scores):
        tried+=1
        if s is None: continue
        ok+=1
        if s<best:
            best,best_src=s,v; cur,cur_src=s,v
            (S/f'perm_{FUNC}.best.c').write_text(v)
            print(f'  [{time.time()-t0:5.0f}s] new best {s}  (tried {tried}, compiled {ok})',flush=True)
        elif s<=cur and rng.random()<0.3: cur,cur_src=s,v
    if rounds%10==0:
        print(f'  [{time.time()-t0:5.0f}s] tried {tried}, compiled {ok}, best {best}, walking at {cur}',flush=True)
        if cur>best+6: cur,cur_src=best,best_src  # drifted too far: restart from best
print(f'DONE {FUNC}: best {best} after {tried} variants ({ok} compiled) in {time.time()-t0:.0f}s',flush=True)
if best==0: (S/f'perm_{FUNC}.MATCH.c').write_text(best_src); print('ZERO SCORE: saved MATCH candidate; verify with the real build',flush=True)
gen.stdin.close()
