/* @header
 * func_80021090
 * VRAM 0x80021090 | ROM 0x21C90 | size 0x44
 * asm: asm/nonmatchings/main/func_80021090.s
 */
#include "common.h"

s32 nw2DisableInterrupts();
void nw2RestoreInterrupts(s32);
extern void *__osViNext;

/* Store the framebuffer's +0x24 field and set its +0 status bit 4, with interrupts
 * disabled. */
void func_80021090(f32 arg0) {
    s32 saved;

    saved = nw2DisableInterrupts();
    *(f32 *)((u8 *)__osViNext + 0x24) = arg0;
    *(u16 *)((u8 *)__osViNext + 0) = (u16) (*(u16 *)((u8 *)__osViNext + 0) | 4);
    nw2RestoreInterrupts(saved);
}
