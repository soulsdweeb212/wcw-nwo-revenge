#include "common.h"

extern s8 D_800484F4[];
extern s8 D_800484F8[];
extern s8 D_800484FC[];

/* Absolute value of x. */
f32 func_80003CF0(f32 x) {
    if (x >= 0.0) {
        return x;
    }
    return -x;
}
