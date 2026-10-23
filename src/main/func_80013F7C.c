#include "common.h"

extern s32 D_800604F0;
extern s32 D_800604F4;
extern u32 D_800604C8;
extern u8 *D_800604D0;
s32 func_8001381C(s32);

/* Runs func_8001381C(arg1) with arg0 registered as the pending voice owner
 * (when it is due), then restores the pending owner. */
s32 func_80014020(s32 arg0, s32 arg1) {
    s32 r;

    if (arg0 != 0 && *(s32 *)((u8 *)arg0 + 0x10) < 0) {
        D_800604F0 = arg0;
    }
    r = func_8001381C(arg1);
    D_800604F0 = D_800604F4;
    return r;
}

/* Sets the pan (clamped 0..0x7F) of every voice whose key matches arg0. Returns
 * the number updated. */
s32 func_80013F7C(s32 arg0, s32 arg1) {
    u32 i;
    s32 n;
    u8 *p;

    if (arg0 == 0) {
        return 0;
    }
    if (arg1 < 0) {
        arg1 = 0;
    } else if (arg1 >= 0x80) {
        arg1 = 0x7F;
    }
    n = 0;
    p = D_800604D0;
    for (i = 0; i < D_800604C8; i++) {
        if (*(s32 *)(p + 0x60) == arg0) {
            n++;
            p[0xEB] = arg1;
            p[0xEC] = 0xFF;
        }
        p += 0x158;
    }
    return n;
}

/* Sets the volume (clamped 1..256) of every voice whose key matches arg0,
 * scaling its base level. Returns the number updated. */
s32 func_80013EF0(s32 arg0, s32 arg1) {
    u32 i;
    s32 n;
    u8 *p;

    if (arg0 == 0) {
        return 0;
    }
    if (arg1 <= 0) {
        arg1 = 1;
    } else if (arg1 >= 0x101) {
        arg1 = 0x100;
    }
    n = 0;
    p = D_800604D0;
    for (i = 0; i < D_800604C8; i++) {
        if (*(s32 *)(p + 0x60) == arg0) {
            n++;
            *(s16 *)(p + 0xB8) = arg1;
            *(s16 *)(p + 0xBC) = (*(u16 *)(p + 0xC8) * arg1) >> 7;
        }
        p += 0x158;
    }
    return n;
}

/* Adds arg1 to the pitch of every voice whose key matches arg0. Returns the
 * number updated. */
s32 func_80013E80(s32 arg0, f32 arg1) {
    u32 i;
    s32 n;
    u8 *p;

    if (arg0 == 0) {
        return 0;
    }
    n = 0;
    p = D_800604D0;
    for (i = 0; i < D_800604C8; i++) {
        if (*(s32 *)(p + 0x60) == arg0) {
            n++;
            *(f32 *)(p + 0x44) = arg1 + *(f32 *)(p + 0xAC);
        }
        p += 0x158;
    }
    return n;
}
