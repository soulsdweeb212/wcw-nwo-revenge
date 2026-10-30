/* @header
 * func_80003CF0
 * VRAM 0x80003CF0 | ROM 0x48F0 | size 0x2C
 * asm: asm/nonmatchings/main/func_80003CF0.s
 */
#include "common.h"

extern s8 D_800484F4[];
extern s8 D_800484F8[];
extern s8 D_800484FC[];

/* Absolute value of x. */
f32 func_80003CF0(f32 x) {
    if (x >= 0.0) {
        return x;
    }
    return -x;
}
