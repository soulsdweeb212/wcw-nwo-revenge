#include "common.h"

s8 func_800D2758(s32, s32, s32, s32, s32);

/* Boundary/position wrapper taking the mode in arg1: (entity, value, 0, mode, 1). */
s8 func_800D2600(s32 arg0, s8 arg1, s32 arg2) {
    return func_800D2758(arg0, arg2, 0, arg1, 1);
}
