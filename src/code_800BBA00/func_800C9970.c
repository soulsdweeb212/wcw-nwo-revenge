/* @header
 * func_800C9970
 * VRAM 0x800C9970 | ROM 0xBCE10 | size 0xC4
 * asm: asm/nonmatchings/code_800BBA00/func_800C9970.s
 */
#include "common.h"

s32 func_800A7188(void *);
void func_800D427C(void *, s32, s32);
void func_800D7E80(void *, void *);
void func_800D8D74(void *, s32);

/* Two-step action state machine for self (D_800FAF5C): step 0 plays animation 0xF04,
 * calls func_800D7E80 with the opponent (D_800F9B00) and advances the step (falling through
 * into case 1); step 1 drives func_800D8D74 and, once func_800A7188 reports completion,
 * resets attached[0] to -1 and clears flag 0x40000000 (pair leader). */
void func_800C9970(void) {
    s16 step;
    Wrestler *e;

    step = D_800FAF5C->step;
    switch (step) {
    case 0:
        func_800D427C(D_800FAF5C, 0xF04, 2);
        func_800D7E80(D_800FAF5C, D_800F9B00);
        D_800FAF5C->step++;
        /* fallthrough */
    case 1:
        func_800D8D74(D_800FAF5C, 0);
        if (func_800A7188(D_800FAF5C) << 24) {
            e = D_800FAF5C;
            e->attached[0] = -1;
            e->flags &= ~0x40000000;
        }
        break;
    }
}
