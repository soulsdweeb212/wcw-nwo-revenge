#include "common.h"

extern void *D_8003761C;
extern u8 D_80065128[];
extern u8 D_8006512C;
extern u8 D_8006512D;
extern u8 D_8006512E;
extern u8 D_8006512F;
extern u8 D_80065130;
extern u8 D_80065131;
extern u8 D_80065134;
extern u32 D_80065138;
extern u8 D_80070A98;

s32 nw2DisableInterrupts(void);
void nw2RestoreInterrupts(s32);
void func_80021F60(u8 *, s32);
void *memset(void *, s32, s32);

/* Registers arg0 as the active PI handle and returns the previous one. */
s32 func_80021A50(void **arg0) {
    s32 t;
    void *old;

    t = nw2DisableInterrupts();
    old = D_8003761C;
    D_8003761C = arg0;
    *arg0 = old;
    nw2RestoreInterrupts(t);
    return 0;
}

/* Lazily initializes the PI handle at D_80065128, registers it and returns it. */
void *func_80021B80(void) {
    u8 *p = &D_80065134;
    s32 t;
    void *old;

    if (*(u32 *)p != 0xA6000000) {
        D_8006512C = 1;
        *(u32 *)p = 0xA6000000;
        D_8006512D = 0x40;
        D_80065130 = 7;
        D_8006512E = 7;
        D_8006512F = 2;
        D_80065131 = 0;
        D_80065138 = 0;
        func_80021F60(p + 8, 0x60);
        t = nw2DisableInterrupts();
        old = D_8003761C;
        D_8003761C = p - 0xC;
        *(void **)(p - 0xC) = old;
        nw2RestoreInterrupts(t);
    }
    return D_80065128;
}

/* Clears arg1 bytes at arg0. */
void func_80021F60(u8 *arg0, s32 arg1) {
    memset(arg0, 0, arg1);
}

typedef struct {
    u8 b0, b1, b2, b3, b4, b5, b6, b7;
} Cmd8;
extern Cmd8 D_8006A260[];

/* Decodes D_80070A98 controller response records into the 4-byte status array:
 * writes the error nibble and, for good entries, the two payload bytes, and
 * returns the connected bitmask. */
void func_800213CC(u8 *arg0, s16 *arg1) {
    s16 *d16;
    u8 *d8;
    Cmd8 *src;
    u8 res;
    s32 i;

    d16 = arg1;
    res = 0;
    src = D_8006A260;
    i = 0;
    d8 = (u8 *)arg1 + 2;
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
