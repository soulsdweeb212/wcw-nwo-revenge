/* @header
 * func_800B1BB8
 * VRAM 0x800B1BB8 | ROM 0xA5058 | size 0x84
 * asm: asm/nonmatchings/code_8009D7A0/func_800B1BB8.s
 */
#include "common.h"

extern u8 *D_800FABD0;
s8 func_800B4C60(void *, void *, s32, s32);
s8 func_800B5DC4(void *, s32);
/* Two-state helper (state +4): state 0 sets the count word to 2 and advances;
 * state 1 resets the action unless the AI wrestler is in state 0x30. */
void func_800B1BB8(void) {
    u8 *o = D_800FABD0;
    switch (*(s16 *)(o + 4)) {
    case 0:
        *(s16 *)(o + 6) = 2;
        (*(s16 *)(o + 4))++;
        break;
    case 1:
        if (D_800FAF58->state != 0x30) {
            Wrestler *g = D_800F9B60;
            *(s16 *)(o + 2) = 0;
            *(s16 *)(o + 4) = 0;
            *(u16 *)(o + 0x2E) = (u16)g->state;
            *(u32 *)(o + 0x5C) &= ~7;
        }
        break;
    }
}
