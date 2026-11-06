/* @header
 * func_8009D8D0
 * VRAM 0x8009D8D0 | ROM 0x90D70 | size 0x348
 * asm: asm/nonmatchings/code_8009D7A0/func_8009D8D0.s
 */
#include "common.h"

extern u8 D_800E2FF0[];
extern s32 D_800E3F20[];
extern s32 D_800FABD8;
extern s8 D_800FABE4;
extern u16 D_800FABE6;
extern u16 D_800FAF8A;
extern s8 D_800FAF78;
extern s8 D_800FADB8;
extern u8 D_800F9B14[];
s32 func_800A93C0(void);
void func_800A712C(void *, void *, void *, void *);
void func_800BF26C(void *);
void updateEntityStunTimer(void *, s32, s32);
void func_800C02E4(void *);
void func_800D7B54(void *, u16, u16, s32);
void func_800D90E8(void *);
void func_800D91C0(void *);
s32 getXZDirectionQuadrant(f32 *);
void updateEntityStatus43Timer(void *, s16);

/* Per-frame main update for the wrestler indexed by D_800FADB8.  It repoints the
 * work pointers (D_800EB408/D_800FAF5C = self, D_800EB40C/D_800F9B00 = the
 * D_800FABE4 record, D_800EB410/FABE0 = partnerId, D_800EB414/9B64 = heldById,
 * D_800EB418/FAF7C = secondAttackerId) and snapshots the partner's flags into
 * self->partnerFlags (word by word) before clearing self flag bits
 * 0xD3BF838EEFAFFFFF and the per-tick frameStatus/frameBits bits.  It ORs the
 * wrestler's D_800E3F20 entry into D_800FABD8, promotes flags 0x2000/0x10 to
 * 0x1000000000, resets the action/target bytes when func_800A93C0() reports an
 * active action, then runs the action interpreter (func_800A712C), updates
 * ringSide, timers and sub-updates, and finally calls the per-state handler from
 * the D_800E2FF0 table indexed by state. */
void func_8009D8D0(void) {
    Wrestler *self;
    Wrestler *opponent;
    s32 partnerOffset;
    s32 partnerFlagsHi, partnerFlagsLo;

    self = &D_800F9D10[D_800FADB8];
    opponent = &D_800F9D10[D_800FABE4];
    D_800EB408 = self;
    D_800FAF5C = self;
    D_800EB40C = opponent;
    D_800F9B00 = opponent;
    D_800EB410 = &D_800F9D10[self->partnerId];
    D_800FABE0 = D_800EB410;
    D_800EB414 = &D_800F9D10[self->heldById];
    D_800F9B64 = D_800EB414;
    D_800EB418 = &D_800F9D10[self->secondAttackerId];
    D_800FAF7C = D_800EB418;
    partnerOffset = self->partnerId * 0x3B0;
    {
        u8 status37 = self->frameStatus;
        partnerFlagsHi = ((WrFlagWords *)((u8 *)&D_800F9D10[0].flags + partnerOffset))->hi;
        partnerFlagsLo = ((WrFlagWords *)((u8 *)&D_800F9D10[0].flags + partnerOffset))->lo;
        ((WrFlagWords *)&self->partnerFlags)->hi = partnerFlagsHi;
        ((WrFlagWords *)&self->partnerFlags)->lo = partnerFlagsLo;
        self->frameStatus = status37 & 0xFE;
        self->flags &= 0xD3BF838EEFAFFFFFULL;
        D_800EB408->frameBits &= 0xFC;
    }
    D_800FABD8 |= D_800E3F20[D_800FADB8];
    if (D_800FABE6 & 0x2000) {
        D_800EB408->flags |= 0x2000000000000000ULL;
    }
    if (func_800A93C0() << 24) {
        D_800FABE6 = 0;
        D_800FAF8A = 0;
        D_800FAF78 = 0;
        D_800EB408->flags |= 0x1000000000ULL;
    }
    if (D_800EB408->flags & 0x10ULL) {
        D_800EB408->flags |= 0x1000000000ULL;
    }
    func_800A712C(D_800EB408, D_800EB40C, D_800F9B14, D_800F9B14 - 8);
    D_800EB408->ringSide = getXZDirectionQuadrant(&D_800EB408->x);
    updateEntityStatus43Timer(D_800EB408, 1);
    updateEntityStunTimer(D_800EB408, 0, 2);
    func_800D90E8(D_800EB408);
    func_800D91C0(D_800EB408);
    func_800BF26C(D_800EB408);
    func_800C02E4(D_800EB408);
    func_800D7B54(D_800EB408, D_800FABE6, D_800FAF8A, 0);
    (*(void (**)(void))(D_800E2FF0 + D_800EB408->state * 4))();
}
