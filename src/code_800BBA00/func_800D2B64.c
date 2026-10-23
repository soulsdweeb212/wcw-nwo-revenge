#include "common.h"

void translateEntityXZ(void *, void *);
s8 func_800D2758(void *, void *, void *, s8, s32);
f32 func_800D63F0(void *, void *, s32);
void *func_800D6610(void *, s16);
void func_800D37C0(void *, f32, void *);
extern void *D_800E3C90[];

/* Boundary-correction convenience wrapper with no auxiliary records. */
s32 func_800D2B64(void *arg0, f32 arg1, u16 arg2, s32 arg3) {
    return func_800D2CAC(arg0, NULL, NULL, arg1, NULL, NULL, NULL, arg2, arg3, 1);
}

/* Correct arg0 around the offset arg2, then restore the original position. */
s32 func_800D2ACC(void *arg0, s32 arg1, f32 *arg2) {
    f32 offset[4];
    s32 result;
    translateEntityXZ(arg0, arg2);
    result = func_800D2CAC(arg0, NULL, NULL, 1.0f, NULL, NULL, NULL, 0, arg1, 0);
    offset[0] = -arg2[0];
    offset[2] = -arg2[2];
    translateEntityXZ(arg0, offset);
    return result;
}

/* Correct arg0 by an optional direction record, then restore the position. */
s8 func_800D26A0(void *arg0, s32 arg1, s8 arg2) {
    Nw2DirectionResult offset;
    s8 result;
    if (arg1 == 0) {
        offset.x = 0.0f;
        offset.z = 0.0f;
    } else {
        offset = *(Nw2DirectionResult *)arg1;
    }
    translateEntityXZ(arg0, &offset);
    result = func_800D2758(arg0, NULL, NULL, arg2, 0);
    offset.x = -offset.x;
    offset.z = -offset.z;
    translateEntityXZ(arg0, &offset);
    return result;
}

/* Apply a facing-dependent offset to arg0 and arg1. */
void func_800D1EA8(void *arg0, void *arg1) {
    f32 offset[4];
    f32 scale;
    void *data;
    scale = func_800D63F0(arg0, offset, (*(u16 *)((u8 *)arg0 + 0x3AC) & 1) * 2);
    if (*(u32 *)((u8 *)arg0 + 0x3AC) & 0x1000) {
        data = func_800D6610(arg0, *(s16 *)((u8 *)arg0 + 0x3E));
    } else {
        data = D_800E3C90[*(s16 *)((u8 *)arg0 + 0x3E)];
    }
    func_800D37C0(data, scale, offset);
    translateEntityXZ(arg0, offset);
    translateEntityXZ(arg1, offset);
}
