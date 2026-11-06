/* @header
 * func_800C2B8C
 * VRAM 0x800C2B8C | ROM 0xB602C | size 0x150
 * asm: asm/nonmatchings/code_800BBA00/func_800C2B8C.s
 */
#include "common.h"

extern f32 func_800D3564(f32);
typedef struct { f32 f[31]; } PartC2B;
extern PartC2B D_80070C70[][23], D_80070C78[][23];
extern f32 D_800E3AC0[], D_800FADE0[][23];
extern f64 D_800E5920;
/* w is only read for w->id. func_800C0354 passes D_800FAF5C; updateEntitySetupAction calls it with no argument,
 * but $a0 there still holds D_800EB408, so w is the wrestler being updated in both cases. */
void func_800C2B8C(Wrestler *w) {
    s16 i=1; s32 id=w->id; f32 x,z; f64 d; f64 scale=D_800E5920; s32 j;
    do { j=i;
        x=func_800D3564(D_80070C70[id][j].f[0]-D_80070C78[id][j].f[1]);
        z=func_800D3564(D_80070C78[id][j].f[0]-D_80070C78[id][j].f[3]);
        if(z<x) d=x; else d=z;
        D_800FADE0[id][j]=d*scale;
        D_800FADE0[id][i]*=D_800E3AC0[i];
        i++;
    }while(i<20);
}
