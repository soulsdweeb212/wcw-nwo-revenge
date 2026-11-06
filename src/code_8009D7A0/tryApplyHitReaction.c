/* @header
 * tryApplyHitReaction  (originally func_800AD454)
 * VRAM 0x800AD454 | ROM 0xA08F4 | size 0x120
 * asm: asm/nonmatchings/code_8009D7A0/tryApplyHitReaction.s
 */
#include "common.h"

extern s16 D_800EB420[];
void func_800A7C40(Wrestler *, s8, s16);
s32 func_800A8D14(Wrestler *, Wrestler *);
s8 func_800D4198(s16);

/* attacker = the opponent (D_800F9B00), victim = the wrestler being updated (D_800FAF5C).
 *
 * When attacker->animFrame is on one of the two frames before attacker->anim.hitEnd, attacker->move.flags has 0x1,
 * victim->flags has neither 0x1 nor 0x8, arg3 has 0x10, and attacker->grappleCtx 0x1 is clear or the random check
 * func_800D4198(250) passes: set 0x2 in victim->pairSignals and give the victim a move from the
 * attacker's move table (func_800A7C40): entry attacker->moveId + 1 when D_800EB420[attacker->id] is set or
 * attacker->grappleCtx has bit 0x400000, else func_800A8D14(attacker, victim) - 2 (moveId - 1 .. moveId + 2). */
void tryApplyHitReaction(Wrestler *attacker, Wrestler *victim, s32 arg2, s32 arg3) {
    s16 animFrame;
    u8 animLimit;
    animLimit = attacker->anim.hitEnd;
    animFrame = attacker->animFrame;
    if (animFrame >= animLimit - 2 && animFrame < animLimit &&
        (attacker->move.flags & 1) && !(victim->flags & 9) && (arg3 & 0x10) &&
        (!(attacker->grappleCtx & 1) || func_800D4198(250))) {
        victim->pairSignals |= 2;
        if (D_800EB420[attacker->id] || (attacker->grappleCtx & 0x400000)) {
            func_800A7C40(victim, attacker->id, attacker->moveId + 1);
        } else {
            s16 reaction = func_800A8D14(attacker, victim) - 2;
            func_800A7C40(victim, attacker->id, reaction);
        }
    }
}
