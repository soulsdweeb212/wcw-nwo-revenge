#include "common.h"

extern s32 D_8007BD60;
s32 nw2DisableInterrupts(void);
s32 func_80026AF0(void);
void nw2RestoreInterrupts(s32);
void func_80028100(s32);

/* Schedule the next timer interrupt `time` ticks from now, relative to the current
 * hardware counter value. */
void programTimerCountdown(u64 time) {
    s32 saved;
    u32 t;
    u64 d;

    saved = nw2DisableInterrupts();
    t = func_80026AF0();
    d = t + time;
    D_8007BD60 = t;
    func_80028100((s32)d);
    nw2RestoreInterrupts(saved);
}
