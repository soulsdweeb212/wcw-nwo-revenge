/* @header
 * func_800B25B4
 * VRAM 0x800B25B4 | ROM 0xA5A54 | size 0x18C
 * asm: asm/nonmatchings/code_8009D7A0/func_800B25B4.s
 */
#include "common.h"

/* Advances the running action (D_800FABD0) substate. Substate 0 seeds the
 * direction field from D_800E3CE0[D_800F9B60->dirIndex] when the action id is 4, then
 * moves to substate 1. Substate 1 copies that value into +6 and, while entity
 * D_800FAF58 is in state 1 and source D_800F9B60 is in state 10 (step 3, 4 or 7) with a
 * target within D_800E5298, starts action 1; otherwise any state change resets
 * the action (clearing low flag bits and tracking the source state). */
extern u8 *D_800FABD0;
extern u16 D_800E3CE0[];
extern f64 D_800E5298;
#define A(o,t) (*(t *)(D_800FABD0+(o)))

void func_800B25B4(void) {
    switch (A(4, s16)) {
    case 0:
        if (A(0, s16) == 4) {
            A(0xA, u16) = D_800E3CE0[D_800F9B60->dirIndex];
        }
        A(6, u16) = A(0xA, u16);
        A(4, s16)++;
        break;
    case 1: {
        u16 dir = A(0xA, u16);
        Wrestler *entity = D_800FAF58;
        A(6, u16) = dir;
        if (entity->state == 1) {
            if (A(0, s16) == 4) {
                Wrestler *source = D_800F9B60;
                if (source->state == 10 &&
                    ((u16)((u16)source->step - 3) < 2 || source->step == 7)) {
                    if ((f64)A(0x48 + source->dirIndex * 4, f32) < D_800E5298) {
                        A(2, s16) = 1;
                        A(4, s16) = 0;
                        A(0x2E, u16) = (u16)source->state;
                        A(0x5C, u32) &= ~7;
                    }
                } else {
                    Wrestler *source2 = D_800F9B60;
                    A(2, s16) = 0;
                    A(4, s16) = 0;
                    A(0x2E, u16) = (u16)source2->state;
                    A(0x5C, u32) &= ~7;
                }
            }
        } else {
            Wrestler *source2 = D_800F9B60;
            u16 state;
            A(2, s16) = 0;
            A(4, s16) = 0;
            state = (u16)source2->state;
            A(0x5C, u32) &= ~7;
            A(0x2E, u16) = state;
        }
        break;
    }
    }
}
#undef A
