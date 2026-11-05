/* @header
 * __osSetTimerIntr  (originally func_800271D0)
 * VRAM 0x800271D0 | ROM 0x27DD0 | size 0x60
 * asm: asm/nonmatchings/main/__osSetTimerIntr.s
 */
/* SDK: libultra 2.0I, ultralib src/os/timerintr.c (same code as the SDK source). */
#include "common.h"

extern s32 __osTimerCounter;
s32 __osDisableInt(void);
s32 osGetCount(void);
void __osRestoreInt(s32);
void __osSetCompare(s32);

/* Schedule the next timer interrupt `time` ticks from now, relative to the current
 * hardware counter value. */
void __osSetTimerIntr(u64 time) {
    s32 saved;
    u32 t;
    u64 d;

    saved = __osDisableInt();
    t = osGetCount();
    d = t + time;
    __osTimerCounter = t;
    __osSetCompare((s32)d);
    __osRestoreInt(saved);
}
