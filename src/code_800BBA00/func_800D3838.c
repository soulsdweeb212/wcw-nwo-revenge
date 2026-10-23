#include "common.h"

/* Write the XZ difference (arg1 - arg0) into arg3, dividing it by arg2 when arg2 is
 * nonzero. */
void func_800D3838(void *arg0, void *arg1, s16 arg2, void *arg3) {
    f32 divisor;

    *(f32 *)((s8 *)arg3 + 0) = (f32) (*(f32 *)((s8 *)arg1 + 0) - *(f32 *)((s8 *)arg0 + 0));
    *(f32 *)((s8 *)arg3 + 8) = (f32) (*(f32 *)((s8 *)arg1 + 8) - *(f32 *)((s8 *)arg0 + 8));
    if (arg2 != 0) {
        divisor = (f32) arg2;
        *(f32 *)((s8 *)arg3 + 0) = (f32) (*(f32 *)((s8 *)arg3 + 0) / divisor);
        *(f32 *)((s8 *)arg3 + 8) = (f32) (*(f32 *)((s8 *)arg3 + 8) / divisor);
    }
}
