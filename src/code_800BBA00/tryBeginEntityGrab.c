/* @header
 * tryBeginEntityGrab  (originally func_800DB72C)
 * VRAM 0x800DB72C | ROM 0xCEBCC | size 0x148
 * asm: asm/nonmatchings/code_800BBA00/tryBeginEntityGrab.s
 */
#include "common.h"

s8 func_800D7B54(void *, s32, s32, s32);
void func_800C4610(Wrestler *, Wrestler *);
void playEntitySound(s8, s32);

/* Called with a candidate `target` of `attacker`'s move (func_800DB4FC, func_800DDAC8, which give up on the target
 * when this returns 1). Returns 1 when the target starts its own action (state 0x5C or 0x40), else 0.
 * func_800C4610(attacker, target) first sets target flag bit 0x8000000 when the attacker's steered heading is within
 * 0x400 of the target's heading (also setting hitInfo bit 0x1000). Returns 0 when the target is the attacker's tag
 * partner. With bit 0x8000000 set: needs func_800D7B54(target, 0, 0, 2) (target's counter roll: D_800F9830[id] bits 1
 * and 8 set, fewer than 3 hits counted in D_800F9828[id], no flag bit 0x1 / 0x8, then a func_800B71F8 chance roll),
 * then plays sound 0x12C and puts the target in state 0x5C. Otherwise the same check is needed unless the target is
 * already in state 0x40 with stateTimer < 3, and the target's flags must not have bit 0x1 or 0x8; then it plays
 * sound 0x12C, links the two (target->opponentId = attacker, attacker->heldById = attacker->opponentId = target),
 * puts the target in state 0x40 and sets its step to 3. */
s32 tryBeginEntityGrab(Wrestler *target, Wrestler *attacker) {
    func_800C4610(attacker, target);
    if (attacker->partnerId == target->id) {
        return 0;
    }
    if (target->flags & 0x8000000LL) {
        if (!func_800D7B54(target, 0, 0, 2)) {
            return 0;
        }
        playEntitySound(target->id, 0x12C);
        func_800A6C48(target, 0x5C);
        return 1;
    }
    if (!(target->state == 0x40 && target->stateTimer < 3)) {
        if (!func_800D7B54(target, 0, 0, 2)) {
            return 0;
        }
    }
    if (target->flags & 9) {
        return 0;
    }
    playEntitySound(target->id, 0x12C);
    target->opponentId = attacker->id;
    attacker->heldById = target->id;
    attacker->opponentId = target->id;
    func_800A6C48(target, 0x40);
    target->step = 3;
    return 1;
}
