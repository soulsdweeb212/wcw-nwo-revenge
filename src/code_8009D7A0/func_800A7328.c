#include "common.h"

void func_800D3838(s32, s32, s16, s32);

/* Write the XZ difference between arg1 and arg0+0x6C (scaled by arg2) into
 * arg0+0x33C. */
void func_800A72FC(s32 arg0, s32 arg1, s32 arg2) {
    func_800D3838(arg0 + 0x6C, arg1, arg2, arg0 + 0x33C);
}

void func_800D36B4(void *, void *, void *);
void translateEntityXZ(void *, void *);

/* Transform the entity's local offset (+0x4C) by its position and apply it. */
void func_800A7328(u8 *arg0) {
    u8 sp10[0x10];

    func_800D36B4(arg0 + 0x4C, arg0 + 0x6C, sp10);
    translateEntityXZ(arg0, sp10);
}

/* Snap the entity's XZ to the +/-265 ring edge selected by its quadrant (+0x3C). */
void func_800A7364(u8 *arg0) {
    f32 a = *(f32 *)(arg0 + 0x6C);
    f32 b = *(f32 *)(arg0 + 0x74);
    s16 t = *(s16 *)(arg0 + 0x3C);

    *(f32 *)(arg0 + 0x4C) = a;
    *(f32 *)(arg0 + 0x54) = b;
    switch (t) {
    case 0:
        *(f32 *)(arg0 + 0x54) = 265.0f;
        break;
    case 1:
        *(f32 *)(arg0 + 0x4C) = 265.0f;
        break;
    case 2:
        *(f32 *)(arg0 + 0x54) = -265.0f;
        break;
    case 3:
        *(f32 *)(arg0 + 0x4C) = -265.0f;
        break;
    }
}

s32 func_800D3550(s32);
s32 func_800D35B0(s32, s32);
s32 func_800D3684(s32, s32);

/* Turn the entity's heading toward arg1 within arg2, setting flags arg4/arg5 on
 * arrival; returns 1 when it arrives. */
s32 func_800A7240(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 temp_v0;
    s32 var_s0;

    temp_v0 = func_800D3684(arg1, *(s32 *)((u8 *)arg0 + 0x58));
    if (func_800D3550(temp_v0) < arg2) {
        *(s32 *)((u8 *)arg0 + 0x58) = arg1;
        *(s32 *)((u8 *)arg0 + 0x20) |= arg4;
        *(s32 *)((u8 *)arg0 + 0x24) |= arg5;
        return 1;
    }
    var_s0 = arg2;
    if (temp_v0 < 0) {
        var_s0 = -arg2;
    }
    *(s32 *)((u8 *)arg0 + 0x58) = func_800D35B0(*(s32 *)((u8 *)arg0 + 0x58), var_s0);
    return 0;
}
