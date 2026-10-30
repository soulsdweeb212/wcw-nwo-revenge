/* @header
 * func_80021130
 * VRAM 0x80021130 | ROM 0x21D30 | size 0x5C
 * asm: asm/nonmatchings/main/func_80021130.s
 */
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
