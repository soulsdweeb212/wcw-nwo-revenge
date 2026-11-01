/* @header
 * func_800AA0D8
 * VRAM 0x800AA0D8 | ROM 0x56848 | size 0x14
 * asm: asm/nonmatchings/code_80090000/func_800AA0D8.s
 */
#include "common.h"

extern s32 D_8007E8C0[];

s32 func_800AA0D8(s32 i) {
    return D_8007E8C0[i];
}
