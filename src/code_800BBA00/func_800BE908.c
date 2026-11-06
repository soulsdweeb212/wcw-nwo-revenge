/* @header
 * func_800BE908
 * VRAM 0x800BE908 | ROM 0xB1DA8 | size 0x20C
 * asm: asm/nonmatchings/code_800BBA00/func_800BE908.s
 */
#include "common.h"

void func_800D427C(void *, s16, s32);
s32 func_800D35B0(s32, s32);
s8 func_800BF150(void *);
void func_800A7D1C(void *, s32);
void func_800B68A0(void *, void *, void *);
void func_800D4AD0(void *);
void beginEntityActionA8D8C(void *);
void func_800C472C(void *, void *, s32);
void func_800BE908(void)
{
    s32 x;
    switch (D_800FAF5C->step) {
    case 0:
        func_800D427C(D_800FAF5C, (s16)(D_800F9B00->animId + 1), 3);
        D_800FAF5C->step++;
        break;
    case 1:
        if (D_800FAF5C->animFramesLeft <= 0) {
            D_800FAF5C->heading = func_800D35B0(D_800FAF5C->heading, (D_800F9B00->pairSignals & 1) ? -0x400 : 0x400);
            func_800D427C(D_800FAF5C, (s16)(D_800F9B00->animId + 1), 1);
            D_800FAF5C->step++;
        }
        break;
    case 2:
        x = (s32)D_800F9B00;
        if (((Wrestler *)x)->pairSignals & 2) {
            x = (u16)((Wrestler *)x)->animId;
            func_800D427C(D_800FAF5C, (s16)(x + 1), 3);
            D_800FAF5C->step++;
        } else if (((Wrestler *)x)->pairSignals & 4) {
            x = (u16)((Wrestler *)x)->animId;
            func_800D427C(D_800FAF5C, (s16)(x + 1), 3);
            D_800FAF5C->step += 2;
        } else if (func_800BF150(D_800FAF5C)) {
            D_800F9B00->pairSignals |= 4;
        }
        break;
    case 3:
        if (D_800FAF5C->animFramesLeft <= 0) {
            func_800A7D1C(D_800FAF5C, (D_800FAF5C->state == 0xE) ? 0x27 : 0x28);
            func_800B68A0(D_800FAF5C, D_800F9B00, D_800FAF5C);
            func_800D4AD0(D_800FAF5C);
            beginEntityActionA8D8C(D_800FAF5C);
            func_800C472C(D_800FAF5C, D_800FAF5C, 2);
        }
        break;
    case 4:
        if (D_800FAF5C->animFramesLeft <= 0) {
            func_800D4AD0(D_800FAF5C);
            func_800A6C48(D_800FAF5C, 0x2B);
        }
        break;
    }
}
