/* @header
 * setupEntityFacingGroup  (originally func_800CD80C)
 * VRAM 0x800CD80C | ROM 0xC0CAC | size 0x184
 * asm: asm/nonmatchings/code_800BBA00/setupEntityFacingGroup.s
 */
#include "common.h"

void func_800A6CDC(Wrestler *, s32);
s32 func_800D3684(s32, s32);

/* Starts a three-wrestler move (called by tryStartFacingGroupAtGate): `lead` and `helper` double-team `victim`.
 * By the signed turn from helper's heading to lead's, one of the two gets grappleCtx bit 0x4000 and the other
 * 0x8000 (lead gets 0x4000 when that turn is negative). Puts them in states 0x76 / 0x77 / 0x78 (func_800A6CDC),
 * raises flag bit 0x1000000000 and WR_FLAG_UPDATED on all three and WR_FLAG_PAIR_LEADER on lead, ORs helper's
 * grappleCtx bit 2 and the low 16 bits of `mode` into lead's grappleCtx, and keeps only bits 0xC040 of helper's
 * grappleCtx, adding lead's bits 0x3800. Links the ids: lead->attached = {helper, victim}; lead and helper get
 * opponentId = victim and each other as secondAttackerId; victim gets opponentId = heldById = lead and
 * secondAttackerId = helper. */
void setupEntityFacingGroup(Wrestler *lead, Wrestler *helper, Wrestler *victim, s32 mode) {
    register int tmp;
    if (func_800D3684(lead->heading, helper->heading) < 0) {
        lead->grappleCtx |= 0x4000;
        helper->grappleCtx |= 0x8000;
    } else {
        lead->grappleCtx |= 0x8000;
        helper->grappleCtx |= 0x4000;
    }
    func_800A6CDC(lead, 0x76);
    func_800A6CDC(helper, 0x77);
    func_800A6CDC(victim, 0x78);
    lead->flags |= 0x1000000000ULL | WR_FLAG_PAIR_LEADER | WR_FLAG_UPDATED;
    helper->flags |= 0x1000000000ULL | WR_FLAG_UPDATED;
    victim->flags |= 0x1000000000ULL | WR_FLAG_UPDATED;
    lead->grappleCtx |= (helper->grappleCtx & 2) | (mode & 0xFFFF);
    lead->attached[0] = helper->id;
    lead->attached[1] = victim->id;
    lead->opponentId = victim->id;
    lead->secondAttackerId = helper->id;
    tmp = helper->grappleCtx & 0xC040;
    helper->opponentId = victim->id;
    helper->secondAttackerId = lead->id;
    helper->grappleCtx = tmp;
    helper->grappleCtx = tmp | (lead->grappleCtx & 0x3800);
    victim->opponentId = lead->id;
    victim->heldById = lead->id;
    victim->secondAttackerId = helper->id;
}
