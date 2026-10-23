#include "common.h"

/* Scales arg0 by base^exponent, where the base is the 16.16 value
 * (arg2<<16 | arg3&0xFFFF) and the exponent is arg1>>3 (binary exponentiation). */
f32 func_8001EFE4(f32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    f32 var_ft0;
    f32 var_fv1;
    s32 var_a1;
    s32 var_v1;

    var_a1 = arg1 >> 3;
    if (var_a1 == 0) {
        return arg0;
    }
    var_ft0 = 1.0f;
    var_v1 = 0;
    var_fv1 = ((f32) (arg2 << 0x10) + (f32) (arg3 & 0xFFFF)) / 65536.0f;
loop_3:
    if (var_a1 & 1) {
        var_ft0 *= var_fv1;
    }
    var_a1 = var_a1 >> 1;
    if (var_a1 != 0) {
        var_v1 += 1;
        var_fv1 *= var_fv1;
        if (var_v1 >= 0x20) {

        } else {
            goto loop_3;
        }
    }
    return arg0 * var_ft0;
}
