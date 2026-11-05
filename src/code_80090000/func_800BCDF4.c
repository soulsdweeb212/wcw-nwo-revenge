/* @header
 * func_800BCDF4
 * VRAM 0x800BCDF4 | ROM 0x69564 | size 0x24FC
 * asm: asm/nonmatchings/code_80090000/func_800BCDF4.s
 */
#include "common.h"










typedef struct { u8 f0; u8 pad1[0xD]; u16 fE; } Cup;
typedef struct {
    u8 pad0[4];
    u8 f4;
    u8 pad5[3];
    u16 mode;
    u8 padA[0x30 - 0xA];
    Cup *cup;
    u8 pad34[0xC90 - 0x34];
    u16 opp[2];
} Game;
typedef struct { void *p; s16 f4; u8 pad6[6]; } Slot;
typedef struct { u8 pad0[7]; u8 f7; } Demo;

extern Game D_8007EF30;
extern struct { u8 pad0[0x688]; s32 ids[8]; } D_8007E228;
extern struct { u8 pad0[0x70]; s32 f70; s32 f74; } D_8007E8C0;
extern s32 D_800E74E0, D_800E7C90, D_800E9F70, D_800DF1CC, D_800DF1D0;
extern s32 D_800E74C4, D_800E74D8, D_800E8204, D_800E8200, D_800E79CC, D_800E74F0;
extern f32 D_800E74F8, D_800E74FC, D_800E7500, D_800E7508, D_800E750C, D_800E7510;
extern s32 D_800E798C, D_800E9F90, D_800E9F8C, D_80038AA8, D_800E7BEC, D_800E74E8;
extern s32 D_800DF1D8, D_800DF1D4, D_800E8210;
extern s16 D_8006E440;
extern s32 D_800E6B7C, D_800E74C8, D_800DF1E0, D_800EA320, D_800D5F28;
extern s32 D_800DF1E4, D_800DF1E8;
extern s32 D_800EA0A8[2];
extern s32 D_800E74B8[2];
extern s16 D_800E74CC[4];
extern u16 D_800EA0C2;
extern s32 D_80038A98, D_80038A8C;
extern s16 D_80038A92, D_80038A90;
extern s32 D_800E79BC, D_800E7CC0, D_800E7CC4, D_800E79C4, D_800EA0B4, D_800E797C;
extern Slot D_800E79D8[];
extern Demo D_800D34C8[];
extern s32 D_800E7C98, D_800E7C9C, D_800E7CA0, D_800E7CA4, D_800DF1C0;
extern s16 D_800E7CB8, D_800E9E3C;
extern s8 D_800CCA09;

void func_80099478(s32, s32, s32);
s32 func_800BBEB8(s32);
s32 guRandom(void);
void func_800B807C(s32, s32);
void func_8000DFD0(s32);
u16 func_8002AEE0(s32);
s32 func_8002AF9C(s32);
s32 func_800C2CAC(s32);
s32 func_800BB5A4(s32);
void func_800C3094(s32, s32, s32, s32, s32, s32);
void func_800BC9AC(void);
void func_800BC50C(s32);
void func_8000E09C(s32);
s32 func_800BABC0(void);
s16 func_8000F6F4(void);
void func_8000EED8(s32);
void func_8000F620(s32);
void func_800BC32C(void);
void findOrAddCacheEntryRaw(s32, s32, s32, s32, s32);
s32 func_800B04BC(s32);
void func_800BCBB4(s32);
s32 func_800AA1E0(s32, s32, s32, s32);
void func_800B8050(void);
void func_800B2588(void);
s32 func_80099148(s32, s32, s32, s32, s32);
s32 func_8002AD04(s32, s32);
s32 func_800C54FC(s32);
void func_800BB440(void);
void func_8002BBCC(s32);
void func_800BA1A4(s32, s32);
void func_800B5300(s32);
void func_800AF978(void);
void func_800B511C(s32);
void func_800B5704(s32);
void func_800B9F18(void);
void func_8000DEE4(s16);

static inline s32 winner(s32 a, s32 b) {
    s32 c, n, e, w;

    c = func_8002AEE0(a) & 0xF0;
    n = func_8002AEE0(b) & 0xF0;
    if (c != 0x80 && n == 0x80) {
        w = 1;
    } else if (c == 0x80 && n != 0x80) {
        w = 2;
    } else {
        e = func_8002AF9C(a);
        if (func_8002AF9C(b) >= e) {
            w = 1;
        } else {
            w = 2;
        }
    }
    return w;
}

static inline s32 reached(s32 n) {
    if (func_800C2CAC(n - 1) >= func_8002AF9C(D_8007E228.ids[D_800DF1E0 + n - 1])) {
        return -1;
    }
    return 0;
}

void func_800BCDF4(void) {
    s32 v, j, k;
    s32 old;
    s32 t, r, s, i;
    Slot *p;

    func_80099478(D_800E74E0, 0x190, 0x28);
    old = D_800E9F70;
    D_800DF1CC = -1;
    D_800DF1D0 = 0;
    switch (D_800E7C90) {
    case 1:
        t = D_800E74E0;
        D_800E74C4 = 0;
        D_800E74D8 = -5;
        D_800E8204 = -5;
        D_800E8200 = -5;
        D_800E74F8 = -868 - (-868 * t) / 16;
        D_800E74FC = -565 - (-565 * t) / 16;
        D_800E7500 = 3081 - (3081 * t) / 16;
        D_800E7508 = 0;
        D_800E750C = -34 - (-34 * t) / 16;
        D_800E7510 = 0;
        D_800E79CC = 0;
        D_800E74E0 = t + 1;
        D_800E74F0 = -1;
        if (t + 1 >= 0x11) {
            D_800E74E0 = 0;
            D_800E798C = 0;
            D_800E9F90 = 0;
            D_800E9F8C = 0;
            if (D_8007EF30.mode & 0x8000) {
                if (D_80038AA8 != 0) {
                    if (D_8007EF30.mode & 0x20) {
                        D_800E7C90 = 6;
                    } else {
                        D_800E7C90 = 4;
                    }
                } else {
                    D_800E7C90 = 2;
                }
            } else {
                D_800E7C90 = 2;
            }
            D_800E7BEC = 0;
            func_800BBEB8(D_800E7C90);
            D_800E74E8 = -1;
            D_800DF1D8 = 0;
            D_800DF1D4 = 0;
            do {
                r = guRandom() % 6;
            } while ((D_800DF1D4 >> r) & 1);
            D_800DF1D4 |= 1 << r;
            func_800B807C(0, r + 1);
            do {
                r = guRandom() % 5;
            } while ((D_800DF1D8 >> r) & 1);
            D_800DF1D8 |= 1 << r;
            D_800E8210 = r;
            D_8006E440 = 1;
            func_8000DFD0(0);
        }
        break;
    case 2:
    case 4:
    case 6:
    case 8:
        func_8000DFD0(0);
        D_800E6B7C = 0;
        if (D_800E798C == 0 || D_800E74C8 < 0xFF) {
            D_800E74D8 = -5;
            D_800E8204 = -5;
            D_800E8200 = -5;
            D_800E7BEC = D_800DF1E0 << 8;
            switch (D_800EA320) {
            case 0:
                if (D_800E74E0 >= 0x38) {
                    D_800E74E0 = 0x38;
                }
                break;
            case 1:
                D_800D5F28 = 0;
                if (D_800E74E0 < 0x40) {
                    D_800E74E0 = 0x40;
                }
                if (D_800E74E0 >= 0x78) {
                    D_800EA0A8[0] = 2;
                    D_800EA0A8[1] = 2;
                }
                if (D_800E74E0 >= 0x41) {
                    func_800B807C(7, 7);
                }
                D_800E7BEC += D_800E74E0 - 0x40;
                break;
            case 2:
                if (D_800E74E0 < 0x80) {
                    D_800E74E0 = 0x80;
                }
                if (D_800E74E0 >= 0xFF) {
                    D_800E74E0 = 0xFF;
                }
                D_800E7BEC += 0x70;
                if (D_800E74E0 == 0x80) {
                    func_800B807C(7, 8);
                    if (D_800DF1E4 & 1) {
                        D_800E9F90 = winner(D_8007E228.ids[D_800DF1E0], D_8007E228.ids[D_800DF1E0 + 1]);
                    } else {
                        D_800E9F90 = 1;
                    }
                }
                s = D_800E9F90;
                if (s != 0 && reached(s)) {
                    {
                        D_800E74C4 = func_800BB5A4(D_8007E228.ids[D_800DF1E0 + D_800E9F90 - 1]);
                        D_800E9F90 = 0;
                    }
                }
                break;
            case 3:
                D_800EA0A8[0] = 4;
                D_800EA0A8[1] = 4;
                D_800E7BEC += D_800E74E0 - 0x80;
                D_800E74B8[1]++;
                D_800E74B8[0]++;
                break;
            case 4:
                if (D_800E74E0 < 0x100) {
                    D_800E74E0 = 0x100;
                }
                if (D_800E74E0 == 0x100) {
                    func_800B807C(1, 0xA);
                }
                D_800E7BEC += D_800E74E0 - 0x80;
                break;
            }
            if (D_800E74CC[3] != 0) {
                func_800C3094(-1, 0, 1000, 0, 0xFF, (0xFF - D_800E74CC[3]) / 4 + 0x40);
            } else {
                func_800C3094(-1, 0, 1000, 0, 0xFF, 0x80);
            }
            func_800BC9AC();
            if (D_800E798C != 0) {
                D_800E74C8 += 0x10;
                if (D_800E74C8 >= 0xFF) {
                    D_800E74C8 = 0xFF;
                    D_800E74E0 = 0;
                }
            } else if (D_800E74C8 != 0) {
                if (D_800E74E0 >= 9) {
                    D_800E74C8 -= 0x20;
                    if (D_800E74C8 < 0) {
                        D_800E74C8 = 0;
                    }
                }
            } else if (D_800E74E0 >= 0x110 || (D_800EA0C2 & 0xD000)) {
                D_800E798C = 1;
                if (D_800EA0C2 & 0x1000) {
                    D_800E798C = 0x81;
                } else if (D_800EA0C2 & 0x4000) {
                    D_800E798C = 0x41;
                }
            }
        } else {
            D_800E74D8 = -1;
            D_800E74C8 = 0xFF;
            D_800E74F0 = -1;
            D_800E7BEC = 0;
            if (D_800E74E0 == 2) {
                func_800B807C(0, 0);
                if (D_800E798C & 0x80) {
                    D_800E9F8C = 10;
                } else if (D_800E798C & 0x40) {
                    D_800E9F8C = D_800E7C90 + 2;
                    if (D_8007EF30.mode & 0x60) {
                        D_800E9F8C = D_800E7C90 + 4;
                    }
                } else {
                    D_800E9F8C = D_800E7C90 + 1;
                }
                D_800E9F8C = func_800BBEB8(D_800E9F8C);
                if (D_800E9F8C != 10 && D_80038A98 != 0) {
                    D_800E7C90 = D_800E9F8C + 0xB;
                    D_80038A92 = 0x15;
                    D_80038A8C = -1;
                    D_80038A98 = 0;
                }
            } else if (D_800E74E0 >= 4) {
                D_800E74E0 = 0;
                D_800E9F90 = 0;
                D_800E798C = 0;
                D_800E7C90 = D_800E9F8C;
                D_800E9F8C = 0;
            }
        }
        break;
    case 3:
    case 5:
    case 7:
    case 9:
        D_800D5F28 = 0;
        func_8000DFD0(0);
        D_800E6B7C = 0;
        D_800E7BEC = 0;
        if (D_800E798C == 0 || D_800E74C8 < 0xFF) {
            D_800E74D8 = -9;
            D_800E8204 = -9;
            D_800E8200 = -9;
            func_800C3094(-1, 0, 1000, 0, 0xFF, 0x80);
            func_800BC9AC();
            func_800BC50C(D_800DF1E8);
            if (D_800E798C != 0) {
                D_800E74C8 += 0x10;
                if (D_800E74C8 >= 0xFF) {
                    D_800E74C8 = 0xFF;
                    D_800E74E0 = 0;
                }
            } else if (D_800E74C8 != 0) {
                if (D_800E74E0 >= 8) {
                    D_800E74C8 -= 0x20;
                    if (D_800E74C8 < 0) {
                        D_800E74C8 = 0;
                    }
                }
            } else if (D_800EA320 == 0xF || (D_800EA0C2 & 0xD000)) {
                D_800E798C = 1;
                if (D_800EA0C2 & 0x1000) {
                    D_800E798C = 0x81;
                }
            }
        } else {
            D_800E74D8 = -1;
            D_800E74C8 = 0xFF;
            D_800E74F0 = -1;
            if (D_800E74E0 == 2) {
                func_800B807C(0, 0);
                if (D_800E798C & 0x80) {
                    D_800E9F8C = 10;
                } else {
                    D_800E9F8C = D_800E7C90 + 1;
                    if (D_8007EF30.mode & 0x60) {
                        D_800E9F8C = D_800E7C90 + 3;
                    }
                }
                D_800E9F8C = func_800BBEB8(D_800E9F8C);
                if (D_800E9F8C < 10 && D_80038A98 != 0) {
                    D_800E7C90 = D_800E9F8C + 0xB;
                    D_80038A92 = 0x15;
                    D_80038A8C = -1;
                    D_80038A98 = 0;
                }
            } else if (D_800E74E0 >= 4) {
                D_800E9F90 = 0;
                D_800E798C = 0;
                D_800E74E0 = 0;
                D_800E7C90 = D_800E9F8C;
                D_800E9F8C = 0;
            }
        }
        break;
    case 0xA:
        D_800E74C8 = 0xFF;
        func_8000E09C(0);
        D_80038A8C = -2;
        D_800E7C90 = 0;
        D_80038A92 = 0x17;
        func_800BABC0();
        break;
    case 0xD:
    case 0xE:
    case 0xF:
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
        if (func_8000F6F4() == 0) {
            func_8000EED8(D_8007EF30.f4);
            func_8000F620(1);
        }
        D_800E74E0 = 0;
        D_800E7C90 -= 0xB;
        func_800BC32C();
        break;
    case 0x16:
        t = D_800E74E0;
        D_800D5F28 = 0xC0;
        D_800E74F8 = -868 - (-868 * t) / 32;
        D_800E74FC = -565 - (-565 * t) / 32;
        D_800E7500 = 3081 - (3081 * t) / 32;
        D_800E7508 = 0;
        D_800E750C = -34 - (-34 * t) / 32;
        D_800E7510 = 0;
        if (t < 0x20) {
            D_800E74C8 = t * 8;
        } else {
            D_800E74C8 = 0xFF;
            D_800E9F70 = -1;
            D_800E74C4 = 0;
            func_800B807C(0, 0x20);
            D_800E74E0 = 0;
            D_800E798C = 0;
            D_800E7C90++;
            func_8000DFD0(0);
        }
        break;
    case 0x17:
        if (D_800E74E0 >= 0x30) {
            s = D_800E74E0 - 0x40;
            if (s == 0x10 || s == 0x20) {
                D_800DF1CC = 0x410;
            }
            if (s >= 0x10) {
                if (s == 0x10) {
                    D_800E74C8 = 0xFF;
                }
                findOrAddCacheEntryRaw(0x10D, 0xF0, 0x50, 0, 0x400);
            } else {
                findOrAddCacheEntryRaw(0x10D, ((0x10 - s) << 5) + 0xF0, 0x50, 0, 0x400);
            }
            if (s >= 0x30) {
                if (s == 0x30) {
                    D_800E74C8 = 0xFF;
                }
                findOrAddCacheEntryRaw(D_8007EF30.cup->fE, 0xF0, 0xA0, 0, 0x400);
            } else if (s >= 0x20) {
                findOrAddCacheEntryRaw(D_8007EF30.cup->fE, 0xF0 - ((0x30 - s) << 5), 0xA0, 0, 0x400);
            }
        }
        if (D_800E74E0 < 0x20) {
            D_800E74C8 = (0x1F - D_800E74E0) * 8;
        } else if (D_800E74C8 != 0) {
            D_800E74C8 -= 0x10;
            if (D_800E74C8 < 0) {
                D_800E74C8 = 0;
            }
        }
        if (D_800E74E0 >= 0xB4 || (D_800EA0C2 & 0xD000)) {
            D_800E7C90 = 0x1B;
            D_800E74E0 = 0;
        }
        break;
    case 0x1B:
        if (D_800E74E0 >= 8) {
            D_800E74C8 = 0xFF;
            if (D_8007EF30.mode & 0x20) {
                D_800E7C90 = 0x11;
            } else {
                D_800E7C90 = 0xF;
            }
            D_80038A92 = 0x15;
            D_80038A8C = -1;
            D_80038A98 = 0;
            D_800D5F28 = 0;
        } else {
            D_800E74C8 = D_800E74E0 << 5;
        }
        break;
    case 0x1C:
        func_8000DFD0(0);
        if (D_800E74E0 >= 0x20) {
            D_800E9F70 = -1;
            func_8000EED8(D_8007EF30.f4);
            func_8000F620(1);
            D_800E7C90 = 0x1D;
            D_800E74E0 = 0;
            if (func_800B04BC(D_8007E228.ids[0]) != 0 ||
                ((D_8007EF30.mode & 0x20) && func_800B04BC(D_8007E228.ids[1]) != 0)) {
                D_800E798C = 1;
            } else {
                D_800E798C = 0;
            }
        } else {
            D_800E74C8 = -D_800E74E0 * 8;
        }
        break;
    case 0x1D:
        D_800D5F28 = 0xC0;
        D_800E74E0 = 0;
        D_8007EF30.mode |= 0x800;
        D_800E7C90++;
        func_800BCBB4(0);
        break;
    case 0x1E:
        func_800BCBB4(1);
        if (D_800E74E0 >= 0x20) {
            D_800E74E0 = 0;
            D_800E7C90++;
            func_800B807C(1, 0x20);
        }
        break;
    case 0x1F:
        D_800E9F70 = -1;
        D_800E74D8 = -8;
        D_800E8204 = -8;
        D_800E8200 = -8;
        func_800AA1E0(0, D_8007E228.ids[0], D_8007E8C0.f70 | (u16)((D_8007EF30.cup->f0 << 4) | 4), 6);
        if (D_8007EF30.mode & 0x20) {
            func_800AA1E0(1, D_8007E228.ids[1], D_8007E8C0.f74 | (u16)((D_8007EF30.cup->f0 << 4) | 4), 6);
        }
        if (D_800E74E0 < 0x258) {
            func_800BCBB4(D_800E74E0 + 1);
        }
        if (D_800E74E0 >= 0x20) {
            D_800E74C8 = 0;
            if (D_800E74E0 >= 0x2D0 || (D_800EA0C2 & 0xC000)) {
                D_800E74E0 = 0;
                D_800E7C90++;
            }
        } else {
            D_800E74C8 = (D_800E74E0 - 0x1F) * 8;
        }
        break;
    case 0x20:
        D_800E74D8 = -8;
        D_800E8204 = -8;
        D_800E8200 = -8;
        func_800AA1E0(0, D_8007E228.ids[0], D_8007E8C0.f70 | (u16)((D_8007EF30.cup->f0 << 4) | 4), 6);
        if (D_8007EF30.mode & 0x20) {
            func_800AA1E0(1, D_8007E228.ids[1], D_8007E8C0.f74 | (u16)((D_8007EF30.cup->f0 << 4) | 4), 6);
        }
        if (D_800E74E0 < 0x20) {
            D_800E74C8 = -D_800E74E0 * 8;
        } else {
            D_800E74E0 = 0;
            D_800E7C90++;
        }
        break;
    case 0x21:
        func_8000E09C(0);
        func_800B8050();
        func_800B807C(0, 0);
        D_800E9F70 = 9;
        D_800E74D8 = -1;
        D_800E8204 = -1;
        D_800E8200 = -1;
        D_80038A90 = 0xF;
        D_8007EF30.mode |= 0x800;
        func_800B2588();
        D_800E7C90 = 0;
        D_800D5F28 = 0;
        break;
    case 0x23:
        if (D_800E74E0 >= 0x20) {
            D_800E9F70 = 0;
            D_800E74E0 = 0;
            D_800E74C4 = -1;
            D_800E79BC = 0;
            D_800E74F0 = -1;
            D_800EA0A8[1] = 0;
            D_800EA0A8[0] = 0;
            D_800E74B8[1] = 0;
            D_800E74B8[0] = 0;
            D_800EA320 = 0;
            D_800E74F8 = D_800E74FC = D_800E7500 = D_800E7508 = D_800E750C = D_800E7510 = 0.0f;
            D_800E7C90++;
            if (D_800E798C == 1) {
                D_800E7CC0 = 0;
                D_800E7CC4 = -1;
            } else {
                D_800E7CC0 = 1;
                D_800E7CC4 = 2;
            }
        } else {
            D_800E74C8 = -D_800E74E0 * 8;
        }
        break;
    case 0x24:
        if (D_800E798C == 1) {
            findOrAddCacheEntryRaw(0x113, 0xF0, 0x3C, 0x18008, 0x402);
        } else {
            findOrAddCacheEntryRaw(0x115, 0xF0, 0x3C, 0x18008, 0x402);
        }
        if (D_800E74E0 >= 0x20) {
            D_800E74E0 = 0;
            D_800E7C90++;
            func_800B807C(0, 1);
        }
        break;
    case 0x25:
        D_800E74D8 = -4;
        D_800E8204 = -4;
        D_800E8200 = -4;
        func_800C3094(-1, 0, 1000, 1000, 0x20, 0x20);
        if (D_800E798C == 1) {
            findOrAddCacheEntryRaw(0x113, 0xF0, 0x3C, 0x18008, 0x402);
            findOrAddCacheEntryRaw(0x114, 0xF0, 0x64, 0x18008, 0x402);
            func_800AA1E0(0, D_8007EF30.opp[0], 8, 6);
            D_800E74B8[1] = D_800E74B8[0];
            D_800EA0A8[1] = D_800EA0A8[0];
        } else {
            findOrAddCacheEntryRaw(0x115, 0xF0, 0x3C, 0x18008, 0x402);
            findOrAddCacheEntryRaw(0x116, 0xF0, 0x64, 0x18008, 0x402);
            func_800AA1E0(0, D_8007EF30.opp[0], 8, 6);
            func_800AA1E0(1, D_8007EF30.opp[1], 8, 6);
        }
        if (D_800EA0A8[0] == D_800EA0A8[1]) {
            D_800EA320 = D_800EA0A8[0];
        }
        if (D_800E74E0 >= 0x20) {
            D_800E74C8 = 0;
        } else {
            D_800E74C8 = (D_800E74E0 - 0x1F) * 8;
        }
        if (D_800EA320 == 1) {
            D_800EA0A8[0] = 2;
            D_800EA0A8[1] = 2;
            D_800E74E0 = 0;
            D_800E9F90 = 0;
            D_800DF1D8 = 0;
            D_800E7C90++;
            do {
                v = guRandom() % 5;
            } while ((D_800DF1D8 >> v) & 1);
            D_800DF1D8 |= 1 << v;
            D_800E8210 = v;
        }
        break;
    case 0x26:
        D_800E74C8 = 0;
        D_800E74D8 = -4;
        D_800E8204 = -4;
        D_800E8200 = -4;
        if (D_800E9F90 == 0 && D_800E74E0 >= func_8002AF9C(D_8007EF30.opp[0])) {
            D_800E9F90 = 1;
            D_800E74C4 = func_800BB5A4(D_8007EF30.opp[0]);
        }
        if (D_800E74E0 < 8) {
            D_800E79BC = D_800E74E0 << 5;
            func_800C3094(-1, 0, 1000, 1000, D_800E79BC, D_800E74E0 << 4);
        } else {
            D_800E79BC = 0xFF;
            func_800C3094(-1, 0, 1000, 1000, D_800E79BC, 0x80);
        }
        if (D_800E798C == 1) {
            func_800AA1E0(0, D_8007EF30.opp[0], 8, 6);
            func_80099148(func_8002AD04(D_8007EF30.opp[0], 0), 0xF0, 0xC8, 0x18008, 0x402);
            D_800E74B8[1] = D_800E74B8[0];
            D_800EA0A8[1] = D_800EA0A8[0];
        } else {
            func_800AA1E0(0, D_8007EF30.opp[0], 8, 6);
            func_800AA1E0(1, D_8007EF30.opp[1], 8, 6);
            func_80099148(func_8002AD04(D_8007EF30.opp[0], 0), 0xF0, 0xB9, 0x18008, 0x402);
            func_80099148(func_8002AD04(D_8007EF30.opp[1], 0), 0xF0, 0xD2, 0x18008, 0x402);
        }
        if (D_800EA0A8[0] == D_800EA0A8[1]) {
            D_800EA320 = D_800EA0A8[0];
        }
        if (D_800EA320 == 3) {
            if (D_800E74E0 >= 0x100 || (D_800EA0C2 & 0xC000)) {
                D_800E74E0 = 0;
                D_800E7C90++;
            }
        }
        break;
    case 0x27:
        D_800E74D8 = -4;
        D_800E8204 = -4;
        D_800E8200 = -4;
        if (D_800E798C == 1) {
            func_800AA1E0(0, D_8007EF30.opp[0], 8, 6);
        } else {
            func_800AA1E0(0, D_8007EF30.opp[0], 8, 6);
            func_800AA1E0(1, D_8007EF30.opp[1], 8, 6);
        }
        if (D_800E74E0 >= 0x20) {
            D_800E74D8 = -1;
            D_800E8204 = -1;
            D_800E8200 = -1;
            D_800E7C90 = 0x36;
            D_800E74E0 = 0;
        } else {
            D_800E74C8 = D_800E74E0 * 8;
        }
        break;
    case 0x35:
        if (D_800E74E0 < 0x20) {
            D_800E74C8 = D_800E74E0 * 8;
        } else {
            D_800E74E0 = 0;
            D_800E7C90++;
        }
        break;
    case 0x36:
        D_800E9F70 = 9;
        if (D_800E74E0 >= 0x30) {
            D_800E74E0 = 0;
            D_800E9F90 = 0;
            D_800E797C = 0;
            D_800E7C90++;
            for (i = 0; i < 0x20; i++) {
                D_800E79D8[i].p = 0;
                D_800E79D8[i].f4 = -1;
            }
        } else if (D_800E74E0 >= 0x10) {
            D_800E74C8 = (0x2F - D_800E74E0) * 8;
        } else {
            D_800E74C8 = 0xFF;
        }
        break;
    case 0x37:
        D_800E79C4 = 0x1A;
        D_800EA0B4 = 1;
        switch (D_800E74E0) {
        case 0x20:
            D_800DF1CC = 0x41C;
            D_800E797C = 0x100;
            break;
        case 0x30:
            D_800DF1CC = 0x41C;
            D_800E797C = 0x100;
            break;
        case 0x40:
            D_800DF1CC = 0x425;
            break;
        case 0x50:
            D_800DF1CC = 0x41E;
            D_800E797C = 0x200;
            func_800C54FC(0x7F);
            break;
        case 0x80:
            D_800DF1CC = 0x426;
            break;
        case 0x90:
            D_800E74E0 = 0;
            D_800E7C90++;
            break;
        }
        break;
    case 0x38:
        func_800C54FC(0);
        D_800E79C4 = 0x1A;
        D_800EA0B4 = 1;
        D_800E74C8 = 0;
        k = D_800E9F90;
        if (D_800E74E0 >= D_800D34C8[k].f7 * 4) {
            if (*(s32 *)&D_800D34C8[k] != 0) {
                for (j = 0, p = D_800E79D8; j < 0x20; j++, p++) {
                    if (p->f4 < 0) {
                        p->f4 = 0;
                        p->p = &D_800D34C8[k];
                        break;
                    }
                }
                D_800E9F90++;
            } else {
                D_800E7C90++;
            }
            D_800E74E0 = 0;
        }
        if (D_800EA0C2 & 0xC000) {
            D_800E7C90 = 0x3B;
            D_800E74E0 = 0;
        }
        break;
    case 0x39:
        v = D_800E74E0 - 0x190;
        if ((u32)v < 0x12C) {
            if (D_800E74E0 >= 0x210) {
                v = 0x7F;
            }
            func_800C54FC(v);
        }
        if (D_800E74E0 == 0x2BC) {
            D_800E797C = 0x400;
            D_800DF1CC = 0x41C;
            func_800C54FC(0);
        }
        if (D_800EA0C2 & 0xC000) {
            D_800E7C90 = 0x3B;
            D_800E74E0 = 0;
        }
        break;
    case 0x3B:
        if (D_800E74E0 >= 0x20) {
            func_800C54FC(0);
            D_80038A8C = -1;
            D_80038A92 = 0;
            D_800E7C90 = 0;
            D_800E74C8 = 0xFF;
            D_80038A98 = -1;
        } else {
            D_800E74C8 = D_800E74E0 * 8;
        }
        break;
    case 0x3C:
        D_800E7CA4 = -1;
        D_800E7CA0 = -1;
        D_800E7C9C = -1;
        D_800E7C98 = -1;
        D_800E74C8 = -0x100;
        D_800DF1CC = 0x410;
        D_800E7C90 = 0x3D;
        D_800E74E0 = 0;
        break;
    case 0x3D:
        D_800E7CA4 = -1;
        D_800E7CA0 = -1;
        D_800E7C9C = -1;
        D_800E7C98 = -1;
        findOrAddCacheEntryRaw(0x11D, 0xF0, 0x64, 8, 0x420);
        break;
    case 0x2F:
        D_800E7CA4 = -1;
        D_800E7CA0 = -1;
        D_800E7C9C = -1;
        D_800E7C98 = -1;
        if (D_80038A98 == 0) {
            D_800E74C8 = -0x100;
        } else {
            D_800E74C8 = -0x80;
        }
        D_800DF1CC = 0x410;
        D_800E7C90 = 0x30;
        D_800E74E0 = 0;
        D_800DF1C0 = 1;
        break;
    case 0x30:
        D_800E7CA4 = -1;
        D_800E7CA0 = -1;
        D_800E7C9C = -1;
        D_800E7C98 = -1;
        func_800BB440();
        break;
    case 0x31:
        D_800E7CA4 = -1;
        D_800E7CA0 = -1;
        D_800E7C9C = -1;
        D_800E7C98 = -1;
        if (D_80038A98 == 0) {
            D_800E74C8 = -0x100;
            D_800E7C90 = 0;
            D_800E74E0 = 0;
            D_80038A98 = 0;
        } else if (D_800E74E0 >= 0x18) {
            D_800E74C8 = 0;
            D_800E7C90 = 0;
            D_800E74E0 = 0;
        } else {
            D_800E74C8 = D_800E74E0 * 8 - 0xC0;
        }
        break;
    case 0x32:
        findOrAddCacheEntryRaw(0x11C, 0xF0, 0x64, 8, 0x420);
        if (D_800E74E0 >= 0x10) {
            D_800E74E0 = 0;
            D_800DF1C0 = 1;
            D_800E7C90++;
        } else {
            D_800E74C8 = -D_800E74E0 * 8;
        }
        break;
    case 0x33:
        findOrAddCacheEntryRaw(0x11C, 0xF0, 0x64, 8, 0x420);
        D_800DF1D0 = 1;
        s = 0;
        if (D_800EA0C2 & 0xC00) {
            D_800DF1CC = 0x409;
            D_800DF1C0 ^= 1;
        } else if (D_800EA0C2 & 0x8000) {
            s = D_800DF1C0 ? -1 : 1;
        } else if (D_800EA0C2 & 0x4000) {
            if (D_800DF1C0 == 0) {
                D_800DF1C0 = 1;
                D_800DF1CC = 0x409;
            } else {
                s = -1;
            }
        }
        findOrAddCacheEntryRaw(0x11E, 0xE0, 0xA0, 8, 0x20);
        findOrAddCacheEntryRaw(0x11F, 0xE0, D_800DF1C0 * 0xE + 0xA0, 8, 0x121);
        switch (s) {
        case 1:
            D_800DF1CC = 0x402;
            func_8002BBCC(D_800E9F8C);
            func_800BA1A4(D_800E9F8C, -1);
            D_800DF1CC = 0x429;
            D_800E7C90 = 0x34;
            break;
        case -1:
            D_800DF1CC = 0x403;
            D_800E7C90 = 0x34;
            break;
        }
        D_800E74E0 = 0x20;
        D_800E74C8 = -0x80;
        break;
    case 0x34:
        D_800E74C8 += 8;
        if (D_800E74C8 >= 0) {
            if ((D_8007EF30.mode & 0xF) != 8) {
                func_800B5300(0x13);
            }
            D_800E74C8 = 0;
            D_800E7C90 = 0;
            D_80038A90 = D_800E9F90;
        }
        break;
    case 0x3F:
        findOrAddCacheEntryRaw(0x117, 0xF0, 0x50, 8, 0x420);
        findOrAddCacheEntryRaw(0x118, 0xF0, 0x78, 8, 0x420);
        if (D_800E74E0 >= 0x10) {
            D_800E74C8 = -0x80;
            D_800E7C90 = 0x40;
            D_800E74E0 = 0;
            D_800DF1C0 = 1;
        } else {
            D_800E74C8 = -D_800E74E0 * 8;
        }
        break;
    case 0x40:
        D_800E74C8 = -0x80;
        findOrAddCacheEntryRaw(0x117, 0xF0, 0x50, 8, 0x420);
        findOrAddCacheEntryRaw(0x118, 0xF0, 0x78, 8, 0x420);
        D_800DF1D0 = 1;
        s = 0;
        if (D_800EA0C2 & 0xC00) {
            D_800DF1CC = 0x409;
            D_800DF1C0 ^= 1;
        } else if (D_800EA0C2 & 0x8000) {
            s = D_800DF1C0 ? -1 : 1;
        } else if (D_800EA0C2 & 0x4000) {
            if (D_800DF1C0 == 0) {
                D_800DF1C0 = 1;
                D_800DF1CC = 0x409;
            } else {
                s = -1;
            }
        }
        findOrAddCacheEntryRaw(0x11E, 0xE0, 0x8C, 8, 0x20);
        findOrAddCacheEntryRaw(0x11F, 0xE0, D_800DF1C0 * 0xE + 0x8C, 8, 0x121);
        switch (s) {
        case 1:
            D_800DF1CC = 0x429;
            D_800E7C90 = 0x41;
            D_800E74E0 = 0;
            break;
        case -1:
            D_800DF1CC = 0x403;
            D_800E7C90 = 0x42;
            D_800E74E0 = 0;
            if (D_800E7CB8 > 0) {
                D_800E7CB8--;
            }
            break;
        }
        break;
    case 0x41:
        if (D_800E74E0 >= 0x10) {
            D_800E74C8 = 0;
            D_800E7C90 = 0;
            D_800E74E0 = 0;
            func_800AF978();
            func_800B511C(D_800CCA09);
            func_800B5704(-1);
            D_80038A90 = 0x17;
            D_800E9E3C = 0;
        } else {
            D_800E74C8 = D_800E74E0 * 8 - 0x80;
        }
        break;
    case 0x2B:
        if (D_800E74E0 >= 8) {
            D_800E74C8 = -0x80;
            D_800E7C90 = 0x2C;
            D_800DF1C0 = 1;
            D_800E74E0 = 0;
            D_800DF1CC = 0x410;
        } else {
            D_800E74C8 = -D_800E74E0 * 16;
        }
        break;
    case 0x2C:
        D_800E74C8 = -0x80;
        if (D_800E798C == 0x40) {
            findOrAddCacheEntryRaw(0x11A, 0xF0, 0x64, 8, 0x420);
        } else {
            findOrAddCacheEntryRaw(0x11B, 0xF0, 0x64, 8, 0x420);
        }
        D_800DF1D0 = 1;
        if (D_800EA0C2 & 0xD000) {
            D_800E7C90 = 0x2D;
            D_800E74E0 = 0;
        }
        break;
    case 0x2D:
        if (D_800E74E0 >= 8) {
            D_800E74C8 = 0;
            D_800E7C90 = 0;
            D_800E74E0 = 0;
            D_80038A90 = D_800E9F90;
        } else {
            D_800E74C8 = D_800E74E0 * 16 - 0x80;
        }
        break;
    case 0x42:
        D_800E74C8 += 8;
        if (D_800E74C8 >= 0) {
            D_800E74C8 = 0;
            D_800E7C90 = 0;
        }
        break;
    case 0x43:
        D_800E74C8 -= 8;
        if (D_800E74C8 < -0xFE) {
            D_800E74E0 = 0;
            D_800E7C90++;
        }
        break;
    default:
        func_800B9F18();
        D_80038A8C = -1;
        D_80038A92 = 1;
        D_800E7C90 = 0;
        D_800E74C8 = 0xFF;
        break;
    }
    if (old != D_800E9F70) {
        if (D_800E9F70 < 0) {
            func_8000F620(1);
        } else {
            func_8000F620(0);
        }
    }
    if (D_800DF1CC >= 0) {
        func_8000DEE4(D_800DF1CC);
    }
}
