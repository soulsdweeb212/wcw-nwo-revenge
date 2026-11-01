/* @header
 * func_800AE0C0
 * VRAM 0x800AE0C0 | ROM 0x5A830 | size 0x64
 * asm: asm/nonmatchings/code_80090000/func_800AE0C0.s
 */
#include "common.h"

extern u8 D_8007EF30[];

s32 func_800AE0C0(void) {
    if (D_8007EF30[0x1A0] == 5 && D_8007EF30[0x1A2] == 1 && D_8007EF30[0x1A3] == 1 && D_8007EF30[0x1A4] == 1) {
        if (D_8007EF30[0x1A1] == 2 || D_8007EF30[0x1A1] == 3) {
            return -1;
        }
    }
    return 0;
}
