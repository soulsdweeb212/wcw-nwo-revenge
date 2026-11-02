/* @header
 * func_800B5D20
 * VRAM 0x800B5D20 | ROM 0x62490 | size 0xF8
 * asm: asm/nonmatchings/code_80090000/func_800B5D20.s
 */
#include "common.h"

typedef struct { f32 v; s16 t; s16 pad; } K;
typedef struct { K *k; s32 n; } C;
extern f64 D_800D6770;

f32 func_800B5D20(s32 t, C *c, f64 *d) {
    K *a = c->k;
    s32 hi = c->n - 1;
    s32 lo = 0;
    s32 mid;
    f64 d0, d1, x, h;
    s32 pad[2];
    if (hi > 0) {
        do {
            mid = (lo + hi) / 2;
            if (a[mid].t < t) {
                lo = mid + 1;
            } else {
                hi = mid;
            }
        } while (lo < hi);
    }
    lo -= 0 < lo;
    d1 = d[lo + 1];
    d0 = d[lo];
    x = t - a[lo].t;
    h = a[lo + 1].t - a[lo].t;
    return (((d1 - d0) * x / h + d0 * D_800D6770) * x + ((a[lo + 1].v - a[lo].v) / h - (d0 + d0 + d1) * h)) * x + a[lo].v;
}
