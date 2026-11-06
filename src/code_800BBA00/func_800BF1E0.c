/* @header
 * func_800BF1E0
 * VRAM 0x800BF1E0 | ROM 0xB2680 | size 0x48
 * asm: asm/nonmatchings/code_800BBA00/func_800BF1E0.s
 */
#include "common.h"

/* Return w->bodyPart[part], or the constant 0x32 (50, the starting value) when
 * WR_FLAG_SPECIAL is set. */
s32 func_800BF1E0(Wrestler *w, s16 part) {
    s32 v;

    if (w->flags & WR_FLAG_SPECIAL) {
        v = 0x32;
    } else {
        v = w->bodyPart[part];
    }
    return v;
}
