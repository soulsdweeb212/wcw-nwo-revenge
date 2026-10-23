#include "common.h"

extern u32 D_80065120;
extern u64 D_80070B20;
s32 nw2DisableInterrupts(void);
u32 func_80026AF0(void);
void nw2RestoreInterrupts(s32);

/* Returns the accumulated timer value: the last latched 64-bit count plus the
 * hardware delta since it was latched. */
u64 func_80026DD0(void) {
    s32 state = nw2DisableInterrupts();
    u32 t = func_80026AF0();
    u64 acc = D_80070B20;
    u32 d = t - D_80065120;
    nw2RestoreInterrupts(state);
    return acc + (u64)d;
}
