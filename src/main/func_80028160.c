/* @header
 * func_80028160
 * VRAM 0x80028160 | ROM 0x28D60 | size 0x40
 * asm: asm/nonmatchings/main/func_80028160.s
 */
#include "common.h"

s32 nw2DisableInterrupts();
void nw2RestoreInterrupts(s32);
extern s32 D_80038810;

/* Set the bits of arg0 in D_80038810, with interrupts disabled. */
void func_80028160(s32 arg0) {
    s32 saved;

    saved = nw2DisableInterrupts();
    D_80038810 |= arg0;
    nw2RestoreInterrupts(saved);
}
