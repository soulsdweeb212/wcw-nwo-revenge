/* @header
 * func_800A627C
 * VRAM 0x800A627C | ROM 0x9971C | size 0x15C
 * asm: asm/nonmatchings/code_8009D7A0/func_800A627C.s
 */
#include "common.h"

/* func_800A627C: three-step action state machine for the wrestler in
 * D_800EB408. Step 0 sets up the action resource and sub-action 0x54 and
 * advances, step 1 advances once the action becomes eligible, and step 2
 * (when the animation ends) clears the pair link (attached[0] = -1 and
 * WR_FLAG_PAIR_LEADER) and releases the action. */
void func_800A7F6C(void *, s32);
void func_800A837C(void *);
void func_800B68A0(void *, void *, void *);
void func_800CE388(void *, void *, void *);
s8 func_800CE6E4(void *, s32);
void func_800D4AD0(void *);
extern s32 D_800F9B24[][4];
extern s8 D_800FADB8;

void func_800A627C(void) {
    Wrestler *p;
    Wrestler *q;

    switch (D_800EB408->step) {
    case 0:
        func_800CE388(D_800EB408, D_800EB40C, D_800F9B24[D_800FADB8]);
        func_800A7F6C(D_800EB408, 0x54);
        func_800A837C(D_800EB408);
        D_800EB408->step++;
    case 1:
        if (func_800CE6E4(D_800EB408, D_800F9B24[D_800FADB8][0])) {
            D_800EB408->step++;
        }
        break;
    case 2:
        if (D_800EB408->animFramesLeft <= 0) {
            func_800B68A0(D_800EB408, D_800EB408, D_800EB40C);
            p = D_800EB408;
            p->attached[0] = -1;
            p->flags &= (q = D_800EB408, ~WR_FLAG_PAIR_LEADER);
            func_800D4AD0(q);
            func_800A6C48(D_800EB408, 0x2B);
        }
        break;
    }
}
