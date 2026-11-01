/* @header
 * func_800AA0EC
 * VRAM 0x800AA0EC | ROM 0x5685C | size 0x14
 * asm: asm/nonmatchings/code_80090000/func_800AA0EC.s
 */
#include "common.h"

extern s32 D_8007E228[];

s32 func_800AA0EC(s32 i) {
    return D_8007E228[i + 0x184];
}
