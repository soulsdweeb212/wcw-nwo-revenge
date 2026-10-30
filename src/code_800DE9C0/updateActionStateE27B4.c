/* @header
 * updateActionStateE27B4  (originally func_800E27B4)
 * VRAM 0x800E27B4 | ROM 0xD5C54 | size 0x264
 * asm: asm/nonmatchings/code_800DE9C0/updateActionStateE27B4.s
 */
#include "common.h"

/* Action state machine for D_800FAF5C (switch on +0x0C):
 *  0 -> mark flag 0x1000000000, run the pre-action (func_800E212C), play the
 *       clip from selector 1 at D_800F9B0C speed, then fall through;
 *  1 -> mark flag 0x1000000000, wait for the action to be ready
 *       (func_800D8D74); on success play clip 0x1002 and, if the field
 *       interaction succeeds (func_800B71F8), begin the follow-up scene;
 *  2 -> once the timer expires: if the mirror flag 0x1000000000000 is set,
 *       copy the current field record D_800F98E0 into the partner record
 *       D_800F98E1 (indexed by D_800F99A0[+mode]) and play clip 0x1013 or
 *       0x1014 depending on flag 0x2000000000000; otherwise play the
 *       failure clip 0x1015;
 *  3 -> once the timer expires, end the action and start action 1. */
typedef struct { s32 f0; s16 f4, f6; s32 f8; s16 fC, fE; u8 p10[16]; u64 flags; } OE27;
extern void *D_800FAF5C;
extern f32 D_800F9B0C;
extern s8 D_800FADB8, D_800F99A0[];
extern u8 D_800F98E0[], D_800F98E1[];
void func_800E212C(void *);
s16 func_800D4D44(void *, s32, f32);
void func_800D427C(void *, s32, s32);
void func_800D7E80(void *, s32);
s8 func_800D8D74(void *, s32);
s8 func_800B71F8(void *, s32, s32);
void func_800E1920(void *, s32);
void func_800D4AD0(void *);
#define P ((OE27 *)D_800FAF5C)

void updateActionStateE27B4(void) {
    s16 state = P->fC;
    s16 id;
    switch (state) {
    case 0:
        P->flags |= 0x1000000000ULL;
        func_800E212C(D_800FAF5C);
        func_800D427C(D_800FAF5C, func_800D4D44(D_800FAF5C, 1, D_800F9B0C), 2);
        func_800D7E80(D_800FAF5C, 0);
        P->fC++;
    case 1:
        P->flags |= 0x1000000000ULL;
        if (func_800D8D74(D_800FAF5C, 0)) {
            func_800D427C(D_800FAF5C, 0x1002, 2);
            if (func_800B71F8(D_800FAF5C, 0, 10))
                func_800E1920(D_800FAF5C, 1);
            P->fC++;
        }
        break;
    case 2:
        if (P->f4 <= 0) {
            if (P->flags & 0x1000000000000ULL) {
                s32 off = D_800F99A0[D_800FADB8] * 48;
                D_800F98E1[off] = D_800F98E0[off];
                id = (P->flags & 0x2000000000000ULL) ? 0x1014 : 0x1013;
                P->fC++;
            } else {
                id = 0x1015;
                P->fC = state + 1;
            }
            func_800D427C(D_800FAF5C, id, 1);
        }
        break;
    case 3:
        if (P->f4 <= 0) {
            func_800D4AD0(D_800FAF5C);
            func_800A6C48(D_800FAF5C, 1);
        }
        break;
    }
}
