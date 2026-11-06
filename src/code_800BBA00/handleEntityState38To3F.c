/* @header
 * handleEntityState38To3F  (originally func_800DB874)
 * VRAM 0x800DB874 | ROM 0xCED14 | size 0x30C
 * asm: asm/nonmatchings/code_800BBA00/handleEntityState38To3F.s
 */
#include "common.h"

/* Paired-wrestler action handler for target states 0x38..0x3F (subState = state - 0x38).
 * For the even subStates it just raises pairSignals bit 0x10 on the target; for the odd
 * subStates it raises it on the target's opponent instead. Otherwise it makes the
 * source the target's holder (and opponent), resolves facing via func_800C4610, and
 * selects an animation (func_800A6D80) based on the target flags and state. */
void func_800E212C(void *);
void func_800A837C(void *);
void func_800A6D80(void *, s32);
void func_800C4610(void *, void *);
void addEntityHealthDelta(void *, s16);
s8 func_800C472C(void *, void *, s32);

void handleEntityState38To3F(Wrestler *source, Wrestler *target)
{
    s16 subState;
    s16 i;

    source->comboHits = 0;
    subState = (u16)target->state - 0x38;
    switch (subState) {
    case 0: case 4: case 6:
        target->pairSignals |= 0x10;
        return;
    case 1: case 5: case 7:
        D_800F9D10[target->opponentId].pairSignals |= 0x10;
        return;
    }
    target->heldById = source->id;
    if (source->partnerId != target->id)
        target->opponentId = source->id;
    func_800E212C(target);
    func_800A837C(source);
    if (target->flags & 0x400000) {
        func_800A6C48(target, 0x57);
        return;
    }
    target->hitInfo = 0x800;
    func_800C4610(source, target);
    if (target->flags & 0x8000000)
        target->hitInfo |= 0x1000;
    if (target->state == 0x17)
        addEntityHealthDelta(target, -10);
    if (target->flags & WR_FLAG_ON_APRON)
        func_800A6D80(target, 0x62);
    else if (target->state == 0x74)
        target->pairSignals |= 4;
    else if (target->state == 0x75) {
        for (i = 0; i < 4; i++) {
            if (D_800F9D10[i].state == 0x74) {
                if (target->flags & 0x8000000)
                    D_800F9D10[i].flags |= 0x8000000;
                else
                    D_800F9D10[i].flags &= ~0x8000000ULL;
                D_800F9D10[i].pairSignals |= 0x10;
                target->opponentId = i;
                target->secondAttackerId = source->id;
                break;
            }
        }
    } else if (!func_800C472C(source, target, 0))
        func_800A6D80(target, 0x28);
}
