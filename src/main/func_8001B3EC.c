/* @header
 * func_8001B3EC
 * VRAM 0x8001B3EC | ROM 0x1BFEC | size 0xAC
 * asm: asm/nonmatchings/main/func_8001B3EC.s
 */
#include "common.h"

/* Applies the 4x4 row-major matrix arg0 (with translation in the fourth column)
 * to the point (arg1,arg2,arg3), writing the transformed point to
 * arg4/arg5/arg6. */
void func_8001B3EC(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 *arg4, f32 *arg5, f32 *arg6) {
    f32 *m = (f32 *)arg0;
    *arg4 = (m[0] * arg1) + (m[4] * arg2) + (m[8] * arg3) + m[12];
    *arg5 = (m[1] * arg1) + (m[5] * arg2) + (m[9] * arg3) + m[13];
    *arg6 = (m[2] * arg1) + (m[6] * arg2) + (m[10] * arg3) + m[14];
}
