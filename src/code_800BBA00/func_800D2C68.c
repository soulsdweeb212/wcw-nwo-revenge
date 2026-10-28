#include "common.h"

s32 func_800D2CAC(void *, void *, void *, f32, void *, void *, void *, u16, s32, u16);
/* Boundary-correction wrapper (entity, linked entity, divisor, optional position
 * and attachment) with the apply flag set. */
s32 func_800D2C68(void *arg0, void *arg1, f32 arg2, void *arg3, s32 arg4) {
    return func_800D2CAC(arg0, arg1, NULL, arg2, NULL, arg3, NULL, 0, arg4, 1);
}
