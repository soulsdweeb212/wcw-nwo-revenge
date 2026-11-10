/* @header
 * updateEntityActionStateD1F50  (originally func_800D1F50)
 * VRAM 0x800D1F50 | ROM 0xC53F0 | size 0x290
 * asm: asm/nonmatchings/code_800BBA00/updateEntityActionStateD1F50.s
 */
#include "common.h"

/* Action state machine for self D_800FAF5C paired with the opponent
 * D_800F9B00 (switch on step):
 *  0 -> pair the two entities and enter the animation clip selected by
 *       grappleCtx 0x40 (0x58/0x59), then fall through;
 *  1 -> run the clip: when stateTimer reaches the per-slot duration table
 *       D_800EB620[id], set heading from D_800EB600[id] and either jump to
 *       step 7 (grappleCtx 0x100000) or advance via func_800CDEE4; otherwise
 *       keep moving (heading via turnPerTick, optional collision with 0x400);
 *  2 -> drive the paired interaction, and once animFramesLeft expires, if
 *       func_800A83DC signals completion, clear the pair-leader flag and end. */
extern s8 D_800FADB8;
extern s32 D_800EB600[];
extern s16 D_800EB620[];

void setupEntityMoveCD990(void *, void *);
void func_800A7C40(void *, s8, s16);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D5438 */
s16 func_800D5438(void *, s16);
#endif
void func_800D427C(void *, s16, s32);
void func_800A7F6C(void *, s32);
u16 func_800CDEE4(void *, void *);
s8 func_800A83DC(void *, void *);
void func_800B68A0(void *, void *, void *);
void func_800D4AD0(void *);
void translateEntityXZ(void *, void *);
s32 func_800D2BEC(void *, void *, void *, f32, u16, s32);

void updateEntityActionStateD1F50(void) {
    switch (D_800FAF5C->step) {
    case 0:
        setupEntityMoveCD990(D_800FAF5C, D_800F9B00);
        func_800A7C40(D_800FAF5C, D_800FADB8,
                ((D_800FAF5C->grappleCtx & 0x40) ? 0x59 : 0x58));
        func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 0), 2);
        func_800A7F6C(D_800FAF5C, 0);
        D_800FAF5C->step = D_800FAF5C->step + 1;
    case 1: {
        s16 advanced;
        Wrestler *ent = D_800FAF5C;
        Wrestler *other = D_800F9B00;
        if (ent->stateTimer >= D_800EB620[ent->id]) {
            ent->heading = D_800EB600[ent->id];
            if (ent->grappleCtx & 0x100000) {
                ent->step = 7;
            } else {
                ent->stateTimer = func_800CDEE4(ent, other);
            }
            advanced = 1;
        } else {
            translateEntityXZ(ent, ent->moveDelta);
            ent->heading = func_800D35B0(ent->heading, ent->turnPerTick);
            if (ent->grappleCtx & 0x400) {
                func_800D2BAC(ent, other, 4.0f, 0xFFFFE);
            }
            ent->stateTimer++;
            advanced = 0;
        }
        if (advanced) {
            D_800FAF5C->step = D_800FAF5C->step + 1;
        }
        break;
    }
    case 2:
        func_800D2BEC(D_800FAF5C, D_800F9B00, 0, 4.0f, 0, 0xFFFFE);
        if (D_800FAF5C->animFramesLeft == 1) {
            func_800B68A0(D_800FAF5C, D_800FAF5C, D_800F9B00);
        }
        if (D_800FAF5C->animFramesLeft <= 0) {
            Wrestler *ent;
            if (func_800A83DC(D_800FAF5C, D_800F9B00) == 0) {
                ent = D_800FAF5C;
                ent->attached[0] = -1;
                ent->flags &= ~WR_FLAG_PAIR_LEADER;
                func_800D4AD0(D_800FAF5C);
                func_800A6C48(D_800FAF5C, 0x2B);
            }
        }
        break;
    }
}
