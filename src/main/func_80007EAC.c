#include "common.h"

f32 cosf(f32);
f32 sinf(f32);
extern f32 D_800307B0;
void initIdentityMatrix4x4(void *);

/* Build a perspective/frustum matrix in arg0: after clearing it to identity, write
 *   m[0][0] (0x00) = tan(fov/2 * D_800307B0) * aspect
 *   m[1][1] (0x14) = tan(fov/2 * D_800307B0)
 *   m[2][3] (0x2C) = (near - far) / (2*near*far)
 *   m[3][3] (0x3C) = (near + far) / (2*near*far)
 * with m[2][2] (0x28) = 0 and m[3][2] (0x38) = -1. */
void func_80007EAC(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    f32 temp_fs0;
    f32 temp_fs0_2;
    f32 temp_fs0_3;
    f32 temp_fs3;
    f32 temp_fv0;

    initIdentityMatrix4x4(arg0);
    temp_fs0 = arg1 * D_800307B0 * 0.5f;
    temp_fs0_2 = sinf(temp_fs0);
    temp_fs0_3 = temp_fs0_2 / cosf(temp_fs0);
    temp_fv0 = 2.0f * arg3 * arg4;
    temp_fs3 = temp_fs0_3 * arg2;
    *(s32 *)((u8 *)arg0 + 0x28) = 0;
    *(f32 *)((u8 *)arg0 + 0x38) = -1.0f;
    *(f32 *)((u8 *)arg0 + 0x14) = temp_fs0_3;
    *(f32 *)((u8 *)arg0 + 0) = temp_fs3;
    *(f32 *)((u8 *)arg0 + 0x2C) = (f32) ((arg3 - arg4) / temp_fv0);
    *(f32 *)((u8 *)arg0 + 0x3C) = (f32) ((arg3 + arg4) / temp_fv0);
}
