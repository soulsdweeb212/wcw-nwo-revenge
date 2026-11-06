/* @header
 * updateActionStateA26AC  (originally func_800A26AC)
 * VRAM 0x800A26AC | ROM 0x95B4C | size 0x2D0
 * asm: asm/nonmatchings/code_8009D7A0/updateActionStateA26AC.s
 */
#include "common.h"

/* D_800EB408 action step machine (cases 0..2): step 0 raises the flag and picks a
 * guard/dodge animation (on the apron: also face D_800E3CA0[ringSide]); step 1 waits
 * on the contact window (D_800FADCF input bit, attachment probe) to advance; step 2
 * times the action out and clears it. */
extern u16 D_800FABE6;
extern u16 D_800FAF8A;
extern s8 D_800FAF78;
extern u8 D_800FADCF;
extern f32 D_800F9B0C;
extern s32 D_800E3CA0[];

void func_800D25D0(void *, f32);
s32 func_800D2B64(void *, f32, u16, s32);
void func_800D427C(void *, s16, s32);
void func_800D4AD0(void *);
void func_800D6658(void *, void *, u16, s32, f32);
void func_800D7B54(void *, u16, u16, s32);
s8 func_800D7894(void *, u16);

void updateActionStateA26AC(void) {
    func_800D25D0(D_800EB408, 4.0f);
    func_800D2B64(D_800EB408, 2.0f, 0, 2);
    switch (D_800EB408->step) {
    case 0:
        D_800EB408->flags |= 0x1000000000ULL;
        if ((D_800EB408->flags & 0x0ULL) != 0 || (D_800EB408->flags & 0x80) != 0) {
            func_800D427C(D_800EB408, 0xF5C, 0);
            D_800EB408->heading = D_800E3CA0[D_800EB408->ringSide];
        } else {
            func_800D427C(D_800EB408, 0xF5A, 1);
        }
        D_800EB408->step++;
        break;
    case 1:
        if ((D_800EB408->flags & 0x0ULL) == 0 && (D_800EB408->flags & 0x80) == 0) {
            func_800D6658(D_800EB408, D_800EB40C, D_800FABE6, 1, D_800F9B0C);
            func_800D7B54(D_800EB408, D_800FABE6, D_800FAF8A, 1);
        }
        if (D_800FADCF & 0x40) {
            if ((D_800EB408->flags & 0x0ULL) != 0 || (D_800EB408->flags & 0x4000) != 0) {
                if ((D_800EB408->flags & 0x0ULL) != 0 || (D_800EB408->flags & 0x80) != 0) {
                    func_800D427C(D_800EB408, 0xF5D, 0);
                } else {
                    func_800D427C(D_800EB408, 0xF5B, 3);
                }
                D_800EB408->step++;
                break;
            }
        }
        if (func_800D7894(D_800EB408, D_800FAF8A) != 0) {
            if (D_800FAF78 != 0) {
                D_800EB408->escapeTimer = 0;
                break;
            }
            if ((D_800EB408->flags & 0x0ULL) != 0 || (D_800EB408->flags & 0x80) != 0) {
                func_800D427C(D_800EB408, 0xF5D, 0);
            } else {
                func_800D427C(D_800EB408, 0xF5B, 3);
            }
            D_800EB408->step++;
        }
        break;
    case 2:
        if ((D_800EB408->flags & 0x0ULL) == 0 && (D_800EB408->flags & 0x80) == 0) {
            func_800D7B54(D_800EB408, D_800FABE6, D_800FAF8A, 1);
        }
        if (D_800EB408->animFramesLeft <= 0) {
            func_800D4AD0(D_800EB408);
            func_800A6C48(D_800EB408, 0x2B);
        }
        break;
    }
}
