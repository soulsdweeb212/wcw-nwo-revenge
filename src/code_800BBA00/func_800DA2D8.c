#include "common.h"

extern void *D_800FAF5C;
extern u8 D_800F9D10[];
void func_800D427C(void *, s32, s32);
void func_800D7E80(void *, void *);
void func_800E212C(void *);
void func_800D8D74(void *, s32);
void func_800D4AD0(void *);
#define FIELD(p,t,o) (*(t *)((u8 *)(p)+(o)))

/* Action sequence on D_800FAF5C (state at +0xC, timer at +4, target id at
 * +0x355). States 0 and 2 play animation 0x108A, attach to the target's record
 * (D_800F9D10 + id*0x3B0) and attach the entity, advancing the state. States 1
 * and 3 drive the attach and, once the timer expires, complete the action and
 * issue command 0x2B. */
void func_800DA2D8(void) {
    switch (FIELD(D_800FAF5C, s16, 0xC)) {
    case 0: case 2:
        func_800D427C(D_800FAF5C, 0x108A, 2);
        func_800D7E80(D_800FAF5C, D_800F9D10 + FIELD(D_800FAF5C, s8, 0x355) * 0x3B0);
        func_800E212C(D_800FAF5C);
        FIELD(D_800FAF5C, s16, 0xC)++;
        break;
    case 1: case 3:
        func_800D8D74(D_800FAF5C, 0);
        if (FIELD(D_800FAF5C, s16, 4) <= 0) {
            func_800D4AD0(D_800FAF5C);
            func_800A6C48(D_800FAF5C, 0x2B);
        }
        break;
    }
}
