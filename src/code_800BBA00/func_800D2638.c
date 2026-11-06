/* @header
 * func_800D2638
 * VRAM 0x800D2638 | ROM 0xC5AD8 | size 0x38
 * asm: asm/nonmatchings/code_800BBA00/func_800D2638.s
 */
#include "common.h"

s8 func_800D2758(Wrestler *, f32, u16, s8, s16);

/* func_800D25D0 with an axis mask: func_800D2758(w, divisor, axisMask (0x300 X, 0xC00 Z; 0 = both), no id
 * ignored, mode 1). */
s8 func_800D2638(Wrestler *w, s32 axisMask, f32 divisor) {
    return func_800D2758(w, divisor, axisMask & 0xFFFF, -1, 1);
}
