"""A second opinion next to m2c: Ghidra's decompiler and a whole-ROM instruction search.

    python3 tools/ghidra.py import              # analyse the ROM once (minutes); results go to build/ghidra/
    python3 tools/ghidra.py decomp FUNC|0xVRAM  # print Ghidra's C for a function
    python3 tools/ghidra.py unmatched           # copy Ghidra's C for every function without real C to build/ghidra/unmatched/
    python3 tools/ghidra.py new                 # list functions Ghidra found that build.json does not have
    python3 tools/ghidra.py search 'lui .*; addiu .*,0x5478'     # instruction sequence, one regex per instruction
    python3 tools/ghidra.py bytes '3C02???? 2442????'            # raw big-endian words anywhere in the ROM, ? = any nibble

The two overlays both load at 0x80090000 (see OVERLAY_TABLE), so each is analysed as its own image together with `main`: a
listing line is only meaningful with its image. `search` matches Ghidra's spelling of an instruction, which is not always splat's (`or v0,s0,zero` for
`move`, hex offsets). Ghidra's C is a reading aid: it shows the logic, not the source shape, and it will not match as is."""
import json,os,re,shutil,struct,subprocess,sys,tempfile
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
# The game's own overlay table, in main's data: ROM start, ROM end, then vram start, text end, data end, bss end (the last
# three each stored twice, as the end of one section and the start of the next).
OVERLAY_TABLE=0x37A30
def overlays():
    out=[]
    for i in (0,1):
        w=struct.unpack('>9I',ROM[OVERLAY_TABLE+i*36:OVERLAY_TABLE+(i+1)*36])
        out.append((f'overlay{i+1}',w[0],w[1],w[2],w[4],w[8]))  # name, rom, rom end, vram, text end, bss end
    return out
IMAGES=overlays()

def image_of(rom):
    for name,start,end,vram,_,_ in IMAGES:
        if start<=rom<end: return name,vram-start
    return 'main',MAIN_VRAM-MAIN_ROM

def do_import():
    shutil.rmtree(OUT,ignore_errors=True); OUT.mkdir(parents=True)
    base_img=bytearray(BSS_END-MAIN_VRAM)
    main=ROM[MAIN_ROM:MAIN_END]; base_img[:len(main)]=main
    for i,(name,start,end,vram,text_end,bss_end) in enumerate(IMAGES):
        d=OUT/name; d.mkdir()
        img=bytearray(bss_end-MAIN_VRAM)
        img[:len(base_img)]=base_img
        img[vram-MAIN_VRAM:vram-MAIN_VRAM+end-start]=ROM[start:end]
        (d/'image.bin').write_bytes(img)
        rows=[]
        for f in B['functions']:
            if f['rom'] is None: continue
            if image_of(f['rom'])[0] in('main',name): rows.append(f"func\t{f['vram']:X}\t{f['name']}")
        known={f['name'] for f in B['functions']}
        for s,a in B['symbols'].items():
            # symbols carry no overlay, so past main a name may be the other overlay's: leave those unnamed
            if s not in known and MAIN_VRAM<=a<BSS_END: rows.append(f"data\t{a:X}\t{s}")
        (d/'labels.tsv').write_text('\n'.join(rows)+'\n')
        ranges=[f'{vram:X}-{text_end:X}']
        if i==0: ranges=[f'{MAIN_VRAM:X}-{MAIN_VRAM+MAIN_END-MAIN_ROM:X}']+ranges
        (OUT/'main').mkdir(exist_ok=True)
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
    ds=[d for d in (OUT/'main',OUT/'overlay1',OUT/'overlay2') if (d/'functions.tsv').exists()]
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
    known={}
    for f in B['functions']: known.setdefault(image_of(f['rom'])[0],set()).add(f['vram'])
    listed=lambda rom:any(x['kind']=='code' and x['start']<=rom<x['end'] for x in B['segments'])
    start={n:(st,v) for n,st,_,v,_,_ in IMAGES}; start['main']=(MAIN_ROM,MAIN_VRAM)
    n=k=size_new=0
    for d,a,size,name in functions():
        v=int(a,16)
        if v in known.get(d.name,()): continue
        rom=v-start[d.name][1]+start[d.name][0]
        if listed(rom): k+=1; continue  # a piece of a known function, or a jump target
        print(f'{d.name:9} ROM {rom:#8x} {a} size {size:#x} {name}'); n+=1; size_new+=size
    print(f'{n} functions ({size_new:#x} bytes) outside the listed code, {k} more inside it (ignored)')

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
