/* @header
 * osViGetCurrentFramebuffer  (originally func_80020DF0)
 * VRAM 0x80020DF0 | ROM 0x219F0 | size 0x38
 * asm: asm/nonmatchings/main/osViGetCurrentFramebuffer.s
 */
/* SDK: libultra 2.0I, ultralib src/io/vigetcurrframebuf.c (same code as the SDK source). */
#include "common.h"

extern s32 __osDisableInt(void);
extern void __osRestoreInt(s32);
extern s32 __osSpGetStatus(void);
extern void *__osViCurr;
extern void *__osViNext;

/* Read the current VI framebuffer's +4 field with interrupts disabled. */
s32 osViGetCurrentFramebuffer(void) {
    s32 temp;
    s32 val;

    temp = __osDisableInt();
    val = *(s32 *)((u8 *)__osViCurr + 4);
    __osRestoreInt(temp);
    return val;
}
