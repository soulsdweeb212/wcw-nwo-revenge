/* @header
 * osViGetNextFramebuffer  (originally func_80020E30)
 * VRAM 0x80020E30 | ROM 0x21A30 | size 0x38
 * asm: asm/nonmatchings/main/osViGetNextFramebuffer.s
 */
/* SDK: libultra 2.0I, ultralib src/io/vigetnextframebuf.c (same code as the SDK source). */
#include "common.h"

extern s32 __osDisableInt(void);
extern void __osRestoreInt(s32);
extern s32 __osSpGetStatus(void);
extern void *__osViNext;

/* Read the pending VI framebuffer's +4 field with interrupts disabled. */
s32 osViGetNextFramebuffer(void) {
    s32 temp;
    s32 val;

    temp = __osDisableInt();
    val = *(s32 *)((u8 *)__osViNext + 4);
    __osRestoreInt(temp);
    return val;
}
