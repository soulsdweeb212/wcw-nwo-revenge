#include "common.h"

s32 nw2DisableInterrupts(void);
void nw2RestoreInterrupts(s32);
extern void *__osViNext;

/* Programs the VI framebuffer registers: the origin (arg0), the width (arg1)
 * and the frame type (arg2) of the next VI mode, with interrupts disabled. */
void func_80020E70(s32 arg0, s32 arg1, s16 arg2) {
    s32 temp_a0;

    temp_a0 = nw2DisableInterrupts();
    *(s32 *)((u8 *)__osViNext + 0x10) = arg0;
    *(s32 *)((u8 *)__osViNext + 0x14) = arg1;
    *(s16 *)((u8 *)__osViNext + 2) = arg2;
    nw2RestoreInterrupts(temp_a0);
}
