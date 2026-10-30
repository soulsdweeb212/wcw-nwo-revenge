#include "common.h"

extern u8 asciiCharTable[];
extern u8 D_80038B40[];
extern u8 D_80038DD0[];
extern u8 D_80038DF0[];
extern u8 *D_80064AD0;
extern u8 *D_80064AD4;
extern u8 D_80064AD8;

#define PLOT(dst, x) { \
    s32 c = (x); \
    switch (D_80064AD8) { \
    case 'R': c = (c & 1) ? 0x7 : 0x70; break; \
    case 'G': c = (c & 1) ? 0xB : 0xB0; break; \
    case 'B': c = (c & 1) ? 0xE : 0xE0; break; \
    case 'Y': c = (c & 1) ? 0x8 : 0x80; break; \
    case 'D': c = (c & 1) ? 0x1 : 0x10; break; \
    default: c = (c & 1) ? 0xF : 0xF0; break; \
    } \
    *((dst) + ((x) >> 1)) |= c; }

s32 func_800291C0(u8 *str, u8 *dst, s32 base, s32 pitch, s32 mult, u32 flags)
{
    u8 *tbl;
    s32 i;
    u8 ch;
    s32 off;
    u8 *t2;
    s32 t7, t6, t3, t1, t0;
    u8 *row;
    u32 bits;

    tbl = asciiCharTable;
    ch = *str;
    i = 0;
    if (flags & 0x8000) {
        tbl = D_80038B40;
    }
    do {
        if (*tbl == ch) goto found;
        tbl++;
        i++;
    } while (*tbl != 0);
    i = 0;
found:
    off = i * 2;
    if (off >= 0) {
        t0 = off;
        if (flags & 0x8000) {
            t2 = D_80064AD4 + (i * 16 + off) * 4;
        } else {
            t2 = D_80064AD0 + (i * 32 - t0);
        }
    } else {
        t2 = D_80038DD0;
        if (flags & 0x8000) {
            t2 = D_80038DF0;
        }
    }
    if (t2 == 0) {
        return 4;
    }
    if (flags & 0x8000) {
        if (flags & 0x80) {
            t7 = 0;
            t6 = 0x17;
        } else {
            t7 = t2[0];
            t6 = t2[1];
        }
        t2 += 3;
        for (t3 = 1; t3 < 0x18; t3++, t2 += 3) {
            row = dst + (mult * (pitch + t3)) / 2;
            t1 = t7;
            bits = (t2[0] << 16) + (t2[1] << 8) + t2[2];
            t0 = 0;
            for (; t1 < t6; t1++) {
                if (!(bits & (0x800000 >> t1))) {
                    PLOT(row, base + t0);
                }
                if (flags & 0x10) t0--; else t0++;
            }
        }
    } else {
        if (flags & 0x80) {
            t7 = 1;
            t6 = 0xF;
        } else {
            t7 = t2[1] >> 4;
            t6 = t2[1] & 0xF;
            if (t6 < t7) return 4;
        }
        t2 += 2;
        for (t3 = 0; t3 < 0xE; t3++, t2 += 2) {
            row = dst + (mult * (pitch + t3)) / 2;
            t1 = t7;
            bits = (t2[0] << 8) + t2[1];
            t0 = 0;
            for (; t1 < t6; t1++) {
                if (!(bits & (0x8000 >> t1))) {
                    PLOT(row, base + t0);
                }
                if (flags & 0x10) t0--; else t0++;
            }
        }
    }
    return t6 - t7 + 1;
}
