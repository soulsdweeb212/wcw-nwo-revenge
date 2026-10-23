#include "common.h"

s32 func_800D3890(void *, void *, void *);

/* Quadrant (0..7) of angle arg0. */
s32 func_800D3638(s32 arg0) {
    s32 v = arg0 + 0x1100;
    return (v / 512) & 7;
}

/* Quadrant (0..7) of the heading between arg0 and arg1. */
s32 func_800D3650(void *arg0, void *arg1) {
    s32 buf[4];
    func_800D3890(arg0, arg1, buf);
    return (buf[3] + 0x1100) / 512 & 7;
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
        if (d >= 0) {
            d -= 0x1000;
        } else {
            d += 0x1000;
        }
    }
    return d;
}

/* Sum angles arg0 + arg1, wrapped to [-0x800, 0x800]. */
s32 func_800D35B0(s32 arg0, s32 arg1) {
    s32 v = arg0 + arg1;
    s32 r = v & 0xFFF;
    if (v & 0x800) {
        r |= ~0xFFF;
    }
    return r;
}
