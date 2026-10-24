#include "common.h"

#define FLAGS (*(u64 *)((u8 *)D_800FAF5C + 0x20))

extern u8 *D_800FAF5C;
extern s32 D_800F9B00;
extern s32 D_800F9B0C;
extern f64 D_800E5910;
s8 func_800D8DF0(void *);
void func_800A7240(void *, s32, s32, u64);
void func_800BF548(void *, s32);
void updateEntityStunTimer(void *, s32, s32);
void func_800D2670(void *, s32);
void func_800D2B64(void *, s32, s32, s32);
s16 findBoundaryQuadrant(void *, s32, s32);
s32 func_800D35B0(s32, s32);
void func_800D3890(void *, f32 *, void *);
void func_800D427C(void *, s16, s32);
s16 func_800D4D44(void *, s32, s32);
void func_800E212C(void *);
f32 func_800D63F0(void *, void *, s32);
void func_800D37C0(s32, f32, void *);
void translateEntityXZ(void *, void *);
s32 func_800D6610(void *, s16);

void func_800C1DCC(void) {
    f32 vec[3];
    Nw2DirectionResult res;
    s16 s0;
    s32 s1;
    s32 q;
    s32 dir;
    f32 fs;

    if (func_800D8DF0(D_800FAF5C) != 0) {
        func_800A6C48(D_800FAF5C, 1);
        return;
    }
    *(s16 *)(D_800FAF5C + 0x40) = 0;
    func_800BF548(D_800FAF5C, 1);
    updateEntityStunTimer(D_800FAF5C, D_800F9B00, 1);
    if (FLAGS & 0x40ULL) {
        func_800D427C(D_800FAF5C, func_800D4D44(D_800FAF5C, 0, D_800F9B0C), 3);
        q = getXZDirectionQuadrant((f32 *)(D_800FAF5C + 0x6C));
        if (FLAGS & 0x200000000ULL) {
            s0 = 0;
            s1 = ((s16)q == 0 || (s16)q == 3) ? -0xAA : 0xAA;
        } else {
            s0 = 2;
            s1 = ((s16)q == 0 || (s16)q == 3) ? 0xAA : -0xAA;
        }
        s1 = func_800D35B0(func_800D6610(D_800FAF5C, s0), s1);
        fs = func_800D63F0(D_800FAF5C, 0, 0);
        func_800D37C0(s1, fs, D_800FAF5C + 0x33C);
        translateEntityXZ(D_800FAF5C, D_800FAF5C + 0x33C);
        func_800A7240(D_800FAF5C, func_800D6610(D_800FAF5C, s0), 0x155, 0);
        func_800D2670(D_800FAF5C, 0x40000000);
        func_800D2B64(D_800FAF5C, 0x3F800000, 0, 2);
        if ((s16)findBoundaryQuadrant(D_800FAF5C, 0, 3) == s0) {
            *(s16 *)(D_800FAF5C + 0x3E) = (s16)q;
            func_800A6C48(D_800FAF5C, 0x60);
            func_800E212C(D_800FAF5C);
        }
    } else {
        if (FLAGS & 0x80ULL) {
            *(u16 *)(D_800FAF5C + 0x3E) = *(u16 *)(D_800FAF5C + 0x3C);
            func_800A6C48(D_800FAF5C, 0x60);
            return;
        }
        if (FLAGS & 0x100ULL) {
            func_800D427C(D_800FAF5C, func_800D4D44(D_800FAF5C, 0, D_800F9B0C), 3);
            dir = getXZDirectionQuadrant((f32 *)(D_800FAF5C + 0x4C));
            if (FLAGS & 0x200000000ULL) {
                switch ((s16)dir) {
                case 0:
                    vec[0] = 170.0f; vec[2] = 310.0f;
                    break;
                case 1:
                    vec[0] = 310.0f; vec[2] = 170.0f;
                    break;
                case 2:
                    vec[0] = 528.0f; vec[2] = -310.0f;
                    break;
                case 3:
                    vec[0] = -310.0f; vec[2] = 528.0f;
                    break;
                }
            } else {
                switch ((s16)dir) {
                case 0:
                    vec[0] = -528.0f; vec[2] = 310.0f;
                    break;
                case 1:
                    vec[0] = 310.0f; vec[2] = -528.0f;
                    break;
                case 2:
                    vec[0] = -170.0f; vec[2] = -310.0f;
                    break;
                case 3:
                    vec[0] = -310.0f; vec[2] = -170.0f;
                    break;
                }
            }
            func_800D3890(D_800FAF5C + 0x6C, vec, &res);
            if (!(FLAGS & 0x8000ULL) && (f64)res.y < D_800E5910) {
                *(s16 *)(D_800FAF5C + 0x3E) = dir;
                func_800A6C48(D_800FAF5C, 0x61);
                return;
            }
            fs = func_800D63F0(D_800FAF5C, 0, 0);
            func_800A7240(D_800FAF5C, res.angle, 0x155, 0);
            func_800D37C0(res.angle, fs, D_800FAF5C + 0x33C);
            translateEntityXZ(D_800FAF5C, D_800FAF5C + 0x33C);
            func_800D2670(D_800FAF5C, 0x40000000);
            func_800D2B64(D_800FAF5C, 0x3F800000, 0, 2);
        }
    }
}
