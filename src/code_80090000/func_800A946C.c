/* @header
 * func_800A946C
 * VRAM 0x800A946C | ROM 0x55BDC | size 0x1A4
 * asm: asm/nonmatchings/code_80090000/func_800A946C.s
 */
#include "common.h"

extern s32 D_800E7908, D_800E7934, D_800E7B58;
extern s16 D_80038A90, D_800E9352, D_800E934E, D_800E921A, D_800E9216;
extern u8 D_8007EF30[];
extern u8 lookupSubTables[];
void func_800B1484(s32, s32);
void func_800A9210(s32);

s32 func_800A946C(s32 a) {
    s32 r = D_80038A90;
    s32 d;

    D_800E7908 = 0;
    if (a < 0) {
        if (r == 0xE) {
            func_800B1484(0xE, -1);
            D_80038A90 = 0xD;
            func_800B1484(0xD, 1);
        }
        {
            s16 *q = (s16 *)(D_8007EF30 + 0x10);
            s16 v = *q;
            if (v == 0xB) {
                *q = 0xC;
            } else if (v == 0xC) {
                *q = 0xB;
            } else {
                *q = v - 1;
                if (*q < 0) {
                    *q = 8;
                }
            }
        }
        r = 0xE;
    } else {
        if (r == 0xD) {
            func_800B1484(0xD, -1);
            D_80038A90 = 0xE;
            func_800B1484(0xE, 1);
        }
        {
            s16 *q = (s16 *)(D_8007EF30 + 0x10);
            s16 v = *q;
            if (v == 0xB) {
                *q = 0xC;
            } else if (v == 0xC) {
                *q = 0xB;
            } else {
                *q = v + 1;
                if (*q >= 9) {
                    *q = 0;
                }
            }
        }
        r = 0xD;
    }
    *(u8 **)(D_8007EF30 + 0x2C) = lookupSubTables + *(s16 *)(D_8007EF30 + 0x10) * 8;
    d = 0x30;
    if (D_80038A90 == 0xD) {
        d = -0x30;
    }
    D_800E7B58 = d;
    func_800A9210(D_800E7934);
    D_800E9352 = 0;
    D_800E934E = 0;
    D_800E921A = 0;
    D_800E9216 = 0;
    return r;
}
