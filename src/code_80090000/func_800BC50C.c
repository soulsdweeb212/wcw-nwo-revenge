/* @header
 * func_800BC50C
 * VRAM 0x800BC50C | ROM 0x68C7C | size 0x4A0
 * asm: asm/nonmatchings/code_80090000/func_800BC50C.s
 */
#include "common.h"

extern s32 D_800EA320, D_800D3990, D_800DF200, D_800E7CC8, D_800E7CCC, D_800DF1E4, D_800EA0AC;
extern s32 D_800E7CC0;
void func_800B807C(s32, s32);
void func_800BB6E8(s32);
void func_800C2CDC_ovl1(s32, f32 *);
void func_800C2370(s32, s32);

static inline s32 sfx(s32 x) {
    switch (x) {
    case 0xC:
    case 0xD:
        return 0x14;
    case 0xE:
        return 0x15;
    case 0xF:
        return 0x16;
    case 0x10:
    case 0x19:
        return 0x17;
    case 0x11:
    case 0x1A:
        return 0x18;
    case 0x12:
    case 0x1B:
        return 0x19;
    case 0x13:
    case 0x18:
        return 0x1A;
    case 0x14:
    case 0x1D:
        return 0x1B;
    case 0x15:
    case 0x1E:
        return 0x1C;
    case 0x16:
    case 0x1F:
        return 0x1D;
    case 0x17:
    case 0x1C:
        return 0x1E;
    }
    return -1;
}

void func_800BC50C(s32 a) {
    s32 x, y;
    f32 buf[4];

    if (D_800EA320 >= 0xD) {
        if (D_800D3990 < 0xD) {
            D_800D3990 = 0xD;
            D_800DF200 = 0x40;
            y = sfx(D_800E7CC8);
            if (y < 0) {
                D_800D3990 = 0xF;
            } else {
                func_800B807C(0, y);
            }
        } else if (D_800D3990 < 0xE && D_800DF1E4 == 1 && D_800EA0AC >= 0xE) {
            D_800D3990 = 0xE;
            D_800DF200 = 0x40;
            x = sfx(D_800E7CC8);
            y = sfx(D_800E7CCC);
            if (y >= 0) {
                func_800B807C(x, y);
            }
        }
        if (D_800D3990 == 0xD) {
            func_800BB6E8(0);
        } else if (D_800D3990 == 0xE) {
            func_800BB6E8(8);
        } else {
            func_800BB6E8(2);
        }
        return;
    }
    if (D_800EA320 >= 0xC) {
        x = 0xF;
        y = 0xF;
    } else if (D_800EA320 >= 0xB) {
        if (!a) {
            x = 0x12;
            y = 0x12;
        } else {
            x = 0x13;
            y = 0x13;
        }
    } else {
        func_800C2CDC_ovl1(0, buf);
        if (D_800E7CC0 / 4 != 2) {
            if (D_800EA320 >= 5) {
                if (D_800D3990 < 8) {
                    D_800D3990 = 8;
                    func_800C2370(0, 8);
                    if (D_800DF1E4) {
                        func_800C2370(1, 8);
                    }
                    func_800BB6E8(D_800DF1E4 == 1 ? 6 : 4);
                    buf[2] = 0.0f;
                }
            } else if (D_800EA320 > 0) {
                if (D_800D3990 < 4) {
                    D_800D3990 = 4;
                    func_800C2370(0, 4);
                    if (D_800DF1E4) {
                        func_800C2370(1, 4);
                    }
                    func_800BB6E8(D_800DF1E4 == 1 ? 6 : 4);
                    buf[2] = 300.0f;
                }
            } else {
                D_800D3990 = 0;
            }
        } else {
            D_800D3990 = 0;
        }
        if (buf[2] >= 600.0f) {
            if (!a) {
                x = 0xC;
                y = 0xC;
            } else {
                x = 0xB;
                y = 0xB;
            }
        } else if (buf[2] >= 300.0f) {
            if (!a) {
                x = 0x10;
                y = 0x10;
            } else {
                x = 0x11;
                y = 0x11;
            }
        } else if (!a) {
     x = 0xD;
     y = 0xD;
 } else {
     x = 0xE;
     y = 0xE;
 }
    }
    func_800B807C(x, y);
}
