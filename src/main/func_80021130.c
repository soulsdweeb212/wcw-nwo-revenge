#include "common.h"

extern s32 nw2DisableInterrupts(void);
extern void nw2RestoreInterrupts(s32);
extern s32 func_80027380(void);
extern void *__osViCurr;
extern void *__osViNext;

/* Set or clear bit 0x20 of the pending VI framebuffer's status, with interrupts off. */
void func_80021130(s32 enable) {
    s32 temp;
    u16 *p;
    u16 v;

    temp = nw2DisableInterrupts();
    if (enable & 0xFF) {
        p = __osViNext;
        v = *p | 0x20;
    } else {
        p = __osViNext;
        v = *p & 0xFFDF;
    }
    *p = v;
    nw2RestoreInterrupts(temp);
}
