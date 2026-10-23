#include "common.h"

void func_800015AC(void *, s8);
f32 func_80003CF0(f32);
extern f64 D_8003B1C0;

/* Initializes the object from descriptor arg3 (0x2C-byte records at arg1): sets
 * its link/callback fields and clears the sub-record's first word. */
void func_80007818(u8 *arg0, u8 *arg1, s32 arg2, s16 arg3) {
    s32 off = arg3 * 0x2C;
    u8 *t = arg1 + off;
    s32 v = *(s32 *)(t + 0xC);

    *(s32 *)(arg0 + 0x10) = arg2;
    *(s32 *)(arg0 + 0xC) = v;
    func_800015AC(arg0, t[2]);
    *(s32 *)(*(s32 **)(arg0 + 0x14)) = 0;
}

/* Initializes the object and its sub-record from descriptor arg3, copying the
 * packed descriptor bytes into the sub-record's size/offset fields. */
void func_80007874(u8 *arg0, u8 *arg1, s32 arg2, s16 arg3) {
    s32 off = arg3 * 0x2C;
    u8 *t = arg1 + off;
    s32 *p;
    s32 v;

    arg0[0x1A] = t[6];
    *(s32 *)(arg0 + 0xC) = *(s32 *)(t + 0xC);
    func_800015AC(arg0, t[2]);
    p = *(s32 **)(arg0 + 0x14);
    p[0] = 1;
    p[0xC] = 0;
    p[0xD] = 0;
    *(s16 *)((u8 *)p + 0x2C) = (s8)t[2];
    *(s16 *)((u8 *)p + 0x2E) = (s8)t[3];
    v = *(s32 *)(t + 0xC);
    *(s32 *)((u8 *)p + 0x34) = arg2;
    *(s32 *)((u8 *)p + 0x30) = v;
}

/* Packs 16 palette entries: each u16 is shifted by the mode (1: >>3, 0: >>8,
 * default: <<2), masked to 5 bits and given the 0xFF00 alpha. */
void func_80007960(u16 *arg0, s32 arg1) {
    s32 mode = arg1 & 0xFF;
    u32 i;
    u32 v;

    i = 0;
    do {
        switch (mode) {
        case 0:
            v = *arg0 >> 8;
            break;
        case 1:
            v = *arg0 >> 3;
            break;
        default:
            v = *arg0 << 2;
            break;
        }
        v &= 0xF8;
        if ((u16)v != 0) {
            v += 7;
        }
        *arg0 = v | 0xFF00;
        i++;
        arg0++;
    } while (i < 16);
}

/* Returns 1 when both x and y are below the D_8003B1C0 limit. */
s32 func_8000CF64(f32 x, f32 y) {
    f64 lim = D_8003B1C0;

    if (func_80003CF0(x) < lim) {
        if (func_80003CF0(y) < lim) {
            return 1;
        }
    }
    return 0;
}
