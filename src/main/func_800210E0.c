/* @header
 * func_800210E0
 * VRAM 0x800210E0 | ROM 0x21CE0 | size 0x44
 * asm: asm/nonmatchings/main/func_800210E0.s
 */
#include "common.h"

s32 nw2DisableInterrupts();
void nw2RestoreInterrupts(s32);
extern void *__osViNext;

/* Store the framebuffer's +4 field and set its +0 status bit 0x10, with interrupts
 * disabled. */
void func_800210E0(s32 arg0) {
    s32 saved;

    saved = nw2DisableInterrupts();
    *(s32 *)((u8 *)__osViNext + 4) = arg0;
    *(u16 *)((u8 *)__osViNext + 0) = (u16) (*(u16 *)((u8 *)__osViNext + 0) | 0x10);
    nw2RestoreInterrupts(saved);
}
