/* @header
 * func_800D9234
 * VRAM 0x800D9234 | ROM 0xCC6D4 | size 0x3C
 * asm: asm/nonmatchings/code_800BBA00/func_800D9234.s
 */
#include "common.h"

extern s16 D_800F9848[];
extern f64 D_800E7020;

f32 func_800D3890(void *, void *, void *);
s8 isEntityActionEligible(void *, s32, s32);
s8 func_800D8DF0(void *);
s8 func_800D96A0(void *);

/* Cache wrestler arg0's health into D_800F9848. */
void func_800D9234(s8 arg0) {
    D_800F9848[arg0] = D_800F9D10[arg0].health;
}
