/* @header
 * updateEntityPairInteraction  (originally func_800CCE50)
 * VRAM 0x800CCE50 | ROM 0xC02F0 | size 0x5A8
 * asm: asm/nonmatchings/code_800BBA00/updateEntityPairInteraction.s
 */
#include "common.h"

/* updateEntityPairInteraction: decides which paired action `self` (the wrestler being updated) starts on `other`.
 * Sets self->grappleCtx bit 0x40 when getEntityPairFacingFlags gives bit 8 (other's heading not within 0x400 of the
 * direction back to self); takes 10 spirit from other when it is in state 0x17 (addEntityHealthDelta). Gives up (0)
 * when other has flag bit 0x400000, or bits 0x600000000000 without 0x0400000000000000; then func_800E212C(other).
 * Unless self's flags have bit 0x1 or 0x8: when other is in state 0xA step 4/5/7, state 0x81 step 3, or (without
 * flag bit 0x1000000000) states 0x6B..0x6F, self must be in the ring and starts 0x7B/0x7C with other
 * (beginPairedEntityActions; grappleCtx reset to 0, or 0x04000000 for state 0xA step 4); grappleCtx bit 4 starts
 * 0x4F/0x50 (returns 0 if bit 0x40 is also set). When both share the ring or floor zone it may instead set
 * self->step 5 and put other in state 0x5F step 2 (func_800D7B54(other, 0, 0, 3)), returning 0, or raise grappleCtx
 * 0x100000 (other in state 0x44 step 2 with D_800FADBE[other id] < 3, or func_800D7B54(other, 0, 0, 4)). Later
 * checks reject other in state 0x74, or 0x46 with grappleCtx 0x100000, or with flag bit 0x1000000000 outside state
 * 0x46; self on the floor with other on the apron (other not in state 0x46) goes straight to the paired action.
 * Unless self's flags have bit 0x1 or 0x8: both profiles having bit 0x400000000 at +0x38 and both health >= 0x97
 * with other in state 0x44 step 4 at animFrame hitStart - 2 .. hitEnd (both in the ring, no self grappleCtx 0x44,
 * no other bit 4) raise grappleCtx 0x40000; tryStartFacingGroupAtGate may start a three-wrestler move. The paired
 * action itself is chosen by selectPairedActionCD3F8(self, other), which is never called while other is in state
 * 0x46. Returns 1 when an action was started. */

void beginPairedEntityActions(void *, s32, void *, s32);
s32 getEntityPairFacingFlags(void *, void *);
void addEntityHealthDelta(void *, s32);
void func_800E212C(void *);
s32 func_800D7B54(void *, s32, s32, s32);
s32 tryStartFacingGroupAtGate(void *, void *);
void selectPairedActionCD3F8(void *, void *);
extern s16 D_800FADBE[];

s32 updateEntityPairInteraction(Wrestler *self, Wrestler *other) {
    int savedFlags;

    if (getEntityPairFacingFlags(self, other) & 8) {
        self->grappleCtx |= 0x40;
    }
    if (other->state == 0x17) {
        addEntityHealthDelta(other, -0xA);
    }
    if (other->flags & 0x400000ULL) {
        return 0;
    }
    if ((other->flags & 0x600000000000ULL) &&
        !(other->flags & 0x0400000000000000ULL)) {
        return 0;
    }
    func_800E212C(other);
    if (self->flags & 0x9ULL) {
        goto join;
    }
    if ((other->state == 0xA && ((u16)(other->step - 4) < 2 || other->step == 7)) ||
        (other->state == 0x81 && other->step == 3) ||
        (!(other->flags & 0x1000000000ULL) && (u16)(other->state - 0x6B) < 5)) {
        if (!(self->flags & WR_FLAG_IN_RING)) {
            return 0;
        }
        if (other->state == 0xA) {
            if (other->step != 4) {
                self->grappleCtx = 0;
            } else {
                self->grappleCtx = 0x04000000;
            }
        } else {
            self->grappleCtx = 0;
        }
        beginPairedEntityActions(self, 0x7B, other, 0x7C);
        goto paired_end;
    }
    if (self->grappleCtx & 4) {
        if (self->grappleCtx & 0x40) {
            return 0;
        }
        beginPairedEntityActions(self, 0x4F, other, 0x50);
    } else {
        goto rest;
    }
paired_end:
    return 1;
rest:
    if (self->grappleCtx & 0x40) {
        goto join;
    }
    if (self->flags & other->flags & (WR_FLAG_IN_RING | WR_FLAG_ON_FLOOR)) {
        if (other->state == 0x5F && other->step < 2) {
            if (other->stateTimer < 3) {
                self->step = 5;
                other->step = 2;
            }
            return 0;
        }
        if ((func_800D7B54(other, 0, 0, 3) << 24) != 0) {
            self->step = 5;
            func_800A6C48(other, 0x5F);
            other->step = 2;
            return 0;
        }
    }
    savedFlags = self->grappleCtx;
    if (savedFlags & 0x40) {
        goto join;
    }
    if (self->flags & other->flags & (WR_FLAG_IN_RING | WR_FLAG_ON_FLOOR)) {
        if (other->state == 0x44 && other->step == 2 &&
            D_800FADBE[other->id] < 3) {
            self->grappleCtx = savedFlags | 0x100000;
            goto call_update;
        }
        if ((func_800D7B54(other, 0, 0, 4) << 24) != 0) {
            if (other->state == 0x46) {
                goto check74;
            }
            self->grappleCtx |= 0x100000;
            selectPairedActionCD3F8(self, other);
            return 1;
        }
    }
join:
    if (other->state != 0x46 && (other->flags & 0x1000000000ULL)) {
        return 0;
    }
check74:
    if (other->state == 0x74) {
        return 0;
    }
    if (other->state == 0x46 && (other->grappleCtx & 0x100000)) {
        return 0;
    }
    if ((self->flags & WR_FLAG_ON_FLOOR) && (other->flags & WR_FLAG_ON_APRON) &&
        other->state != 0x46) {
        goto call_update;
    }
    if (self->flags & 0x9ULL) {
        goto tail;
    }
    if (*(u64 *)(self->profile + 0x38) & 0x400000000ULL) {
        if (*(u64 *)(other->profile + 0x38) & 0x400000000ULL) {
            if (self->health >= 0x97 &&
                other->health >= 0x97 &&
                other->state == 0x44 &&
                other->step == 4 &&
                (self->flags & other->flags & WR_FLAG_IN_RING) &&
                !(self->grappleCtx & 0x44) &&
                !(other->grappleCtx & 4) &&
                !(other->animFrame < other->anim.hitStart - 2) &&
                !(other->anim.hitEnd < other->animFrame)) {
                self->grappleCtx |= 0x40000;
                goto call_update;
            }
        }
    }
    if ((tryStartFacingGroupAtGate(self, other) << 16) != 0) {
        return 1;
    }
tail:
    if (other->state != 0x46) {
call_update:
        selectPairedActionCD3F8(self, other);
        return 1;
    }
    return 0;
}
