"""A second opinion next to m2c: Ghidra's decompiler and a whole-ROM instruction search.

    python3 tools/ghidra.py import              # analyse the ROM once (minutes); results go to build/ghidra/
    python3 tools/ghidra.py decomp FUNC|0xVRAM  # print Ghidra's C for a function
    python3 tools/ghidra.py unmatched           # copy Ghidra's C for every function without real C to build/ghidra/unmatched/
    python3 tools/ghidra.py new                 # list functions Ghidra found that build.json does not have
    python3 tools/ghidra.py search 'lui .*; addiu .*,0x5478'     # instruction sequence, one regex per instruction
    python3 tools/ghidra.py bytes '3C02???? 2442????'            # raw big-endian words anywhere in the ROM, ? = any nibble

The overlays share addresses, so each is analysed as its own image together with `main`: a listing line is only meaningful
with its image. `search` matches Ghidra's spelling of an instruction, which is not always splat's (`or v0,s0,zero` for
`move`, hex offsets). Ghidra's C is a reading aid: it shows the logic, not the source shape, and it will not match as is."""
import json,os,re,shutil,subprocess,sys,tempfile
from pathlib import Path

ROOT=Path(__file__).resolve().parent.parent
OUT=ROOT/'build'/'ghidra'
GH=Path.home()/'.local'/'share'/'decompnet'/'toolchains'/'ghidra'
B=json.load(open(ROOT/'build.json'))
SEG={s['name']:s for s in B['segments']}
ROM=(ROOT/B['image']).read_bytes()
MAIN_ROM,MAIN_VRAM=SEG['entry']['start'],SEG['entry']['vram']
MAIN_END=SEG['main']['end']
BSS_END=SEG['main']['bss_vram']+SEG['main']['bss_size']
# name, ROM range, vram base: each runs up to the next image, so the blobs after the code are analysed as well
IMAGES=[('ovl80090000',SEG['code_80090000']['start'],SEG['code_8009D7A0']['start'],SEG['code_80090000']['vram']),
        ('ovl8009D7A0',SEG['code_8009D7A0']['start'],SEG['D5FB0']['start'],SEG['code_8009D7A0']['vram'])]

def image_of(rom):
    for name,start,end,vram in IMAGES:
        if start<=rom<end: return name,vram-start
    return 'main',MAIN_VRAM-MAIN_ROM

def do_import():
    shutil.rmtree(OUT,ignore_errors=True); OUT.mkdir(parents=True)
    base_img=bytearray(BSS_END-MAIN_VRAM)
    main=ROM[MAIN_ROM:MAIN_END]; base_img[:len(main)]=main
    for i,(name,start,end,vram) in enumerate(IMAGES):
        d=OUT/name; d.mkdir()
        img=bytearray(vram+(end-start)-MAIN_VRAM)
        img[:len(base_img)]=base_img
        img[vram-MAIN_VRAM:vram-MAIN_VRAM+end-start]=ROM[start:end]
        (d/'image.bin').write_bytes(img)
        rows=[]
        for f in B['functions']:
            if f['rom'] is None: continue
            im,off=image_of(f['rom'])
            if im in('main',name): rows.append(f"func\t{f['vram']:X}\t{f['name']}")
        known={f['name'] for f in B['functions']}
        own_end=vram+(end-start if i else SEG['code_80090000']['end']-start)
        for s,a in B['symbols'].items():
            if s in known: continue
            # the images overlap in vram, so a label past this overlay's own code belongs to the other one
            if MAIN_VRAM<=a<BSS_END or vram<=a<own_end: rows.append(f"data\t{a:X}\t{s}")
        (d/'labels.tsv').write_text('\n'.join(rows)+'\n')
        ranges=[f'{vram:X}-{vram+end-start:X}']
        if i==0: ranges=[f'{MAIN_VRAM:X}-{MAIN_VRAM+MAIN_END-MAIN_ROM:X}']+ranges
        for r in ranges:  # main is exported once, with the first image
            sub=d if r==ranges[-1] else OUT/'main'
            sub.mkdir(exist_ok=True)
        cmd=[str(GH/'support'/'analyzeHeadless'),str(d),'proj','-import',str(d/'image.bin'),'-overwrite',
             '-loader','BinaryLoader','-loader-baseAddr',f'0x{MAIN_VRAM:X}',
             '-processor','MIPS:BE:64:64-32addr','-cspec','o32',
             '-scriptPath',str(ROOT/'tools'/'ghidra_scripts'),
             '-preScript','NwoLabels.java',str(d/'labels.tsv'),
             '-postScript','NwoExport.java',str(d),ranges[-1],ranges[-1]]
        if i==0:
            cmd+=['-postScript','NwoExport.java',str(OUT/'main'),ranges[0]]
        print('analysing',name,flush=True)
        r=subprocess.run(cmd,capture_output=True,text=True,cwd=d)
        (d/'headless.log').write_text(r.stdout+r.stderr)
        if r.returncode or not (d/'functions.tsv').exists():
            sys.exit(f'Ghidra failed for {name}; see {d/"headless.log"}')
        (d/'image.bin').unlink()
    print('done:',OUT)

def dirs():
    ds=[d for d in (OUT/'main',OUT/IMAGES[0][0],OUT/IMAGES[1][0]) if (d/'functions.tsv').exists()]
    if not ds: sys.exit('run `python3 tools/ghidra.py import` first')
    return ds
def functions():
    for d in dirs():
        for l in open(d/'functions.tsv'):
            a,size,name=l.rstrip('\n').split('\t')
            yield d,a,int(size),name
def c_path(fn):
    name=fn['name']; im=image_of(fn['rom'])[0]
    return OUT/im/'c'/f"{fn['vram']:08x}.c"

def do_decomp(arg):
    fn=next((f for f in B['functions'] if f['name']==arg),None)
    if fn: print(c_path(fn).read_text()); return
    a=f'{int(arg,16)&0xFFFFFFFF:08x}'
    hits=[d/'c'/f'{x}.c' for d,x,_,_ in functions() if x==a]
    if not hits: sys.exit(f'no function {arg}')
    for p in hits: print(f'// {p.parent.parent.name}'); print(p.read_text())

def do_unmatched():
    dst=OUT/'unmatched'; dst.mkdir(exist_ok=True); n=0
    for f in B['functions']:
        p=ROOT/f['c'] if f.get('c') else ROOT/'src'/f['seg']/f"{f['name']}.c"
        if p.exists(): continue
        c=c_path(f)
        if c.exists(): shutil.copy(c,dst/f"{f['name']}.c"); n+=1
    print(f'{n} files in {dst}')

def do_new():
    known={f['vram'] for f in B['functions']}
    ours=lambda d,v:any(s['kind']=='code' and s['vram']<=v<s['vram']+s['end']-s['start'] for s in B['segments'] if s['kind']=='code'
                        and ((d.name=='ovl80090000')==(s['name']=='code_80090000')))
    n=k=0
    for d,a,size,name in functions():
        v=int(a,16)
        if v in known: continue
        if d.name!='main' and ours(d,v): k+=1; continue  # inside listed code: a piece of a known function, or a jump target
        print(f'{d.name:12} {a} size {size:#x} {name}'); n+=1
    print(n,'functions outside the listed code,',k,'more inside it (ignored)')

def do_search(pat):
    ps=[re.compile(p.strip()) for p in pat.split(';')]
    n=0
    for d in dirs():
        rows=[l.rstrip('\n').split('\t') for l in open(d/'instructions.tsv')]
        texts=[r[2].lstrip('_') for r in rows]
        for i in range(len(rows)-len(ps)+1):
            if all(p.search(texts[i+k]) for k,p in enumerate(ps)):
                print(d.name,rows[i][0],' ; '.join(texts[i:i+len(ps)])); n+=1
    print(n,'hits')

def do_bytes(pat):
    h=pat.replace(' ','').upper()
    if len(h)%2: sys.exit('whole bytes only')
    def one(x):
        if x=='??': return b'.'
        if '?' not in x: return re.escape(bytes([int(x,16)]))
        return b'['+b''.join(re.escape(bytes([v])) for v in range(256) if re.fullmatch(x.replace('?','.'),f'{v:02X}'))+b']'
    rx=re.compile(b''.join(one(h[i:i+2]) for i in range(0,len(h),2)),re.S)
    n=0
    for m in rx.finditer(ROM):
        if m.start()%4: continue
        im,off=image_of(m.start())
        print(f'ROM {m.start():#x}  {im} vram {m.start()+off:08X}  {m.group().hex().upper()}'); n+=1
    print(n,'hits')

if __name__=='__main__':
    c=sys.argv[1] if len(sys.argv)>1 else ''
    if c=='import': do_import()
    elif c=='decomp': do_decomp(sys.argv[2])
    elif c=='unmatched': do_unmatched()
    elif c=='new': do_new()
    elif c=='search': do_search(sys.argv[2])
    elif c=='bytes': do_bytes(sys.argv[2])
    else: print(__doc__)
