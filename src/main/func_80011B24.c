#include "common.h"

extern u8 D_80059DA8[];

extern u8 D_80059D90[];

void releaseHeapBlock(s32);

extern u8 D_8005AAAD[];
extern u8 D_80036DFC[];
extern u8 D_80036E04[];
extern u8 D_80036E0C[];

/* Builds a 16-bit RGBA5551 colour for vertex arg0: looks up its palette index
 * (clamped at 5) and scales the three channel tables, always setting the
 * visibility bit. */
s32 func_80011B24(s32 arg0) {
    s32 idx;
    u32 a;
    u32 b;
    u32 c;
    u32 r;

    idx = D_8005AAAD[((s16)arg0) << 4];
    if (idx == 6) {
        idx = 5;
    }
    a = D_80036DFC[idx] >> 1;
    if (a != 0) {
        a += 0x40;
    }
    b = D_80036E04[idx] >> 1;
    if (b != 0) {
        b += 0x40;
    }
    c = D_80036E0C[idx] >> 1;
    if (c != 0) {
        c += 0x40;
    }
    r = (a & 0xF8) << 8;
    r |= 1;
    r |= (b & 0xF8) << 3;
    r |= (c & 0xF8) >> 2;
    return r;
}
