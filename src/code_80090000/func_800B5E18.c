/* @header
 * func_800B5E18
 * VRAM 0x800B5E18 | ROM 0x62588 | size 0x1B8
 * asm: asm/nonmatchings/code_80090000/func_800B5E18.s
 */
#include "common.h"

extern const double D_800D6778, D_800D6780, D_800D6788;

s32 func_800B5E18(s32 x, s32 y) {
    f32 t;
    f32 s;
    f32 r;
    s32 m;
    s32 i, k;

    if (x == 0 && y == 0) {
        return -1;
    }
    if (x == 0) {
        return (y < 1) << 11;
    }
    if (y == 0) {
        return (x >> 31 & 0xC00) | 0x400;
    }
    t = (f64)y / (f64)x;
    if (t > 1.0f) {
        m = 1;
        t = 1.0f / t;
    } else if (t < -1.0f) {
        m = -1;
        t = 1.0f / t;
    } else {
        m = 0;
    }
    s = 0.0f;
    i = 0x14;
    k = 0x29;
    for (; i > 0; i--) {
        s = (f32)(i * i) * t * t / ((f32)k + s);
        k -= 2;
    }
    if (m > 0) {
        r = D_800D6778 - (t / (s + 1.0f));
    } else if (m < 0) {
        r = D_800D6780 - (t / (s + 1.0f));
    } else {
        r = t / (s + 1.0f);
    }
    i = (r * -4096.0f) * D_800D6788;
    if (x < 0) {
        i -= 0x400;
    } else {
        i += 0x400;
    }
    return i & 0xFFF;
}
