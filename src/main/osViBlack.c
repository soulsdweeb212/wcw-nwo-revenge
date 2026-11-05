/* @header
 * osViBlack  (originally func_80021130)
 * VRAM 0x80021130 | ROM 0x21D30 | size 0x5C
 * asm: asm/nonmatchings/main/osViBlack.s
 */
/* SDK: libultra 2.0I, ultralib src/io/viblack.c (same code as the SDK source). */
#include "common.h"

extern s32 __osDisableInt(void);
extern void __osRestoreInt(s32);
extern s32 __osSpGetStatus(void);
extern void *__osViCurr;
extern void *__osViNext;

/* Set or clear bit 0x20 of the pending VI framebuffer's status, with interrupts off. */
void osViBlack(s32 enable) {
    s32 temp;
    u16 *p;
    u16 v;

    temp = __osDisableInt();
    if (enable & 0xFF) {
        p = __osViNext;
        v = *p | 0x20;
    } else {
        p = __osViNext;
        v = *p & 0xFFDF;
    }
    *p = v;
    __osRestoreInt(temp);
}
