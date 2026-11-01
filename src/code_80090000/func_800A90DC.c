/* @header
 * func_800A90DC
 * VRAM 0x800A90DC | ROM 0x5584C | size 0x2C
 * asm: asm/nonmatchings/code_80090000/func_800A90DC.s
 */
#include "common.h"

void func_800A90DC(u8 *a) {
    a[0] = 0xFF;
    a[1] = a[2] = a[3] = a[4] = a[5] = 0x32;
    a[6] = a[7] = 0;
}
