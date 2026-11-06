/* @header
 * updatePairedEntityStateA4028  (originally func_800A4028)
 * VRAM 0x800A4028 | ROM 0x974C8 | size 0x24C
 * asm: asm/nonmatchings/code_8009D7A0/updatePairedEntityStateA4028.s
 */
#include "common.h"

/* Paired-entity action state machine for D_800EB408 with its opponent
 * D_800EB40C (switch on step):
 *  0 -> choose the clip from the counterKind bit word. When any of 0x1BE is
 *       set the animation is one of 0x9E/0xA0/0xA2/0xA4/0xA6/7/8 using the
 *       character bank D_800FABE4; otherwise it is clip 0x99 (or move.moveCode
 *       when bit 1 is set) for bank D_800FADB8. It then sets up the pair
 *       and advances;
 *  1 -> when bit 0x1000000 of move.flags is set push forward, else run the
 *       paired interaction; once the animation ends, if func_800A83DC signals
 *       completion, clear flag 0x40000000 and end the action. */
extern u8 D_800FABE4;
extern u8 D_800FADB8;

void func_800A7328(void *);
void func_800A7C40(void *, s8, s16);
void func_800A7F6C(void *, s32);
void func_800A837C(void *);
s8 func_800A83DC(void *, void *);
void func_800B68A0(void *, void *, void *);
void func_800D25D0(void *, f32);
s32 func_800D2B64(void *, f32, u16, s32);
s32 func_800D2BEC(void *, void *, void *, f32, u16, s32);
void func_800D427C(void *, s16, s32);
void func_800D4AD0(void *);
s16 func_800D5438(void *, s32);

void updatePairedEntityStateA4028(void) {
    Wrestler *p;
    unsigned anim;
    u16 f;
    Wrestler *q;
    long bank;

    switch (D_800EB408->step) {
    case 0:
        f = D_800EB408->counterKind;
        if (f & 0x1BE) {
            bank = *(u8 *)&D_800FABE4;
            if (f & 2)
                anim = 0x9E;
            if (f & 4)
                anim = 0xA0;
            if (f & 8)
                anim = 0xA2;
            if (f & 0x10)
                anim = 0xA4;
            if (f & 0x20)
                anim = 0xA6;
            if (f & 0x80)
                anim = 7;
            if (f & 0x100)
                anim = 8;
        } else {
            bank = D_800FADB8;
            anim = 0x99;
            if (f & 1)
                anim = D_800EB408->move.moveCode;
        }
        func_800A7C40(D_800EB408, bank, anim);
        func_800A7F6C(D_800EB408, 0);
        func_800A837C(D_800EB408);
        func_800A7328(D_800EB408);
        func_800D427C(D_800EB408, func_800D5438(D_800EB408, 0), 2);
        D_800EB408->step = D_800EB408->step + 1;
        break;
    case 1:
        if (D_800EB408->move.flags & 0x1000000) {
            f32 four = 4.0f;
            func_800D25D0(D_800EB408, four);
            func_800D2B64(D_800EB408, four, 0, 0xFFFFE);
        } else {
            func_800D2BEC(D_800EB408, D_800EB40C, 0, 4.0f, 0, 0xFFFFE);
        }
        if (D_800EB408->animFramesLeft <= 0) {
            func_800B68A0(D_800EB408, D_800EB408, D_800EB40C);
            if ((func_800A83DC(D_800EB408, D_800EB40C) << 24) == 0) {
                p = D_800EB408;
                p->attached[0] = -1;
                p->flags &= (q = D_800EB408, ~WR_FLAG_PAIR_LEADER);
                func_800D4AD0(q);
                func_800A6C48(D_800EB408, 0x2B);
            }
        }
        break;
    }
}
