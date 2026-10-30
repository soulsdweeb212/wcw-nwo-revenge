/* @header
 * func_8000801C
 * VRAM 0x8000801C | ROM 0x8C1C | size 0x7C
 * asm: asm/nonmatchings/main/func_8000801C.s
 */
#include "common.h"

/* Applies the 4x4 matrix arg0 to the point (arg1,arg2,arg3), writing only the X
 * and Z outputs to arg4/arg5. */
void func_8000801C(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 *arg4, f32 *arg5) {
    f32 *m = (f32 *)arg0;
    *arg4 = (m[0] * arg1) + (m[4] * arg2) + (m[8] * arg3) + m[12];
    *arg5 = (m[2] * arg1) + (m[6] * arg2) + (m[10] * arg3) + m[14];
}
