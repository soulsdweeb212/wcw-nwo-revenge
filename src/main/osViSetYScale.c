/* @header
 * osViSetYScale  (originally func_80021090)
 * VRAM 0x80021090 | ROM 0x21C90 | size 0x44
 * asm: asm/nonmatchings/main/osViSetYScale.s
 */
/* SDK: libultra 2.0I, ultralib src/io/visetyscale.c (same code as the SDK source). */
#include "common.h"

s32 __osDisableInt();
void __osRestoreInt(s32);
extern void *__osViNext;

/* Store the framebuffer's +0x24 field and set its +0 status bit 4, with interrupts
 * disabled. */
void osViSetYScale(f32 arg0) {
    s32 saved;

    saved = __osDisableInt();
    *(f32 *)((u8 *)__osViNext + 0x24) = arg0;
    *(u16 *)((u8 *)__osViNext + 0) = (u16) (*(u16 *)((u8 *)__osViNext + 0) | 4);
    __osRestoreInt(saved);
}
