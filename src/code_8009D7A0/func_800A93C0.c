/* @header
 * func_800A93C0
 * VRAM 0x800A93C0 | ROM 0x9C860 | size 0xC8
 * asm: asm/nonmatchings/code_8009D7A0/func_800A93C0.s
 */
#include "common.h"

extern u8 D_800FADCF;

s32 func_800A93C0(void) {
    s16 i;

    if (D_800FADCF & 0x40) {
        return 1;
    }
    for (i = 0; i < 4; i++) {
        if (D_800F9D10[i].characterId != -1) {
            if (D_800F9D10[i].state == 0x8F || (D_800F9D10[i].flags & 0x10)) {
                return 1;
            }
        }
    }
    return 0;
}
