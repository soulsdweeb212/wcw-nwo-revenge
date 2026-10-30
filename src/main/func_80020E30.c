/* @header
 * func_80020E30
 * VRAM 0x80020E30 | ROM 0x21A30 | size 0x38
 * asm: asm/nonmatchings/main/func_80020E30.s
 */
#include "common.h"

extern s32 nw2DisableInterrupts(void);
extern void nw2RestoreInterrupts(s32);
extern s32 func_80027380(void);
extern void *__osViNext;

/* Read the pending VI framebuffer's +4 field with interrupts disabled. */
s32 func_80020E30(void) {
    s32 temp;
    s32 val;

    temp = nw2DisableInterrupts();
    val = *(s32 *)((u8 *)__osViNext + 4);
    nw2RestoreInterrupts(temp);
    return val;
}
