/* @header
 * func_800AA05C
 * VRAM 0x800AA05C | ROM 0x567CC | size 0x14
 * asm: asm/nonmatchings/code_80090000/func_800AA05C.s
 */
#include "common.h"

extern s32 D_8007E228[];

s32 func_800AA05C(s32 i) {
    return D_8007E228[i + 0x1A2];
}
