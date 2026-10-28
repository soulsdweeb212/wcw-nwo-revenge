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
