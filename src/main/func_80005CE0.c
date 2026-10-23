#include "common.h"

typedef struct {u32 w0,w1;} GfxPair;
typedef struct {u32 f0;u8 clampS,clampT,maskS,maskT;} TexInfo;
typedef struct {
    u8 pad0[2];
    s8 count;
    s8 first;
    u8 pad4[4];
    u16 w;
    u16 h;
    void *maybe;
    GfxPair *dl;
    void *next;
    TexInfo *tex;
    u32 palette;
} TexRect;
#define EMIT(a,b) {GfxPair *g=dl++;g->w0=(u32)(a);g->w1=(u32)(b);}

/* Emits the RDP display list for one textured rectangle.  It first takes the
 * tile clamp masks from obj->tex and records the tile size (1<<maskS / 1<<maskT)
 * in obj->w/h, optionally emitting a 0x03 tiling command when a render mode is
 * present, then loads the texture image (obj->tex) and TEXEL0 (obj->palette) and
 * emits the texture-rectangle, the 16-bit texel scale (F5400000) and the
 * full-size rectangle (F2000000).  It finishes by chaining to obj->next's
 * display list, or writing the DF000000 end marker. */
void func_80005CE0(TexRect *obj) {
    u8 clampS,clampT,maskS,maskT;
    GfxPair *dl=obj->dl;
    clampS=obj->tex->clampS;clampT=obj->tex->clampT;maskS=obj->tex->maskS;maskT=obj->tex->maskT;
    obj->w=(u16)(1<<maskS);obj->h=(u16)(1<<maskT);
    if(obj->maybe!=0) {
        if(obj->count<9) {
            GfxPair *g=dl++;
            g->w0=((u32)(obj->first*2)&0xFFFF)|0x03000000;
            g->w1=(u32)((obj->first+obj->count)*2)&0xFFFF;
        }
    }
    EMIT(0xE200001C,0x504240);
    EMIT(0xFA000000,0xD0);
    EMIT(0xFCFFB3FF,0xFF64FE7F);
    EMIT(0xFD100000,obj->palette-0x80000000);
    EMIT(0xE8000000,0);
    EMIT(0xF5000100,0x07000000);
    EMIT(0xE6000000,0);
    EMIT(0xF0000000,0x0703C000);
    EMIT(0xE7000000,0);
    EMIT(0xFD500000,(u32)obj->tex+0x80000008);
    EMIT(0xF5500000,(((u32)clampT&3)<<18)|0x07000000|(((u32)maskT&15)<<14)|(((u32)clampS&3)<<8)|(((u32)maskS&15)<<4));
    EMIT(0xE6000000,0);
    {GfxPair *g=dl++;s32 numerator;s32 count;
     g->w0=0xF3000000;
     if((s16)obj->w/16>0)numerator=(s16)obj->w/16+0x7FF;
     else numerator=0x800;
     count=((((s16)obj->w)*((s16)obj->h)+3)>>2)-1;
     if(count>=0x800)count=0x7FF;
     g->w1=((count&0xFFF)<<12)|0x07000000|((((s16)obj->w/16)>0)?numerator/((s16)obj->w/16):numerator)&0xFFF;}
    EMIT(0xE7000000,0);
    EMIT(0xF5400000|((((((s16)obj->w>>1)+7)>>3)&0x1FF)<<9),(((u32)clampT&3)<<18)|(((u32)maskT&15)<<14)|(((u32)clampS&3)<<8)|(((u32)maskS&15)<<4));
    EMIT(0xF2000000,((((((s16)obj->w-1)*4)&0xFFF)<<12)|((((s16)obj->h-1)*4)&0xFFF)));
    if(obj->next!=0) {EMIT(0xDE010000,(u32)obj->next-0x80000000);}
    else {EMIT(0xDF000000,0);}
}
