#include "common.h"

extern s32 nw2DisableInterrupts(void);
extern void nw2RestoreInterrupts(s32);
extern s32 func_80027380(void);
extern void *__osViCurr;
extern void *__osViNext;

/* Read the current VI framebuffer's +4 field with interrupts disabled. */
s32 func_80020DF0(void) {
    s32 temp;
    s32 val;

    temp = nw2DisableInterrupts();
    val = *(s32 *)((u8 *)__osViCurr + 4);
    nw2RestoreInterrupts(temp);
    return val;
}
