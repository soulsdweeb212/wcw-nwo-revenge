#include "common.h"

f32 func_80003A3C(f32, f32);
f32 nw2Sqrtf(f32);
extern f64 D_800E6B98;
extern f64 D_800E6BA0;

/* Evaluate sqrt(x*x + y*y); the result is not consumed here. */
void func_800D371C(f32 x, f32 y) {
    nw2Sqrtf(x * x + y * y);
}
