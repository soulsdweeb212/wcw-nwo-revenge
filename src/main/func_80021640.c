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

s32 __osCheckId(s32);
s32 func_80027950(void);
s32 func_80026E60(s32, void *, s32);
s32 func_8001CAC0(s32, void *, s32);

/* Decodes D_80070A98 controller response records into the 4-byte status array:
 * writes the error nibble and, for good entries, the two payload bytes, and
 * returns the connected bitmask. */
void func_800213CC(u8 *arg0, s16 *arg1) {
    Cmd8 *src;
    s16 *d16;
    u8 *d8;
    u8 res;
    s32 i;

    src = D_8006A260;
    d16 = arg1;
    d8 = (u8 *)arg1 + 2;
    res = 0;
    i = 0;
    for (; i < D_80070A98; i++) {
        Cmd8 t = src[i];
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

/* Copies the Pak's stored 32-byte name from arg0 into arg1, returning its
 * length in *arg2 (or 5/2 on bad arguments/id). */
s32 func_80021640(s32 arg0, u8 *arg1, s32 *arg2) {
    s32 i;
    u8 c;

    if (arg1 == NULL) {
        return 5;
    }
    if (__osCheckId(arg0) == 2) {
        return 2;
    }
    for (i = 0; i < 0x20; i++) {
        c = ((u8 *)arg0)[0x2C + i];
        if (c == 0) {
            break;
        }
        *arg1++ = c;
    }
    *arg2 = i;
    return 0;
}

/* Builds the read/rumble command buffer D_8007DFD0 from arg0's type byte and a
 * 0xFE terminator. */
void func_8002184C(u8 arg0) {
    Cmd8 t;
    Cmd8 *q;
    s32 i;

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
    q = D_8007DFD0;
    for (i = 0; i < D_80070A98; i++) {
        *q++ = t;
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
    if (arg1[2] == 1) {
        return func_80026E60(func_80027950(), arg1, 0);
    }
    return func_8001CAC0(func_80027950(), arg1, 0);
}
