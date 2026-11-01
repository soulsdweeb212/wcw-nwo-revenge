/* @header
 * func_800A9E40
 * VRAM 0x800A9E40 | ROM 0x565B0 | size 0x34
 * asm: asm/nonmatchings/code_80090000/func_800A9E40.s
 */
#include "common.h"

extern u8 D_8007EF30[];

s32 func_800A9E40(void) {
    s32 n = 0;
    s32 i;
    for (i = 0; i < 0x80; i += 0x10) {
        n += *(s16 *)(D_8007EF30 + 0x4E + i) > 0;
    }
    return n;
}
