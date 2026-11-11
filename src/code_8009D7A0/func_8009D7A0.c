/* @header
 * func_8009D7A0
 * VRAM 0x8009D7A0 | ROM 0x90C40 | size 0xA4
 * asm: asm/nonmatchings/code_8009D7A0/func_8009D7A0.s
 */
#include "common.h"

s32 buildColorOverlayDisplayList(void *, s32, s32, s32, s32);
extern s16 D_800EB37A;
extern u8 D_800EB37B;
#ifndef TARGET_PC /* on PC D_800F99D4 has no symbol: it is the work of D_800F99C0, which port_decls.h declares */
extern s32 *D_800F99D4;
#endif

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
#ifdef TARGET_PC
        /* PC: D_800F99C0 keeps its N64 layout (Nw2SceneObj), so its work (+0x14, the N64 label D_800F99D4) is the
         * handle (port.h's PTR_TO_SLOT) of its work block (Nw2SceneWork), whose kind is the N64's flags word. */
        ((Nw2SceneWork *)SLOT_TO_PTR(D_800F99C0.work))->kind &= ~0x80;
#else
        *D_800F99D4 &= ~0x80;
#endif
        return 1;
    }
    return 0;
}
