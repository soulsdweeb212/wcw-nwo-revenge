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
