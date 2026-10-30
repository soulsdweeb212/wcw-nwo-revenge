/* @header
 * buildScaleMatrixFixed  (originally func_8001BED0)
 * VRAM 0x8001BED0 | ROM 0x1CAD0 | size 0x7C
 * asm: asm/nonmatchings/main/buildScaleMatrixFixed.s
 */
#include "common.h"

void func_8001B090(void *,void *);
/* Builds a scale matrix (diagonal arg1/arg2/arg3, 1 for w) and converts it to
 * fixed point at arg0. */
void buildScaleMatrixFixed(void *arg0,f32 arg1,f32 arg2,f32 arg3) {
 f32 m[4][4]; f32 (*p)[4]=m;
 initIdentityMatrix4x4(p);
 p[0][0]=arg1;p[1][1]=arg2;p[2][2]=arg3;p[3][3]=1.0f;
 func_8001B090(p,arg0);
}
void func_8001F070(void *,void *,void *,s32);
s32 func_800202B0(s32,s32,s32,s32,s32);
void func_8001D720(void);void func_8001DF00(void);void func_8001F200(void);void func_8001F3EC(void);
u32 func_8001CE80(u32);
