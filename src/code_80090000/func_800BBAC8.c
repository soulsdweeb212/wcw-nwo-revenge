/* @header
 * func_800BBAC8
 * VRAM 0x800BBAC8 | ROM 0x68238 | size 0x3F0
 * asm: asm/nonmatchings/code_80090000/func_800BBAC8.s
 */
#include "common.h"

extern struct { u8 pad0[0x688]; s32 ids[8]; } D_8007E228;
extern struct { u8 pad0[8]; u16 mode; } D_8007EF30;
extern s32 D_800DF1E0, D_800DF1E4;
extern s32 D_800E7CC0[];
typedef struct { s32 v; } Cnt;
extern Cnt D_800E7CC8, D_800E7CCC;
extern s32 D_800E7CD0, D_800E7CD4;
s32 func_8002AEE0(s32);
s32 func_800BB994(s32, s32);

void func_800BBAC8(s32 a) {
    s32 f0, f1;

    f0 = func_8002AEE0(D_8007E228.ids[D_800DF1E0]) & 0x100;
    if (D_800DF1E4 == 1) {
        f1 = func_8002AEE0(D_8007E228.ids[D_800DF1E0 + 1]) & 0x100;
    }
    if (f0) {
        D_800E7CC0[0] += 8;
        if (D_800DF1E4 & 1) {
            D_800E7CC0[1] += 8;
        } else if (D_8007EF30.mode & 0x80) {
            if (!a) {
                D_800E7CC0[1] = D_800DF1E0 / 2 + 4;
            } else {
                D_800E7CC0[1] = D_800DF1E0 / 2;
            }
        } else if (!a) {
            D_800E7CC0[1] += 4;
        } else {
            D_800E7CC0[1] = D_800E7CC0[1];
        }
    } else if (!a) {
        D_800E7CC0[0] += 4;
        D_800E7CC0[1] += 4;
    } else {
        D_800E7CC0[0] = D_800E7CC0[0];
        D_800E7CC0[1] = D_800E7CC0[1];
    }
    f0 = func_8002AEE0(D_8007E228.ids[D_800DF1E0]) & 0x600;
    if (D_800DF1E4 == 1) {
        f1 = func_8002AEE0(D_8007E228.ids[D_800DF1E0 + 1]) & 0x600;
    }
    if (D_8007EF30.mode & 0x80) {
        switch (f0) {
        case 0x200:
            D_800E7CC8.v = D_800DF1E0 + 0x18;
            break;
        case 0x400:
            D_800E7CC8.v = D_800DF1E0 + 0x1C;
            break;
        default:
            D_800E7CC8.v = 0xC;
            break;
        }
        D_800E7CCC.v = -1;
    } else if (D_800DF1E4 != 1) {
        switch (f0) {
        case 0x200:
            D_800E7CC8.v = 0x10;
            break;
        case 0x400:
            D_800E7CC8.v = 0x14;
            break;
        default:
            D_800E7CC8.v = 0xC;
            break;
        }
        if (a) {
            D_800E7CC8.v++;
        }
        D_800E7CCC.v = -1;
    } else if (f0 == 0 && f1 == 0) {
        D_800E7CC8.v = 0xE;
        D_800E7CCC.v = 0xF;
    } else if (f0 != 0 && f1 != 0) {
        if (f0 == 0x200) {
            D_800E7CC8.v = 0x13;
        } else {
            D_800E7CC8.v = 0x17;
        }
        if (f1 == 0x200) {
            D_800E7CCC.v = 0x12;
        } else {
            D_800E7CCC.v = 0x16;
        }
    } else if (f0 != 0) {
        if (f0 == 0x200) {
            D_800E7CC8.v = 0x10;
        } else {
            D_800E7CC8.v = 0x14;
        }
        if (a) {
            D_800E7CC8.v++;
        }
        D_800E7CCC.v = 0xC;
    } else {
        D_800E7CC8.v = 0xC;
        if (f1 == 0x200) {
            D_800E7CCC.v = 0x10;
        } else {
            D_800E7CCC.v = 0x14;
        }
        if (a) {
            D_800E7CCC.v++;
        }
    }
    D_800E7CD0 = func_800BB994(D_800E7CC0[0], D_800E7CC8.v);
    D_800E7CD4 = func_800BB994(D_800E7CC0[1], D_800E7CCC.v);
}
