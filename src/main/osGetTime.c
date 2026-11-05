/* @header
 * osGetTime  (originally func_80026DD0)
 * VRAM 0x80026DD0 | ROM 0x279D0 | size 0x84
 * asm: asm/nonmatchings/main/osGetTime.s
 */
/* SDK: libultra 2.0I, ultralib src/os/gettime.c (same code as the SDK source). */
#include "common.h"

extern u32 __osBaseCounter;
extern u64 __osCurrentTime;
s32 __osDisableInt(void);
u32 osGetCount(void);
void __osRestoreInt(s32);

/* Returns the accumulated timer value: the last latched 64-bit count plus the
 * hardware delta since it was latched. */
u64 osGetTime(void) {
    s32 state = __osDisableInt();
    u32 t = osGetCount();
    u64 acc = __osCurrentTime;
    u32 d = t - __osBaseCounter;
    __osRestoreInt(state);
    return acc + (u64)d;
}
