#include "common.h"

/* Translates entity arg0 and all of its 19 part records by the XZ delta arg1:
 * moves the root position (+0x4C/+0x54) and each part's two XZ pairs. */
void translateEntityXZ(void *arg0, void *arg1) {
    s16 temp_v0;
    s16 var_a2;
    void *temp_v1;

    *(f32 *)((u8 *)arg0 + 0x4C) = (f32) (*(f32 *)((u8 *)arg0 + 0x4C) + *(f32 *)((u8 *)arg1 + 0));
    var_a2 = 1;
    *(f32 *)((u8 *)arg0 + 0x54) = (f32) (*(f32 *)((u8 *)arg0 + 0x54) + *(f32 *)((u8 *)arg1 + 8));
    do {
        temp_v1 = (u8 *)arg0 + ((s32) (var_a2 << 0x10) >> 0xC);
        *(f32 *)((u8 *)temp_v1 + 0x5C) = (f32) (*(f32 *)((u8 *)temp_v1 + 0x5C) + *(f32 *)((u8 *)arg1 + 0));
        *(f32 *)((u8 *)temp_v1 + 0x64) = (f32) (*(f32 *)((u8 *)temp_v1 + 0x64) + *(f32 *)((u8 *)arg1 + 8));
        *(f32 *)((u8 *)temp_v1 + 0x1CC) = (f32) (*(f32 *)((u8 *)temp_v1 + 0x1CC) + *(f32 *)((u8 *)arg1 + 0));
        temp_v0 = var_a2 + 1;
        var_a2 = temp_v0;
        *(f32 *)((u8 *)temp_v1 + 0x1D4) = (f32) (*(f32 *)((u8 *)temp_v1 + 0x1D4) + *(f32 *)((u8 *)arg1 + 8));
    } while (temp_v0 < 0x14);
}
