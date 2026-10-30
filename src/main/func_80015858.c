/* @header
 * func_80015858
 * VRAM 0x80015858 | ROM 0x16458 | size 0x194
 * asm: asm/nonmatchings/main/func_80015858.s
 */
#include "common.h"

extern f64 D_8003B348;
extern f64 D_8003B350;
extern f64 D_8003B358;
extern f64 D_8003B360;
extern f64 D_8003B368;
extern f64 D_8003B370;
extern f64 D_8003B378;
extern f64 D_8003B380;
extern f64 D_8003B388;
extern f64 D_8003B390;
extern f64 D_8003B398;
extern f64 D_8003B3A0;
extern f64 D_8003B3A8;
extern f64 D_8003B3B0;

f32 func_80015858(f32 x) {
    f32 x2;
    if (x == 0.0f) {
        return 1.0f;
    }
    if (x > 0.0f) {
        x2 = x * x;
        return x * D_8003B380 + D_8003B3A0 + x2 * D_8003B388 + x2 * x * D_8003B390
             + x2 * x2 * D_8003B398 + x2 * x2 * x * D_8003B3A8 + x2 * x2 * x2 * D_8003B3B0;
    } else {
        f32 x3, x4, x5, x6;
        x = -x;
        x2 = x * x;
        x3 = x2 * x;
        x4 = x2 * x2;
        x5 = x4 * x;
        x6 = x4 * x2;
        return D_8003B368 / (x * D_8003B348 + D_8003B368 + x2 * D_8003B350 + x3 * D_8003B358
             + x4 * D_8003B360 + x5 * D_8003B370 + x6 * D_8003B378);
    }
}
