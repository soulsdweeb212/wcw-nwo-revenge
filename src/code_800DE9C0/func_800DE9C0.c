/* @header
 * func_800DE9C0
 * VRAM 0x800DE9C0 | ROM 0xD1E60 | size 0x2EC
 * asm: asm/nonmatchings/code_800DE9C0/func_800DE9C0.s
 */
#include "common.h"

extern u8 D_8007EF30[];
extern u16 D_800E3CD0[];
extern u16 D_800E3CD8[];
s16 func_800A76FC(void *, u16);
s16 func_800D7B08(u16, u64);
s8 func_800D8DF0(void *);
void func_800E212C(void *);

/* Zone-dependent reactions of self to other when flags3 has bit 0x8000 (returns 1 when an action is started):
 * - unless bit 0x404 of the u16 at D_8007EF30+0x170 is set: self WR_FLAG_IN_RING with other WR_FLAG_ON_FLOOR sets
 *   self->dirIndex = func_800A76FC(self, arg4) and starts action 0x64; self WR_FLAG_ON_APRON with other
 *   WR_FLAG_ON_FLOOR, profile bit 0x100000 and D_800E3CD0[ringSide] in mask starts 0x67;
 * - self WR_FLAG_ON_APRON with other WR_FLAG_IN_RING, profile bit 0x2000000, D_800E3CD8[ringSide] in arg4 and
 *   func_800D8DF0(self) starts 0x69;
 * - both WR_FLAG_IN_RING, other flag 0x400000, profile bit 0x80000, mask & 0xF00 and func_800D7B08(mask,
 *   other->flags) == -1 sets dirIndex as above and starts 0x65. */
s32 func_800DE9C0(Wrestler *self, Wrestler *other, s32 mask, s32 flags3, u16 arg4)
{
    s32 m = mask;
    u64 f0;
    u64 f1;
    u64 fa;
    s16 r;

    if ((flags3 & 0x8000) == 0) {
        return 0;
    }
    if ((*(u16 *)(D_8007EF30 + 0x170) & 0x404) == 0) {
        if ((self->flags & WR_FLAG_IN_RING) != 0 && (other->flags & WR_FLAG_ON_FLOOR) != 0) {
            self->dirIndex = func_800A76FC(self, arg4);
            func_800A6C48(self, 0x64);
            func_800E212C(self);
            return 1;
        }
        if ((self->flags & WR_FLAG_ON_APRON) != 0 && (other->flags & WR_FLAG_ON_FLOOR) != 0
            && (*(u64 *)(self->profile + 0x38) & 0x100000ULL) != 0
            && (D_800E3CD0[self->ringSide] & m) != 0) {
            func_800A6C48(self, 0x67);
            return 1;
        }
    }
    if ((self->flags & WR_FLAG_ON_APRON) != 0 && (other->flags & WR_FLAG_IN_RING) != 0
        && (*(u64 *)(self->profile + 0x38) & 0x2000000ULL) != 0
        && (arg4 & D_800E3CD8[self->ringSide]) != 0
        && func_800D8DF0(self) != 0) {
        func_800A6C48(self, 0x69);
        return 1;
    }
    f0 = self->flags;
    f1 = other->flags;
    if ((f0 & f1 & WR_FLAG_IN_RING) == 0) {
        return 0;
    }
    if ((f1 & 0x400000ULL) == 0) {
        return 0;
    }
    fa = *(u64 *)(self->profile + 0x38);
    if ((fa & 0x80000ULL) == 0) {
        return 0;
    }
    if ((m & 0xF00) == 0) {
        return 0;
    }
    r = func_800D7B08(m, f1);
    if (r != -1) {
        return 0;
    }
    func_800E212C(self);
    self->dirIndex = func_800A76FC(self, arg4);
    func_800A6C48(self, 0x65);
    return 1;
}
