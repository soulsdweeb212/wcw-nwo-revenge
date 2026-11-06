/* @header
 * func_800D00FC
 * VRAM 0x800D00FC | ROM 0xC359C | size 0x4E8
 * asm: asm/nonmatchings/code_800BBA00/func_800D00FC.s
 */
#include "common.h"

void beginPairedEntityActions(Wrestler *self, s32 selfAction, Wrestler *other, s32 otherAction);
void func_800A7C40(Wrestler *, s8, s16);
void func_800A7F6C(void *, s32);
s8 func_800D05E4(Wrestler *, Wrestler *);
extern u16 D_800E3C20[2][2][3];
extern u16 D_800E3C38[2][2][2];

/* Picks self's response to the opponent (called with D_800FAF5C, D_800F9B00 and D_800FAF8E[slot] as arg2) from
 * self->grappleCtx bits and the arg2 bits. It either starts a paired state pair with beginPairedEntityActions and
 * returns 1, or sets self's move from a table (func_800A7C40; tables D_800E3C20 / D_800E3C38 for grappleCtx bit
 * 0x400) and returns 3 when func_800D05E4 accepts it, else 0; 2 when no case applies. move.flags bits 0x1800 with
 * WR_FLAG_ON_APRON / WR_FLAG_IN_RING lead to states 0x4D/0x4E; profile word +0x38 bit 0 to states 0x4B/0x4C. */
s32 func_800D00FC(Wrestler *self, Wrestler *opponent, u16 arg2) {
    s32 s0;
    s8 i, j, k;

    if (self->grappleCtx & 0x40) {
        if (arg2 & 8) {
            beginPairedEntityActions(self, 0x74, opponent, 0x75);
            return 1;
        }
        if (arg2 & 0x20) {
            beginPairedEntityActions(self, 0x72, opponent, 0x73);
            return 1;
        }
    }
    if (self->grappleCtx & 0x300) {
        if (self->grappleCtx & 0x200000) {
            s0 = (self->grappleCtx & 0x100) ? 0x7E : 0x82;
            func_800A7C40(self, self->id, (s16)s0);
            return 0;
        }
        if (arg2 & 0xC000) {
            if (self->grappleCtx & 0x100) {
                s0 = (self->grappleCtx & 2) ? 0x7D : 0x7C;
            } else {
                s0 = (self->grappleCtx & 2) ? 0x81 : 0x80;
            }
            func_800A7C40(self, self->id, (s16)s0);
            func_800A7F6C(self, 0);
            if (func_800D05E4(self, opponent)) {
                return 3;
            }
            if (self->move.flags & 0x1800) {
                if (self->flags & WR_FLAG_ON_APRON) {
                    beginPairedEntityActions(self, 0x4D, opponent, 0x4E);
                    return 1;
                }
            }
ret0:
            return 0;
        }
        if (arg2 & 4) {
            if (self->grappleCtx & 0x100) {
                beginPairedEntityActions(self, 0xD, opponent, 0xE);
            } else {
                beginPairedEntityActions(self, 0xF, opponent, 0x10);
            }
            return 1;
        }
    }
    if (self->grappleCtx & 0x80) {
        if (self->grappleCtx & 0x200000) {
            func_800A7C40(self, self->id, 0x6E);
            func_800A7F6C(self, 0);
            return 0;
        }
        if (arg2 & 0xC000) {
            if (self->grappleCtx & 2) {
                s0 = (arg2 & 0x8000) ? 0x64 : 0x69;
            } else {
                s0 = (arg2 & 0x8000) ? 0x5A : 0x5F;
            }
            func_800A7C40(self, self->id, (s16)s0);
            func_800A7F6C(self, 0);
            return func_800D05E4(self, opponent) ? 3 : 0;
        }
    }
    if (arg2 & 4) {
        if (!(self->grappleCtx & 0x300)) {
            if (!(self->grappleCtx & 0x40)) {
                beginPairedEntityActions(self, 0xB, opponent, 0xC);
                return 1;
            }
        }
    }
    if (self->grappleCtx & 0x400) {
        if ((self->grappleCtx & 0x200003) == 0x200003) {
            s0 = (self->grappleCtx & 0x40) ? 0x41 : 0x3A;
            func_800A7C40(self, self->id, (s16)s0);
            func_800A7F6C(self, 0);
            return 0;
        }
        if ((self->grappleCtx & 1) && (arg2 & 0xC000) == 0xC000 && !(opponent->flags & 9)) {
            s0 = (self->grappleCtx & 0x40) ? 0x43 : 0x3C;
            func_800A7C40(self, opponent->id, (s16)s0);
            func_800A7F6C(self, 0);
            return 0;
        }
        if ((*(u64 *)(self->profile + 0x38) & 1) && ((self->grappleCtx & 0x42) == 2) && (arg2 & 0x4000)) {
            beginPairedEntityActions(self, 0x4B, opponent, 0x4C);
            return 1;
        }
        if (!(arg2 & 0xC000)) {
            return 2;
        }
        if (self->grappleCtx & 0x40) {
            u8 jj, kk;
            if (arg2 & 0x8000) {
                jj = 0;
            } else {
                jj = 1;
            }
            if (arg2 & 0xF00) {
                kk = 1;
            } else {
                kk = 0;
            }
            s0 = D_800E3C38[(self->grappleCtx >> 1) & 1][jj][kk];
        } else {
            i = (self->grappleCtx >> 1) & 1;
            if (arg2 & 0x8000) {
                j = 0;
            } else {
                j = 1;
            }
            if (arg2 & 0x800) {
                k = 1;
            } else {
                k = (arg2 >> 9) & 2;
            }
            s0 = D_800E3C20[i][j][k];
        }
        func_800A7C40(self, self->id, (s16)s0);
        if (!(self->move.flags & 0x1800)) {
            goto L5A0;
        }
        if (self->flags & WR_FLAG_IN_RING) {
            func_800A7F6C(self, 0);
            if (func_800D05E4(self, opponent)) {
                return 3;
            }
            beginPairedEntityActions(self, 0x4D, opponent, 0x4E);
            return 1;
        }
        func_800A7C40(self, self->id, (s16)(s0 + 5));
L5A0:
        func_800A7F6C(self, 0);
        if (!func_800D05E4(self, opponent)) {
            goto ret0;
        }
        return 3;
    }
    return 2;
}
