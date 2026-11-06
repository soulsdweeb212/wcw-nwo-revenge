/* @header
 * updateEntityCounterAttackState  (originally func_800CA2FC)
 * VRAM 0x800CA2FC | ROM 0xBD79C | size 0x45C
 * asm: asm/nonmatchings/code_800BBA00/updateEntityCounterAttackState.s
 */
#include "common.h"

/* Paired counter-attack state machine (steps 0..3) for self (D_800FAF5C)
 * reacting to its opponent (D_800F9B00). It selects the counter animation from
 * the pairSignals/opponent flag bits, aligns to the target with
 * func_800D2BAC/func_800D2BEC, and in step 3 picks dirIndex from self's heading
 * relative to the opponent's (func_800D3684) before playing the counter animation. */
extern u16 D_800FAF8A;

void func_800A7C40(void *, s8, s16);
s16 func_800D5438(void *, s32);
void func_800D427C(void *, s16, s32);
s8 func_800A93C0(void);
s32 func_800D2BEC(void *, void *, void *, f32, u16, s32);
void func_800D4AD0(void *);
void func_800D36B4(void *, void *, f32 *);
void translateEntityXZ(void *, void *);
s32 func_800D35B0(s32, s32);
s32 func_800D3684(s32, s32);

void updateEntityCounterAttackState(void) {
    s16 animId;
    s32 dir;
    u32 f;
    f32 vec[4];

    switch (D_800FAF5C->step) {
    case 0:
        D_800FAF5C->flags |= 0x200000000000ULL;
        if (D_800FAF5C->state == 0x38) {
            func_800D427C(D_800FAF5C, D_800FAF5C->animId + 2, 0);
        } else {
            func_800A7C40(D_800FAF5C, D_800FAF5C->moveOwnerId, (s16)((s8)D_800FAF5C->move.unk3A7 + 0xEF));
            func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 0), 1);
        }
        D_800FAF5C->step++;
        break;
    case 1:
        D_800FAF5C->flags |= 0x200000000000ULL;
        func_800D2BAC(D_800FAF5C, D_800F9B00, 4.0f, 0xFFFFE);
        if ((D_800F9B00->flags & 0x8000) && !(D_800F9B00->flags & 0x10000)) {
            D_800FAF5C->pairSignals |= 8;
        }
        if (!(D_800FAF5C->pairSignals & 0x1F)) {
            if ((D_800FAF8A & 0x10) || func_800A93C0()) {
                D_800FAF5C->pairSignals |= 1;
                D_800F9B00->pairSignals |= 0x40;
            }
        }
        if (!(D_800FAF5C->animFramesLeft > 0 && (D_800FAF5C->pairSignals & 0x13) == 0)) {
            f = D_800FAF5C->pairSignals;
            if (f & 0x1F) {
                f |= 0x20;
                D_800FAF5C->pairSignals = f;
                if (f & 0x10) animId = 6;
                else if (f & 0x8) animId = 4;
                else animId = 2;
                if (D_800FAF5C->state == 0x38) animId = animId + D_800FAF5C->animId;
                else animId = func_800D5438(D_800FAF5C, animId);
                func_800D427C(D_800FAF5C, animId, 6);
                D_800FAF5C->step++;
            }
        }
        break;
    case 2: {
        Wrestler *ent;
        func_800D2BEC(D_800FAF5C, D_800F9B00, NULL, 2.0f, 0, 0xFFFFE);
        ent = D_800FAF5C;
        if (ent->animFramesLeft <= 0) {
            ent->attached[0] = -1;
            ent->flags &= ~WR_FLAG_PAIR_LEADER;
            func_800D4AD0(D_800FAF5C);
            func_800A6C48(D_800FAF5C, 0x2B);
        }
        break;
    }
    case 3:
        func_800D36B4(&D_800FAF5C->jointA[2], &D_800F9B00->jointA[2], vec);
        translateEntityXZ(D_800FAF5C, vec);
        if (D_800FAF5C->animFramesLeft > 0) break;
        func_800D4AD0(D_800FAF5C);
        if (D_800FAF5C->animId == 0x1BE4) D_800FAF5C->heading = func_800D35B0(D_800FAF5C->heading, 0x800);
        dir = func_800D3684(D_800F9B00->heading, D_800FAF5C->heading);
        if (dir < 0) D_800FAF5C->dirIndex = 1;
        else D_800FAF5C->dirIndex = 3;
        switch (D_800FAF5C->dirIndex) {
        case 1:
            animId = 0xF7F;
            break;
        case 3:
            animId = 0xFB1;
            break;
        }
        func_800D427C(D_800FAF5C, animId, 1);
        D_800FAF5C->step = 1;
        D_800FAF5C->flags |= WR_FLAG_RERUN;
        break;
    }
}
