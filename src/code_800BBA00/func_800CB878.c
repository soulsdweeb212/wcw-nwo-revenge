/* @header
 * func_800CB878
 * VRAM 0x800CB878 | ROM 0xBED18 | size 0x3D4
 * asm: asm/nonmatchings/code_800BBA00/func_800CB878.s
 */
#include "common.h"

typedef struct {
    s8 f0;
    u8 pad1[3];
    s16 f4;
    u8 pad6[2];
    u16 f8;
    s16 fA;
    s16 fC;
    s16 fE;
    u8 pad10[4];
    s16 f14;
    s16 f16;
    s16 f18;
    u8 pad1A[6];
    u64 flags;
    u8 pad28[0x1C];
    s16 f44;
    u8 pad46[0x12];
    s32 f58;
    u8 pad5C[0x304];
    u16 f360;
    u8 pad362[0x4A];
    u32 f3AC;
} Nw2F5C;

extern void *D_800FAF5C;
extern void *D_800F9B00;
extern u16 D_800FAF8A;
extern s8 D_800FAF78;

void func_800A9290(void *);
void func_800CBD5C(void *, void *, u16);
void func_800D2BEC(void *, void *, void *, f32, u16, s32);
void func_800D4AD0(void *);
void beginEntityActionA8D8C(void *);
void func_800C472C(void *, void *, s32);
void func_800D427C(void *, s16, s32);
s32 func_800D5438(void *, s32);
void beginPairedEntityActions(void *, s32, void *, s32);
void func_800A7F6C(void *, s32);
void func_800A837C(void *);
s8 func_800D7984(void *, u16, s8);
void func_800D43B4(void *, s16, s32);
void func_800A6C48(void *, s32);

#define SELF ((Nw2F5C *)D_800FAF5C)
#define OTHER ((Nw2F5C *)D_800F9B00)

/* Paired-entity action state machine, cases 0..5 on SELF->fC (+0xC).  SELF plays
 * a grab/throw sequence against OTHER: it raises its u64 flag bit0x1000000000,
 * waits on the s16 timer SELF->f4, then advances the case and either re-sends the
 * animation (func_800D427C), starts a paired maneuvre
 * (func_800D2BEC/func_800D2BAC/beginPairedEntityActions), or transitions SELF
 * back to case 1 with flag 0x80000000000000 on completion.  OTHER->f360 bits
 * 1/2/4/8/0x20 select which branch runs, and D_800FAF78/D_800FAF8A feed the
 * proximity test func_800D7984. */
void func_800CB878(void) {
    switch (SELF->fC) {
    case 0:
        func_800A9290(SELF);
        SELF->fC++;
        /* fall through */
    case 1: {
        u16 targetFlags;
        SELF->flags |= 0x1000000000ULL;
        func_800CBD5C(SELF, OTHER, D_800FAF8A);
        targetFlags = OTHER->f360;
        if (targetFlags & 1) {
            func_800D427C(SELF, (s16)func_800D5438(OTHER, 1), 6);
            SELF->fC++;
        } else if (targetFlags & 2) {
            func_800D427C(SELF, (s16)func_800D5438(SELF, 0), 6);
            beginPairedEntityActions(SELF, 0x3A, OTHER, 0x3B);
            SELF->fC = 4;
            OTHER->fC = 2;
            func_800A7F6C(SELF, 0);
            func_800A837C(SELF);
        } else if (targetFlags & 4) {
            func_800D427C(SELF, (s16)(OTHER->f8 + 1), 6);
            SELF->fC = 3;
        }
        break;
    }
    case 2:
        func_800D2BEC(SELF, OTHER, 0, 8.0f, 0, 0xFFFFE);
        if (SELF->f4 <= 0) {
            func_800D4AD0(SELF);
            beginEntityActionA8D8C(SELF);
            func_800C472C(OTHER, SELF, 2);
        }
        break;
    case 3:
        func_800D2BAC(SELF, OTHER, 4.0f, 0xFFFFE);
        if (SELF->f4 <= 0) {
            func_800D427C(SELF, (s16)(OTHER->f8 + 1), 0);
            SELF->fC++;
        }
        break;
    case 4:
        if (func_800D7984(SELF, D_800FAF8A, D_800FAF78)) {
            SELF->f360 |= 0x10;
        }
        if (SELF->f4 <= 0) {
            if (OTHER->f360 & 0x20) {
                func_800D427C(SELF, (s16)(OTHER->f8 + 1), 1);
                SELF->fC++;
            } else {
                func_800D43B4(SELF, (s16)SELF->f8, 1);
            }
        }
        func_800D2BAC(SELF, OTHER, 4.0f, 0xFFFFE);
        break;
    case 5:
        func_800D2BAC(SELF, OTHER, 4.0f, 0xFFFFE);
        if (SELF->f4 <= 0) {
            func_800D4AD0(SELF);
            if (SELF->f360 & 8) {
                func_800A6C48(SELF, 0x2C);
                SELF->fC = 1;
            } else {
                SELF->flags |= 0x80000000000000ULL;
                func_800A6C48(SELF, 0x2B);
            }
        }
        break;
    }
}
