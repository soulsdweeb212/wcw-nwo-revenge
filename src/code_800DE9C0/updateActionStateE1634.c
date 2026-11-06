/* @header
 * updateActionStateE1634  (originally func_800E1634)
 * VRAM 0x800E1634 | ROM 0xD4AD4 | size 0x2E8
 * asm: asm/nonmatchings/code_800DE9C0/updateActionStateE1634.s
 */
#include "common.h"

/* D_800FAF5C step machine (steps 0..2): step 0 chooses a turning animation from
 * the heading delta against D_800F9B14 and latches a direction bit; step 1 waits
 * for the animation while step-rotating toward the chosen turn, then sets up a
 * 4.5-unit moveDelta; step 2 translates the wrestler by it and, when the
 * animation ends, flags the action done. */
extern u16 D_800FABE6;
extern s32 D_800F9B14;

s32 func_800D35B0(s32, s32);
s32 func_800D3684(s32, s32);
void func_800D2B64(void *, f32, u16, s32);
void func_800D427C(void *, s16, s32);
void func_800D4AD0(void *);
void func_800D37C0(s32, f32, void *);
void translateEntityXZ(void *, void *);

void updateActionStateE1634(void) {
    s16 anim;
    s32 s1;

    switch (D_800FAF5C->step) {
    case 0:
        if (!(D_800FABE6 & 0x300)) {
            s1 = func_800D3684(D_800FAF5C->heading, D_800F9B14);
            if ((D_800FAF5C->flags & 0x0ULL) || (D_800FAF5C->flags & 0x200000)) {
                if (s1 >= 0) {
                    D_800FABE6 |= 0x100;
                } else {
                    D_800FABE6 |= 0x200;
                }
            } else if (s1 < 0) {
                D_800FABE6 |= 0x100;
            } else {
                D_800FABE6 |= 0x200;
            }
        }
        if ((D_800FAF5C->flags & 0x0ULL) || (D_800FAF5C->flags & 0x200000)) {
            anim = 0xF20;
            if (D_800FABE6 & 0x200) {
                anim = 0xF1E;
            }
        } else {
            anim = (-((D_800FABE6 & 0x200) == 0) & 0xF1F) | 0xF1D;
        }
        func_800D427C(D_800FAF5C, anim, 6);
        D_800FAF5C->step = D_800FAF5C->step + 1;
        break;
    case 1:
        func_800D2B64(D_800FAF5C, 2.0f, 0, 0xFFFFE);
        if (D_800FAF5C->animFramesLeft <= 0) {
            if (!(D_800FAF5C->flags & 0x0ULL) && !(D_800FAF5C->flags & 0x200000)) {
                D_800FAF5C->heading = func_800D35B0(D_800FAF5C->heading, 0x800);
            }
            func_800D4AD0(D_800FAF5C);
            if (D_800FAF5C->animId >= 0xF1D) {
                if (D_800FAF5C->animId < 0xF1F) {
                    anim = 0xF21;
                    s1 = func_800D35B0(D_800FAF5C->heading, -0x400);
                } else if (D_800FAF5C->animId < 0xF21) {
                    anim = 0xF22;
                    s1 = func_800D35B0(D_800FAF5C->heading, 0x400);
                }
            }
            func_800D427C(D_800FAF5C, anim, 1);
            func_800D37C0(s1, 4.5f, D_800FAF5C->moveDelta);
            D_800FAF5C->step = D_800FAF5C->step + 1;
        }
        break;
    case 2:
        translateEntityXZ(D_800FAF5C, D_800FAF5C->moveDelta);
        func_800D2B64(D_800FAF5C, 2.0f, 0, 0xFFFFE);
        if (D_800FAF5C->animFramesLeft <= 0) {
            D_800FAF5C->flags |= 0x200000;
            func_800A6C48(D_800FAF5C, 0x43);
        }
        break;
    }
}
