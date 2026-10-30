/* @header
 * updateRingLeapAction  (originally func_800C9B5C)
 * VRAM 0x800C9B5C | ROM 0xBCFFC | size 0x5B8
 * asm: asm/nonmatchings/code_800BBA00/func_800C9B5C.s
 */
#include "common.h"

/* updateRingLeapAction: paired-entity "leap toward the ring" action, a six-state
 * machine driven by D_800FAF5C->fC.  State 0 picks an animation; state 1 chooses a
 * quadrant/launch vector toward the ring boundary and computes the heading delta
 * stored in D_800EB560; states 2-5 play the animation, apply boundary correction
 * and the quadratic spline step, and finish by setting the input bits on
 * D_800F9B00->f360. */

typedef struct { s32 f0; s16 f4, f6, f8, fA, fC; u8 pE[0x12]; u64 flags; u8 p28[0x16]; s16 f3E; u8 p40[0x18]; s32 heading; u8 p5C[0x304]; u16 f360; s8 f362; u8 p363; void *f364; } Nw2RingLeapObj;
typedef struct { u8 p[0x38]; u64 flags; } Nw2RingLeapAttachment;
extern Nw2RingLeapObj *D_800FAF5C, *D_800F9B00;
extern s32 D_800F9B14;
extern s8 D_800FADB8;
extern s32 D_800EB560[];
extern u8 D_800FACF8[];
s32 func_800D3684(s32, s32);
s32 func_800D3550(s32);
s32 func_800D35B0(s32, s32);
void func_800D3E40(void *, f32 *, s32, void *);
void func_800D7128(void *, void *, void *, void *);
s32 func_800D2C68(void *, void *, f32, void *, s32);
s8 stepEntityXZQuadraticSpline(void *, void *);
s8 func_800A7240(void *, s32, s32, u64);
void func_800D427C(void *, s16, s32);
s32 func_800D2BAC(void *, void *, f32, s32);
void func_800A6C48(void *, s32);

void updateRingLeapAction(void) {
    f32 moveVec[4];
    f32 splineOut[4];
    s16 animId;
    s32 facing;
    s16 quadrant;
    s16 done;
    s32 angleDelta;
    s32 quad;

    switch (D_800FAF5C->fC) {
    case 0:
        animId = (D_800FAF5C->flags & 0x200000000000000ULL) ? 0xF3A : 0xFB9;
        func_800D427C(D_800FAF5C, animId, 3);
        D_800FAF5C->fC++;
        break;
    case 1: {
        Nw2RingLeapObj *b = D_800F9B00;
        angleDelta = func_800D3684(b->heading, D_800F9B14);
        if (func_800D3550(angleDelta) >= 0x601)
            quadrant = 2;
        else if (func_800D3550(angleDelta) < 0x200)
            quadrant = 0;
        else
            quadrant = (angleDelta >= 0) ? 3 : 1;
        if (b->flags & 0x200000ULL)
            quadrant = (quadrant + 2) & 3;
        quad = quadrant;
        D_800FAF5C->f3E = quad;
        switch (quad) {
        case 0: moveVec[0] = 0.0f; moveVec[2] = -130.0f; facing = 0; break;
        case 1: moveVec[0] = -100.0f; moveVec[2] = -25.0f; facing = 0x400; break;
        case 2: moveVec[0] = 0.0f; moveVec[2] = 150.0f; facing = 0x800; break;
        case 3: moveVec[0] = 100.0f; moveVec[2] = -25.0f; facing = -0x400; break;
        }
        D_800EB560[D_800FADB8] = func_800D35B0(facing, D_800F9B00->heading);
        if (D_800F9B00->flags & 0x200000ULL) {
            moveVec[0] = -moveVec[0];
            moveVec[2] = -moveVec[2];
            D_800EB560[D_800FADB8] = func_800D35B0(D_800EB560[D_800FADB8], 0x800);
        }
        func_800D3E40((u8 *)D_800F9B00 + 0x4C, moveVec, D_800F9B00->heading, splineOut);
        func_800D7128(D_800F9B00, D_800FAF5C, splineOut, D_800FACF8 + D_800FADB8 * 0x30);
        D_800FAF5C->fC++;
    }
    case 2:
        func_800D2C68(D_800FAF5C, D_800F9B00, 4.0f, D_800FACF8 + D_800FADB8 * 0x30, 0xFFFFE);
        done = stepEntityXZQuadraticSpline(D_800FAF5C, D_800FACF8 + D_800FADB8 * 0x30);
        done += (s8)func_800A7240(D_800FAF5C, D_800EB560[D_800FADB8], 0x71, 0ULL);
        if (done == 2 && D_800FAF5C->f4 <= 0) {
            if (D_800F9B00->flags & 0x200000ULL) {
                func_800D427C(D_800FAF5C, D_800FAF5C->f3E * 2 + 0xF63, 0);
                D_800F9B00->f360 |= 1;
                D_800FAF5C->fC++;
            } else {
                D_800FAF5C->fC = 4;
                D_800FAF5C->flags |= 0x10000000ULL;
            }
        }
        break;
    case 3: {
        Nw2RingLeapObj *o = D_800FAF5C;
        if (o->f4 <= 0) {
            o->flags |= 0x10000000ULL;
            o->fC++;
        }
    } break;
    case 4:
        D_800F9B00->f360 |= 2;
        animId = D_800FAF5C->f3E * 10 + 0xF73;
        switch (D_800FAF5C->f3E) {
        case 1:
            if (((Nw2RingLeapAttachment *)D_800FAF5C->f364)->flags & 0x4000000ULL)
                animId = 0xF9B;
            break;
        case 3:
            if (((Nw2RingLeapAttachment *)D_800FAF5C->f364)->flags & 0x8000000ULL)
                animId = 0xFA5;
            break;
        }
        func_800D427C(D_800FAF5C, animId, 0);
        D_800FAF5C->fC++;
        break;
    case 5:
        func_800D2BAC(D_800FAF5C, D_800F9B00, 4.0f, 0xFFFFE);
        if (D_800FAF5C->f4 <= 0) {
            D_800F9B00->f360 |= 4;
            func_800A6C48(D_800FAF5C, 0x38);
        }
        break;
    }
}
