/* @header
 * func_800A8FE4
 * VRAM 0x800A8FE4 | ROM 0x55754 | size 0x2C
 * asm: asm/nonmatchings/code_80090000/func_800A8FE4.s
 */
#include "common.h"

extern s32 D_80038AA8;
extern u8 D_8007EF30[];

void func_800A8FE4(void) {
    s32 i;
    D_80038AA8 = 0;
    for (i = 0x27; i >= 0; i--) {
        ((u16 *)(D_8007EF30 + 0xC90))[i] = 0;
    }
}
