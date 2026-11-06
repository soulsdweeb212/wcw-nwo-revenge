/* @header
 * func_800D2C2C
 * VRAM 0x800D2C2C | ROM 0xC60CC | size 0x3C
 * asm: asm/nonmatchings/code_800BBA00/func_800D2C2C.s
 */
#include "common.h"

/* Boundary correction of wrestler w, moving the linked records linked1 / linked2 and the position pos along with
 * it: func_800D2CAC(w, linked1, linked2, divisor, pos, bodyMask, apply). */
s32 func_800D2C2C(Wrestler *w, Wrestler *linked1, Wrestler *linked2, f32 divisor, void *pos, s32 bodyMask) {
    return func_800D2CAC(w, linked1, linked2, divisor, NULL, NULL, pos, 0, bodyMask, 1);
}
