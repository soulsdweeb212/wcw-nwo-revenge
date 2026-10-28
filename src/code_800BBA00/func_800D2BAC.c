#include "common.h"

s32 func_800D2CAC(void *, void *, void *, f32, void *, void *, void *, u16, s32, u16);
/* Simplest boundary-correction wrapper. */
s32 func_800D2BAC(void *arg0, void *arg1, f32 arg2, s32 arg3) {
    return func_800D2CAC(arg0, arg1, NULL, arg2, NULL, NULL, NULL, 0, arg3, 1);
}
