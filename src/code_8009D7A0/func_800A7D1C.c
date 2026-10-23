#include "common.h"

s32 func_800D36E8(f32, f32);
void unpackAnimationParameters(void *, void *);
extern u8 D_8007BD64[];
void func_800D4AD0(void *);
void func_800DECAC(void *, s32, s32, s32);
void func_800D3890(void *, void *, void *);

/* Four-way XZ heading from a three-float vector; 4096 angle units per turn. */
s32 getXZDirectionQuadrant(f32 *arg0) {
    return ((func_800D36E8(arg0[0], arg0[2]) + 0x1200) / 0x400) & 3;
}
/* Sets the entity's animation to arg1 and unpacks its parameters from the
 * 0x18-byte table entry. */
void func_800A7D1C(void *arg0, s16 arg1) {
    *(s16 *)((u8 *)arg0 + 0x386) = arg1;
    *((u8 *)arg0 + 0x384) = *(u8 *)arg0;
    unpackAnimationParameters((u8 *)arg0 + 0x38C, D_8007BD64 + 0x14 + arg1 * 0x18);
}
/* Resets the entity's action when its +4 counter is 1: clears the substate,
 * timer, anim and input words, replaces the 0x10810000000 flags with
 * 0x1000000000, resets the action variant and sets 0x10000000. Returns 1. */
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
/* Computes the heading and distance between arg0 and arg1, optionally returning
 * the angle in *arg2 and the distance in *arg3. */
void func_800A712C(void *arg0, void *arg1, s32 *arg2, f32 *arg3) {
    struct { f32 x, y, z; s32 angle; } result;
    func_800D3890((u8 *)arg0 + 0x6C, (u8 *)arg1 + 0x6C, &result);
    if (arg2 != NULL) *arg2 = result.angle;
    if (arg3 != NULL) *arg3 = result.y;
}
