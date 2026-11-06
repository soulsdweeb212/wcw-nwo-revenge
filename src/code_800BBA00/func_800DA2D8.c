/* @header
 * func_800DA2D8
 * VRAM 0x800DA2D8 | ROM 0xCD778 | size 0x100
 * asm: asm/nonmatchings/code_800BBA00/func_800DA2D8.s
 */
#include "common.h"

void func_800D427C(void *, s32, s32);
void func_800D7E80(void *, void *);
void func_800E212C(void *);
void func_800D8D74(void *, s32);
void func_800D4AD0(void *);

/* Action sequence on D_800FAF5C (switch on step). Steps 0 and 2 play animation
 * 0x108A, attach to the partner's record (D_800F9D10[partnerId]) and attach the
 * entity, advancing the step. Steps 1 and 3 drive the attach and, once
 * animFramesLeft expires, complete the action and issue command 0x2B. */
void func_800DA2D8(void) {
    switch (D_800FAF5C->step) {
    case 0: case 2:
        func_800D427C(D_800FAF5C, 0x108A, 2);
        func_800D7E80(D_800FAF5C, &D_800F9D10[D_800FAF5C->partnerId]);
        func_800E212C(D_800FAF5C);
        D_800FAF5C->step++;
        break;
    case 1: case 3:
        func_800D8D74(D_800FAF5C, 0);
        if (D_800FAF5C->animFramesLeft <= 0) {
            func_800D4AD0(D_800FAF5C);
            func_800A6C48(D_800FAF5C, 0x2B);
        }
        break;
    }
}
