#include "common.h"

s32 func_800D36E8(f32, f32);
void func_800D4AD0(void *);
void func_800DECAC(void *, s32, s32, s32);

/* Four-way XZ heading (4096 units per turn) from a float vector. */
s32 getXZDirectionQuadrant(f32 *arg0) {
    s32 angle = func_800D36E8(arg0[0], arg0[2]);
    angle += 0x1200;
    angle /= 0x400;
    return angle & 3;
}

/* If the entity's timer (+4) has just reached 1, reset it to action state 0x2B and
 * return 1; otherwise return 0. */
s32 func_800A7188(void *arg0) {
    if (*(s16 *)((u8 *)arg0 + 4) == 1) {
        func_800D4AD0(arg0);
        *(s16 *)((u8 *)arg0 + 0xA) = 0x2B;
        *(s16 *)((u8 *)arg0 + 0xC) = 0;
        *(s16 *)((u8 *)arg0 + 0xE) = 0;
        *(s16 *)((u8 *)arg0 + 0x360) = 0;
        *(u64 *)((u8 *)arg0 + 0x20) = (*(u64 *)((u8 *)arg0 + 0x20) & ~0x10810000000ULL) | 0x1000000000ULL;
        func_800DECAC(arg0, 0, 0, 0);
        *(u64 *)((u8 *)arg0 + 0x20) |= 0x10000000ULL;
        return 1;
    }
    return 0;
}
