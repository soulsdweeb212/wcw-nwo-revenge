/* @header
 * func_8002B790
 * VRAM 0x8002B790 | ROM 0x2C390 | size 0x50
 * asm: asm/nonmatchings/main/func_8002B790.s
 */
#include "common.h"

extern s32 D_8003A594;

/* Return the pointer to the 0x2A-byte variant arg1 of group arg0 (1..0x4F), or the
 * buffer base for an out-of-range request. */
s32 func_8002B790(s32 arg0, u32 arg1) {
    u32 idx;

    if ((u32)(arg0 - 1) < 0x4F) {
        if (arg1 < 4) {
            goto good;
        }
    }
    return D_8003A594;
good:
    idx = arg0 * 4 + arg1;
    return D_8003A594 + idx * 0x2A;
}
