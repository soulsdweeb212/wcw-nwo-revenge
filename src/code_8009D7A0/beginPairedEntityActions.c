/* @header
 * beginPairedEntityActions  (originally func_800A6E44)
 * VRAM 0x800A6E44 | ROM 0x9A2E4 | size 0x1C8
 * asm: asm/nonmatchings/code_8009D7A0/beginPairedEntityActions.s
 */
#include "common.h"

/* Start a matched pair of states: put each wrestler in its new state (step, stepFlags and pairSignals cleared, flag
 * bits 0x10800000000 and WR_FLAG_RERUN cleared, 0x1000000000 set, func_800DECAC(w, 0, 0, 0) which only zeroes the
 * slot's D_800F98D0 counter), clear its attached[] slots and WR_FLAG_PAIR_LEADER, and unlink it from every record's
 * attached[] (func_800A700C). Then self leads the pair: self gets WR_FLAG_PAIR_LEADER | WR_FLAG_UPDATED, other
 * WR_FLAG_UPDATED (both also 0x1000000000); self->attached[0] = other, self->heldById = -1, each becomes the other's
 * opponentId, and other->heldById = self. */
void beginPairedEntityActions(Wrestler *self, s16 selfAction, Wrestler *other, s16 otherAction) {
    self->state = selfAction;
    self->step = 0; self->stepFlags = 0; self->pairSignals = 0;
    self->flags = (self->flags & ~0x10810000000ULL) | 0x1000000000ULL;
    func_800DECAC(self, 0, 0, 0);
    self->attached[0] = -1; self->attached[1] = -1;
    self->flags &= ~WR_FLAG_PAIR_LEADER;
    other->state = otherAction;
    other->step = 0; other->stepFlags = 0; other->pairSignals = 0;
    other->flags = (other->flags & ~0x10810000000ULL) | 0x1000000000ULL;
    func_800DECAC(other, 0, 0, 0);
    other->attached[0] = -1; other->attached[1] = -1;
    other->flags &= ~WR_FLAG_PAIR_LEADER;
    func_800A700C(self); func_800A700C(other);
    self->flags |= 0x1000000000ULL | WR_FLAG_PAIR_LEADER | WR_FLAG_UPDATED;
    other->flags |= 0x1000000000ULL | WR_FLAG_UPDATED;
    self->attached[0] = other->id;
    self->heldById = -1;
    self->opponentId = other->id;
    other->opponentId = self->id;
    other->heldById = self->id;
}
