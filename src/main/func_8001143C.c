#include "common.h"

extern s32 D_8005A3B0[];

s32 func_8001143C(s32 arg0) {
    return D_8005A3B0[arg0 & 3];
}

extern u8 D_80059DA8[];

void func_800112BC(s32 arg0) {
    u8 *p;
    s32 i;

    i = 0;
    if ((u16)arg0) {
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

extern s32 D_80059D90[];

void releaseHeapBlock(s32);

void func_80011264(void) {
    s32 *p;
    u32 i;

    p = D_80059D90;
    i = 0;
    do {
        i++;
        releaseHeapBlock(p[3]);
        releaseHeapBlock(p[4]);
        p[3] = 0;
        p[4] = 0;
        p += 0x37;
    } while (i < 4);
}

extern u8 D_8005AAAD[];
extern u8 D_80036DFC[];
extern u8 D_80036E04[];
extern u8 D_80036E0C[];

s32 func_80011B24(s32 arg0) {
    s32 idx;
    u32 a;
    u32 b;
    u32 c;

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
    return ((a & 0xF8) << 8) | 1 | ((b & 0xF8) << 3) | ((c & 0xF8) >> 2);
}
