#include "common.h"

s32 func_800D36E8(f32, f32);
void unpackAnimationParameters(void *, void *);
extern u8 D_8007BD64[];
void func_800D4AD0(void *);
void func_800DECAC(void *, s32, s32, s32);
void func_800D3890(void *, void *, void *);
/* Compute the direction result from arg0's and arg1's positions; optionally return
 * the angle through arg2 and the Y component through arg3. */
void func_800A712C(void *arg0, void *arg1, s32 *arg2, f32 *arg3) {
    struct { f32 x, y, z; s32 angle; } result;
    func_800D3890((u8 *)arg0 + 0x6C, (u8 *)arg1 + 0x6C, &result);
    if (arg2 != NULL) *arg2 = result.angle;
    if (arg3 != NULL) *arg3 = result.y;
}
