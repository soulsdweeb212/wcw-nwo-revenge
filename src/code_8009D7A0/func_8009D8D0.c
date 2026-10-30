/* @header
 * func_8009D8D0
 * VRAM 0x8009D8D0 | ROM 0x90D70 | size 0x348
 * asm: asm/nonmatchings/code_8009D7A0/func_8009D8D0.s
 */
#include "common.h"

typedef struct {
    u8 pad0[0xA];
    s16 fA;
    u8 padC[0x14];
    u64 flags;
    u8 pad28[0xF];
    u8 f37;
    u8 f38;
    u8 pad39[3];
    s16 f3C;
    u8 pad3E[0xE];
    f32 f4C;
    u8 pad50[0x301];
    s8 f351;
    s8 f352;
    u8 pad353[2];
    s8 f355;
    u8 pad356[2];
    s32 f358;
    s32 f35C;
} Entity3B0;

extern u8 D_800F9D10[];
extern u8 D_800F9D30[];
extern u8 D_800F9D34[];
extern u8 D_800E2FF0[];
extern s32 D_800E3F20[];
extern Entity3B0 *D_800EB40C;
extern Entity3B0 *D_800F9B00;
extern Entity3B0 *D_800F9B64;
extern Entity3B0 *D_800FABE0;
extern Entity3B0 *D_800EB410;
extern Entity3B0 *D_800EB414;
extern Entity3B0 *D_800EB418;
extern Entity3B0 *D_800FAF7C;
extern Entity3B0 *D_800FAF5C;
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

#define EB ((Entity3B0 *)D_800EB408)

/* Per-frame main update for the entity indexed by D_800FADB8.  It repoints the
 * work pointers (D_800EB408/D_800FAF5C = self, D_800EB40C/D_800F9B00 = the
 * D_800FABE4 entity, D_800EB410/FABE0 = self[0x355], D_800EB414/9B64 = self[0x351],
 * D_800EB418/FAF7C = self[0x352]) and snapshots the linked entity's u64 flags into
 * self+0x358/0x35C before clearing self flag bits 0xD3BF838EEFAFFFFF and the low
 * status bits.  It ORs the entity's D_800E3F20 entry into D_800FABD8, promotes
 * flags 0x2000/0x10 to 0x1000000000, resets the action/target bytes when
 * func_800A93C0() reports an active action, then runs the action interpreter
 * (func_800A712C), updates quadrant f3C, timers and sub-updates, and finally calls
 * self's per-state handler from the D_800E2FF0 table indexed by fA. */
void func_8009D8D0(void) {
    Entity3B0 *self;
    Entity3B0 *partner;
    s32 linkedOffset;
    s32 savedFlagsLo, savedFlagsHi;

    self = (Entity3B0 *)(D_800F9D10 + D_800FADB8 * 0x3B0);
    partner = (Entity3B0 *)(D_800F9D10 + D_800FABE4 * 0x3B0);
    D_800EB408 = self;
    D_800FAF5C = self;
    D_800EB40C = partner;
    D_800F9B00 = partner;
    D_800EB410 = (Entity3B0 *)(D_800F9D10 + self->f355 * 0x3B0);
    D_800FABE0 = D_800EB410;
    D_800EB414 = (Entity3B0 *)(D_800F9D10 + self->f351 * 0x3B0);
    D_800F9B64 = D_800EB414;
    D_800EB418 = (Entity3B0 *)(D_800F9D10 + self->f352 * 0x3B0);
    D_800FAF7C = D_800EB418;
    linkedOffset = self->f355 * 0x3B0;
    {
        u8 status37 = self->f37;
        savedFlagsLo = *(s32 *)(D_800F9D30 + linkedOffset);
        savedFlagsHi = *(s32 *)(D_800F9D34 + linkedOffset);
        self->f358 = savedFlagsLo;
        self->f35C = savedFlagsHi;
        self->f37 = status37 & 0xFE;
        self->flags &= 0xD3BF838EEFAFFFFFULL;
        EB->f38 &= 0xFC;
    }
    D_800FABD8 |= D_800E3F20[D_800FADB8];
    if (D_800FABE6 & 0x2000) {
        EB->flags |= 0x2000000000000000ULL;
    }
    if (func_800A93C0() << 24) {
        D_800FABE6 = 0;
        D_800FAF8A = 0;
        D_800FAF78 = 0;
        EB->flags |= 0x1000000000ULL;
    }
    if (EB->flags & 0x10ULL) {
        EB->flags |= 0x1000000000ULL;
    }
    func_800A712C(EB, D_800EB40C, D_800F9B14, D_800F9B14 - 8);
    EB->f3C = getXZDirectionQuadrant(&EB->f4C);
    updateEntityStatus43Timer(EB, 1);
    updateEntityStunTimer(EB, 0, 2);
    func_800D90E8(EB);
    func_800D91C0(EB);
    func_800BF26C(EB);
    func_800C02E4(EB);
    func_800D7B54(EB, D_800FABE6, D_800FAF8A, 0);
    (*(void (**)(void))(D_800E2FF0 + EB->fA * 4))();
}
