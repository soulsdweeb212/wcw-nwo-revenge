/* @header
 * func_800DD370
 * VRAM 0x800DD370 | ROM 0xD0810 | size 0x344
 * asm: asm/nonmatchings/code_800BBA00/func_800DD370.s
 */
#include "common.h"

extern s32 D_800E3F20[], D_800FABD8;
extern s8 D_800FADB8;

void func_800A7C40(void *, s8, s16);
void func_800A7D1C(void *, s32);
void func_800A7F6C(void *, s32);
void beginEntityActionA8D8C(void *);
void func_800B68A0(void *, void *, void *);
void addEntityHealthDelta(void *, s32);
void func_800D427C(void *, s16, s32);
void func_800D4AD0(void *);
s8 func_800D4CC4(void *);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D5438 */
s16 func_800D5438(void *, s32);
#endif
s32 func_800DACE4(void *, void *);
void func_800DB348(void *, void *);
s8 func_800DB4FC(void *, void *);
s8 isEntityActionEligible(void *, void *, s32);

/* Three-step close-combat action machine on self (D_800FAF5C) step.  Step 0
 * selects an animation id (0xE2/0xE3/0xE4/0xEA) from the opponent's state and
 * flags: an opponent carrying 0x600000000000 enters a per-state switch (0xE3 for
 * 0x38/39, 0xE2 or 0xE3 for 0x3C..3F depending on move flag 0x800000 of the
 * opponent or of its own opponent, 0xE2 for 0x72/73, 0xEA for 0x75 when its
 * step<3 and it is in the ring); otherwise isEntityActionEligible / flag
 * 0x400000 pick 0xE4/0xE3/0xE2.  It sends it via func_800A7C40, then runs
 * func_800D427C/func_800A7F6C/func_800DACE4 and advances.  Step 1 clears self's
 * D_800FABD8 bit and waits for func_800DB4FC, then falls into step 2, which
 * pumps func_800DB348 and when animFramesLeft runs out either runs the 0x23
 * attack (func_800A7D1C/func_800B68A0/func_800D4CC4/addEntityHealthDelta/
 * beginEntityActionA8D8C) or ends with func_800A6C48(0x2B). */
void func_800DD370(void) {
    Wrestler *self;
    s16 animId;
    s32 linkedField;

    switch (D_800FAF5C->step) {
    case 0:
        if (D_800F9B00->flags & 0x600000000000ULL) {
            animId = 0xE2;
            switch ((s16)(D_800F9B00->state - 0x38)) {
            case 0:
            case 1:
                animId = 0xE3;
                break;
            case 4:
            case 5:
            case 6:
            case 7:
                if (D_800F9B00->flags & 0x200000000000ULL) {
                    linkedField = D_800F9B00->move.flags;
                } else {
                    linkedField = D_800F9D10[D_800F9B00->opponentId].move.flags;
                }
                animId = (linkedField & 0x800000) ? 0xE2 : 0xE3;
                break;
            case 0x3A:
            case 0x3B:
                animId = 0xE2;
                break;
            case 0x3D:
                if (D_800F9B00->step < 3 && (D_800F9B00->flags & WR_FLAG_IN_RING)) {
                    animId = 0xEA;
                }
                break;
            }
        } else {
            if (isEntityActionEligible(D_800FAF5C, D_800F9B00, 0xE4)) {
                animId = 0xE4;
            } else if (D_800F9B00->flags & 0x400000) {
                animId = 0xE3;
            } else {
                animId = 0xE2;
            }
        }
        func_800A7C40(D_800FAF5C, D_800FADB8, animId);
        func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 0), 3);
        func_800A7F6C(D_800FAF5C, 0);
        func_800DACE4(D_800FAF5C, D_800F9B00);
        D_800FAF5C->step++;
        break;
    case 1:
        D_800FABD8 &= ~D_800E3F20[D_800FADB8];
        if (func_800DB4FC(D_800FAF5C, D_800F9B00)) {
            D_800FAF5C->step++;
        }
        /* fallthrough */
    case 2:
        func_800DB348(D_800FAF5C, D_800F9B00);
        if (D_800FAF5C->animFramesLeft <= 0) {
            func_800D4AD0(D_800FAF5C);
            self = D_800FAF5C;
            if (self->step == 1) {
                func_800A7D1C(self, 0x23);
                func_800B68A0(D_800FAF5C, D_800FAF5C, D_800FAF5C);
                if (func_800D4CC4(self)) {
                    addEntityHealthDelta(self, self->move.spiritOnFinish);
                }
                beginEntityActionA8D8C(self);
            } else {
                func_800A6C48(self, 0x2B);
            }
        }
        break;
    }
}
