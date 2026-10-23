#include "common.h"

/* Advances the running action (D_800FABD0) substate. Substate 0 seeds the
 * direction field from D_800E3CE0[entity+0x3E] when the action id is 4, then
 * moves to substate 1. Substate 1 copies that value into +6 and, while entity
 * D_800FAF58 is in state 1 and source D_800F9B60 is in a hit state with a
 * target within D_800E5298, starts action 1; otherwise any state change resets
 * the action (clearing low flag bits and tracking the source state). */
extern u8 *D_800FABD0, *D_800F9B60, *D_800FAF58;
extern u16 D_800E3CE0[];
extern f64 D_800E5298;
#define A(o,t) (*(t *)(D_800FABD0+(o)))

void func_800B25B4(void) {
    switch (A(4, s16)) {
    case 0:
        if (A(0, s16) == 4) {
            A(0xA, u16) = D_800E3CE0[*(s16 *)(D_800F9B60 + 0x3E)];
        }
        A(6, u16) = A(0xA, u16);
        A(4, s16)++;
        break;
    case 1: {
        u16 dir = A(0xA, u16);
        u8 *entity = D_800FAF58;
        A(6, u16) = dir;
        if (*(s16 *)(entity + 0xA) == 1) {
            if (A(0, s16) == 4) {
                u8 *source = D_800F9B60;
                if (*(s16 *)(source + 0xA) == 10 &&
                    ((u16)(*(u16 *)(source + 0xC) - 3) < 2 || (s16)*(u16 *)(source + 0xC) == 7)) {
                    if ((f64)A(0x48 + *(s16 *)(source + 0x3E) * 4, f32) < D_800E5298) {
                        A(2, s16) = 1;
                        A(4, s16) = 0;
                        A(0x2E, u16) = *(u16 *)(source + 0xA);
                        A(0x5C, u32) &= ~7;
                    }
                } else {
                    u8 *source2 = D_800F9B60;
                    A(2, s16) = 0;
                    A(4, s16) = 0;
                    A(0x2E, u16) = *(u16 *)(source2 + 0xA);
                    A(0x5C, u32) &= ~7;
                }
            }
        } else {
            u8 *source2 = D_800F9B60;
            u16 state;
            A(2, s16) = 0;
            A(4, s16) = 0;
            state = *(u16 *)(source2 + 0xA);
            A(0x5C, u32) &= ~7;
            A(0x2E, u16) = state;
        }
        break;
    }
    }
}
#undef A
