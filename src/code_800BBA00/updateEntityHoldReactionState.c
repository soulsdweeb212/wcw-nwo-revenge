/* @header
 * updateEntityHoldReactionState  (originally func_800D1724)
 * VRAM 0x800D1724 | ROM 0xC4BC4 | size 0x438
 * asm: asm/nonmatchings/code_800BBA00/func_800D1724.s
 */
#include "common.h"

/* Entity hold reaction state machine (states 0..3). The holder D_800FAF5C
 * reacts to its partner D_800F9B00's actionFlags: it aligns to the partner
 * (func_800D2BAC/func_800D2BEC), transfers the hold flag and slot index
 * (0x40000000 / f362), and releases the hold when the animation finishes. */
typedef struct {
    u8 pad0[4];
    s16 f4;             /* +0x04 animation countdown */
    s16 f6;
    u8 pad8[4];
    s16 fC;             /* +0x0C case selector */
    u8 padE[0x12];
    u64 flags20;        /* +0x20 entity status bits */
    u8 pad28[0x16];
    s16 f3E;            /* +0x3E facing quadrant */
    u8 pad40[6];
    s16 f46;            /* +0x46 saved partner slot */
    u8 pad48[0x31A];
    s8 f362;            /* +0x362 hold slot */
    u8 pad363[0x11];
    u8 f374;            /* +0x374 */
} Nw2StateObj;

typedef struct {
    u8 pad0[0x1E];
    u64 flags20;        /* +0x20 entity status bits */
    u8 pad28[0x16];
    s16 f3E;            /* +0x3E facing quadrant */
    u8 pad40[0x320];
    u16 f360;           /* +0x360 action flags */
    s8 f362;            /* +0x362 hold slot */
    u8 pad363[0x37];
    s8 f39A;            /* +0x39A */
    u8 pad39B[9];
    s8 f3A4;            /* +0x3A4 */
    u8 pad3A5[7];
    s32 f3AC;           /* +0x3AC */
} Nw2B00Obj;

extern Nw2StateObj *D_800FAF5C;
extern Nw2B00Obj *D_800F9B00;
extern u8 D_800FABE4;
extern u16 D_800E3CD0[];

void func_800A6BE0(void *, s32);
void beginEntityActionA8D8C(void *);
void func_800B68A0(void *, void *, void *);
void func_800C472C(void *, void *, s32);
s32 func_800D2BAC(void *, void *, f32, s32);
s32 func_800D2BEC(void *, void *, void *, f32, u16, s32);
s16 findBoundaryQuadrant(void *, void *, s32);
void func_800D427C(void *, s16, s32);
void func_800D43B4(void *, s16, s32);
void func_800D4AD0(void *);
s16 func_800D5438(void *, s32);

void updateEntityHoldReactionState(void) {
    D_800FAF5C->flags20 |= 0x1000000000ULL;
    switch (D_800FAF5C->fC) {
    case 0:
        func_800D427C(D_800FAF5C, func_800D5438(D_800F9B00, 1), 2);
        D_800FAF5C->f46 = (s8)D_800F9B00->f3A4;
        D_800FAF5C->fC++;
        /* fallthrough */
    case 1:
        if (!(D_800F9B00->f360 & 0x40)) {
            func_800D2BAC(D_800FAF5C, D_800F9B00, 1.0f, 2);
        }
        if (D_800F9B00->f360 & 8) {
            D_800F9B00->flags20 &= ~0x40000000ULL;
            D_800FAF5C->flags20 |= 0x40000000ULL;
            D_800F9B00->f362 = -1;
            D_800FAF5C->f362 = D_800FABE4;
            func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 0), 1);
            func_800A6BE0(D_800FAF5C, 0x49);
            break;
        }
        if (D_800FAF5C->f4 <= 0) {
            func_800D43B4(D_800FAF5C, func_800D5438(D_800F9B00, 1), 3);
            D_800FAF5C->fC++;
        }
        break;
    case 2:
        if (D_800FAF5C->f4 <= 0) {
            func_800D43B4(D_800FAF5C, func_800D5438(D_800F9B00, 1), 0);
        }
        if (D_800F9B00->f3AC & 0x1000) {
            if (D_800F9B00->f3AC & 0x40000) {
                s16 r = findBoundaryQuadrant(D_800FAF5C, (u8 *)D_800FAF5C + (D_800F9B00->f39A * 16 + 0x5C), 1);
                if (r != -1 && r == D_800FAF5C->f3E) {
                    D_800F9B00->f360 |= 1;
                }
            }
            if (!(D_800F9B00->f360 & 0x40)) {
                func_800D2BAC(D_800FAF5C, D_800F9B00, 1.0f, 2);
            }
        } else {
            s32 r = func_800D2BAC(D_800FAF5C, D_800F9B00, 1.0f, 2);
            if (r & 0xFFFF) {
                if ((D_800F9B00->f3AC & 0x40000) && (D_800E3CD0[D_800F9B00->f3E] & r)) {
                    D_800F9B00->f360 |= 1;
                }
            }
        }
        if (D_800F9B00->f360 & 2) {
            func_800D427C(D_800FAF5C, func_800D5438(D_800F9B00, 3), 3);
            D_800FAF5C->fC++;
        }
        break;
    case 3:
        if (D_800FAF5C->f374 != 1) {
            func_800D2BEC(D_800FAF5C, D_800F9B00, 0, 4.0f, 0, 2);
        }
        if (D_800FAF5C->f4 == 1) {
            func_800B68A0(D_800F9B00, D_800F9B00, D_800FAF5C);
        }
        if (D_800FAF5C->f4 <= 0) {
            func_800D4AD0(D_800FAF5C);
            beginEntityActionA8D8C(D_800FAF5C);
            {
                s16 tmp = D_800FAF5C->f46;
                func_800C472C(D_800F9B00, D_800FAF5C, 2);
                D_800FAF5C->f46 = tmp;
            }
        }
        break;
    }
}
