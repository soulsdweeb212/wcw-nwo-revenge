#include "common.h"

extern u8 *D_800FABD0;
extern u8 *D_800F9B60;

/* Three-state action handler on D_800FABD0 (state +4). State 0 either sets the
 * count word to 4 (when the entity is in state 0x14) or resets the action, then
 * advances. State 1 advances again unless +0x14 is 2. State 2, when the entity
 * is in state 0x14 and +0x14 is 1, resets the action to substate 2; otherwise it
 * resets fully. */
void func_800AFDAC(void) {
    u8 *p = D_800FABD0;
    u8 *g;
    s16 state = *(s16 *)(p + 4);

    switch (state) {
    case 0:
        g = D_800F9B60;
        if (*(s16 *)(g + 0xA) == 0x14) {
            *(s16 *)(p + 6) = 4;
        } else {
            *(s16 *)(p + 2) = 0;
            *(s16 *)(p + 4) = 0;
            *(u16 *)(p + 0x2E) = *(u16 *)(g + 0xA);
            *(u32 *)(p + 0x5C) &= ~7;
        }
        (*(s16 *)(D_800FABD0 + 4))++;
        break;
    case 1:
        if (*(s16 *)(p + 0x14) != 2) {
            *(s16 *)(p + 4) = state + 1;
        }
        break;
    case 2:
        g = D_800F9B60;
        if (*(s16 *)(g + 0xA) == 0x14) {
            if (*(s16 *)(p + 0x14) == 1) {
                *(s16 *)(p + 2) = 2;
                *(s16 *)(p + 4) = 0;
                *(u16 *)(p + 0x2E) = *(u16 *)(g + 0xA);
                *(u32 *)(p + 0x5C) &= ~7;
            }
        } else {
            *(s16 *)(p + 2) = 0;
            *(s16 *)(p + 4) = 0;
            *(u16 *)(p + 0x2E) = *(u16 *)(g + 0xA);
            *(u32 *)(p + 0x5C) &= ~7;
        }
        break;
    }
}
