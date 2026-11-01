/* @header
 * func_800AA474
 * VRAM 0x800AA474 | ROM 0x56BE4 | size 0x68
 * asm: asm/nonmatchings/code_80090000/func_800AA474.s
 */
#include "common.h"

extern s16 D_800E7CB8;
extern u16 D_800E7B68[];

void func_800AA474(s32 a, s32 b) {
    if (D_800E7CB8 < 0) {
        D_800E7CB8 = 0;
    }
    D_800E7B68[D_800E7CB8++] = a | (b << 8);
    if (D_800E7CB8 >= 0x40) {
        D_800E7CB8 = 0;
    }
}
