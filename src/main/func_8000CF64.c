/* @header
 * func_8000CF64
 * VRAM 0x8000CF64 | ROM 0xDB64 | size 0x70
 * asm: asm/nonmatchings/main/func_8000CF64.s
 */
#include "common.h"

void func_800015AC(void *, s8);
f32 func_80003CF0(f32);
extern f64 D_8003B1C0;

/* Returns 1 when both x and y are below the D_8003B1C0 limit. */
s32 func_8000CF64(f32 x, f32 y) {
    f64 lim = D_8003B1C0;

    if (func_80003CF0(x) < lim) {
        if (func_80003CF0(y) < lim) {
            return 1;
        }
    }
    return 0;
}
