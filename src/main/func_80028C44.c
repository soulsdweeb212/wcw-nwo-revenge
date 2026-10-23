#include "common.h"

u64 func_80028624(u32, u32, u32, u32);
u64 func_80028528(u32, u32, u32, u32);

extern u8 asciiCharTable[];
extern u8 sjisCodeTable[];

/* 64-bit helper: with arg2==0 forwards to func_80028624 and returns arg3, else
 * forwards to func_80028528 and returns arg0:arg1 packed. */
u64 func_80028880(u32 arg0, u32 arg1, u32 arg2, u32 arg3) {
    if (arg2 == 0) {
        func_80028624(arg0, arg1, arg2, arg3);
        return arg3;
    }
    func_80028528(arg0, arg1, arg2, arg3);
    return ((u64)arg0 << 32) | arg1;
}

/* Converts up to arg2 (max 255) ASCII characters from arg1 into their two-byte
 * Shift-JIS codes at arg0, NUL-terminating the result. Returns the end cursor. */
u8 *func_80028AB0(u8 *arg0, u8 *arg1, s32 arg2) {
    s32 i;
    s32 k;
    u8 *p;
    u8 c;

    arg2 &= 0xFF;
    i = 0;
    if (arg2 > 0) {
        do {
            c = *arg1;
            p = asciiCharTable;
            k = 0;
            while (*p != c) {
                p++;
                k++;
                if (*p == 0) {
                    k = 0;
                    break;
                }
            }
            arg0[0] = sjisCodeTable[k * 2];
            arg0[1] = sjisCodeTable[k * 2 + 1];
            arg1++;
            arg0 += 2;
            i++;
        } while (*arg1 != 0 && i < arg2);
    }
    *arg0 = 0;
    return arg0;
}

/* Copies arg1 to arg0 while outside {} braces (brace contents are dropped).
 * Returns the end cursor. */
u8 *func_80028C44(u8 *arg0, u8 *arg1) {
    s32 f;
    u8 c;

    f = 1;
    c = *arg1;
    if (c != 0) {
        do {
            switch (c) {
            case 0x3C:
                break;
            case 0x3E:
                break;
            case 0x7B:
                f = 0;
                break;
            case 0x7D:
                f = 1;
                break;
            default:
                if (f != 0) {
                    *arg0 = *arg1;
                    arg0++;
                }
                break;
            }
            arg1++;
            c = *arg1;
        } while (c != 0);
    }
    return arg0;
}

/* Writes arg1 as a run-length encoding of '#'+digit pairs into arg0, NUL-
 * terminating; returns the end cursor. */
u8 *func_80028CC0(u8 *arg0, s32 arg1) {
    u8 *p;
    u8 *q;
    s32 d;

    q = arg0;
    p = arg0 + 1;
    if (arg1 > 0) {
        do {
            d = arg1;
            if (d >= 0x23) {
                d = 0x23;
            }
            *q = 0x23;
            if (d < 0xA) {
                *p = d + 0x30;
            } else {
                *p = d + 0x37;
            }
            p += 2;
            arg1 -= d;
            q += 2;
        } while (arg1 > 0);
    }
    *q = 0;
    return q;
}
