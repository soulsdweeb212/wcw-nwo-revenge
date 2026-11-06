/* @header
 * func_800D2BEC
 * VRAM 0x800D2BEC | ROM 0xC608C | size 0x40
 * asm: asm/nonmatchings/code_800BBA00/func_800D2BEC.s
 */
#include "common.h"

/* Boundary correction of w, moving the linked records along with it unless w's animation has passed frame
 * anim.unk379 (when nonzero): func_800D2CAC(w, linked1, linked2, divisor, &w->anim, dirMask, bodyMask, apply). */
s32 func_800D2BEC(Wrestler *w, Wrestler *linked1, Wrestler *linked2, f32 divisor, u16 dirMask, s32 bodyMask) {
    return func_800D2CAC(w, linked1, linked2, divisor, &w->anim, NULL, NULL, dirMask, bodyMask, 1);
}
