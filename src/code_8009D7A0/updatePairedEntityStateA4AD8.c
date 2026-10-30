/* @header
 * updatePairedEntityStateA4AD8  (originally func_800A4AD8)
 * VRAM 0x800A4AD8 | ROM 0x97F78 | size 0x29C
 * asm: asm/nonmatchings/code_8009D7A0/updatePairedEntityStateA4AD8.s
 */
#include "common.h"

/* Paired-entity action state machine: steps the global entity pair
 * (D_800EB408 primary / D_800EB40C partner) through phases 0..4.
 * Phase 0 kicks off the shared action (0xEBF) and phase 1 waits for the
 * ready callback (func_800D8D74). Phase 2 watches controller bits
 * (D_800FABE6 & 0xC000) together with the partner's script id (0x9B/0x9C)
 * and the +0x360 flag word to decide when both actors begin the paired
 * animation (beginPairedEntityActions with actions 0x5D/0x5E). Phases 3/4
 * play it out and tear the pair down. */
typedef struct {
    s8 f0;
    u8 pad1[3];
    s16 f4;
    u8 pad6[6];
    s16 fC;
    u8 padE[0x352];
    u16 f360;
} Nw2Primary;

typedef struct {
    u8 pad0[0xC];
    s16 fC;
    u8 padE[0x352];
    u16 f360;
    u8 pad362[0x24];
    s16 f386;
} Nw2Partner;

extern void *D_800EB408;
extern void *D_800EB40C;
extern u16 D_800FABE6;

void func_800D2BEC(void *, void *, void *, f32, u16, s32);
void func_800D427C(void *, s16, s32);
void func_800D7E80(void *, void *);
s8 func_800D8D74(void *, s32);
void func_800A7C40(void *, s8, s16);
void func_800A7F6C(void *, s32);
void func_800A837C(void *);
void beginPairedEntityActions(void *, s32, void *, s32);
s16 func_800D5438(void *, s16);
void func_800D4AD0(void *);
void beginEntityActionA8D8C(void *);
void func_800C472C(void *, void *, s32);

#define P ((Nw2Primary *)D_800EB408)
#define E40C ((Nw2Partner *)D_800EB40C)

void updatePairedEntityStateA4AD8(void) {
    func_800D2BEC(D_800EB408, D_800EB40C, 0, 4.0f, 0, 0xFFFFE);
    switch (P->fC) {
    case 0:
        func_800D427C(D_800EB408, 0xEBF, 2);
        func_800D7E80(D_800EB408, D_800EB40C);
        P->fC++;
    case 1:
        if ((s8)func_800D8D74(D_800EB408, 0)) {
            P->fC++;
        }
        break;
    case 2:
        if (!(E40C->f360 & 0x2))
            goto start_pair;
        if (D_800FABE6 & 0xC000) {
            if ((D_800FABE6 & 0xC000) != 0xC000) {
                if (D_800FABE6 & 0x8000) {
                    if (E40C->f386 == 0x9B) {
                        P->f360 |= 8;
                    }
                }
                if (D_800FABE6 & 0x4000) {
                    if (E40C->f386 == 0x9C) {
                        P->f360 |= 8;
                    }
                }
            }
        }
        if (!(P->f360 & 0x8)) {
            P->fC++;
            break;
        }
    start_pair:
        if (E40C->f360 & 0x4)
            goto begin_anim;
        if (!(P->f360 & 0x8))
            break;
    begin_anim:
        func_800A7C40(D_800EB408, P->f0, 0x9A);
        func_800A7F6C(D_800EB408, 0);
        func_800A837C(D_800EB408);
        beginPairedEntityActions(D_800EB408, 0x5D, D_800EB40C, 0x5E);
        P->fC = 3;
        E40C->fC = 3;
        break;
    case 3:
        func_800D427C(D_800EB408, func_800D5438(D_800EB40C, 1), 2);
        P->fC++;
        break;
    case 4:
        if (P->f4 <= 0) {
            func_800D4AD0(D_800EB408);
            beginEntityActionA8D8C(D_800EB408);
            func_800C472C(D_800EB40C, D_800EB408, 2);
        }
        break;
    }
}
