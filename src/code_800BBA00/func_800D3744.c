#include "common.h"

f32 func_80003A3C(f32, f32);
f32 nw2Sqrtf(f32);
extern f64 D_800E6B88;

/* Computes the length of the 2D vector (arg0,arg1) into *arg2 and its heading
 * (16.16 fixed point) into *arg3. */
void func_800D3744(f32 arg0, f32 arg1, f32 *arg2, s32 *arg3) {
    *arg2 = nw2Sqrtf((arg0 * arg0) + (arg1 * arg1));
    *arg3 = (s32) ((f64) func_80003A3C(arg0, arg1) * D_800E6B88);
}
