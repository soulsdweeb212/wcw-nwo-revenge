#include "common.h"

/* Scales arg0 by 2^arg2 (integer power of two). */
f64 func_8001ED40(f64 arg0, s32 arg2) {
    f64 var_fa0;

    var_fa0 = arg0;
    if (arg2 != 0) {
        var_fa0 *= (f64) (1 << arg2);
    }
    return var_fa0;
}
