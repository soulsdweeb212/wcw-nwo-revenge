#include "common.h"

extern u32 D_80037230;

/* Advance the pseudo-random sequence and return the new value. */
u32 func_8001C580(void) {
    s32 t = D_80037230 * 4;
    return D_80037230 = (u32)((t + 2) * (t + 3)) >> 2;
}
