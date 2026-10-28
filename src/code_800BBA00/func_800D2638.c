#include "common.h"

s8 func_800D2758(s32, s32, s32, s32, s32);

/* Boundary correction with a body-part mask from arg1. */
s8 func_800D2638(s32 arg0, s32 arg1, s32 arg2) {
    return func_800D2758(arg0, arg2, arg1 & 0xFFFF, -1, 1);
}
