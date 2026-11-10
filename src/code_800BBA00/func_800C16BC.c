/* @header
 * func_800C16BC
 * VRAM 0x800C16BC | ROM 0xB4B5C | size 0x11C
 * asm: asm/nonmatchings/code_800BBA00/func_800C16BC.s
 */
#include "common.h"

extern u16 D_800E3CF0[];
extern void *D_800F9B14;
extern f32 D_800F9B0C;
void func_800A7240(void *, void *, s32, u64);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D6658 */
s32 func_800D6658(void *, void *, u16, s32, f32);
#endif
s32 func_800D36E8(f32, f32);
s16 func_800D3614(s32);
void func_800E212C(void *);

/* Two-step facing/approach action on D_800FAF5C: raises the wrestler's
 * 0x1000000000 flag, then step 0 sets dirIndex from the root X/Z position and
 * refreshes the wrestler; step 1 plays animation 0x155 and waits for the
 * approach test, then stores dirIndex from the pelvis position and starts
 * action 0x61. */
void func_800C16BC(void) {
    s32 state;

    D_800FAF5C->flags |= 0x1000000000ULL;
    state = D_800FAF5C->step;
    switch (state) {
    case 0:
        D_800FAF5C->dirIndex = func_800D3614(func_800D36E8(D_800FAF5C->x, D_800FAF5C->z));
        func_800E212C(D_800FAF5C);
        D_800FAF5C->step++;
        return;
    case 1:
        func_800A7240(D_800FAF5C, D_800F9B14, 0x155, 0x100000000ULL);
        if ((u16)func_800D6658(D_800FAF5C, D_800F9B00, D_800E3CF0[D_800FAF5C->dirIndex], 0, D_800F9B0C)) {
            D_800FAF5C->dirIndex = getXZDirectionQuadrant(&D_800FAF5C->jointA[1].x);
            func_800A6C48(D_800FAF5C, 0x61);
        }
        return;
    }
}
