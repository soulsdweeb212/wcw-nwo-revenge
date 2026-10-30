/* @header
 * advanceTimeoutAction  (originally func_800B2354)
 * VRAM 0x800B2354 | ROM 0xA57F4 | size 0xD8
 * asm: asm/nonmatchings/code_8009D7A0/func_800B2354.s
 */
#include "common.h"

extern u8 *D_800FABD0;
extern u8 *D_800F9B60;

void advanceTimeoutAction(void) {
    u8 *o = D_800FABD0;
    u16 c;
    switch (*(s16 *)(o + 4)) {
    case 0:
        *(s16 *)(o + 0xE) = 0x96;
        (*(s16 *)(o + 4))++;
        break;
    case 1:
        if (*(s16 *)(o + 0x14) != 1 || *(s16 *)(o + 0x2E) != *(s16 *)(D_800F9B60 + 0xA)) {
            u8 *g = D_800F9B60;
            *(s16 *)(o + 2) = 0;
            *(s16 *)(o + 4) = 0;
            *(u16 *)(o + 0x2E) = *(u16 *)(g + 0xA);
            *(u32 *)(o + 0x5C) &= ~7;
        }
        o = D_800FABD0;
        c = *(u16 *)(o + 0xE) - 1;
        *(u16 *)(o + 0xE) = c;
        if ((s16)c < 0) {
            u8 *g = D_800F9B60;
            *(s16 *)(o + 2) = 0;
            *(s16 *)(o + 4) = 0;
            *(u16 *)(o + 0x2E) = *(u16 *)(g + 0xA);
            *(u32 *)(o + 0x5C) &= ~7;
        }
        break;
    }
}
