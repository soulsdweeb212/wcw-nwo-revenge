#include "common.h"

s32 func_800D2CAC(void *, void *, void *, f32, void *, void *, void *, u16, s32, u16);

/* Boundary-correction wrapper (entity, two linked entities, optional buffer,
 * divisor) with the apply flag set. */
s32 func_800D2C2C(void *arg0, void *arg1, void *arg2, f32 arg3, void *arg4, s32 arg5) {
    return func_800D2CAC(arg0, arg1, arg2, arg3, NULL, NULL, arg4, 0, arg5, 1);
}
