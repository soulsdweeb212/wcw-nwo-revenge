/* @header
 * updateActionStateE1634  (originally func_800E1634)
 * VRAM 0x800E1634 | ROM 0xD4AD4 | size 0x2E8
 * asm: asm/nonmatchings/code_800DE9C0/func_800E1634.s
 */
#include "common.h"

/* D_800FAF5C action-record state machine (cases 0..2): state 0 chooses a turning
 * animation from the heading delta against D_800F9B14 and latches a direction bit;
 * state 1 runs a 2.0s timer while step-rotating toward the chosen turn; state 2
 * translates the entity and, on timeout, flags the action done. */
typedef struct {
    s32 f0;
    s16 timer, f6;
    s16 anim;
    s16 fA;
    s16 state;
    u8 padE[0x12];
    u64 flags;
    u8 pad28[0x30];
    s32 heading;
    u8 pad5C[0x2E0];
} Nw2F5C;

extern void *D_800FAF5C;
extern u16 D_800FABE6;
extern s32 D_800F9B14;

s32 func_800D35B0(s32, s32);
s32 func_800D3684(s32, s32);
void func_800D2B64(void *, f32, u16, s32);
void func_800D427C(void *, s16, s32);
void func_800D4AD0(void *);
void func_800A6C48(void *, s32);
void func_800D37C0(s32, f32, void *);
void translateEntityXZ(void *, void *);

#define P ((Nw2F5C *)D_800FAF5C)

void updateActionStateE1634(void) {
    s16 anim;
    s32 s1;

    switch (P->state) {
    case 0:
        if (!(D_800FABE6 & 0x300)) {
            s1 = func_800D3684(P->heading, D_800F9B14);
            if ((P->flags & 0x0ULL) || (P->flags & 0x200000)) {
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
        if ((P->flags & 0x0ULL) || (P->flags & 0x200000)) {
            anim = 0xF20;
            if (D_800FABE6 & 0x200) {
                anim = 0xF1E;
            }
        } else {
            anim = (-((D_800FABE6 & 0x200) == 0) & 0xF1F) | 0xF1D;
        }
        func_800D427C(D_800FAF5C, anim, 6);
        P->state = P->state + 1;
        break;
    case 1:
        func_800D2B64(D_800FAF5C, 2.0f, 0, 0xFFFFE);
        if (P->timer <= 0) {
            if (!(P->flags & 0x0ULL) && !(P->flags & 0x200000)) {
                P->heading = func_800D35B0(P->heading, 0x800);
            }
            func_800D4AD0(D_800FAF5C);
            if (P->anim >= 0xF1D) {
                if (P->anim < 0xF1F) {
                    anim = 0xF21;
                    s1 = func_800D35B0(P->heading, -0x400);
                } else if (P->anim < 0xF21) {
                    anim = 0xF22;
                    s1 = func_800D35B0(P->heading, 0x400);
                }
            }
            func_800D427C(D_800FAF5C, anim, 1);
            func_800D37C0(s1, 4.5f, (u8 *)D_800FAF5C + 0x33C);
            P->state = P->state + 1;
        }
        break;
    case 2:
        translateEntityXZ(D_800FAF5C, (u8 *)D_800FAF5C + 0x33C);
        func_800D2B64(D_800FAF5C, 2.0f, 0, 0xFFFFE);
        if (P->timer <= 0) {
            P->flags |= 0x200000;
            func_800A6C48(D_800FAF5C, 0x43);
        }
        break;
    }
}
