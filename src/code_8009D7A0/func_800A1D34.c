#include "common.h"

extern u16 D_800E3262[];

void func_800D427C(void *, s16, s32);
s32 func_800D4D44(void *, s32, s32);

#define E D_800EB408
#define F (*(u64 *)((u8 *)E + 0x20))

void func_800A1D34(void)
{
    s8 idx;
    s32 a3;
    s16 state;

    F |= 0x1000000000ULL;
    state = *(s16 *)((u8 *)E + 0xC);
    switch (state) {
    case 0:
        *(u8 *)((u8 *)E + 0x42) = *(u8 *)((u8 *)E + 0x36F);
        idx = *(s8 *)((u8 *)E + 0x42);
        switch (idx) {
        case 0:
            if (F & 0x1000000000000ULL)
                a3 = func_800D4D44(E, 1, 0);
            else if (F & 0x80ULL) {
                snapEntityToRingBoundary((u8 *)E);
                a3 = 0x1081;
            } else
                a3 = 0x10FF;
            break;
        case 1:
            a3 = 0xF38;
            break;
        case 2:
            func_800A6C48(E, 0x2E);
            return;
        case 3:
            if (F & 0x80ULL) {
                snapEntityToRingBoundary((u8 *)E);
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
            F &= ~0x200000ULL;
            a3 = D_800E3262[*(s8 *)((u8 *)E + 0x42)];
            break;
        case 8: case 10: case 12: case 14: case 16: case 18:
        case 20: case 22: case 24: case 26: case 28: case 30: case 32:
            F |= 0x200000ULL;
            a3 = D_800E3262[*(s8 *)((u8 *)E + 0x42)];
            break;
        default:
            break;
        }
        if (F & 0x80ULL)
            func_800D427C(E, a3, 0);
        else
            func_800D427C(E, a3, 1);
        (*(u16 *)((u8 *)E + 0xC))++;
        break;
    case 1:
        idx = *(s8 *)((u8 *)E + 0x42);
        switch (idx) {
        case 0:
            func_800A6C48(E, 1);
            break;
        case 1:
            func_800A6C48(E, 0x42);
            *(s16 *)((u8 *)E + 0xC) = 2;
            break;
        case 2:
            func_800A6C48(E, 0x2E);
            break;
        case 3:
            func_800A6C48(E, 0x2D);
            break;
        case 4:
        case 5:
            func_800A6C48(E, 1);
            break;
        case 6:
            break;
        case 7: case 8: case 9: case 10: case 11: case 12: case 13: case 14:
        case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22:
        case 23: case 24: case 25: case 26: case 27: case 28: case 29: case 30:
        case 31: case 32:
            if (F & 0x80000000000000ULL)
                func_800A6C48(E, 0x43);
            else
                func_800A6C48(E, 0x42);
            break;
        default:
            break;
        }
        F &= ~0x80000000000000ULL;
        break;
    }
}
