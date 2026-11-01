/* @header
 * func_800B8050
 * VRAM 0x800B8050 | ROM 0x647C0 | size 0x2C
 * asm: asm/nonmatchings/code_80090000/func_800B8050.s
 */
#include "common.h"

extern s32 D_800DC92C[];
extern s32 D_800D28F4;

void func_800B8050(void) {
    s32 i;
    for (i = 5; i >= 0; i--) {
        D_800DC92C[i - 5] = 0;
    }
    D_800D28F4 = -1;
}
