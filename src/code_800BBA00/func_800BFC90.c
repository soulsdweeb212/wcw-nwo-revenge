/* @header
 * func_800BFC90
 * VRAM 0x800BFC90 | ROM 0xB3130 | size 0x60
 * asm: asm/nonmatchings/code_800BBA00/func_800BFC90.s
 */
#include "common.h"

/* Returns 1 when wrestler arg0's spirit is full (WR_FLAG_SPIRIT_FULL). */
s32 func_800BFC90(s8 arg0) {
    if (D_800F9D10[arg0].flags & WR_FLAG_SPIRIT_FULL)
        return 1;
    return 0;
}

s8 func_800D26A0(void *, s32, s8);
s32 func_800D3550(s32);
s32 func_800D3684(s32, s32);
void func_800D3890(void *, void *, void *);
