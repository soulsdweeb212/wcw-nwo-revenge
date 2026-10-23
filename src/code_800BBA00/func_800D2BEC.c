#include "common.h"

s32 func_800D2CAC(void *, void *, void *, f32, void *, void *, void *, u16, s32, u16);
/* Boundary-correction wrapper (entity, two linked entities, divisor) using the
 * entity's +0x368 as the position and applying the correction. */
s32 func_800D2BEC(void *arg0, void *arg1, void *arg2, f32 arg3, u16 arg4, s32 arg5) {
    return func_800D2CAC(arg0, arg1, arg2, arg3, (u8 *)arg0 + 0x368, NULL, NULL, arg4, arg5, 1);
}
