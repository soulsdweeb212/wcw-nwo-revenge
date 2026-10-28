#include "common.h"

s8 func_800D2758(s32, s32, s32, s32, s32);

/* Boundary correction with no records and direction mask -1. */
s8 func_800D25D0(s32 arg0, s32 arg1) {
    return func_800D2758(arg0, arg1, 0, -1, 1);
}
