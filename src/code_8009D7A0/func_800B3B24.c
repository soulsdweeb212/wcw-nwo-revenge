/* @header
 * func_800B3B24
 * VRAM 0x800B3B24 | ROM 0xA6FC4 | size 0x6C
 * asm: asm/nonmatchings/code_8009D7A0/func_800B3B24.s
 */
#include "common.h"

extern u8 *D_800FABD0;
extern f64 D_800E5430;
s8 func_800B4C60(void *, void *, s32, s32);
s8 func_800B5DC4(void *, s32);
/* Resets the action when the AI self's pelvis Z (jointA[1].z) is below D_800E5430, then sets
 * the count word to 0x400. */
void func_800B3B24(void) {
    if (D_800FAF58->jointA[1].z < D_800E5430) {
        u8 *o = D_800FABD0;
        Wrestler *g = D_800F9B60;
        *(s16 *)(o + 2) = 0;
        *(s16 *)(o + 4) = 0;
        *(u16 *)(o + 0x2E) = g->state;
        *(u32 *)(o + 0x5C) &= ~7;
    }
    *(s16 *)(D_800FABD0 + 6) = 0x400;
}
