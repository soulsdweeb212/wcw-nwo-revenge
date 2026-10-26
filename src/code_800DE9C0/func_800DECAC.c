#include "common.h"

extern u16 D_800F98D0[];
extern s16 D_800F9D12[4][0x1D8];
extern s16 D_800F9D1A[4][0x1D8];
extern s16 D_800F9D4E[4][0x1D8];
s32 func_800D65D0(void *, s32);
s32 func_800DEEE8(void *, s32);

static s32 func_800DECAC_impl(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 id = *(u8 *)arg0;
    s32 s3 = (s16)arg3;
    u16 a2 = arg2;
    s32 s7;
    s16 i;
    s16 a2v;

    if (s3 == 0) {
        D_800F98D0[(s8)id] = 0;
        return 0;
    }
    if (s3 != 1) return 0;
    if (!(*(u64 *)((u8 *)arg0 + 0x20) & 0x80)) return 0;
    s7 = func_800D65D0(arg0, a2);
    if ((s16)s7 == 0) goto clear;
    if (((arg1 & arg2) & 0xFFFF) == 0) goto clear;
    if ((s8)func_800DEEE8(arg0, a2) == 0) return 0;
    if ((s16)++D_800F98D0[(s8)id] < 13) return 0;
    a2v = *(u16 *)((u8 *)arg0 + 0x3C);
    if ((s16)s7 == s3) a2v = (a2v - 1) & 3;
    for (i = 0; i < 4; i++) {
        if (D_800F9D12[i][0] != -1 && D_800F9D1A[i][0] == 2 && D_800F9D4E[i][0] == a2v) break;
    }
    if (i != 4) return 0;
    *(u64 *)((u8 *)arg0 + 0x20) &= ~0x8000000000ULL;
    if ((s16)s7 == 1) *(u64 *)((u8 *)arg0 + 0x20) |= 0x8000000000ULL;
    *(u16 *)((u8 *)arg0 + 0x3E) = a2v;
    func_800A6C48(arg0, 2);
    return 1;
clear:
    D_800F98D0[(s8)id] = 0;
    return 0;
}

void func_800DECAC(void *, s32, s32, s32) __attribute__((alias("func_800DECAC_impl")));
