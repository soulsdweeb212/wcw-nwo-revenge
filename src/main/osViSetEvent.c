/* @header
 * osViSetEvent  (originally func_80020E70)
 * VRAM 0x80020E70 | ROM 0x21A70 | size 0x58
 * asm: asm/nonmatchings/main/osViSetEvent.s
 */
/* SDK: libultra 2.0I, ultralib src/io/visetevent.c (same code as the SDK source). */
#include "common.h"

s32 __osDisableInt(void);
void __osRestoreInt(s32);
extern void *__osViNext;

/* Programs the VI framebuffer registers: the origin (arg0), the width (arg1)
 * and the frame type (arg2) of the next VI mode, with interrupts disabled. */
void osViSetEvent(s32 arg0, s32 arg1, s16 arg2) {
    s32 temp_a0;

    temp_a0 = __osDisableInt();
    *(s32 *)((u8 *)__osViNext + 0x10) = arg0;
    *(s32 *)((u8 *)__osViNext + 0x14) = arg1;
    *(s16 *)((u8 *)__osViNext + 2) = arg2;
    __osRestoreInt(temp_a0);
}
