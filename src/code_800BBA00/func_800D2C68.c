/* @header
 * func_800D2C68
 * VRAM 0x800D2C68 | ROM 0xC6108 | size 0x44
 * asm: asm/nonmatchings/code_800BBA00/func_800D2C68.s
 */
#include "common.h"

/* Boundary correction of w, moving other and the three 16-byte points at arg3 (callers pass the slot's
 * D_800FACF8 entry) along with it: func_800D2CAC(w, other, divisor, points arg3, bodyMask, apply). */
s32 func_800D2C68(Wrestler *w, Wrestler *other, f32 divisor, void *arg3, s32 bodyMask) {
    return func_800D2CAC(w, other, NULL, divisor, NULL, arg3, NULL, 0, bodyMask, 1);
}
