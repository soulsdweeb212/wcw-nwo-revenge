/* @header
 * func_800D9DD4
 * VRAM 0x800D9DD4 | ROM 0xCD274 | size 0x48
 * asm: asm/nonmatchings/code_800BBA00/func_800D9DD4.s
 */
#include "common.h"

extern s16 D_800F9848[];
extern f64 D_800E7020;

f32 func_800D3890(void *, void *, void *);
s8 isEntityActionEligible(void *, s32, s32);
s8 func_800D8DF0(void *);
s8 func_800D96A0(void *);

/* Returns 1 when the distance between the pelvis joints (jointA[1]) of arg0 and arg1 is below D_800E7020. */
s32 func_800D9DD4(Wrestler *arg0, Wrestler *arg1) {
    return func_800D3890(&arg0->jointA[1], &arg1->jointA[1], 0) < D_800E7020;
}
