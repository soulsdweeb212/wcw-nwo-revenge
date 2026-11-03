/* @header
 * func_800B2D20
 * VRAM 0x800B2D20 | ROM 0x5F490 | size 0x274
 * asm: asm/nonmatchings/code_80090000/func_800B2D20.s
 */
#include "common.h"

typedef struct { s32 w[10]; s32 f28; } Ent2D20;
extern Ent2D20 D_800EA220[];
typedef struct { u8 pad0[0x1B4]; s32 tbl[0x20][2]; u8 pad2B4[0x2B8 - 0x2B4]; } Plr2D20;
typedef struct { u8 on; u8 on2; u8 pad2[0x16]; } Slot2D20;
typedef struct { u8 pad0[0x628]; Slot2D20 slot[4]; } Cfg2D20;
extern Plr2D20 D_8007EF30[];
extern Cfg2D20 D_8007E228;

#define TBL(i, k) (D_8007EF30[i].tbl[k][0])

void func_800B2D20(s32 a) {
    s32 x, y, z, w;
    s32 i;

    w = -1;
    z = -1;
    y = -1;
    x = -1;
    switch (a) {
    case 0: x = 0; y = 4; break;
    case 1: x = 1; y = 5; break;
    case 2: x = 2; y = 6; break;
    case 3: x = 3; y = 7; break;
    case 4: x = 8; y = 10; break;
    case 5: x = 9; y = 11; break;
    case 6: x = 12; y = 16; break;
    case 7: x = 13; y = 17; break;
    case 8: x = 14; y = 18; break;
    case 9: x = 15; y = 19; z = 20; w = 21; break;
    }
    for (i = 0; i < 4; i++) {
        if (D_8007E228.slot[i].on) {
            D_800EA220[i].w[a] = TBL(i, x);
            if (z >= 0) {
                D_800EA220[i].w[a] |= (TBL(i, z) & 0x3F) << 12;
            }
            if (D_8007E228.slot[i].on2) {
                D_800EA220[i].w[a] |= 0x1000000 | ((TBL(i, y) & 0x3F) << 6);
                if (w >= 0) {
                    D_800EA220[i].w[a] |= (TBL(i, w) & 0x3F) << 18;
                }
            }
        } else {
            D_800EA220[i].w[a] = TBL(i, y);
            if (w >= 0) {
                D_800EA220[i].w[a] |= (TBL(i, w) & 0x3F) << 12;
            }
        }
        if (a == i) {
            D_800EA220[i].w[i] = -1;
        }
        if (a + 1 == 10) {
            D_800EA220[i].f28 = TBL(i, 22) - TBL(i, 23) + TBL(i, 24);
        }
    }
}
