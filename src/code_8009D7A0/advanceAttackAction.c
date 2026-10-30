/* @header
 * advanceAttackAction  (originally func_8009F654)
 * VRAM 0x8009F654 | ROM 0x92AF4 | size 0xE8
 * asm: asm/nonmatchings/code_8009D7A0/advanceAttackAction.s
 */
#include "common.h"

void func_800A7C40(void *, s8, s16);
void func_800A7F6C(void *, s32);
void func_800A837C(void *);
s32 func_800D2B64(void *, f32, u16, s32);
void func_800D427C(void *, s16, s32);
void func_800D4AD0(void *);
s16 func_800D5438(void *, s32);
extern s8 D_800FADB8;

/* Attack action on D_800EB408: state 0 plays animation 0xAE, sets the action
 * from func_800D5438 and runs the two setup handlers; state 1 drives the action
 * until the entry value at +0x4 equals the state, then completes with command
 * 0x2B. */
void advanceAttackAction(void) {
    s16 state = ((Nw2F408 *)D_800EB408)->fC;
    switch (state) {
    case 0:
        func_800A7C40(D_800EB408, D_800FADB8, 0xAE);
        func_800D427C(D_800EB408, func_800D5438(D_800EB408, 0), 1);
        func_800A7F6C(D_800EB408, 0);
        func_800A837C(D_800EB408);
        ((Nw2F408 *)D_800EB408)->fC++;
        break;
    case 1:
        func_800D2B64(D_800EB408, 1.0f, 0, 0xFFFFE);
        if (((Nw2F408 *)D_800EB408)->f4 == state) {
            func_800D4AD0(D_800EB408);
            func_800A6C48(D_800EB408, 0x2B);
        }
        break;
    }
}
