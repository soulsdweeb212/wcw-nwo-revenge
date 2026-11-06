/* @header
 * func_800D2600
 * VRAM 0x800D2600 | ROM 0xC5AA0 | size 0x38
 * asm: asm/nonmatchings/code_800BBA00/func_800D2600.s
 */
#include "common.h"

s8 func_800D2758(Wrestler *, f32, u16, s8, s16);

/* func_800D25D0 with one wrestler left out: func_800D2758(w, divisor, 0 (axis mask 0xF00), ignoreId, mode 1). */
s8 func_800D2600(Wrestler *w, s8 ignoreId, f32 divisor) {
    return func_800D2758(w, divisor, 0, ignoreId, 1);
}
