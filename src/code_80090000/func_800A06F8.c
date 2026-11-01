/* @header
 * func_800A06F8
 * VRAM 0x800A06F8 | ROM 0x4CE68 | size 0x58
 * asm: asm/nonmatchings/code_80090000/func_800A06F8.s
 */
#include "common.h"

s32 func_800A06F8(u8 *a, s32 b) {
    switch (*(u8 *)(*(s32 *)(a + 0x24) + 0xF) & 0xF) {
    case 6:
    case 7:
    case 8:
    case 9:
        return b;
    case 1:
    case 5:
        return b << 7;
    default:
        return b << 6;
    }
}
