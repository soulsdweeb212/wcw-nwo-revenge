#include "common.h"

s32 func_800D2CAC(void *, void *, void *, f32, void *, void *, void *, u16, s32, u16);

/* Boundary-correction wrapper (entity, two linked entities, optional buffer,
 * divisor) with the apply flag set. */
s32 func_800D2C2C(void *arg0, void *arg1, void *arg2, f32 arg3, void *arg4, s32 arg5) {
    return func_800D2CAC(arg0, arg1, arg2, arg3, NULL, NULL, arg4, 0, arg5, 1);
}
/* Boundary-correction wrapper (entity, linked entity, divisor, optional position
 * and attachment) with the apply flag set. */
s32 func_800D2C68(void *arg0, void *arg1, f32 arg2, void *arg3, s32 arg4) {
    return func_800D2CAC(arg0, arg1, NULL, arg2, NULL, arg3, NULL, 0, arg4, 1);
}
/* Boundary-correction wrapper taking the divisor as raw float bits in arg3 and
 * using the entity's +0x368 as the position. */
void func_800D2BEC(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    union { s32 i; f32 f; } scale;
    scale.i = arg3;
    func_800D2CAC(arg0, (void *)arg1, (void *)arg2, scale.f, (u8 *)arg0 + 0x368, NULL, NULL, (u16)arg4, arg5, 1);
}
/* Boundary-correction wrapper (entity, linked entity, divisor, body-part mask)
 * with the apply flag set. */
s32 func_800D2BAC(void *arg0, void *arg1, f32 arg2, s32 arg3) {
    return func_800D2CAC(arg0, arg1, NULL, arg2, NULL, NULL, NULL, 0, arg3, 1);
}
