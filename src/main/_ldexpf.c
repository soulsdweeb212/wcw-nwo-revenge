/* @header
 * _ldexpf  (originally func_8001ED40)
 * VRAM 0x8001ED40 | ROM 0x1F940 | size 0x24
 * asm: asm/nonmatchings/main/_ldexpf.s
 */
/* SDK: libultra 2.0I, ultralib src/audio/env.c (same code as the SDK source). */
#include "common.h"

/* Scales arg0 by 2^arg2 (integer power of two). */
f64 _ldexpf(f64 arg0, s32 arg2) {
    f64 var_fa0;

    var_fa0 = arg0;
    if (arg2 != 0) {
        var_fa0 *= (f64) (1 << arg2);
    }
    return var_fa0;
}
