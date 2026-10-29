#include "common.h"

f32 sqrtf(f32);

/* Normalizes the vector (*x, *y, *z) in place. */
void func_8001B4A0(f32 *x, f32 *y, f32 *z) {
    f32 inv = 1.0f / sqrtf(*x * *x + *y * *y + *z * *z);

    *x *= inv;
    *y *= inv;
    *z *= inv;
}
