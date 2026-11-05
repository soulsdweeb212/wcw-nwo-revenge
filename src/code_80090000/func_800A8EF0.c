/* @header
 * func_800A8EF0
 * VRAM 0x800A8EF0 | ROM 0x55660 | size 0x70
 * asm: asm/nonmatchings/code_80090000/func_800A8EF0.s
 */
#include "common.h"

extern u8 D_800CCA10[], D_8007EF30[];
void func_800BA59C(s32);
void bcopy(void *, void *, s32);

void func_800A8EF0(s32 a) {
    if (a == 7) {
        func_800BA59C(0);
    } else if (a == 8) {
        func_800BA59C(1);
    } else {
        bcopy(D_800CCA10 + a * 12, D_8007EF30 + 0x1A0, 0xB);
    }
}
