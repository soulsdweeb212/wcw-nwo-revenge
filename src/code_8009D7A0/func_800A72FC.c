#include "common.h"

void func_800D3838(s32, s32, s16, s32);

/* Forwards the entity's local position and the given parameters to
 * func_800D3838. */
void func_800A72FC(s32 arg0, s32 arg1, s32 arg2) {
    func_800D3838(arg0 + 0x6C, arg1, arg2, arg0 + 0x33C);
}

void func_800D36B4(void *, void *, void *);
void translateEntityXZ(void *, void *);

/* Translates the entity by the delta between its +0x4C and +0x6C positions. */
void func_800A7328(u8 *arg0) {
    u8 sp10[0x10];

    func_800D36B4(arg0 + 0x4C, arg0 + 0x6C, sp10);
    translateEntityXZ(arg0, sp10);
}

/* Copies the entity's X/Z (from +0x6C/+0x74) to +0x4C/+0x54, then clamps the
 * facing-quadrant (+0x3C) axis to the ring edge (+/-265). */
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

/* Turns the entity's heading (+0x58) toward arg1 by up to arg2, OR-ing arg4 into
 * the +0x20 flags and arg5 into the +0x24 flags when the angle is reached.
 * Returns 1 when it snapped to arg1. */
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
