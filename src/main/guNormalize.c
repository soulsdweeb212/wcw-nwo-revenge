/* @header
 * guNormalize  (originally func_8001B4A0)
 * VRAM 0x8001B4A0 | ROM 0x1C0A0 | size 0xA8
 * asm: asm/nonmatchings/main/guNormalize.s
 */
/* SDK: libultra 2.0I, ultralib src/gu/normalize.c (same code as the SDK source). */
#include "common.h"

f32 sqrtf(f32);

/* Normalizes the vector (*x, *y, *z) in place. */
void guNormalize(f32 *x, f32 *y, f32 *z) {
    f32 inv = 1.0f / sqrtf(*x * *x + *y * *y + *z * *z);

    *x *= inv;
    *y *= inv;
    *z *= inv;
}
