/* @header
 * func_800DACB4
 * VRAM 0x800DACB4 | ROM 0xCE154 | size 0x30
 * asm: asm/nonmatchings/code_800BBA00/func_800DACB4.s
 */
#include "common.h"

extern s16 D_800F9848[];
extern f64 D_800E7020;

f32 func_800D3890(void *, void *, void *);
s8 isEntityActionEligible(void *, s32, s32);
s8 func_800D8DF0(void *);
s8 func_800D96A0(void *);

/* Returns action 0xD2 when the wrestler is eligible for it, else 0xD1. */
s32 func_800DACB4(Wrestler *arg0) {
    if (isEntityActionEligible(arg0, 0, 0xD2)) {
        return 0xD2;
    }
    return 0xD1;
}
