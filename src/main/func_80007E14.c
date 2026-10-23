#include "common.h"

f32 cosf(f32);                             /* extern */
f32 sinf(f32);                             /* extern */
extern f32 D_800307B0;

/* Builds a 4x4 Y-axis rotation matrix (degrees arg1 scaled by D_800307B0) into
 * arg0, with the identity diagonal and zeros elsewhere. */
void func_80007E14(void *arg0, f32 arg1) {
    f32 temp_fs0;
    f32 temp_fs0_2;
    f32 temp_fv0;

    temp_fs0 = arg1 * D_800307B0;
    temp_fs0_2 = sinf(temp_fs0);
    temp_fv0 = cosf(temp_fs0);
    *(f32 *)((u8 *)arg0 + 0x20) = temp_fs0_2;
    *(f32 *)((u8 *)arg0 + 0) = temp_fv0;
    *(s32 *)((u8 *)arg0 + 4) = 0;
    *(s32 *)((u8 *)arg0 + 0xC) = 0;
    *(s32 *)((u8 *)arg0 + 0x10) = 0;
    *(s32 *)((u8 *)arg0 + 0x18) = 0;
    *(s32 *)((u8 *)arg0 + 0x1C) = 0;
    *(s32 *)((u8 *)arg0 + 0x24) = 0;
    *(f32 *)((u8 *)arg0 + 0x28) = temp_fv0;
    *(s32 *)((u8 *)arg0 + 0x2C) = 0;
    *(s32 *)((u8 *)arg0 + 0x30) = 0;
    *(s32 *)((u8 *)arg0 + 0x34) = 0;
    *(s32 *)((u8 *)arg0 + 0x38) = 0;
    *(f32 *)((u8 *)arg0 + 8) = (f32) -temp_fs0_2;
    *(f32 *)((u8 *)arg0 + 0x14) = 1.0f;
    *(f32 *)((u8 *)arg0 + 0x3C) = 1.0f;
}
