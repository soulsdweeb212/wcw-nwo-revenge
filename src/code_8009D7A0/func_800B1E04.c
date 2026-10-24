#include "common.h"

typedef struct {
    u8 pad0[2];
    u16 f2;
    s16 f4;
    u16 f6;
    u8 pad8[0xA];
    s16 f12;
    u8 pad14[0xE];
    s16 f22;
    u8 pad24[0xA];
    s16 f2E;
    u8 pad30[4];
    f32 f34;
    u8 pad38[0xC];
    s32 f44;
    u8 pad48[0x10];
    s32 f58;
    u32 f5C;
} ActB1E04;

typedef struct {
    u8 pad0[0xA];
    s16 fA;
    s16 fC;
    u8 padE[0x4A];
    s32 f58;
} F58B1E04;

typedef struct {
    u8 pad0[0xA];
    s16 fA;
} F9B60B1E04;

extern ActB1E04 *D_800FABD0;
extern F58B1E04 *D_800FAF58;
extern F9B60B1E04 *D_800F9B60;
extern f64 D_800E5280, D_800E5288;
s32 func_800D3550(s32);
s32 func_800D3684(s32, s32);
s32 func_800D4148(void);
s8 func_800D4198(s16);

void func_800B1E04(void) {
    s16 t;
    u16 flag;
    s16 state = D_800FABD0->f4;

    switch (state) {
    case 0:
        if (D_800FAF58->fC == 2) {
            if (!(D_800FABD0->f34 < D_800E5280) || !(D_800FABD0->f5C & 0x1110000)) {
                goto incr;
            }
            D_800FABD0->f6 = 0x10;
            if (func_800D3550(func_800D3684(D_800FAF58->f58, D_800FABD0->f44)) >= 0xAA) {
                goto check;
            }
            if (D_800FABD0->f2E != D_800F9B60->fA) {
                if (!func_800D4198(0x320)) {
                    goto check;
                }
                if (func_800D4198(D_800FABD0->f12)) {
                    switch (D_800FABD0->f22) {
                    case 1:
                        if (func_800D4198(500)) {
                            flag = 0x4000;
                        } else {
                            flag = 0x8000;
                        }
                        goto apply;
                    case 10:
                        D_800FABD0->f2 = 0;
                        D_800FABD0->f4 = 0;
                        D_800FABD0->f6 |= 0x4000;
                        D_800FABD0->f2E = D_800F9B60->fA;
                        D_800FABD0->f5C &= ~7;
                        break;
                    case 18:
                        D_800FABD0->f2 = 0;
                        D_800FABD0->f4 = 0;
                        D_800FABD0->f6 |= 0x8000;
                        D_800FABD0->f2E = D_800F9B60->fA;
                        D_800FABD0->f5C &= ~7;
                        break;
                    case 6:
                        D_800FABD0->f6 |= 0x20;
                        D_800FABD0->f4++;
                        break;
                    default:
                        D_800FABD0->f2E = D_800F9B60->fA;
                        break;
                    }
                    goto check;
                }
                t = func_800D4148();
                if (t < 450) {
                    if (func_800D4198(500)) {
                        flag = 0x8000;
                    } else {
                        flag = 0x4000;
                    }
                apply:
                    D_800FABD0->f2 = 0;
                    D_800FABD0->f4 = 0;
                    D_800FABD0->f6 |= flag;
                    D_800FABD0->f2E = D_800F9B60->fA;
                    D_800FABD0->f5C &= ~7;
                    goto check;
                }
                if (t >= 900) {
                    D_800FABD0->f6 = 0;
                    D_800FABD0->f4++;
                    goto check;
                }
                goto inc20;
            }
            if (!func_800D4198(150)) {
                goto check;
            }
            t = func_800D4148();
            if (t < 450) {
            inc20:
                D_800FABD0->f6 |= 0x20;
                D_800FABD0->f4++;
            } else if (t < 900) {
                if (func_800D4198(500)) {
                    D_800FABD0->f6 |= 0x4000;
                } else {
                    D_800FABD0->f6 |= 0x8000;
                }
                D_800FABD0->f2 = 0;
                D_800FABD0->f4 = 0;
                D_800FABD0->f2E = D_800F9B60->fA;
                D_800FABD0->f5C &= ~7;
            } else {
            incr:
                D_800FABD0->f4++;
            }
        } else if (D_800FAF58->fC < 2) {
            if (func_800D4198(D_800FABD0->f12)) {
                if (D_800FABD0->f34 < D_800E5288) {
                    D_800FABD0->f6 = 0x10;
                }
            }
        } else {
            D_800FABD0->f4 = state + 1;
        }
    check:
        if (D_800FAF58->fA == 0x43) {
            return;
        }
        D_800FABD0->f2 = 0;
        D_800FABD0->f4 = 0;
        D_800FABD0->f2E = D_800F9B60->fA;
        D_800FABD0->f5C &= ~7;
        return;
    case 1:
        switch (D_800FAF58->fA) {
        case 0x43:
            return;
        case 1:
        case 0x2B:
            if (func_800D4198(D_800FABD0->f12)) {
                switch (D_800FABD0->f22) {
                case 6:
                    D_800FABD0->f6 = 0x10;
                    return;
                case 10:
                    if (func_800D4198(500)) {
                        D_800FABD0->f2 = 0x1D;
                        D_800FABD0->f4 = 0;
                        D_800FABD0->f2E = D_800F9B60->fA;
                        D_800FABD0->f5C &= ~7;
                    } else {
                        D_800FABD0->f2 = 0x1C;
                        D_800FABD0->f4 = 0;
                        D_800FABD0->f2E = D_800F9B60->fA;
                        D_800FABD0->f5C &= ~7;
                    }
                    return;
                }
            }
            break;
        }
        D_800FABD0->f2 = 0;
        D_800FABD0->f4 = 0;
        D_800FABD0->f2E = D_800F9B60->fA;
        D_800FABD0->f5C &= ~7;
        return;
    case 2:
        if (D_800FAF58->fA == 0x21) {
            return;
        }
        D_800FABD0->f2 = 0;
        D_800FABD0->f4 = 0;
        D_800FABD0->f2E = D_800F9B60->fA;
        D_800FABD0->f5C &= ~7;
        return;
    }
}
