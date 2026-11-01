/* @header
 * func_800A9F64
 * VRAM 0x800A9F64 | ROM 0x566D4 | size 0x14
 * asm: asm/nonmatchings/code_80090000/func_800A9F64.s
 */
#include "common.h"

extern u8 D_8007EF30[];

u8 func_800A9F64(s32 i) {
    return D_8007EF30[(i << 4) + 0x51];
}
