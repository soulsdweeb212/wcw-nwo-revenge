/* @header
 * func_800A946C
 * VRAM 0x800A946C | ROM 0x55BDC | size 0x1A4
 * asm: asm/nonmatchings/code_80090000/func_800A946C.s
 */
#include "common.h"

extern s32 D_800E7908, D_800E7934, D_800E7B58;
#ifdef TARGET_PC
/* PC: D_800E9216 and D_800E921A are the fE and f12 of D_800E8230[13], D_800E934E and D_800E9352 those of [14]. The
 * menus hold addresses, so they are common.h's Nw2Menu (0x140 bytes on PC), and the labels have no PC symbol: the PC
 * reads the menus by field name. */
extern s16 D_80038A90;
extern Nw2Menu D_800E8230[];
#else
extern s16 D_80038A90, D_800E9352, D_800E934E, D_800E921A, D_800E9216;
#endif
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
#ifdef TARGET_PC
    /* PC: D_8007EF30 keeps its N64 layout, so its +0x2C holds the name table's handle (port.h's PTR_TO_SLOT); the
     * tables (common.h's Nw2IdSubTable) are 16 bytes each on PC. */
    *(u32 *)(D_8007EF30 + 0x2C) = PTR_TO_SLOT(&((Nw2IdSubTable *)lookupSubTables)[*(s16 *)(D_8007EF30 + 0x10)]);
#else
    *(u8 **)(D_8007EF30 + 0x2C) = lookupSubTables + *(s16 *)(D_8007EF30 + 0x10) * 8;
#endif
    d = 0x30;
    if (D_80038A90 == 0xD) {
        d = -0x30;
    }
    D_800E7B58 = d;
    func_800A9210(D_800E7934);
#ifdef TARGET_PC
    /* PC: by name (see above) */
    D_800E8230[14].f12 = 0;
    D_800E8230[14].fE = 0;
    D_800E8230[13].f12 = 0;
    D_800E8230[13].fE = 0;
#else
    D_800E9352 = 0;
    D_800E934E = 0;
    D_800E921A = 0;
    D_800E9216 = 0;
#endif
    return r;
}
