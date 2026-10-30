/* @header
 * func_800CA114
 * VRAM 0x800CA114 | ROM 0xBD5B4 | size 0x1E8
 * asm: asm/nonmatchings/code_800BBA00/func_800CA114.s
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
    u8 pad28[0x338];
    u16 f360;
} Nw2CA114Obj;

typedef struct {
    u8 pad0[8];
    u16 f8;
} Nw2F9B00CA114;

extern void *D_800FAF5C;
extern Nw2F9B00CA114 *D_800F9B00;
void func_800A9290(void *);
s8 func_800D4CC4(void *);
void func_800D4AD0(void *);
void func_800D427C(void *, s16, s32);
void func_800A6C48(void *, s32);

/* 'Get-up / recovery' action for the entity D_800FAF5C. State 0 enters the pose
 * and raises the 0x1000000000 flag. State 1 waits for the f360 bits: bit 1 skips
 * to state 3 and lights 0x10000000, bit 0 starts the animation from D_800F9B00
 * and advances. State 2 re-raises the flag and, when the timer expires, drops the
 * pose, advances, and lights 0x10000000. State 3 restarts the animation from
 * D_800F9B00 (variant 1 or 6 depending on bit 0) and advances. State 4 finishes
 * into action 0x39 when f360 has bit 2. */
void func_800CA114(void) {
    switch (((Nw2CA114Obj *)D_800FAF5C)->fC) {
    case 0:
        func_800A9290(D_800FAF5C);
        ((Nw2CA114Obj *)D_800FAF5C)->fC++;
        /* fall through */
    case 1:
        ((Nw2CA114Obj *)D_800FAF5C)->flags |= 0x1000000000ULL;
        if (((Nw2CA114Obj *)D_800FAF5C)->f360 & 2) {
            ((Nw2CA114Obj *)D_800FAF5C)->fC = 3;
            ((Nw2CA114Obj *)D_800FAF5C)->flags |= 0x10000000;
        } else if (((Nw2CA114Obj *)D_800FAF5C)->f360 & 1) {
            func_800D427C(D_800FAF5C, (s16)(D_800F9B00->f8 + 1), 6);
            ((Nw2CA114Obj *)D_800FAF5C)->fC++;
        }
        break;
    case 2:
        ((Nw2CA114Obj *)D_800FAF5C)->flags |= 0x1000000000ULL;
        if (((Nw2CA114Obj *)D_800FAF5C)->f4 <= 0) {
            func_800D4CC4(D_800FAF5C);
            func_800D4AD0(D_800FAF5C);
            ((Nw2CA114Obj *)D_800FAF5C)->fC++;
            ((Nw2CA114Obj *)D_800FAF5C)->flags |= 0x10000000;
        }
        break;
    case 3:
        if (((Nw2CA114Obj *)D_800FAF5C)->f360 & 2) {
            if (((Nw2CA114Obj *)D_800FAF5C)->f360 & 1) {
                func_800D427C(D_800FAF5C, (s16)(D_800F9B00->f8 + 1), 1);
            } else {
                func_800D427C(D_800FAF5C, (s16)(D_800F9B00->f8 + 1), 6);
            }
            ((Nw2CA114Obj *)D_800FAF5C)->fC++;
        }
        break;
    case 4:
        if (((Nw2CA114Obj *)D_800FAF5C)->f360 & 4)
            func_800A6C48(D_800FAF5C, 0x39);
        break;
    }
}
