#include "common.h"

/* Paired-entity action state machine for D_800EB408 with partner
 * D_800EB40C (switch on +0x0C):
 *  0 -> start action 0xEBE (setup 0x21), pair the entities, fall through;
 *  1 -> wait for readiness; set the action timer (+0x16) to 0x5A, or 0x1E
 *       when the partner's +0x20 has flag 0x80000, then advance;
 *  2 -> React: on controller bits D_800FAF8A & 0xC000 set flag 2 and play
 *       clip 0x9B (bit 0x8000) or 0x9C, else count the timer down and set
 *       flag 4 when it expires;
 *  3 -> play the reaction animation, advance;
 *  4 -> when the timer expires, end the pair: clear flag 0x40000000,
 *       run func_800A83DC and finish the action. */
typedef struct {
    s32 f0;
    s16 f4;
    s16 f6;
    s32 f8;
    s16 fC;
    s16 fE;
    u8 pad10[6];
    u16 f16;
    u8 pad18[8];
    u64 f20;
    u8 pad28[0x338];
    u16 f360;
    s8 f362;
} Nw2Entity;

s32 func_800D2BEC(void *, void *, void *, f32, u16, s32);
void func_800D427C(void *, s16, s32);
void func_800A7F6C(void *, s32);
void func_800A837C(void *);
void func_800D7E80(void *, void *);
s8 func_800D8D74(void *, s32);
void func_800A7C40(void *, s8, s16);
s16 func_800D5438(void *, s16);
void func_800B68A0(void *, void *, void *);
s8 func_800A83DC(void *, void *);
void func_800D4AD0(void *);
void func_800A6C48(void *, s32);
extern u8 *D_800EB40C;
extern u16 D_800FAF8A;

#define P ((Nw2Entity *)D_800EB408)

void updatePairedEntityStateA4864(void) {
    s16 state;
    s16 anim;

    func_800D2BEC(D_800EB408, D_800EB40C, 0, 4.0f, 0, 0xFFFFE);
    state = P->fC;
    switch (state) {
    case 0:
        func_800D427C(D_800EB408, 0xEBE, 2);
        func_800A7F6C(D_800EB408, 0x21);
        func_800A837C(D_800EB408);
        func_800D7E80(D_800EB408, D_800EB40C);
        P->fC++;
    case 1:
        if ((s8)func_800D8D74(D_800EB408, 0)) {
            if (*(u64 *)((u8 *)D_800EB40C + 0x20) & 0x80000ULL) {
                P->f16 = 0x1E;
            } else {
                P->f16 = 0x5A;
            }
            P->fC++;
        }
        break;
    case 2:
        if (D_800FAF8A & 0xC000) {
            P->f360 |= 2;
            anim = 0x9C;
            if (D_800FAF8A & 0x8000) {
                anim = 0x9B;
            }
            func_800A7C40(D_800EB408, *(s8 *)D_800EB408, anim);
            P->fC++;
        } else {
            P->f16--;
            if ((s16)P->f16 < 0) {
                P->f360 |= 4;
            }
        }
        break;
    case 3:
        func_800D427C(D_800EB408, func_800D5438(D_800EB408, 0), 2);
        P->fC++;
        break;
    case 4:
        if (P->f4 <= 0) {
            Nw2Entity *p;
            func_800B68A0(D_800EB408, D_800EB408, D_800EB40C);
            if ((s8)func_800A83DC(D_800EB408, D_800EB40C) == 0) {
                p = P;
                p->f362 = -1;
                p->f20 &= 0xFFFFFFFFBFFFFFFFULL;
                func_800D4AD0(D_800EB408);
                func_800A6C48(D_800EB408, 0x2B);
            }
        }
        break;
    }
}
