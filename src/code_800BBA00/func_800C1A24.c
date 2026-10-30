/* @header
 * func_800C1A24
 * VRAM 0x800C1A24 | ROM 0xB4EC4 | size 0x3A8
 * asm: asm/nonmatchings/code_800BBA00/func_800C1A24.s
 */
#include "common.h"

typedef struct {
    u8 pad0[4];
    s16 f4;
    s16 f6;
    s16 f8;
    s16 fA;
    s16 fC;
    u8 padE[0x12];
    u64 flags;
    u8 pad28[0x16];
    s16 f3E;
    u8 pad40[0xC];
    f32 f4C;
    f32 f50;
    f32 f54;
    s32 f58;
    u8 pad5C[0x10];
    f32 f6C;
    f32 f70;
    f32 f74;
    u8 pad78[0x2C4];
    f32 f33C;
    u8 pad340[4];
    f32 f344;
    s32 f348;
    u8 pad34C[0x20];
    u8 f36C;
} Nw2Obj1A24;

#define ACTOR ((Nw2Obj1A24 *)D_800FAF5C)

extern s32 D_800E3C90[];
extern f64 D_800E58F0;
extern f64 D_800E58F8;
extern f64 D_800E5900;
extern f64 D_800E5908;
extern void *D_800FAF5C;
s32 func_800D35B0(s32, s32);
s32 func_800D3684(s32, s32);
void func_800D427C(void *, s32, s32);
void func_800D4AD0(void *);
void func_800D2B64(void *, f32, u16, s32);
void beginEntityActionA8D8C(void *);
void translateEntityXZ(void *, void *);

/* Four-step dodge-roll state machine on ACTOR->fC (+0xC).  Step 0 computes the
 * facing quadrant (f3E) from the XZ vector at f4C and selects a side-step
 * animation id (0xF1E/0xF20, or 0xF1D|0xF1F branchless).  Step 1 picks the
 * lateral direction mask from D_800E3C90[(f3E +/- 1) & 3] and derives a
 * per-frame heading increment (f348) and per-frame displacement (f33C on one
 * axis, f344 on the other) from the f64 goal constants, all divided by the step
 * count f36C.  Step 2 slides the entity (translateEntityXZ) until the s16 timer
 * f4 expires, then steps to the next animation frame.  Step 3 finishes. */
void func_800C1A24(void)
{
    s32 animCmd;
    s32 aimHeading;

    switch (ACTOR->fC) {
    case 0:
        ACTOR->f3E = getXZDirectionQuadrant(&ACTOR->f4C);
        aimHeading = func_800D3684(ACTOR->f58, D_800E3C90[ACTOR->f3E]);
        if (ACTOR->flags & 0x200000ULL) {
            if (aimHeading > 0) {
                animCmd = 0xF1E;
            } else {
                animCmd = 0xF20;
            }
        } else {
            animCmd = (-(aimHeading > 0) & 0xF1F) | 0xF1D;
        }
        func_800D427C(D_800FAF5C, (s16)animCmd, 6);
        ACTOR->fC++;
        break;
    case 1:
        func_800D2B64(D_800FAF5C, 2.0f, 0, 0xFFFFE);
        if (ACTOR->f4 > 0) {
            return;
        }
        if (!(ACTOR->flags & 0x200000ULL)) {
            ACTOR->f58 = func_800D35B0(ACTOR->f58, 0x800);
        }
        func_800D4AD0(D_800FAF5C);
        if (ACTOR->f8 >= 0xF1D) {
            if (ACTOR->f8 < 0xF1F) {
                animCmd = 0xF21;
                aimHeading = D_800E3C90[(ACTOR->f3E + 1) & 3];
            } else if (ACTOR->f8 < 0xF21) {
                animCmd = 0xF22;
                aimHeading = D_800E3C90[(ACTOR->f3E - 1) & 3];
            }
        }
        func_800D427C(D_800FAF5C, (s16)animCmd, 1);
        animCmd = ACTOR->f36C;
        ACTOR->f348 = func_800D3684(aimHeading, ACTOR->f58) / animCmd;
        switch (ACTOR->f3E) {
        case 0:
            ACTOR->f33C = 0.0f;
            ACTOR->f344 = (f32)((D_800E58F0 - (f64)ACTOR->f74) / (f64)animCmd);
            break;
        case 1:
            ACTOR->f344 = 0.0f;
            ACTOR->f33C = (f32)((D_800E58F8 - (f64)ACTOR->f6C) / (f64)animCmd);
            break;
        case 2:
            ACTOR->f33C = 0.0f;
            ACTOR->f344 = (f32)((D_800E5900 - (f64)ACTOR->f74) / (f64)animCmd);
            break;
        case 3:
            ACTOR->f344 = 0.0f;
            ACTOR->f33C = (f32)((D_800E5908 - (f64)ACTOR->f6C) / (f64)animCmd);
            break;
        }
        ACTOR->fC++;
        break;
    case 2:
        ACTOR->f58 = func_800D35B0(ACTOR->f58, ACTOR->f348);
        translateEntityXZ(D_800FAF5C, &ACTOR->f33C);
        func_800D2B64(D_800FAF5C, 2.0f, 0, 0xFFFFE);
        if (ACTOR->f4 > 0) {
            return;
        }
        func_800D427C(D_800FAF5C, (s16)((u16)ACTOR->f8 + 2), 1);
        ACTOR->fC++;
        break;
    case 3:
        if (ACTOR->f4 > 0) {
            return;
        }
        func_800D4AD0(D_800FAF5C);
        beginEntityActionA8D8C(D_800FAF5C);
        return;
    default:
        return;
    }
}
