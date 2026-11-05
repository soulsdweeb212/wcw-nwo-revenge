/* @header
 * guScale  (originally func_8001BED0)
 * VRAM 0x8001BED0 | ROM 0x1CAD0 | size 0x7C
 * asm: asm/nonmatchings/main/guScale.s
 */
/* SDK: libultra 2.0I, ultralib src/gu/scale.c (same code as the SDK source). */
#include "common.h"

void guMtxF2L(void *,void *);
/* Builds a scale matrix (diagonal arg1/arg2/arg3, 1 for w) and converts it to
 * fixed point at arg0. */
void guScale(void *arg0,f32 arg1,f32 arg2,f32 arg3) {
    f32 m[4][4]; f32 (*p)[4]=m;
    guMtxIdentF(p);
    p[0][0]=arg1;p[1][1]=arg2;p[2][2]=arg3;p[3][3]=1.0f;
    guMtxF2L(p,arg0);
}
void alFilterNew(void *,void *,void *,s32);
s32 alHeapDBAlloc(s32,s32,s32,s32,s32);
void alAdpcmPull(void);void alLoadParam(void);void alResamplePull(void);void alResampleParam(void);
u32 osVirtualToPhysical(u32);
