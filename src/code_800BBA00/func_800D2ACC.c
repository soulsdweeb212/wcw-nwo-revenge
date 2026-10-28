#include "common.h"

void translateEntityXZ(void *, void *);
s8 func_800D2758(void *, void *, void *, s8, s32);
f32 func_800D63F0(void *, void *, s32);
void *func_800D6610(void *, s16);
void func_800D37C0(void *, f32, void *);
extern void *D_800E3C90[];
/* Moves the entity by arg2, runs boundary correction, then moves it back. */
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
