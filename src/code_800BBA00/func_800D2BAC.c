/* @header
 * func_800D2BAC
 * VRAM 0x800D2BAC | ROM 0xC604C | size 0x40
 * asm: asm/nonmatchings/code_800BBA00/func_800D2BAC.s
 */
#include "common.h"

/* Boundary correction of w, moving other along with it: func_800D2CAC(w, other, divisor, bodyMask, apply). */
s32 func_800D2BAC(Wrestler *w, Wrestler *other, f32 divisor, s32 bodyMask) {
    return func_800D2CAC(w, other, NULL, divisor, NULL, NULL, NULL, 0, bodyMask, 1);
}
