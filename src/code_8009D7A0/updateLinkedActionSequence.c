/* @header
 * updateLinkedActionSequence  (originally func_800A58BC)
 * VRAM 0x800A58BC | ROM 0x98D5C | size 0x184
 * asm: asm/nonmatchings/code_8009D7A0/updateLinkedActionSequence.s
 */
#include "common.h"

void func_800A7F6C(void *, s32);
void func_800A837C(void *);
void func_800B68A0(void *, void *, void *);
void func_800CE388(void *, void *, void *);
s8 func_800CE6E4(void *, s32);
s32 func_800D2B64(void *,f32,u16,s32);
void func_800D4AD0(void *);
extern s32 D_800F9B24[][4];
extern s8 D_800FADB8;
/* Three-step handler for a linked action on D_800EB408 (step).
 * Step 0 kicks off the paired action using the D_800F9B24 record for the
 * current wrestler, sets animation 0x54 and advances. Step 1 waits for the
 * paired action to finish. Step 2 runs boundary correction from animFrame 0x2C
 * on and, when the animation ends, clears attached[0] and the pair-leader flag,
 * tears the action down and returns to action 0x2B. */
void updateLinkedActionSequence(void) {
    Wrestler *p;
    Wrestler *q;
    switch (D_800EB408->step) {
    case 0:
        func_800CE388(D_800EB408,D_800EB40C,D_800F9B24[D_800FADB8]);
        func_800A7F6C(D_800EB408,0x54);
        func_800A837C(D_800EB408);
        D_800EB408->step++;
    case 1:
        if(func_800CE6E4(D_800EB408,D_800F9B24[D_800FADB8][0])) D_800EB408->step++;
        break;
    case 2:
        if(D_800EB408->animFrame>=0x2C) func_800D2B64(D_800EB408,2.0f,0,0xFFFFE);
        if(D_800EB408->animFramesLeft<=0) {
            func_800B68A0(D_800EB408,D_800EB408,D_800EB40C);
            p=D_800EB408;
            p->attached[0]=-1;
            p->flags&=(q=D_800EB408,~WR_FLAG_PAIR_LEADER);
            func_800D4AD0(q);
            func_800A6C48(D_800EB408,0x2B);
        }
        break;
    }
}
