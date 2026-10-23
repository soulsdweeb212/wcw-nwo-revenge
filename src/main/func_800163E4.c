#include "common.h"

extern f64 D_8003B3C8;
extern f64 D_8003B3D0;
extern f64 D_8003B3D8;
extern f64 D_8003B3E0;

/* Decode a one-byte release rate into +0xD2/+0xD4. */
u8 *func_800163D0(u8 *arg0, u8 *arg1) {
    u8 v;

    v = *arg1;
    *(s16 *)(arg0 + 0xD2) = 0;
    *(s16 *)(arg0 + 0xD4) = v;
    return arg1 + 1;
}

/* Decode a two-byte (big-endian) release rate into +0xD2. */
u8 *func_800163E4(u8 *arg0, u8 *arg1) {
    u8 hi;
    u8 lo;

    hi = *arg1;
    arg1++;
    lo = *arg1;
    *(s16 *)(arg0 + 0xD4) = 0;
    *(s16 *)(arg0 + 0xD2) = lo | (hi << 8);
    return arg1 + 1;
}

/* Decode envelope rates and compute the +0x34/+0xFC increments. */
u8 *func_80016408(u8 *arg0, u8 *arg1) {
    arg0[0xD6] = *arg1++;
    arg0[0xF5] = *arg1++;
    *(f32 *)(arg0 + 0x34) = (f32)((f32)*arg1 / D_8003B3C8);
    *(f32 *)(arg0 + 0xFC) = (f32)(D_8003B3D0 / (f32)arg0[0xF5]);
    return arg1 + 1;
}

/* As func_80016408, with a negated attack increment. */
u8 *func_80016478(u8 *arg0, u8 *arg1) {
    arg0[0xD6] = *arg1++;
    arg0[0xF5] = *arg1;
    *(f32 *)(arg0 + 0xFC) = (f32)(D_8003B3D8 / (f32)arg0[0xF5]);
    arg1++;
    *(f32 *)(arg0 + 0x34) = (f32)(-(f32)*arg1 / D_8003B3E0);
    return arg1 + 1;
}
