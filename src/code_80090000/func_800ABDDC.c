/* @header
 * func_800ABDDC
 * VRAM 0x800ABDDC | ROM 0x5854C | size 0x84
 * asm: asm/nonmatchings/code_80090000/func_800ABDDC.s
 */
#include "common.h"

extern s16 D_80038A90;
extern u8 D_8007EF30[];
extern s32 D_800E6B88;

s32 func_800ABDDC(void) {
    s32 r = 0;
    switch (D_80038A90) {
    case 0xF:
    case 0x17:
        r = 5;
        break;
    case 0xD:
    case 0xE:
        r = D_8007EF30[(*(s32 *)(D_8007EF30 + 0xD00) << 4) + 0x51];
        r -= r != 0;
        break;
    }
    if (D_800E6B88 != r) {
        D_800E6B88 = r;
    }
    return r;
}
