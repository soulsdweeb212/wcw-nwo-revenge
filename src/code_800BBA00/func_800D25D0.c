/* @header
 * func_800D25D0
 * VRAM 0x800D25D0 | ROM 0xC5A70 | size 0x30
 * asm: asm/nonmatchings/code_800BBA00/func_800D25D0.s
 */
#include "common.h"

s8 func_800D2758(Wrestler *, f32, u16, s8, s16);

/* Push w out of the other wrestlers in its zone: func_800D2758(w, divisor, 0 (axis mask 0xF00), no id ignored,
 * mode 1). Returns the first wrestler id found close, or -1. */
s8 func_800D25D0(Wrestler *w, f32 divisor) {
    return func_800D2758(w, divisor, 0, -1, 1);
}
