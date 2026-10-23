#include "common.h"

extern s32 D_800FABD8;
extern u16 D_800E3F84[];
extern u16 D_800E3F8C[];
extern u8 D_80030560[];
extern u8 D_8007C438[];

typedef struct { f32 x; f32 y; } Nw2Vec2C50;
extern Nw2Vec2C50 D_800E3C50[];

extern void func_800D36E8(f32, f32);

/* Report whether the D_800FABD8 status has bit 2 set. */
s32 func_800D633C(void) {
    return (D_800FABD8 & 2) != 0;
}

/* Classify the entity's quadrant (+0x3C) against mask arg1: 1, 2 or 0. */
s32 func_800D65D0(u8 *arg0, s32 arg1) {
    s32 idx = *(s16 *)(arg0 + 0x3C) * 2;
    s32 v;

    if (D_800E3F84[idx / 2] & arg1) {
        v = 1;
    } else {
        v = (D_800E3F8C[idx / 2] & arg1) != 0;
        v *= 2;
    }
    return v;
}

/* Compute the heading from the entity position toward quadrant-table entry arg1. */
void func_800D6610(u8 *arg0, s32 arg1) {
    s32 i = (s16)arg1;

    func_800D36E8(D_800E3C50[i].x - *(f32 *)(arg0 + 0x6C),
                  D_800E3C50[i].y - *(f32 *)(arg0 + 0x74));
}

/* Look up the animation id for the entity's current animation plus arg1. */
s16 func_800D5438(u8 *arg0, s32 arg1) {
    return *(u16 *)((u8 *)D_8007C438 + 0x180 + *(s8 *)(arg0 + 0x384) * 0x600
                    + (s16)(((u16 *)((u8 *)D_80030560 + 0x10))[*(s16 *)(arg0 + 0x386)] + arg1) * 2)
           + 0x110B;
}
