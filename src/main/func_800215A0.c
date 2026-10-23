#include "common.h"

extern u8 D_80070A98;
extern u8 D_8007BD30;
extern s32 D_8006A298;
extern s32 D_8006A29C;

typedef struct {
    u8 b0, b1, b2, b3, b4, b5, b6, b7;
} Cmd8;
extern Cmd8 D_8006A260[];

extern void func_80027744(void);
extern void func_800277B0(void);
extern s32 func_80024640(s32, s32);
extern s32 readControllerPakId(void *);
extern s32 osPfsChecker(void *);

/* Decodes D_80070A98 controller response records into the 4-byte status array:
 * writes the error nibble and, for good entries, the two payload bytes, and
 * returns the connected bitmask. */
void func_800213CC(u8 *arg0, s16 *arg1) {
    u8 res;
    s32 i;
    s16 *d16;
    u8 *d8;
    Cmd8 *src;

    res = 0;
    d16 = arg1;
    src = D_8006A260;
    d8 = (u8 *)arg1 + 2;
    i = 0;
    for (; i < D_80070A98; i++) {
        Cmd8 t = src[i];
        s32 v = (t.b2 & 0xC0) >> 4;
        d8[1] = v;
        if (v != 0) {
            d16[0] = t.b4 | (t.b5 << 8);
            res |= 1 << i;
            d8[0] = t.b6;
        }
        d16 += 2;
        d8 += 4;
    }
    *arg0 = res;
}

/* Clears the 15 command words, then fills the D_8006A260 command buffer with
 * arg0's type record and a 0xFE terminator. */
void func_80021480(s32 arg0) {
    s32 i;
    s32 *p;
    u8 *flag;
    Cmd8 *q;
    Cmd8 tmp;

    for (i = 0xE, p = &D_8006A298; i >= 0; i--) {
        *p = 0;
        p--;
    }
    flag = (u8 *)&D_8006A29C;
    q = (Cmd8 *)(flag - 0x3C);
    tmp.b0 = 0xFF;
    tmp.b1 = 1;
    tmp.b2 = 3;
    tmp.b3 = arg0;
    tmp.b4 = 0xFF;
    tmp.b5 = 0xFF;
    tmp.b6 = 0xFF;
    tmp.b7 = 0xFF;
    *(s32 *)flag = 1;
    for (i = 0; i < D_80070A98; i++) {
        *q++ = tmp;
    }
    *(u8 *)q = 0xFE;
}

/* Sets the active controller count (clamped to 4) and re-arms the Pak status. */
s32 func_80021540(s32 arg0) {
    func_80027744();
    if ((u8)arg0 >= 5) {
        D_80070A98 = 4;
    } else {
        D_80070A98 = (u8)arg0;
    }
    D_8007BD30 = 0xFE;
    func_800277B0();
    return 0;
}

/* Initializes a Controller Pak handle arg1 for channel arg0: records the channel
 * and query id, reads the Pak id and runs the file-system checker. Returns the
 * first error encountered. */
s32 func_800215A0(s32 arg0, u8 *arg1, s32 arg2) {
    s32 ret;

    func_80027744();
    ret = func_80024640(arg0, arg2);
    func_800277B0();
    if (ret != 0) {
        return ret;
    }
    *(s32 *)(arg1 + 4) = arg0;
    *(s32 *)(arg1 + 8) = arg2;
    *(s32 *)(arg1 + 0) = 0;
    arg1[0x65] = 0xFF;
    ret = readControllerPakId(arg1);
    if (ret != 0) {
        return ret;
    }
    ret = osPfsChecker(arg1);
    *(s32 *)arg1 |= 1;
    return ret;
}
