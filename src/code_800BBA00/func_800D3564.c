/* @header
 * func_800D3564
 * VRAM 0x800D3564 | ROM 0xC6A04 | size 0x2C
 * asm: asm/nonmatchings/code_800BBA00/func_800D3564.s
 */
#include "common.h"

/* identical to func_80003CF0 (matched), with its names changed by decompdecomp */
extern s8 D_800484F4[];
extern s8 D_800484F8[];
extern s8 D_800484FC[];

/* Absolute value of x. */
f32 func_800D3564(f32 x) {
    if (x >= 0.0) {
        return x;
    }
    return -x;
}
