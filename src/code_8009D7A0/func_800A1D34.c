/* @header
 * func_800A1D34
 * VRAM 0x800A1D34 | ROM 0x951D4 | size 0x31C
 * asm: asm/nonmatchings/code_8009D7A0/func_800A1D34.s
 */
#include "common.h"

extern u16 D_800E3262[];

void func_800D427C(void *, s16, s32);
s32 func_800D4D44(void *, s32, s32);

void func_800A1D34(void)
{
    s8 idx;
    s32 a3;
    s16 step;

    D_800EB408->flags |= 0x1000000000ULL;
    step = D_800EB408->step;
    switch (step) {
    case 0:
        D_800EB408->pose = D_800EB408->anim.endPose;
        idx = (s8)D_800EB408->pose;
        switch (idx) {
        case 0:
            if (D_800EB408->flags & 0x1000000000000ULL)
                a3 = func_800D4D44(D_800EB408, 1, 0);
            else if (D_800EB408->flags & WR_FLAG_ON_APRON) {
                snapEntityToRingBoundary((u8 *)D_800EB408);
                a3 = 0x1081;
            } else
                a3 = 0x10FF;
            break;
        case 1:
            a3 = 0xF38;
            break;
        case 2:
            func_800A6C48(D_800EB408, 0x2E);
            return;
        case 3:
            if (D_800EB408->flags & WR_FLAG_ON_APRON) {
                snapEntityToRingBoundary((u8 *)D_800EB408);
                a3 = 0xF5C;
            } else
                a3 = 0x10FF;
            break;
        case 4:
        case 5:
            a3 = 0x10FF;
            break;
        case 6:
            break;
        case 7: case 9: case 11: case 13: case 15: case 17:
        case 19: case 21: case 23: case 25: case 27: case 29: case 31:
            D_800EB408->flags &= ~0x200000ULL;
            a3 = D_800E3262[(s8)D_800EB408->pose];
            break;
        case 8: case 10: case 12: case 14: case 16: case 18:
        case 20: case 22: case 24: case 26: case 28: case 30: case 32:
            D_800EB408->flags |= 0x200000ULL;
            a3 = D_800E3262[(s8)D_800EB408->pose];
            break;
        default:
            break;
        }
        if (D_800EB408->flags & WR_FLAG_ON_APRON)
            func_800D427C(D_800EB408, a3, 0);
        else
            func_800D427C(D_800EB408, a3, 1);
        D_800EB408->step++;
        break;
    case 1:
        idx = (s8)D_800EB408->pose;
        switch (idx) {
        case 0:
            func_800A6C48(D_800EB408, 1);
            break;
        case 1:
            func_800A6C48(D_800EB408, 0x42);
            D_800EB408->step = 2;
            break;
        case 2:
            func_800A6C48(D_800EB408, 0x2E);
            break;
        case 3:
            func_800A6C48(D_800EB408, 0x2D);
            break;
        case 4:
        case 5:
            func_800A6C48(D_800EB408, 1);
            break;
        case 6:
            break;
        case 7: case 8: case 9: case 10: case 11: case 12: case 13: case 14:
        case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22:
        case 23: case 24: case 25: case 26: case 27: case 28: case 29: case 30:
        case 31: case 32:
            if (D_800EB408->flags & 0x80000000000000ULL)
                func_800A6C48(D_800EB408, 0x43);
            else
                func_800A6C48(D_800EB408, 0x42);
            break;
        default:
            break;
        }
        D_800EB408->flags &= ~0x80000000000000ULL;
        break;
    }
}
