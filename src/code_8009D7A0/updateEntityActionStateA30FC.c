#include "common.h"

/* Taunt/action state machine for D_800EB408 (switch on +0x0C):
 *  0 -> choose an animation id from the +0x30 input flags and play it. The
 *       mask 0xE1 selects one of two id families (3/4/5 or 6/7/8) driven by
 *       flags 0x10000000/0x20000000/0x40000000, then advance;
 *  1 -> wait out animation, then run the shared DONE() tail;
 *  2 -> play the next animation (id from selector 3) and advance;
 *  3 -> wait out animation, then run the shared DONE() tail.
 * DONE() starts the follow-up clip and finishes the action with timer 100. */
typedef struct { s32 f0; s16 f4, f6; s32 f8; s16 fC, fE; u8 p10[6]; s16 f16; u8 p18[24]; u32 f30; } OA30;
void func_800A7D1C(void *, s32);
void func_800B68A0(void *, void *, void *);
s32 func_800D2B64(void *, f32, u16, s32);
void func_800D427C(void *, s32, s32);
s16 func_800D4D44(void *, s32, f32);
#define P ((OA30 *)D_800EB408)
#define DONE() func_800D427C(D_800EB408, func_800D4D44(D_800EB408, 2, 0.0f), 3); func_800A6C48(D_800EB408, 0x40); P->f16 = 100; P->fC = 1

void updateEntityActionStateA30FC(void) {
    s16 id;
    switch (P->fC) {
    case 0:
        if (P->f30 & 0xE1) {
            if (P->f30 & 0x10000000)
                id = func_800D4D44(D_800EB408, 3, 0.0f);
            if (P->f30 & 0x20000000)
                id = func_800D4D44(D_800EB408, 4, 0.0f);
            if (P->f30 & 0x40000000)
                id = func_800D4D44(D_800EB408, 5, 0.0f);
        } else {
            if (P->f30 & 0x10000000)
                id = func_800D4D44(D_800EB408, 6, 0.0f);
            if (P->f30 & 0x20000000)
                id = func_800D4D44(D_800EB408, 7, 0.0f);
            if (P->f30 & 0x40000000)
                id = func_800D4D44(D_800EB408, 8, 0.0f);
        }
        func_800D427C(D_800EB408, id, 1);
        P->fC++;
        break;
    case 1:
        func_800D2B64(D_800EB408, 1.0f, 0, 2);
        if (P->f4 <= 0) {
            func_800A7D1C(D_800EB408, 3);
            func_800B68A0(D_800EB408, D_800EB408, D_800EB408);
            DONE();
        }
        break;
    case 2:
        func_800D427C(D_800EB408, func_800D4D44(D_800EB408, 3, 0.0f), 1);
        P->fC++;
        break;
    case 3:
        func_800D2B64(D_800EB408, 1.0f, 0, 2);
        if (P->f4 <= 0) {
            DONE();
        }
        break;
    }
}
