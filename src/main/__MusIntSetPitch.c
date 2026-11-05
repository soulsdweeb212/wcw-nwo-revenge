/* @header
 * __MusIntSetPitch  (originally func_80014F5C)
 * VRAM 0x80014F5C | ROM 0x15B5C | size 0x10C
 * asm: asm/nonmatchings/main/__MusIntSetPitch.s
 */
/* SDK: libmus, libmus/src/player.c (same code as the SDK source). */
#include "common.h"

typedef struct {u8 pad0[0x38];f32 f38,f3C,f40;u8 pad44[0x24];f32 f68,f6C;u8 pad70[0x5A];u16 fCA;u8 padCC[12];u8 fD8,fD9,fDA,fDB;} Voice14F;
extern f64 D_8003B330,D_8003B338;
extern u8 *D_800604CC;
f32 __MusIntPowerOf2(f32);
void n_alSynSetPitch(void *,f32);
void __MusIntSetPitch(Voice14F *p,s32 index,f32 delta) {
    f32 v=p->f40; u8 steps=p->fD8;
    if(steps) {
        if(steps>=p->fCA) v=p->f68+((v-p->f68)/(f32)steps)*(f32)p->fCA;
        p->f6C=v;
    }
    v=v+(delta+p->f38);
    if(v!=p->f3C) {
        p->f3C=v;
        v=__MusIntPowerOf2((f32)((f64)v*D_8003B330));
        if(D_8003B338<(f64)v) {v=2.0f;p->fDB=0;}
        n_alSynSetPitch(D_800604CC+index*0x1C,v);
    }
}
