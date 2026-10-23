#include "common.h"

extern u8 D_80059DA8[];

/* Sets bit 0x80 on the four D_80059DA8 records when arg0 is zero, clears it when
 * arg0 is nonzero. */
void func_800112BC(s32 arg0) {
    s32 i;
    u8 *p;

    i = 0;
    if ((s16)arg0) {
        p = D_80059DA8;
        do {
            i++;
            *p &= 0x7F;
            p += 0xDC;
        } while (i < 4);
    } else {
        p = D_80059DA8;
        do {
            i++;
            *p |= 0x80;
            p += 0xDC;
        } while (i < 4);
    }
}

extern u8 D_80059D90[];

void releaseHeapBlock(s32);

/* Frees the two heap buffers of each of the four D_80059D90 records. */
void func_80011264(void) {
    u8 *p;
    u32 i;

    p = D_80059D90;
    i = 0;
    do {
        i++;
        releaseHeapBlock(*(s32 *)(p + 0xC));
        releaseHeapBlock(*(s32 *)(p + 0x10));
        *(s32 *)(p + 0xC) = 0;
        *(s32 *)(p + 0x10) = 0;
        p += 0xDC;
    } while (i < 4);
}

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
