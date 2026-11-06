/* @header
 * func_800D2B64
 * VRAM 0x800D2B64 | ROM 0xC6004 | size 0x48
 * asm: asm/nonmatchings/code_800BBA00/func_800D2B64.s
 */
#include "common.h"

/* Boundary correction of w alone: func_800D2CAC(w, no linked records, divisor, dirMask, bodyMask, apply). */
s32 func_800D2B64(Wrestler *w, f32 divisor, u16 dirMask, s32 bodyMask) {
    return func_800D2CAC(w, NULL, NULL, divisor, NULL, NULL, NULL, dirMask, bodyMask, 1);
}
