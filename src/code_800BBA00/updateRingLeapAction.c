/* @header
 * updateRingLeapAction  (originally func_800C9B5C)
 * VRAM 0x800C9B5C | ROM 0xBCFFC | size 0x5B8
 * asm: asm/nonmatchings/code_800BBA00/updateRingLeapAction.s
 */
#include "common.h"

/* updateRingLeapAction: paired-entity "leap toward the ring" action, a six-state
 * machine driven by D_800FAF5C->step.  State 0 picks an animation; state 1 chooses a
 * quadrant (dirIndex)/launch vector toward the ring boundary and computes the heading delta
 * stored in D_800EB560; states 2-5 play the animation, apply boundary correction
 * and the quadratic spline step, and finish by setting the input bits on
 * D_800F9B00->pairSignals. */

/* The 64-bit flag word at +0x38 of the character profile (Wrestler.profile). */
typedef struct { u8 p[0x38]; u64 flags; } Nw2RingLeapAttachment;
extern s32 D_800F9B14;
extern s8 D_800FADB8;
extern s32 D_800EB560[];
extern u8 D_800FACF8[];
s32 func_800D3684(s32, s32);
s32 func_800D3550(s32);
s32 func_800D35B0(s32, s32);
void func_800D3E40(void *, f32 *, s32, void *);
void func_800D7128(void *, void *, void *, void *);
s8 stepEntityXZQuadraticSpline(void *, void *);
s8 func_800A7240(void *, s32, s32, u64);
void func_800D427C(void *, s16, s32);

void updateRingLeapAction(void) {
    f32 moveVec[4];
    f32 splineOut[4];
    s16 animId;
    s32 facing;
    s16 quadrant;
    s16 done;
    s32 angleDelta;
    s32 quad;

    switch (D_800FAF5C->step) {
    case 0:
        animId = (D_800FAF5C->flags & 0x200000000000000ULL) ? 0xF3A : 0xFB9;
        func_800D427C(D_800FAF5C, animId, 3);
        D_800FAF5C->step++;
        break;
    case 1: {
        Wrestler *b = D_800F9B00;
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
        D_800FAF5C->dirIndex = quad;
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
        func_800D3E40(&D_800F9B00->x, moveVec, D_800F9B00->heading, splineOut);
        func_800D7128(D_800F9B00, D_800FAF5C, splineOut, D_800FACF8 + D_800FADB8 * 0x30);
        D_800FAF5C->step++;
    }
    case 2:
        func_800D2C68(D_800FAF5C, D_800F9B00, 4.0f, D_800FACF8 + D_800FADB8 * 0x30, 0xFFFFE);
        done = stepEntityXZQuadraticSpline(D_800FAF5C, D_800FACF8 + D_800FADB8 * 0x30);
        done += (s8)func_800A7240(D_800FAF5C, D_800EB560[D_800FADB8], 0x71, 0ULL);
        if (done == 2 && D_800FAF5C->animFramesLeft <= 0) {
            if (D_800F9B00->flags & 0x200000ULL) {
                func_800D427C(D_800FAF5C, D_800FAF5C->dirIndex * 2 + 0xF63, 0);
                D_800F9B00->pairSignals |= 1;
                D_800FAF5C->step++;
            } else {
                D_800FAF5C->step = 4;
                D_800FAF5C->flags |= WR_FLAG_RERUN;
            }
        }
        break;
    case 3: {
        Wrestler *o = D_800FAF5C;
        if (o->animFramesLeft <= 0) {
            o->flags |= WR_FLAG_RERUN;
            o->step++;
        }
    } break;
    case 4:
        D_800F9B00->pairSignals |= 2;
        animId = D_800FAF5C->dirIndex * 10 + 0xF73;
        switch (D_800FAF5C->dirIndex) {
        case 1:
            if (((Nw2RingLeapAttachment *)D_800FAF5C->profile)->flags & 0x4000000ULL)
                animId = 0xF9B;
            break;
        case 3:
            if (((Nw2RingLeapAttachment *)D_800FAF5C->profile)->flags & 0x8000000ULL)
                animId = 0xFA5;
            break;
        }
        func_800D427C(D_800FAF5C, animId, 0);
        D_800FAF5C->step++;
        break;
    case 5:
        func_800D2BAC(D_800FAF5C, D_800F9B00, 4.0f, 0xFFFFE);
        if (D_800FAF5C->animFramesLeft <= 0) {
            D_800F9B00->pairSignals |= 4;
            func_800A6C48(D_800FAF5C, 0x38);
        }
        break;
    }
}
