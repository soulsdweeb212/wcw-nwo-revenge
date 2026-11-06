/* @header
 * func_800D2670
 * VRAM 0x800D2670 | ROM 0xC5B10 | size 0x30
 * asm: asm/nonmatchings/code_800BBA00/func_800D2670.s
 */
#include "common.h"

s8 func_800D2758(Wrestler *, f32, u16, s8, s16);

/* func_800D25D0 in mode 2: func_800D2758(w, divisor, 0 (axis mask 0xF00), no id ignored, mode 2). */
s8 func_800D2670(Wrestler *w, f32 divisor) {
    return func_800D2758(w, divisor, 0, -1, 2);
}
