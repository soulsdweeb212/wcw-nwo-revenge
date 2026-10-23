#include "common.h"

typedef struct {
    u8 b0, b1, b2, b3, b4, b5, b6, b7;
} Cmd8;

extern Cmd8 D_8006A260[];
extern u8 D_80070A98;
extern u8 D_8007BD30;
extern Cmd8 D_8007DFD0[];
extern s32 D_8007E00C;
extern s32 D_80037600;

s32 func_80027950(void);
s32 func_80026E60(s32, void *, s32);
s32 func_8001CAC0(s32, void *, s32);

/* Decodes D_80070A98 controller response records into the 4-byte status array:
 * writes the error nibble and, for good entries, the two payload bytes, and
 * returns the connected bitmask. */
void func_800213CC(u8 *arg0, s16 *arg1) {
    s16 *d16;
    u8 *d8;
    u8 res;
    s32 i;

    d16 = arg1;
    res = 0;
    i = 0;
    d8 = (u8 *)arg1 + 2;
    for (; i < D_80070A98; i++) {
        Cmd8 t = D_8006A260[i];
        s32 v = (t.b2 & 0xC0) >> 4;
        d8[1] = v;
        if (v == 0) {
            d16[0] = t.b4 | (t.b5 << 8);
            res |= 1 << i;
            d8[0] = t.b6;
        }
        d16 += 2;
        d8 += 4;
    }
    *arg0 = res;
}

/* Builds the read/rumble command buffer D_8007DFD0 from arg0's type byte and a
 * 0xFE terminator. */
void func_8002184C(u8 arg0) {
    Cmd8 t;
    Cmd8 *q;
    s32 i;
    s32 n;

    n = D_80070A98;
    q = D_8007DFD0;
    i = 0;
    D_8007E00C = 1;
    t.b1 = 1;
    D_8007BD30 = arg0;
    t.b0 = 0xFF;
    t.b2 = 3;
    t.b3 = arg0;
    t.b4 = 0xFF;
    t.b5 = 0xFF;
    t.b6 = 0xFF;
    t.b7 = 0xFF;
    if (n > 0) {
        do {
            *q++ = t;
        } while (++i < D_80070A98);
    }
    *(u8 *)q = 0xFE;
}

/* Sends the controller command arg1 (of type arg2, channel arg0) to the
 * controller queue. Returns -1 when the controller system is unavailable. */
s32 func_800219B0(s32 arg0, u8 *arg1, s32 arg2) {
    if (D_80037600 == 0) {
        return -1;
    }
    *(s32 *)(arg1 + 0x14) = arg0;
    if (arg2 == 0) {
        *(s16 *)arg1 = 0xF;
    } else {
        *(s16 *)arg1 = 0x10;
    }
    if (arg1[2] != 1) {
        return func_8001CAC0(func_80027950(), arg1, 0);
    }
    return func_80026E60(func_80027950(), arg1, 0);
}
