#include "common.h"

extern u8 D_80048288[8];
extern s32 D_80046860[];
extern s16 D_80047062;
extern u8 *D_80046858;
extern s16 D_80047060;

void multiplyMatrix4x4(s32, s32, void *);
void func_8001C0F0(void *, s32, s32, f32);
void initIdentityMatrix4x4(void *);

/* Multiply matrix arg2 by arg1 into the D_80048288 scratch result; arg0 is
 * unused by this wrapper. */
void func_800014AC(s32 arg0, s32 arg1, s32 arg2) {
    multiplyMatrix4x4(arg2, arg1, D_80048288);
}

void initializeTransformNode(void *arg0, u8 arg1, s32 arg2, s32 arg3, f32 arg4) {
    u8 *p = arg0;

    p[0x18] = arg1;
    *(s32 *)(p + 0x0) = 0;
    *(s32 *)(p + 0x4) = 0;
    *(s32 *)(p + 0x8) = 0;
    p[0x19] = 0;
    p[0x1A] = 0;
    *(s32 *)(p + 0xC) = 0;
    *(s32 *)(p + 0x10) = 0;
    *(s32 *)(p + 0x14) = 0;
    func_8001C0F0(p + 0x1C, arg2, arg3, arg4);
    initIdentityMatrix4x4(p + 0x5C);
    initIdentityMatrix4x4(p + 0x9C);
}

void func_80001544(void *arg0) {
    s32 v = *(s32 *)((u8 *)arg0 + 0x14);
    s32 i;

    for (i = 0; i < D_80047062; i++) {
        if (D_80046860[i] == v) {
            return;
        }
    }
    D_80046860[D_80047062] = v;
    D_80047062++;
}

void func_80001694(void) {
    volatile u64 pad;
    u8 *p = D_80046858 + D_80047060 * 0xB8;

    *(s32 *)(p + 0x0) = 0;
    *(s32 *)(p + 0x4) = 0;
    *(s32 *)(p + 0x8) = 0;
    *(s32 *)(p + 0x24) = 0;
    *(s16 *)(p + 0x2C) = 0;
    *(s16 *)(p + 0x2E) = 0;
    *(s32 *)(p + 0x30) = 0;
    *(s32 *)(p + 0x34) = 0;
    D_80047060++;
}
