#include "common.h"

/* D_800EB408 action state machine (cases 0..2): state 0 raises the flag and picks a
 * guard/dodge animation from the facing quadrant; state 1 waits on the contact window
 * (D_800FADCF input bit, attachment probe) to advance; state 2 times the action out
 * and clears it. */
typedef struct {
    s32 f0;
    s16 timer, f6;
    s32 f8;
    s16 state, fE;
    u8 pad10[8];
    s16 f18;
    u8 pad1A[6];
    u64 flags;
    u8 pad28[0x14];
    s16 quadrant;
    u8 pad3E[0x1A];
    s32 heading;
} Nw2F408a;

extern void *D_800EB408;
extern void *D_800EB40C;
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
void func_800A6C48(void *, s32);
void func_800D6658(void *, void *, u16, s32, f32);
void func_800D7B54(void *, u16, u16, s32);
s8 func_800D7894(void *, u16);

#define P ((Nw2F408a *)D_800EB408)

void updateActionStateA26AC(void) {
    func_800D25D0(D_800EB408, 4.0f);
    func_800D2B64(D_800EB408, 2.0f, 0, 2);
    switch (P->state) {
    case 0:
        P->flags |= 0x1000000000ULL;
        if ((P->flags & 0x0ULL) != 0 || (P->flags & 0x80) != 0) {
            func_800D427C(D_800EB408, 0xF5C, 0);
            P->heading = D_800E3CA0[P->quadrant];
        } else {
            func_800D427C(D_800EB408, 0xF5A, 1);
        }
        P->state++;
        break;
    case 1:
        if ((P->flags & 0x0ULL) == 0 && (P->flags & 0x80) == 0) {
            func_800D6658(D_800EB408, D_800EB40C, D_800FABE6, 1, D_800F9B0C);
            func_800D7B54(D_800EB408, D_800FABE6, D_800FAF8A, 1);
        }
        if (D_800FADCF & 0x40) {
            if ((P->flags & 0x0ULL) != 0 || (P->flags & 0x4000) != 0) {
                if ((P->flags & 0x0ULL) != 0 || (P->flags & 0x80) != 0) {
                    func_800D427C(D_800EB408, 0xF5D, 0);
                } else {
                    func_800D427C(D_800EB408, 0xF5B, 3);
                }
                P->state++;
                break;
            }
        }
        if (func_800D7894(D_800EB408, D_800FAF8A) != 0) {
            if (D_800FAF78 != 0) {
                P->f18 = 0;
                break;
            }
            if ((P->flags & 0x0ULL) != 0 || (P->flags & 0x80) != 0) {
                func_800D427C(D_800EB408, 0xF5D, 0);
            } else {
                func_800D427C(D_800EB408, 0xF5B, 3);
            }
            P->state++;
        }
        break;
    case 2:
        if ((P->flags & 0x0ULL) == 0 && (P->flags & 0x80) == 0) {
            func_800D7B54(D_800EB408, D_800FABE6, D_800FAF8A, 1);
        }
        if (P->timer <= 0) {
            func_800D4AD0(D_800EB408);
            func_800A6C48(D_800EB408, 0x2B);
        }
        break;
    }
}
