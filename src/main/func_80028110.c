#include "common.h"

s32 nw2DisableInterrupts();
void nw2RestoreInterrupts(s32);
extern s32 D_80038810;

/* Clear the bits of arg0 in D_80038810 (always leaving bits 0 and 0x400 set), with
 * interrupts disabled. */
void func_80028110(s32 arg0) {
    s32 saved;

    saved = nw2DisableInterrupts();
    D_80038810 &= ~arg0 | 0x401;
    nw2RestoreInterrupts(saved);
}
