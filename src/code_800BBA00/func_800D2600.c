#include "common.h"

s8 func_800D2758(s32, s32, s32, s32, s32);

/* Boundary/position wrapper: (entity, value, 0, -1, mode 1). */
s8 func_800D25D0(s32 arg0, s32 arg1) {
    return func_800D2758(arg0, arg1, 0, -1, 1);
}

/* Boundary/position wrapper taking the mode in arg1: (entity, value, 0, mode, 1). */
s8 func_800D2600(s32 arg0, s8 arg1, s32 arg2) {
    return func_800D2758(arg0, arg2, 0, arg1, 1);
}

/* Boundary/position wrapper taking a u16 mask: (entity, value, mask, -1, 1). */
s8 func_800D2638(s32 arg0, s32 arg1, s32 arg2) {
    return func_800D2758(arg0, arg2, arg1 & 0xFFFF, -1, 1);
}

/* Boundary/position wrapper with mode 2. */
s8 func_800D2670(s32 arg0, s32 arg1) {
    return func_800D2758(arg0, arg1, 0, -1, 2);
}
