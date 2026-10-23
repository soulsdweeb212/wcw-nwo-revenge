#include "common.h"

extern u16 D_800EB4B8[];

void func_800BF254(s32 arg0) {
    D_800EB4B8[(s8)arg0] = 0;
}

void func_800BF26C(u8 *arg0) {
    u64 *flags = (u64 *)(arg0 + 0x20);
    u16 *p;
    u16 v;

    *flags &= ~0x1000000000000000ULL;
    p = &D_800EB4B8[(s8)arg0[0]];
    v = *p - 1;
    *p = v;
    if ((s16)v < 0) {
        D_800EB4B8[(s8)arg0[0]] = 0;
        return;
    }
    *flags |= 0x1000000000000000ULL;
}

void func_800BF228(s32 arg0, s16 arg1, s32 arg2) {
    u8 *p = (u8 *)(arg0 + arg1 + 0x34C);
    u8 v = *p + arg2;

    *p = v;
    if ((s8)v < 0) {
        *p = 0;
    }
}

s8 func_800BF1E0(void *arg0, s16 arg1) {
    s8 v = 0x32;

    if (!(*(u32 *)((u8 *)arg0 + 0x20) & 0) && !(*(u32 *)((u8 *)arg0 + 0x24) & 0x80000)) {
        v = *(s8 *)((u8 *)arg0 + arg1 + 0x34C);
    }
    return v;
}
