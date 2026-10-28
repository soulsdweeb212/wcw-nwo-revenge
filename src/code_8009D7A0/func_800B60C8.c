#include "common.h"

extern u8 *D_800FABD0;
extern u8 *D_800F9B60;
extern u8 *D_800FAF58;
s8 func_800B4C60(void *, void *, s32, s32);
s8 func_800B5DC4(void *, s32);
/* Returns 1 when arg0 is outside arg1's boundary but within the clamp region. */
s32 func_800B60C8(void *arg0, void *arg1) {
    if (!func_800B4C60(arg0, arg1, 0, 1)) {
        return func_800B5DC4(arg0, 1) != 0;
    }
    return 0;
}
