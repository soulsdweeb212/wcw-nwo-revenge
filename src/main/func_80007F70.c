#include "common.h"

typedef struct {
    f32 m00, m01, m02, m03;
    f32 m10, m11, m12, m13;
    f32 m20, m21, m22, m23;
} Nw2Mat3x4;

/* Transform point (arg1, arg2, arg3) by the 3x4 matrix arg0 and write the
 * resulting x/y/z through arg4/arg5/arg6. */
void func_80007F70(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 *arg4, f32 *arg5, f32 *arg6) {
    Nw2Mat3x4 *m = arg0;
    *arg4 = (m->m00 * arg1) + (m->m01 * arg2) + (m->m02 * arg3) + m->m03;
    *arg5 = (m->m10 * arg1) + (m->m11 * arg2) + (m->m12 * arg3) + m->m13;
    *arg6 = (m->m20 * arg1) + (m->m21 * arg2) + (m->m22 * arg3) + m->m23;
}
