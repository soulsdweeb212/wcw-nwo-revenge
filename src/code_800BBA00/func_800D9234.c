#include "common.h"

extern s16 D_800F9848[];
extern u8 D_800F9D20[];
extern f64 D_800E7020;

f32 func_800D3890(void *, void *, void *);
s8 isEntityActionEligible(void *, s32, s32);
s8 func_800D8DF0(void *);
s8 func_800D96A0(void *);

/* Cache entity arg0's id word into D_800F9848. */
void func_800D9234(s8 arg0) {
    D_800F9848[arg0] = *(u16 *)(D_800F9D20 + arg0 * 0x3B0);
}
