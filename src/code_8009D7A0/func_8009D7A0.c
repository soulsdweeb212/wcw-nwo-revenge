/* @header
 * func_8009D7A0
 * VRAM 0x8009D7A0 | ROM 0x90C40 | size 0xA4
 * asm: asm/nonmatchings/code_8009D7A0/func_8009D7A0.s
 */
#include "common.h"

s32 buildColorOverlayDisplayList(void *, s32, s32, s32, s32);
extern s16 D_800EB37A;
extern u8 D_800EB37B;
extern s32 *D_800F99D4;

/* Advances the overlay fade-in by 8 (clamped at 0xFF), rebuilds the colour
 * overlay display list with the given RGB and clears the overlay's 0x80 flag.
 * Returns 1 when it advanced, 0 when the fade is already complete. */
s32 func_8009D7A0(s32 arg0, s32 arg1, s32 arg2) {
    s16 temp_v0;

    if (D_800EB37A < 0xFF) {
        temp_v0 = D_800EB37A + 8;
        D_800EB37A = temp_v0;
        if (temp_v0 >= 0x100) {
            D_800EB37A = 0xFF;
        }
        buildColorOverlayDisplayList(&D_800F99C0, arg0 & 0xFF, arg1 & 0xFF, arg2 & 0xFF, (s32) D_800EB37B);
        *D_800F99D4 &= ~0x80;
        return 1;
    }
    return 0;
}
