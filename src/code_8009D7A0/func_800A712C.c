#include "common.h"

s32 func_800D36E8(f32, f32);
void unpackAnimationParameters(void *, void *);
extern u8 D_8007BD64[];
void func_800D4AD0(void *);
void func_800DECAC(void *, s32, s32, s32);
void func_800D3890(void *, void *, void *);

/* Four-way XZ heading (4096 units per turn) from a float vector. */
s32 getXZDirectionQuadrant(f32 *arg0) {
    return ((func_800D36E8(arg0[0], arg0[2]) + 0x1200) / 0x400) & 3;
}
/* Select animation `arg1`: store it, latch the entity's type byte, and unpack the
 * animation metadata for that id. */
void func_800A7D1C(void *arg0, s16 arg1) {
    *(s16 *)((u8 *)arg0 + 0x386) = arg1;
    *((u8 *)arg0 + 0x384) = *(u8 *)arg0;
    unpackAnimationParameters((u8 *)arg0 + 0x38C, D_8007BD64 + 0x14 + arg1 * 0x18);
}
/* If the entity's timer (+4) has just reached 1, reset it to action state 0x2B and
 * return 1; otherwise return 0. */
s32 func_800A7188(void *arg0) {
    s32 result = 0;
    if (*(s16 *)((u8 *)arg0 + 4) == 1) {
        func_800D4AD0(arg0);
        *(s16 *)((u8 *)arg0 + 0xA) = 0x2B;
        *(s16 *)((u8 *)arg0 + 0xC) = 0;
        *(s16 *)((u8 *)arg0 + 0xE) = 0;
        *(s16 *)((u8 *)arg0 + 0x360) = 0;
        *(u64 *)((u8 *)arg0 + 0x20) = (*(u64 *)((u8 *)arg0 + 0x20) & ~0x10810000000ULL) | 0x1000000000ULL;
        func_800DECAC(arg0, 0, 0, 0);
        result = 1;
        *(u64 *)((u8 *)arg0 + 0x20) |= 0x10000000ULL;
    }
    return result;
}
/* Compute the direction result from arg0's and arg1's positions; optionally return
 * the angle through arg2 and the Y component through arg3. */
void func_800A712C(void *arg0, void *arg1, s32 *arg2, f32 *arg3) {
    struct { f32 x, y, z; s32 angle; } result;
    func_800D3890((u8 *)arg0 + 0x6C, (u8 *)arg1 + 0x6C, &result);
    if (arg2 != NULL) *arg2 = result.angle;
    if (arg3 != NULL) *arg3 = result.y;
}
