/* @header
 * func_800DFDD4
 * VRAM 0x800DFDD4 | ROM 0xD3274 | size 0x2B4
 * asm: asm/nonmatchings/code_800DE9C0/func_800DFDD4.s
 */
#include "common.h"

extern u16 D_800E3CD0[];
extern u16 D_800E3CD8[];
s32 tryStartPairedEntityActions(Wrestler *, Wrestler *, u16, f32);
void func_800E212C(Wrestler *);
s32 func_800D23B4(Wrestler *, Wrestler *, Nw2DirectionResult *);
/* Clears self flag 0x20000000000; returns 0 unless arg2 has bit 0x8000. Then clears flag 0x0100000000000000 and
 * returns 1 when tryStartPairedEntityActions(self, other, arg2, dir->y) starts something. Otherwise: self in
 * state 0x17 re-arms flag 0x20000000000; with neither flag bit 0x1 nor 0x8 it starts action 0x44. With one of
 * them, func_800D23B4(self, other, dir) starts 0x44 at step 4; failing that flag 0x0100000000000000 is set and a
 * self not WR_FLAG_ON_APRON starts 0x1E, while an apron self picks 0x1B / 0x1C / 0x1D like chooseDodgeAction
 * (ringSide tables against arg2, then other's zone; nothing when other is in no zone). Returns 1. */
s32 func_800DFDD4(Wrestler *self, Wrestler *other, s32 arg2, Nw2DirectionResult *dir)
{
    u16 m = arg2;
    s32 ret;
    self->flags &= ~0x0000020000000000ULL;
    if (arg2 & 0x8000)
    {
        u64 f;
        self->flags &= ~0x0100000000000000ULL;
        if ((s8) tryStartPairedEntityActions(self, other, m, dir->y))
        {
            func_800E212C(self);
            return 1;
        }
        goto body;
ret1:
        return 1;

body:
        if (self->state == 0x17)
        {
            self->flags |= 0x0000020000000000ULL;
        }

        if (self->flags & 9)
        {
            func_800E212C(self);
            if ((s8) func_800D23B4(self, other, dir))
            {
                func_800A6C48(self, 0x44);
                self->step = 4;
                goto ret1;
            }
            f = self->flags | 0x0100000000000000ULL;
            self->flags = f;
            if (f & WR_FLAG_ON_APRON)
            {
                s32 index = self->ringSide;
                if (D_800E3CD8[index] & arg2)
                {
                    func_800A6C48(self, 0x1B);
                    return 1;
                }
                if (D_800E3CD0[index] & arg2)
                {
                    func_800A6C48(self, 0x1C);
                    return 1;
                }
                if (other->flags & WR_FLAG_IN_RING)
                {
                    func_800A6C48(self, 0x1B);
                    return 1;
                }
                if (other->flags & WR_FLAG_ON_FLOOR)
                {
                    func_800A6C48(self, 0x1C);
                    return 1;
                }
                if (!(other->flags & WR_FLAG_ON_APRON))
                {
                    return 1;
                }
                self->flags = f & (~0x0000008000000000ULL);
                if (func_800D3684(self->heading, dir->angle) <= 0)
                {
                    self->flags |= 0x0000008000000000ULL;
                }
                func_800A6C48(self, 0x1D);
                return 1;
            }
            else
            {
                func_800A6C48(self, 0x1E);
            }
        }
        else
        {
            func_800A6C48(self, 0x44);
        }
        ret = 1;
    }
    else
    {
        ret = 0;
    }
    return ret;
}
