/* @header
 * func_800C1A24
 * VRAM 0x800C1A24 | ROM 0xB4EC4 | size 0x3A8
 * asm: asm/nonmatchings/code_800BBA00/func_800C1A24.s
 */
#include "common.h"

extern s32 D_800E3C90[];
extern f64 D_800E58F0;
extern f64 D_800E58F8;
extern f64 D_800E5900;
extern f64 D_800E5908;
s32 func_800D35B0(s32, s32);
s32 func_800D3684(s32, s32);
void func_800D427C(void *, s32, s32);
void func_800D4AD0(void *);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D2B64 */
void func_800D2B64(void *, f32, u16, s32);
#endif
void beginEntityActionA8D8C(void *);
void translateEntityXZ(void *, void *);

/* Four-step dodge-roll state machine on D_800FAF5C->step.  Step 0 computes the
 * ring side (dirIndex) from the root position and selects a side-step
 * animation id (0xF1E/0xF20, or 0xF1D|0xF1F branchless).  Step 1 picks the
 * lateral direction from D_800E3C90[(dirIndex +/- 1) & 3] and derives a
 * per-frame heading increment (turnPerTick) and per-frame displacement
 * (moveDelta x on one axis, z on the other, measured from the pelvis) from the
 * f64 goal constants, all divided by anim.frameCount.  Step 2 slides the wrestler
 * (translateEntityXZ) until animFramesLeft expires, then steps to the next
 * animation.  Step 3 finishes. */
void func_800C1A24(void)
{
    s32 animCmd;
    s32 aimHeading;

    switch (D_800FAF5C->step) {
    case 0:
        D_800FAF5C->dirIndex = getXZDirectionQuadrant(&D_800FAF5C->x);
        aimHeading = func_800D3684(D_800FAF5C->heading, D_800E3C90[D_800FAF5C->dirIndex]);
        if (D_800FAF5C->flags & 0x200000ULL) {
            if (aimHeading > 0) {
                animCmd = 0xF1E;
            } else {
                animCmd = 0xF20;
            }
        } else {
            animCmd = (-(aimHeading > 0) & 0xF1F) | 0xF1D;
        }
        func_800D427C(D_800FAF5C, (s16)animCmd, 6);
        D_800FAF5C->step++;
        break;
    case 1:
        func_800D2B64(D_800FAF5C, 2.0f, 0, 0xFFFFE);
        if (D_800FAF5C->animFramesLeft > 0) {
            return;
        }
        if (!(D_800FAF5C->flags & 0x200000ULL)) {
            D_800FAF5C->heading = func_800D35B0(D_800FAF5C->heading, 0x800);
        }
        func_800D4AD0(D_800FAF5C);
        if (D_800FAF5C->animId >= 0xF1D) {
            if (D_800FAF5C->animId < 0xF1F) {
                animCmd = 0xF21;
                aimHeading = D_800E3C90[(D_800FAF5C->dirIndex + 1) & 3];
            } else if (D_800FAF5C->animId < 0xF21) {
                animCmd = 0xF22;
                aimHeading = D_800E3C90[(D_800FAF5C->dirIndex - 1) & 3];
            }
        }
        func_800D427C(D_800FAF5C, (s16)animCmd, 1);
        animCmd = D_800FAF5C->anim.frameCount;
        D_800FAF5C->turnPerTick = func_800D3684(aimHeading, D_800FAF5C->heading) / animCmd;
        switch (D_800FAF5C->dirIndex) {
        case 0:
            D_800FAF5C->moveDelta[0] = 0.0f;
            D_800FAF5C->moveDelta[2] = (f32)((D_800E58F0 - (f64)D_800FAF5C->jointA[1].z) / (f64)animCmd);
            break;
        case 1:
            D_800FAF5C->moveDelta[2] = 0.0f;
            D_800FAF5C->moveDelta[0] = (f32)((D_800E58F8 - (f64)D_800FAF5C->jointA[1].x) / (f64)animCmd);
            break;
        case 2:
            D_800FAF5C->moveDelta[0] = 0.0f;
            D_800FAF5C->moveDelta[2] = (f32)((D_800E5900 - (f64)D_800FAF5C->jointA[1].z) / (f64)animCmd);
            break;
        case 3:
            D_800FAF5C->moveDelta[2] = 0.0f;
            D_800FAF5C->moveDelta[0] = (f32)((D_800E5908 - (f64)D_800FAF5C->jointA[1].x) / (f64)animCmd);
            break;
        }
        D_800FAF5C->step++;
        break;
    case 2:
        D_800FAF5C->heading = func_800D35B0(D_800FAF5C->heading, D_800FAF5C->turnPerTick);
        translateEntityXZ(D_800FAF5C, &D_800FAF5C->moveDelta[0]);
        func_800D2B64(D_800FAF5C, 2.0f, 0, 0xFFFFE);
        if (D_800FAF5C->animFramesLeft > 0) {
            return;
        }
        func_800D427C(D_800FAF5C, (s16)((u16)D_800FAF5C->animId + 2), 1);
        D_800FAF5C->step++;
        break;
    case 3:
        if (D_800FAF5C->animFramesLeft > 0) {
            return;
        }
        func_800D4AD0(D_800FAF5C);
        beginEntityActionA8D8C(D_800FAF5C);
        return;
    default:
        return;
    }
}
