/* @header
 * func_800B3A08
 * VRAM 0x800B3A08 | ROM 0xA6EA8 | size 0xD0
 * asm: asm/nonmatchings/code_8009D7A0/func_800B3A08.s
 */
#include "common.h"

extern u8 *D_800FABD0;
extern u8 *D_800F9B60;
extern u8 *D_800FAF58;
s8 func_800D4198(s16);

void func_800B3A08(void) {
    switch (*(s16 *)(D_800FABD0 + 4)) {
    case 0:
        if (func_800D4198(0x1F4)) {
            *(u16 *)(D_800FABD0 + 0xA) = 0x8000;
        } else {
            *(u16 *)(D_800FABD0 + 0xA) = 0x4000;
        }
        (*(s16 *)(D_800FABD0 + 4))++;
        break;
    case 1:
        if (*(s16 *)(D_800FAF58 + 0xA) == 0x5E) {
            *(u16 *)(D_800FABD0 + 6) = *(u16 *)(D_800FABD0 + 0xA);
        } else {
            u8 *g = D_800F9B60;
            *(s16 *)(D_800FABD0 + 2) = 0;
            *(s16 *)(D_800FABD0 + 4) = 0;
            *(u16 *)(D_800FABD0 + 0x2E) = *(u16 *)(g + 0xA);
            *(u32 *)(D_800FABD0 + 0x5C) &= ~7;
        }
        break;
    }
}
