/* @header
 * func_800A9488
 * VRAM 0x800A9488 | ROM 0x9C928 | size 0x2C
 * asm: asm/nonmatchings/code_8009D7A0/func_800A9488.s
 */
#include "common.h"

/* When other's state is 0x2C or 0x2D, add w's anim.frameCount (the length of w's current animation) to
 * other's escapeTimer. */
void func_800A9488(Wrestler *w, Wrestler *other) {
    if ((u32) ((u16)other->state - 0x2C) < 2U) {
        other->escapeTimer += w->anim.frameCount;
    }
}
