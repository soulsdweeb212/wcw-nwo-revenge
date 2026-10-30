/* @header
 * func_800DF99C
 * VRAM 0x800DF99C | ROM 0xD2E3C | size 0x2F0
 * asm: asm/nonmatchings/code_800DE9C0/func_800DF99C.s
 */
#include "common.h"

s32 func_800A9208(void *, s32 *);
f32 func_800D3EEC(void *, void *, s32);
void chooseDodgeAction(void *, void *, s32, void *);

/* Contact/counter reaction test between self and target.  It clears self flag
 * 0x20000000000, and when mask bit0x4000 is set also clears flag
 * 0x0100000000000000 and checks the shared 0x140 flags.  If the range/angle
 * conditions hold (gap from func_800D3EEC below the f64 D_800E76B0 plus a heading
 * delta under 0x155) it sends action 0x55 (or 0x24 with self flag
 * 0x1000000000000); otherwise a different shared-flag (0x40/0x100), target
 * 0x200000000000 / not-0x0400000000000000 and angle test sends 0x25, or it
 * re-arms flag 0x20000000000 for state 0x17 and sends 0x1E.  With only flag 0x80
 * it defers to chooseDodgeAction. */
s8 func_800DF99C(u8 *self, u8 *target, u16 mask, u8 *info) {
    u64 flags;
    flags = *(u64 *)(self + 0x20);
    flags &= ~0x20000000000ULL;
    *(u64 *)(self + 0x20) = flags;
    if (mask & 0x4000) {
        flags &= ~0x0100000000000000ULL;
        *(u64 *)(self + 0x20) = flags;
        if (flags & 0x140ULL) {
            if ((flags & *(u64 *)(target + 0x20) & 0x140ULL)
                && (f64)*(f32 *)(info + 4) < (f64)func_800D3EEC(target + 0x6C, self + 0x6C, *(s32 *)(target + 0x58)) + D_800E76B0
                && (*(u64 *)(target + 0x20) & 0x400000ULL)
                && (func_800A9208(target, 0), func_800D3550(func_800D3684(*(s32 *)(self + 0x58), *(s32 *)(info + 0xC))) < 0x155)) {
                if (*(u64 *)(self + 0x20) & 0x1000000000000ULL) func_800A6C48(self, 0x24);
                else func_800A6C48(self, 0x55);
            } else {
                if (((*(u64 *)(self + 0x20) & *(u64 *)(target + 0x20) & 0x40ULL) || (*(u64 *)(self + 0x20) & *(u64 *)(target + 0x20) & 0x100ULL))
                    && (*(u64 *)(target + 0x20) & 0x200000000000ULL)
                    && !(*(u64 *)(target + 0x20) & 0x0400000000000000ULL)
                    && (f64)*(f32 *)(info + 4) < (f64)func_800D3EEC(target + 0x6C, self + 0x6C, *(s32 *)(target + 0x58)) + D_800E76B8
                    && func_800D3550(func_800D3684(*(s32 *)(info + 0xC), *(s32 *)(self + 0x58))) < 0x200) func_800A6C48(self, 0x25);
                else {
                    if (*(s16 *)(self + 0xA) == 0x17) *(u64 *)(self + 0x20) |= 0x20000000000ULL;
                    func_800A6C48(self, 0x1E);
                }
            }
            return 1;
        }
        if (flags & 0x80ULL) {
            chooseDodgeAction(self, target, mask & 0xFFFF, info);
            return 1;
        }
        return 0;
    }
    return 0;
}
