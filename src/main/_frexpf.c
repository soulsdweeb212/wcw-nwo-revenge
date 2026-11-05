/* @header
 * _frexpf  (originally func_8001EC60)
 * VRAM 0x8001EC60 | ROM 0x1F860 | size 0xE0
 * asm: asm/nonmatchings/main/_frexpf.s
 */
/* SDK: libultra 2.0I, ultralib src/audio/env.c (same code as the SDK source). */
#include "common.h"

extern const f64 D_8003B768;   /* 2^N upper bound */
extern const f64 D_8003B770;   /* 2^-N scaling */
extern const f64 D_8003B778;   /* 0.5 */

/* frexp-style split: normalise |x| into [0.5, 1) by repeated halving/doubling,
 * returning the mantissa and storing the exponent in *exp. Zero returns itself
 * with exponent 0. */
f64 _frexpf(f64 x, s32 *exp) {
    f64 v;
    f64 r;

    *exp = 0;
    if (x == 0.0)
        return x;
    v = x;
    if (!(x > 0.0))
        v = -x;
    while (D_8003B768 <= v) {
        v *= D_8003B770;
        (*exp)++;
    }
    while (v < D_8003B778) {
        v *= 2.0;
        (*exp)--;
    }
    r = v;
    if (!(x > 0.0))
        r = -r;
    return r;
}
