#include "common.h"

extern u32 D_800604C8;
extern u8 *D_800604D0;

/* Decode a one-byte envelope flag into +0xD8 and reload the target when set. */
u8 *func_80016198(u8 *arg0, u8 *arg1) {
    u8 c = *arg1++;

    arg0[0xD8] = c;
    if (c != 0) {
        *(f32 *)(arg0 + 0x6C) = *(f32 *)(arg0 + 0x40);
    }
    return arg1;
}

/* Decode a one- or two-byte value into +0xCE. */
void *func_80016168(void *arg0, u8 *arg1) {
    s32 v = *arg1++;

    if (v & 0x80) {
        v = *arg1++ | ((v & 0x7F) << 8);
    }
    *(u16 *)((u8 *)arg0 + 0xCE) = v;
    return arg1;
}

/* Apply (arg1, arg2) to the status word of every voice with key arg0. */
void func_800160E8(s32 arg0, u32 arg1, u32 arg2) {
    u32 count = D_800604C8;
    u8 *p = D_800604D0;
    u32 i = 0;

    if (count != 0) {
        do {
            if (*(s32 *)(p + 0x60) == arg0) {
                *(s32 *)p = (*(s32 *)p & arg1) | arg2;
            }
            i++;
            p += 0x158;
        } while (i < count);
    }
}

/* Add arg1 to each of arg2 nonzero words at arg0. */
void func_80015F2C(s32 *arg0, s32 arg1, u32 arg2) {
    u32 i = 0;

    if (arg2 != 0) {
        do {
            if (*arg0 != 0) {
                *arg0 += arg1;
            }
            i++;
            arg0++;
        } while (i < arg2);
    }
}
