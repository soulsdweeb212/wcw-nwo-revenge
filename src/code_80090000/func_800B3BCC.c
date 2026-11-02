/* @header
 * func_800B3BCC
 * VRAM 0x800B3BCC | ROM 0x6033C | size 0x18C
 * asm: asm/nonmatchings/code_80090000/func_800B3BCC.s
 */
#include "common.h"

extern u8 D_800E7C60[][8];
extern s32 D_800E7BF0[];
extern s32 D_800E79A0[];

void func_800B3BCC(s32 i, s32 a) {
    if (a == 0) {
        D_800E7C60[i][D_800E7BF0[i]] = func_800996A0(D_800E79A0[i]);
        D_800E7C60[i][D_800E7BF0[i] + 1] = 0;
        return;
    }
    D_800E7C60[i][D_800E7BF0[i]] = 0x40;
    switch (i) {
    case 0:
        D_800E7C60[i][D_800E7BF0[i] + 1] = 0x42;
        break;
    case 1:
        D_800E7C60[i][D_800E7BF0[i] + 1] = 0x52;
        break;
    case 2:
        D_800E7C60[i][D_800E7BF0[i] + 1] = 0x47;
        break;
    default:
        D_800E7C60[i][D_800E7BF0[i] + 1] = 0x59;
        break;
    }
    D_800E7C60[i][D_800E7BF0[i] + 2] = func_800996A0(D_800E79A0[i]);
    D_800E7C60[i][D_800E7BF0[i] + 3] = 0;
}
