/* @header
 * func_800C858C
 * VRAM 0x800C858C | ROM 0xBBA2C | size 0x13C
 * asm: asm/nonmatchings/code_800BBA00/func_800C858C.s
 */
#include "common.h"

void func_800A9290(void *);
void func_800D427C(void *, s32, s32);
void func_800D4CC4(void *);
void func_800D4AD0(void *);

/* Three-step action machine on self->step:
 *   0: run the enter-action helper, advance to step 1
 *   1: lock the record (flag 0x1000000000); when the opponent's pairSignals bit 0
 *      is set, start animation (opponent animId + 1) with arg 6 and advance to step 2
 *   2: while animFramesLeft is below 3, run the exit helpers, request state
 *      0x2C and reset to step 1. */
void func_800C858C(void) {
    s16 step = D_800FAF5C->step;

    switch (step) {
    case 0:
        func_800A9290(D_800FAF5C);
        D_800FAF5C->step++;
        /* fallthrough */
    case 1:
        D_800FAF5C->flags |= 0x1000000000ULL;
        if (D_800F9B00->pairSignals & 1) {
            func_800D427C(D_800FAF5C, (s16)(D_800F9B00->animId + 1), 6);
            D_800FAF5C->step++;
        }
        break;
    case 2: {
        s32 timerElapsed = D_800FAF5C->animFramesLeft < 3;
        D_800FAF5C->flags |= 0x1000000000ULL;
        if (timerElapsed) {
            func_800D4CC4(D_800FAF5C);
            func_800D4AD0(D_800FAF5C);
            func_800A6C48(D_800FAF5C, 0x2C);
            D_800FAF5C->step = 1;
        }
        break;
    }
    }
}
