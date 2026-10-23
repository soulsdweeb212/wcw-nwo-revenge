#include "common.h"

extern s32 D_800389A0;
extern u8 D_80064AC0[];
extern u8 D_80073E98[];
extern u8 D_80070A98;

extern s32 D_80037248;
extern void *D_80037250;

s32 func_8001C890(void *, void *, s32);
s32 func_8001C990(void *, void *, s32);
s32 func_8001CAC0(void *, s32, s32);
s32 nw2DisableInterrupts(void);
void func_800265AC(s32 *, s32);
void nw2RestoreInterrupts(s32);

/* Lazily initialize the two message queues, then block waiting on the audio queue. */
void func_80027F54(void) {
    s32 msg;

    if (D_800389A0 == 0) {
        D_800389A0 = 1;
        func_8001C890(D_80064AC0 + 0xF3D8, D_80064AC0, 1);
        func_8001CAC0(D_80073E98, 0, 0);
    }
    func_8001C990((u8 *)&D_80070A98 + 0x3400, &msg, 1);
}

/* Mark the current thread stopped (state 2) and enqueue it on the runnable list. */
void func_800281A0(void) {
    s32 s;
    s32 v;

    s = nw2DisableInterrupts();
    v = 2;
    *(s16 *)((u8 *)D_80037250 + 0x10) = v;
    func_800265AC(&D_80037248, v);
    nw2RestoreInterrupts(s);
}

/* Report whether the PI is busy. */
s32 func_800281F0(void) {
    return (*(volatile u32 *)0xA4800018 & 3) != 0;
}

/* 64-bit multiply-accumulate: (arg0*arg2) + (arg1*arg3), returning the low word of
 * the sum plus the high word of the product. */
u32 func_800284F4(u32 arg0, u32 arg1, u32 arg2, u32 arg3) {
    u32 t;
    u64 p;

    t = arg1 * arg2 + arg0 * arg3;
    p = (u64)arg0 * (u64)arg2;
    return t + (u32)(p >> 32);
}
