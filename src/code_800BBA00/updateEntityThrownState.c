/* @header
 * updateEntityThrownState  (originally func_800BE4E0)
 * VRAM 0x800BE4E0 | ROM 0xB1980 | size 0x428
 * asm: asm/nonmatchings/code_800BBA00/updateEntityThrownState.s
 */
#include "common.h"

/* Entity thrown/knockback state machine (steps 0..4). The wrestler
 * D_800FAF5C is thrown by its opponent D_800F9B00: it runs the throw
 * hip-check (updateEntityBoundaryFlags/func_800BF018), plays the throw animation, moves
 * along its trajectory vector (moveDelta) via translateEntityXZ, then clears the
 * pair-leader flag and attached[0] and frees the display object. */
extern s8 D_800FADB8;
extern u16 D_800FAF8E[];
extern s32 D_800E3C90[];

s8 updateEntityBoundaryFlags(void *, void *, u16 *);
s16 func_800BF018(void *, void *, u16);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800BF150 */
s8 func_800BF150(void *, void *);
#endif
void func_800D8D74(void *, void *);
s16 func_800D7A2C(u16);
void func_800D7E80(void *, s32);
void func_800D37C0(s32, f32, void *);
f32 func_800D63F0(void *, void *, s32);
void translateEntityXZ(void *, void *);
s32 func_800D35B0(s32, s32);
void func_800D427C(void *, s16, s32);
void func_800A7F6C(void *, s32);
void func_800A837C(void *);
void func_800D4AD0(void *);
void beginEntityActionA8D8C(void *);

void updateEntityThrownState(void)
{
    Wrestler *ent;
    switch (D_800FAF5C->step) {
    case 0:
        if (D_800FAF5C->state == 0xD) {
            D_800FAF5C->dirIndex = D_800F9B00->ringSide;
        } else {
            D_800FAF5C->dirIndex = D_800FAF5C->ringSide;
        }
        if (updateEntityBoundaryFlags(D_800FAF5C, D_800F9B00, &D_800FAF8E[D_800FADB8]) << 24) {
            D_800FAF5C->pairSignals |= 1;
        }
        {
            s16 anim = (D_800FAF5C->state == 0xD) ? 0x10DF : 0x10EF;
            if (D_800FAF5C->pairSignals & 1) {
                anim += 8;
            }
            func_800D427C(D_800FAF5C, anim, 2);
        }
        func_800D7E80(D_800FAF5C, 0);
        D_800FAF5C->step++;
        return;
    case 1:
        func_800D8D74(D_800FAF5C, D_800F9B00);
        if (D_800FAF5C->animFramesLeft > 0) {
            return;
        }
        D_800FAF5C->heading = func_800D35B0(D_800FAF5C->heading, ((D_800FAF5C->pairSignals & 1) ? 0 : -0x400) | 0x400);
        func_800D427C(D_800FAF5C, (s16)(D_800FAF5C->animId + 2), 1);
        func_800D37C0(D_800E3C90[func_800D7A2C(D_800FAF8E[D_800FADB8])], func_800D63F0(D_800FAF5C, NULL, 5), D_800FAF5C->moveDelta);
        D_800FAF5C->step++;
        return;
    case 2:
        translateEntityXZ(D_800FAF5C, D_800FAF5C->moveDelta);
        translateEntityXZ(D_800F9B00, D_800FAF5C->moveDelta);
        {
            s16 r = func_800BF018(D_800FAF5C, D_800F9B00, D_800FAF8E[D_800FADB8]);
            if (r != 0) {
                if (r == 1) {
                    D_800FAF5C->pairSignals |= 2;
                } else {
                    D_800FAF5C->pairSignals |= 4;
                }
            }
        }
#ifdef TARGET_PC
        /* func_800BF150 reads the id byte that its second argument points to; the N64 code passes the opponent's
         * record, whose id is at offset 0. On PC the call passes &D_800F9B00->id, the same address, with the s8 *
         * type of port_decls.h's declaration. The N64 code shifts the result left by 24 to test its low byte; the PC
         * tests the same byte as an s8 (the result is 0 or 1). */
        if ((s8)func_800BF150(D_800FAF5C, &D_800F9B00->id)) {
#else
        if (func_800BF150(D_800FAF5C, D_800F9B00) << 24) {
#endif
            D_800FAF5C->pairSignals |= 4;
        }
        if (D_800FAF5C->pairSignals & 2) {
            if (D_800F9B00->flags & 0x2000000ULL) {
                D_800FAF5C->pairSignals = (D_800FAF5C->pairSignals & 0xFFFD) | 4;
            } else {
                func_800D427C(D_800FAF5C, (s16)(D_800FAF5C->animId + 2), 3);
                D_800FAF5C->step++;
                return;
            }
        }
        if (D_800FAF5C->pairSignals & 4) {
            func_800D427C(D_800FAF5C, (s16)(D_800FAF5C->animId + 4), 3);
            D_800FAF5C->step += 2;
        }
        return;
    case 3:
        if (D_800FAF5C->animFramesLeft > 0) {
            return;
        }
        func_800A7F6C(D_800FAF5C, 0x53);
        func_800A837C(D_800FAF5C);
        func_800D4AD0(D_800FAF5C);
        func_800A6C48(D_800FAF5C, 0x2B);
        break;
    case 4:
        if (D_800FAF5C->animFramesLeft > 0) {
            return;
        }
        func_800D4AD0(D_800FAF5C);
        beginEntityActionA8D8C(D_800FAF5C);
        break;
    default:
        return;
    }
    ent = D_800FAF5C;
    ent->attached[0] = -1;
    ent->flags &= ~WR_FLAG_PAIR_LEADER;
}
