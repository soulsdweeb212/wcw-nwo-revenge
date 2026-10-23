#include "common.h"

extern u32 D_800FABD8;

s32 func_800D633C(void) {
    u32 v = D_800FABD8;
    u32 m = v & 2;
    u32 r = m != 0;
    return r;
}
