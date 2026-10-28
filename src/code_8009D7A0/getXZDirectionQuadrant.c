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
