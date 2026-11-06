/* @header
 * func_800BF150
 * VRAM 0x800BF150 | ROM 0xB25F0 | size 0x8C
 * asm: asm/nonmatchings/code_800BBA00/func_800BF150.s
 */
#include "common.h"

s8 func_800D26A0(void *, s32, s8);
s32 func_800D3550(s32);
s32 func_800D3684(s32, s32);
void func_800D3890(void *, void *, void *);

/* Returns 1 when wrestler arg0 faces within 0x400 of the direction from its pelvis to the pelvis of
 * the wrestler func_800D26A0 picks for *arg1. */
s32 func_800BF150(Wrestler *arg0, s8 *arg1) {
    s32 buf[4];
    s8 idx = func_800D26A0(arg0, 0, *arg1);

    if (idx != -1) {
        func_800D3890(&arg0->jointA[1], &D_800F9D10[idx].jointA[1], buf);
        if (func_800D3550(func_800D3684(arg0->heading, buf[3])) < 0x400)
            return 1;
    }
    return 0;
}
