/* @header
 * func_800AA290
 * VRAM 0x800AA290 | ROM 0x9D730 | size 0x710
 * asm: asm/nonmatchings/code_8009D7A0/func_800AA290.s
 */
#include "common.h"

typedef struct {
    s8 f0;
    u8 pad1[9];
    s16 fA;
    u8 padC[0x14];
    u64 flags;
    u8 pad28[4];
    u32 f2C;
    u8 pad30[4];
    f32 f34;
    u8 pad38[0x31B];
    s8 f353;
    u8 f354;
    u8 f355;
    u8 pad356[2];
    u64 f358;
    u8 pad360[4];
    u8 *f364;
} Nw2EntAA290;

typedef struct {
    u8 pad0[0x12];
    s16 f12;
    u8 pad14[0xE];
    s16 f22;
    u8 pad24[0x10];
    f32 f34;
    u8 pad38[4];
    f32 f3C;
} Nw2FABD0AA290;

extern Nw2EntAA290 *D_800FAF58;
extern Nw2EntAA290 *D_800F9B60;
extern Nw2FABD0AA290 *D_800FABD0;
extern u8 D_8007E228[];
extern u8 D_8007EF30[];
extern f64 D_800E4D68;
extern f64 D_800E4D70;
extern f64 D_800E4D98;
extern s16 D_800E33CC[];
extern s16 D_800E33D4[];
extern s8 D_800E3378[];
extern s8 D_800E339C[];

s8 func_800AB0E8(void);
s8 func_800AB1B0(void);
s8 func_800AB2B4(void);
void func_800AD958(s32);
s8 func_800D9270(Nw2EntAA290 *);
s8 func_800D4198(s16);
s8 func_800ABFF8(void);
void func_800AB780(void);
void func_800AB96C(void);
void func_800ABC40(void);
void func_800ABCD8(void);
void selectActionVariantLevel(void);
void func_800ABE20(void);
void func_800AB560(void);
void func_800AB64C(void);
void func_800ADA38(s8 *);

void func_800AA290(void) {
    s16 x;
    s16 y;
    s8 q;
    f64 d;

    if (func_800AB0E8()) return;
    if (func_800AB1B0()) return;
    if (func_800AB2B4()) return;

    if ((D_800FAF58->flags & 0x80)
        && (*(u16 *)(D_8007E228 + 0x58) & 0x200)
        && !(*(u16 *)(D_8007EF30 + 0x170) & 0x40)
        && !(D_800FAF58->flags & 0x200)) {
        func_800AD958(0x2C);
        return;
    }

    if (func_800D9270(D_800FAF58)) {
        func_800AD958(0x2D);
        return;
    }

    if (D_800FAF58->flags & 0x80) {
        if (func_800D4198(0xC8)) {
            if (func_800D4198(0x320)) {
                func_800AD958(0x15);
            } else {
                func_800AD958(0x16);
            }
            return;
        }
    }

    if (D_800FABD0->f22 == 0x11) {
        func_800ABE20();
        return;
    }
    if (D_800FABD0->f22 == 0xE) {
        selectActionVariantLevel();
        return;
    }
    if (D_800FABD0->f22 == 0x17) {
        if (func_800D4198(D_800FABD0->f12)) {
            func_800AD958(0x3D);
            return;
        }
    }

    if ((*(u16 *)(D_8007E228 + 0x58) & 0x200)
        && !(*(u16 *)(D_8007EF30 + 0x170) & 0x40)
        && !(D_800FAF58->flags & 0x200)) {
        if (D_800FAF58->f358 & 0x600000000000ULL) {
            if (D_800FAF58->f358 & 0x200000000000ULL) {
                if (D_800F9B60->flags & 0x400000000000ULL) {
                    D_800FAF58->f353 = D_800F9B60->f355;
                    if (D_800FAF58->f353 == D_800F9B60->f0) {
                        func_800AD958(0x13);
                        return;
                    }
                }
                func_800AD958(7);
                return;
            } else {
                if (D_800F9B60->flags & 0x200000000000ULL) {
                    if (D_800FABD0->f3C < D_800E4D68) {
                        func_800AD958(3);
                        return;
                    }
                } else {
                    D_800FAF58->f353 = D_800F9B60->f355;
                    if (D_800FAF58->f353 == D_800F9B60->f0) {
                        func_800AD958(0x13);
                        return;
                    }
                }
                func_800AD958(0x31);
                return;
            }
        }
    }

    if (func_800ABFF8()) return;

    if (D_800FABD0->f34 < D_800E4D70) {
        switch ((s16)(*(u16 *)&D_800FABD0->f22 - 6)) {
        case 2:
            func_800AB780();
            return;
        case 3:
        case 7:
            func_800AB96C();
            return;
        case 5:
            func_800ABC40();
            return;
        case 6:
            func_800ABCD8();
            return;
        case 0:
        case 4:
            x = *(u16 *)&D_800FABD0->f12;
            if (D_800FABD0->f22 == 0xA) {
                if (D_800F9B60->f2C & 2) {
                    x = (s16)(f64)x;
                } else {
                    x = (s16)((f64)x * D_800E4D98);
                }
            }
            if (func_800D4198(x)) {
                if (D_800FABD0->f22 == 0xA) {
                    func_800AB560();
                } else {
                    func_800AB64C();
                }
                return;
            }
            if (func_800D4198(D_800FABD0->f12)) {
                func_800ADA38(D_800E3378);
                return;
            }
            func_800AD958(0x1B);
            return;
        case 1:
        default:
            break;
        }
        if (D_800F9B60->flags & 0x1000000000ULL) {
            func_800AD958(0x13);
            return;
        }
        y = *(u16 *)&D_800FABD0->f12;
        if (func_800D4198(y / 2)) {
            func_800ADA38(D_800E3378);
            return;
        }
        func_800AD958(0x1B);
    } else {
        if (func_800D4198(D_800FABD0->f12)) {
            if (D_800F9B60->fA == 7) {
                func_800AB64C();
            }
        }
        if (D_800F9B60->flags & 0x1000000000ULL) {
            if (func_800D4198(0x12C)) {
                func_800AD958(0x13);
            } else {
                func_800AD958(0x19);
            }
            return;
        }
        if (func_800D4198(0x64)) {
            q = (s8)*(u8 *)(D_800FAF58->f364 + 0x18) / 3;
            if (func_800D4198(D_800E33CC[q])) {
                func_800AD958(0x1E);
                return;
            }
        }
        if (func_800D4198(D_800FABD0->f12)) {
            if (func_800D4198(0xFA)) {
                q = (s8)*(u8 *)(D_800FAF58->f364 + 0x18) / 3;
                if (func_800D4198(D_800E33D4[q])) {
                    func_800AD958(7);
                    return;
                }
            }
        }
        func_800ADA38(D_800E339C);
    }
}
