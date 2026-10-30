/* @header
 * func_800033F8
 * VRAM 0x800033F8 | ROM 0x3FF8 | size 0x20
 * asm: asm/nonmatchings/main/func_800033F8.s
 */
#include "common.h"

s32 func_80013C24(s32);

/* Report whether audio channel 2 is still busy. */
s32 func_800033F8(void) {
    return func_80013C24(2) != 0;
}
