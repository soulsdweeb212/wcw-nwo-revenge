/* @header
 * func_800C858C
 * VRAM 0x800C858C | ROM 0xBBA2C | size 0x13C
 * asm: asm/nonmatchings/code_800BBA00/func_800C858C.s
 */
#include "common.h"

typedef struct {
    s32 f0;
    s16 f4;
    s16 f6;
    s32 f8;
    s16 fC;
    s16 fE;
    u8 pad10[0x10];
    u64 flags;
} Nw2F408c;

typedef struct {
    u8 pad0[8];
    u16 f8;
    u8 padA[0x356];
    u16 f360;
} Nw2F9B00c;

extern void *D_800FAF5C;
extern void *D_800F9B00;

void func_800A9290(void *);
void func_800D427C(void *, s32, s32);
void func_800D4CC4(void *);
void func_800D4AD0(void *);
void func_800A6C48(void *, s32);

#define P ((Nw2F408c *)D_800FAF5C)

/* Three-state action machine on the action object's s16 +0xC:
 *   0: run the enter-action helper, advance to state 1
 *   1: lock the object (flag 0x1000000000); when the input object's +0x360 bit 0
 *      is set, start animation (id +0x8 + 1) with arg 6 and advance to state 2
 *   2: while the +0x4 timer is below 3, run the exit helpers, request action
 *      0x2C and reset to state 1. */
void func_800C858C(void) {
    s16 state = P->fC;

    switch (state) {
    case 0:
        func_800A9290(D_800FAF5C);
        P->fC++;
        /* fallthrough */
    case 1:
        P->flags |= 0x1000000000ULL;
        if (((Nw2F9B00c *)D_800F9B00)->f360 & 1) {
            func_800D427C(D_800FAF5C, (s16)(((Nw2F9B00c *)D_800F9B00)->f8 + 1), 6);
            P->fC++;
        }
        break;
    case 2: {
        s32 timerElapsed = P->f4 < 3;
        P->flags |= 0x1000000000ULL;
        if (timerElapsed) {
            func_800D4CC4(D_800FAF5C);
            func_800D4AD0(D_800FAF5C);
            func_800A6C48(D_800FAF5C, 0x2C);
            P->fC = 1;
        }
        break;
    }
    }
}
