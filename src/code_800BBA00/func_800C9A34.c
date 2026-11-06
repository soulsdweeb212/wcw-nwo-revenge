/* @header
 * func_800C9A34
 * VRAM 0x800C9A34 | ROM 0xBCED4 | size 0x8C
 * asm: asm/nonmatchings/code_800BBA00/func_800C9A34.s
 */
#include "common.h"

s32 func_800A7328(void *);
void beginEntityActionA8D8C(void *);
void func_800D427C(void *, s32, s32);
void func_800D4AD0(void *);

/* Two-step action on self (D_800FAF5C, step): step 0 plays animation 0xF05 and
 * advances; step 1, once animFramesLeft reaches 1, tears the action down and
 * restarts the wrestler's action. */
void func_800C9A34(void) {
    s16 temp_v1;

    temp_v1 = D_800FAF5C->step;
    switch (temp_v1) {
    case 0:
        func_800A7328(D_800FAF5C);
        func_800D427C(D_800FAF5C, 0xF05, 2);
        D_800FAF5C->step++;
        return;
    case 1:
        if (D_800FAF5C->animFramesLeft == temp_v1) {
            func_800D4AD0(D_800FAF5C);
            beginEntityActionA8D8C(D_800FAF5C);
        }
        return;
    }
}
