#include "common.h"

extern s16 D_800F9848[];
extern u8 D_800F9D20[];
extern f64 D_800E7020;

f32 func_800D3890(void *, void *, void *);
s8 isEntityActionEligible(void *, s32, s32);
s8 func_800D8DF0(void *);
s8 func_800D96A0(void *);

/* Caches entity arg0's D_800F9D20 word into D_800F9848. */
void func_800D9234(s8 arg0) {
    D_800F9848[arg0] = *(u16 *)(D_800F9D20 + arg0 * 0x3B0);
}

/* Returns 1 when the XZ distance between arg0 and arg1 is below D_800E7020. */
s32 func_800D9DD4(s32 arg0, s32 arg1) {
    return func_800D3890((void *)(arg0 + 0x6C), (void *)(arg1 + 0x6C), 0) < D_800E7020;
}

/* Returns action 0xD2 when the entity is eligible, else 0xD1. */
s32 func_800DACB4(s32 arg0) {
    if (isEntityActionEligible((void *)arg0, 0, 0xD2)) {
        return 0xD2;
    }
    return 0xD1;
}

/* Returns 1 when the entity is in a state that blocks its action (0x200 flag,
 * 0x6000 high flag, or either of the two busy checks). */
s32 func_800DA6DC(s32 arg0) {
    if ((*(s32 *)(arg0 + 0x20) & 0) || (*(s32 *)(arg0 + 0x24) & 0x200)) {
        return 1;
    }
    if ((*(s32 *)(arg0 + 0x358) & 0x6000) || (*(s32 *)(arg0 + 0x35C) & 0)) {
        return 1;
    }
    if (func_800D8DF0((void *)arg0)) {
        return 1;
    }
    if (func_800D96A0((void *)arg0)) {
        return 1;
    }
    return 0;
}
