#include "common.h"

extern u8 D_800F9D30[];

/* Returns 1 when entity arg0's 64-bit flag word has the 0x40000 bit. */
s32 func_800BFC90(s8 arg0) {
    s32 off = arg0 * 0x3B0;
    if (*(u64 *)(D_800F9D30 + off) & 0x40000ULL)
        return 1;
    return 0;
}

s8 func_800D26A0(void *, s32, s8);
s32 func_800D3550(s32);
s32 func_800D3684(s32, s32);
void func_800D3890(void *, void *, void *);
extern u8 D_800F9D7C[];
