/* @header
 * func_800AF978
 * VRAM 0x800AF978 | ROM 0x5C0E8 | size 0x578
 * asm: asm/nonmatchings/code_80090000/func_800AF978.s
 */
#include "common.h"

typedef struct {
    u8 pad0[4];
    u8 f4;
    u8 pad5[3];
    u16 mode;
    u8 padA[0x1A0 - 0xA];
    u8 f1A0, f1A1, f1A2, f1A3, f1A4, f1A5, f1A6, f1A7, f1A8, f1A9, f1AA;
    u8 pad1AB[0xCE0 - 0x1AB];
    u8 fCE0;
    u8 padCE1[0xCFC - 0xCE1];
    u8 fCFC;
} Game;
typedef struct {
    u8 pad0[0x80];
    u16 f80[4];
    u8 pad88[0x92 - 0x88];
    u8 f92;
    u8 pad93[0x624 - 0x93];
    u8 f624;
} Cfg;
typedef struct {
    s32 f0[4];
    s32 f10;
    u8 pad14[0x66C - 0x14];
    u8 f66C;
    u8 f66D;
} Cfg2;

extern Game D_8007EF30;
extern Cfg D_8007E228;
extern Cfg2 D_8007E8C0;
extern s32 D_80038AA8;
extern u16 D_8007E280; /* D_8007E228 + 0x58 */
extern u16 D_8007F0A0; /* D_8007EF30 + 0x170 */
void func_8000EED8(s32);

void func_800AF978(void) {
    s32 v;

    D_8007E280 = 0;
    D_8007F0A0 = 0;
    if (D_8007EF30.mode & 0x10) {
        D_8007E8C0.f10 = 0;
    } else if (D_8007EF30.mode & 0x20) {
        D_8007E8C0.f10 = 1;
    } else if (D_8007EF30.mode & 0x40) {
        D_8007E8C0.f10 = 2;
    } else if (D_8007EF30.mode & 0x80) {
        D_8007E8C0.f10 = 3;
    }
    switch (D_8007E8C0.f66D) {
    case 0:
        v = 0;
        break;
    case 1:
        v = 1;
        break;
    default:
        v = 2;
        break;
    }
    D_8007E228.f80[0] = v;
    D_8007E228.f80[1] = v;
    D_8007E228.f80[2] = v;
    D_8007E228.f80[3] = v;
    if (D_8007E8C0.f0[0] <= 0) {
        D_8007E280 |= 1;
    }
    if (D_8007E8C0.f0[1] <= 0) {
        D_8007E280 |= 2;
    }
    if (D_8007E8C0.f0[2] <= 0) {
        D_8007E280 |= 4;
    }
    if (D_8007E8C0.f0[3] <= 0) {
        D_8007E280 |= 8;
    }
    switch (D_8007EF30.mode & 0xF0) {
    case 0x10:
        D_8007E280 |= 0x120;
        break;
    case 0x20:
    case 0x40:
        D_8007E280 |= 0x2C0;
        break;
    case 0x80:
        D_8007E280 |= 0x400;
        break;
    }
    if (D_8007EF30.mode & 0x800) {
        D_8007E280 |= 0x5000;
    } else if (D_8007EF30.mode & 0x1000) {
        D_8007E280 |= 0x800;
    }
    if (D_8007EF30.mode & 0x8000) {
        D_8007E280 |= 0x1000;
    }
    switch (D_8007EF30.f1A0) {
    case 0:
        D_8007E228.f92 = 1;
        break;
    case 1:
        D_8007E228.f92 = 2;
        break;
    case 2:
        D_8007E228.f92 = 3;
        break;
    case 3:
        D_8007E228.f92 = 4;
        break;
    case 4:
        D_8007E228.f92 = 5;
        break;
    default:
        D_8007E228.f92 = 0;
        break;
    }
    switch (D_8007EF30.f1AA) {
    case 0:
        D_8007EF30.fCFC = 0;
        break;
    case 1:
        D_8007EF30.fCFC = 1;
        break;
    case 2:
        D_8007EF30.fCFC = 2;
        break;
    case 3:
        D_8007EF30.fCFC = 3;
        break;
    case 4:
        D_8007EF30.fCFC = 4;
        break;
    case 5:
        D_8007EF30.fCFC = 5;
        break;
    default:
        D_8007EF30.fCFC = 6;
        break;
    }
    if (D_8007EF30.f1A2 == 0) {
        D_8007F0A0 |= 0x20;
    }
    if (D_8007EF30.f1A3 == 0) {
        D_8007F0A0 |= 0x10;
    }
    if (D_8007EF30.f1A4 == 0) {
        D_8007F0A0 |= 1;
    }
    if (D_8007EF30.f1A5 == 0) {
        D_8007F0A0 |= 2;
    }
    if (D_8007EF30.f1A6 == 0) {
        D_8007F0A0 |= 8;
    }
    if (D_8007EF30.f1A9 == 1) {
        D_8007F0A0 |= 0x40;
    }
    if (D_8007EF30.f1A7 == 0) {
        D_8007F0A0 |= 0x100;
    }
    if (D_8007EF30.f1A8 == 0) {
        D_8007F0A0 |= 0x200;
    }
    D_8007EF30.fCE0 = D_8007EF30.f4;
    func_8000EED8(D_8007EF30.f4);
    switch (D_8007EF30.f1A1) {
    case 0:
        D_8007E8C0.f66C = 1;
        break;
    case 1:
        D_8007E8C0.f66C = 2;
        break;
    case 2:
        D_8007E8C0.f66C = 0;
        D_8007F0A0 |= 4;
        break;
    case 4:
        D_8007E8C0.f66C = 0;
        D_8007F0A0 |= 0x400;
        break;
    default:
        D_8007E8C0.f66C = 0;
        break;
    }
    if (D_8007EF30.mode & 0x8000) {
        D_8007E228.f624 = D_80038AA8 + 1;
    } else {
        switch (D_8007EF30.fCE0) {
        case 0:
            D_8007E228.f624 = 1;
            break;
        case 1:
            D_8007E228.f624 = 2;
            break;
        case 2:
            D_8007E228.f624 = 3;
            break;
        case 3:
            D_8007E228.f624 = 4;
            break;
        case 4:
            D_8007E228.f624 = 5;
            break;
        default:
            D_8007E228.f624 = 6;
            break;
        }
    }
}
