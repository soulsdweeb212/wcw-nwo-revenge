#include "common.h"

/* Quadrant (0..7) of angle arg0. */
s32 func_800D3638(s32 arg0) {
    s32 v = arg0 + 0x1100;
    s32 w = v;
    if (v < 0) {
        w += 0x1FF;
    }
    return (w >> 9) & 7;
}

/* Signed angular difference arg0 - arg1, wrapped to [-0x800, 0x800]. */
s32 func_800D3684(s32 arg0, s32 arg1) {
    s32 d = arg0 - arg1;
    s32 a;
    if (d < 0) {
        a = -d;
    } else {
        a = d;
    }
    if (a >= 0x801) {
        d += (d >= 0) ? -0x1000 : 0x1000;
    }
    return d;
}

/* Sum angles arg0 + arg1, wrapped to [-0x800, 0x800]. */
s32 func_800D35B0(s32 arg0, s32 arg1) {
    s32 v = arg0 + arg1;
    s32 t = v;
    v &= 0xFFF;
    if (t & 0x800) {
        v |= 0xFFFFF000;
    }
    return v;
}
