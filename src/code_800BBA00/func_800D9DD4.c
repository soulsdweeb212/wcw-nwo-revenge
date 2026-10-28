#include "common.h"

extern s16 D_800F9848[];
extern u8 D_800F9D20[];
extern f64 D_800E7020;

f32 func_800D3890(void *, void *, void *);
s8 isEntityActionEligible(void *, s32, s32);
s8 func_800D8DF0(void *);
s8 func_800D96A0(void *);

/* Returns 1 when the XZ distance between arg0 and arg1 is below D_800E7020. */
s32 func_800D9DD4(s32 arg0, s32 arg1) {
    return func_800D3890((void *)(arg0 + 0x6C), (void *)(arg1 + 0x6C), 0) < D_800E7020;
}
