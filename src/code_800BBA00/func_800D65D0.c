#include "common.h"

extern u32 D_800FABD8;
extern u16 D_800E3F84[];
extern u16 D_800E3F8C[];
extern u8 D_80030560[];
extern u8 D_8007C438[];

/* Report whether the D_800FABD8 status has bit 2 set. */
s32 func_800D633C(void) {
    return (D_800FABD8 & 2) == 2;
}

/* Classify the entity's quadrant (+0x3C) against mask arg1: 1, 2 or 0. */
s32 func_800D65D0(u8 *arg0, s32 arg1) {
    s32 idx = *(s16 *)(arg0 + 0x3C);

    if (D_800E3F84[idx] & arg1) {
        return 1;
    }
    return ((D_800E3F8C[idx] & arg1) != 0) * 2;
}

/* Look up the animation id for the entity's current animation plus arg1. */
s16 func_800D5438(u8 *arg0, s32 arg1) {
    s32 idx = *(s16 *)(arg0 + 0x386);
    s32 row = *(s8 *)(arg0 + 0x384);
    u16 t = ((u16 *)((u8 *)D_80030560 + 0x10))[idx];
    u8 *base = (u8 *)D_8007C438 + 0x180 + row * 0x600;

    return *(u16 *)(base + (s16)(t + arg1) * 2) + 0x110B;
}
