/* @header
 * func_800C17D8
 * VRAM 0x800C17D8 | ROM 0xB4C78 | size 0xFC
 * asm: asm/nonmatchings/code_800BBA00/func_800C17D8.s
 */
#include "common.h"

extern s32 D_800E3C90[];
extern u16 D_800E3CD0[];
extern f32 D_800F9B0C;
void func_800A7240(void *, s32, s32, u64);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D6658 */
s32 func_800D6658(void *, void *, u16, s32, f32);
#endif

/* Two-step quadrant approach action on D_800FAF5C: raises the 0x1000000000
 * flag, then step 0 stores dirIndex from the pelvis position; step 1 plays
 * the quadrant animation and waits for the approach test, then starts action
 * 0x60. */
void func_800C17D8(void) {
    s32 state;

    D_800FAF5C->flags |= 0x1000000000ULL;
    state = D_800FAF5C->step;
    switch (state) {
    case 0:
        D_800FAF5C->dirIndex = getXZDirectionQuadrant(&D_800FAF5C->jointA[1].x);
        D_800FAF5C->step++;
        break;
    case 1:
        func_800A7240(D_800FAF5C, D_800E3C90[D_800FAF5C->dirIndex], 0x155, 0);
        if ((u16)func_800D6658(D_800FAF5C, D_800F9B00, D_800E3CD0[D_800FAF5C->dirIndex], 0, D_800F9B0C)) {
            func_800A6C48(D_800FAF5C, 0x60);
        }
        break;
    }
}
