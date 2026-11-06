/* @header
 * func_800DF99C
 * VRAM 0x800DF99C | ROM 0xD2E3C | size 0x2F0
 * asm: asm/nonmatchings/code_800DE9C0/func_800DF99C.s
 */
#include "common.h"

s32 func_800A9208(void *, s32 *);
f32 func_800D3EEC(void *, void *, s32);
void chooseDodgeAction(Wrestler *, Wrestler *, s32, Nw2DirectionResult *);

/* Contact/counter reaction test between self and target.  It clears self flag
 * 0x20000000000, and when mask bit 0x4000 is set also clears flag
 * 0x0100000000000000.  If self is in the ring or on the floor: when both share
 * a zone bit (WR_FLAG_IN_RING / WR_FLAG_ON_FLOOR), info->y is below
 * func_800D3EEC(&target->jointA[1], &self->jointA[1], target->heading) +
 * D_800E76B0, target has flag 0x400000 and the heading delta
 * func_800D3550(func_800D3684(self->heading, info->angle)) is under 0x155, it
 * starts action 0x55 (0x24 with self flag 0x1000000000000); otherwise, when
 * both are WR_FLAG_IN_RING or both WR_FLAG_ON_FLOOR, target has 0x200000000000
 * and not 0x0400000000000000, info->y is below the same gap + D_800E76B8 and the
 * reverse heading delta is under 0x200, it starts 0x25; else it re-arms flag
 * 0x20000000000 when self is in state 0x17 and starts 0x1E.  A self in
 * neither zone but WR_FLAG_ON_APRON defers to chooseDodgeAction. */
s8 func_800DF99C(Wrestler *self, Wrestler *target, u16 mask, Nw2DirectionResult *info) {
    u64 flags;
    flags = self->flags;
    flags &= ~0x20000000000ULL;
    self->flags = flags;
    if (mask & 0x4000) {
        flags &= ~0x0100000000000000ULL;
        self->flags = flags;
        if (flags & (WR_FLAG_IN_RING | WR_FLAG_ON_FLOOR)) {
            if ((flags & target->flags & (WR_FLAG_IN_RING | WR_FLAG_ON_FLOOR))
                && (f64)info->y < (f64)func_800D3EEC(&target->jointA[1], &self->jointA[1], target->heading) + D_800E76B0
                && (target->flags & 0x400000ULL)
                && (func_800A9208(target, 0), func_800D3550(func_800D3684(self->heading, info->angle)) < 0x155)) {
                if (self->flags & 0x1000000000000ULL) func_800A6C48(self, 0x24);
                else func_800A6C48(self, 0x55);
            } else {
                if (((self->flags & target->flags & WR_FLAG_IN_RING) || (self->flags & target->flags & WR_FLAG_ON_FLOOR))
                    && (target->flags & 0x200000000000ULL)
                    && !(target->flags & 0x0400000000000000ULL)
                    && (f64)info->y < (f64)func_800D3EEC(&target->jointA[1], &self->jointA[1], target->heading) + D_800E76B8
                    && func_800D3550(func_800D3684(info->angle, self->heading)) < 0x200) func_800A6C48(self, 0x25);
                else {
                    if (self->state == 0x17) self->flags |= 0x20000000000ULL;
                    func_800A6C48(self, 0x1E);
                }
            }
            return 1;
        }
        if (flags & WR_FLAG_ON_APRON) {
            chooseDodgeAction(self, target, mask & 0xFFFF, info);
            return 1;
        }
        return 0;
    }
    return 0;
}
