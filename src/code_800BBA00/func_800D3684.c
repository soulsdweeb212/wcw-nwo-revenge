#include "common.h"

/* Signed angular difference arg0 - arg1, wrapped to [-0x800, 0x800]. */
s32 func_800D3684(s32 arg0, s32 arg1) {
    s32 d = arg0 - arg1;
    s32 a;
    if (d < 0) {
        a = -d;
    } else {
        a = d;
    }
    if (a >= 0x801) {
        if (d < 0) {
            d += 0x1000;
        } else {
            d -= 0x1000;
        }
    }
    return d;
}
