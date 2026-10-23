#include "common.h"

extern u16 D_800EB638[];
s32 func_8001C580(void);
s32 func_800D4204(void);

/* Random-chance test: advances the RNG, refreshes the distribution entry and
 * returns whether arg0 is at least the previous value. */
s32 func_800D4198(s16 arg0) {
    s32 i = func_8001C580() & 0x1F;
    u16 old = D_800EB638[i];
    D_800EB638[i] = func_800D4204();
    return arg0 >= (s16)old;
}
