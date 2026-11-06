/* @header
 * selectPairedActionCD3F8  (originally func_800CD3F8)
 * VRAM 0x800CD3F8 | ROM 0xC0898 | size 0x2CC
 * asm: asm/nonmatchings/code_800BBA00/selectPairedActionCD3F8.s
 */
#include "common.h"

void beginPairedEntityActions(Wrestler *source, s32 sourceAction, Wrestler *target, s32 targetAction);

/* Chooses the paired states for source and target from their zone flags, source's grappleCtx and target's
 * state, and starts them via beginPairedEntityActions (source leads):
 *  - source on the apron, flag bits 0x9 clear, grappleCtx bit 0x40: 0x72/0x73, target->grappleCtx = source's
 *    without bit 2;
 *  - source on the floor, target on the apron: grappleCtx |= 0x10000, 0x87/0x88, grappleCtx copied to target;
 *  - source on the floor, target in the ring: grappleCtx |= 0x20000, 0x79/0x7A, grappleCtx copied to target;
 *  - otherwise, with flag bits 0x9 clear: grappleCtx bit 0x40000 gives 0x47/0x48. Else it sets grappleCtx bit
 *    0x80 and copies target's dirIndex when target is in state 0x14 step 3, bit 0x200 when source is on the apron,
 *    bit 0x100 when target is, and bit 0x400 when none of 0x40384 is set; then 0x8B/0x8C if bit 0x400 was set
 *    and bit 0x20 is set, else 0x45/0x46 with target->grappleCtx = source's without bit 2. */
void selectPairedActionCD3F8(Wrestler *source, Wrestler *target) {
    s32 var_a1;
    s32 var_a3;

    if (!(source->flags & 0x9ULL) && (source->flags & WR_FLAG_ON_APRON)) {
        if (source->grappleCtx & 0x40) {
            beginPairedEntityActions(source, 0x72, target, 0x73);
            target->grappleCtx = source->grappleCtx & ~2;
            return;
        }
        goto block_7;
    }
block_7:
    if ((source->flags & WR_FLAG_ON_FLOOR) && (target->flags & WR_FLAG_ON_APRON)) {
        source->grappleCtx = source->grappleCtx | 0x10000;
        beginPairedEntityActions(source, 0x87, target, 0x88);
        target->grappleCtx = source->grappleCtx;
        return;
    }
    if ((source->flags & WR_FLAG_ON_FLOOR) && (target->flags & WR_FLAG_IN_RING)) {
        source->grappleCtx = source->grappleCtx | 0x20000;
        beginPairedEntityActions(source, 0x79, target, 0x7A);
        target->grappleCtx = source->grappleCtx;
        return;
    }
    if (!(source->flags & 0x0ULL) && !(source->flags & 0x9ULL)) {
        s32 temp_a0_2 = source->grappleCtx;
        s32 temp_v1;
        if (temp_a0_2 & 0x40000) {
            beginPairedEntityActions(source, 0x47, target, 0x48);
            return;
        }
        if ((target->state == 0x14) && (target->step == 3)) {
            source->grappleCtx = temp_a0_2 | 0x80;
            source->dirIndex = target->dirIndex;
        }
        if (source->flags & WR_FLAG_ON_APRON) {
            source->grappleCtx = source->grappleCtx | 0x200;
        }
        if (target->flags & WR_FLAG_ON_APRON) {
            source->grappleCtx = source->grappleCtx | 0x100;
        }
        temp_v1 = source->grappleCtx & ~0x400;
        source->grappleCtx = temp_v1;
        if (!(temp_v1 & 0x40384)) {
            temp_v1 = temp_v1 | 0x400;
            source->grappleCtx = temp_v1;
            if (!(temp_v1 & 0x40384)) {
                if (temp_v1 & 0x20) {
                    beginPairedEntityActions(source, 0x8B, target, 0x8C);
                    return;
                }
            }
        }
        var_a1 = 0x45;
        var_a3 = 0x46;
        beginPairedEntityActions(source, var_a1, target, var_a3);
        target->grappleCtx = source->grappleCtx & ~2;
    }
}
