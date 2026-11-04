/* @header
 * func_800AA508
 * VRAM 0x800AA508 | ROM 0x56C78 | size 0x65C
 * asm: asm/nonmatchings/code_80090000/func_800AA508.s
 */
#include "common.h"

typedef struct { u8 pad0[0x12]; s16 f12; } Sub;
typedef struct {
    u8 pad0[8];
    s16 f8;
    u16 flags;
    u8 padC[8];
    s16 f14;
    u8 pad16[0xA];
    s16 f20;
    u16 f22;
    Sub *f24;
    u8 pad28[0x148 - 0x28];
} El;
typedef struct {
    void *items;
    s16 cur;
    u8 pad6[8];
    s16 fE;
    u8 pad10[2];
    s16 f12;
    El *el;
    u8 pad18[0x138 - 0x18];
} Menu;
typedef struct { s16 f4C; s16 f4E; u8 f50; u8 pad51; u8 f52; u8 pad53; u8 b[8]; } Pl;
typedef struct { u8 pad0[6]; u16 f6; } Opt;
typedef struct { u8 *p; u16 n; u16 c; } L;
typedef struct {
    u8 pad0[4];
    u8 f4;
    u8 pad5[3];
    u16 mode;
    u8 padA[2];
    s16 fC;
    s16 fE;
    s16 f10;
    s16 f12;
    u8 pad14[0x18];
    L *f2C;
    Opt *f30;
    u8 pad34[0x18];
    Pl pl[0xCB];
} Game;
typedef struct { u8 b[8]; u8 pad[8]; } X;

extern s16 D_80038A90;
extern s16 D_800E7CB8;
extern u16 D_800E7B68[];
extern Game D_8007EF30;
extern s32 D_8007FC30; /* right after D_8007EF30 */
#define XX ((X *)((u8 *)&D_8007EF30 + 0x54))
extern Menu D_800E8230[];
extern s32 D_800E8204, D_800E8200[], D_800E9F70, D_800E6B7C, D_800E7934, D_800EA31C;
extern s16 D_800E9F7C;
extern L lookupSubTables[];

void func_800B5704(s32);
void func_800ADEF8(void);
void func_800B1484(s32, s32);
void func_800A9E74(s32, s32, s32, s32, s32);
s32 findIdSubTableIndex(s32);
s32 func_800B11BC(s32, s32);
void func_800A9108(void);
void func_800A9210(s32);
void func_800AEF28(s32);
void func_800AD840(void);

static inline s32 team(s32 x) {
    if (D_8007EF30.mode & 0x90) {
        return x;
    }
    return x / 2;
}

static inline void setId(s32 id) {
    D_8007EF30.f10 = findIdSubTableIndex(id);
    D_8007EF30.fE = func_800B11BC(D_8007EF30.f10, D_8007EF30.pl[D_8007FC30].f4E);
}

s32 func_800AA508(Menu *m) {
    u16 e;
    s32 cur;
    Menu *p;
    El *el;
    s32 n, i, old;

    if (D_800E7CB8 > 0) {
        D_800E7CB8--;
    }
    e = D_800E7B68[D_800E7CB8];
    cur = e & 0xFF;
    p = &D_800E8230[cur];
    n = e >> 8;
    el = &p->el[n];
    p->cur = n;
    func_800B5704(cur);

    switch (D_80038A90) {
    case 9:
        func_800ADEF8();
        break;
    case 4:
    case 0x13:
        D_800E8204 = -1;
        D_800E8200[0] = -1;
        break;
    case 2:
        D_800E9F70 = D_8007EF30.f4;
        break;
    case 0xD:
    case 0xE:
        D_800E8200[D_800E6B7C] = -1;
        break;
    }
    D_800E9F7C = 0;

    switch (cur) {
    case 7:
        for (i = 3; i >= 0; i--) {
            D_8007EF30.pl[i].f4E = -1;
        }
        D_8007FC30 = 0;
        D_800E8230[20].el[3].f20 = 0x120F;
        break;
    case 0xD:
    case 0xE:
        old = D_8007FC30;
        el->f14 = 0xFF;
        el->f8 = 0;
        D_8007FC30 = old - 1;
        D_800E8230[20].el[3].f20 = D_8007FC30 | 0x1200;
        if (D_80038A90 == 0xD || D_80038A90 == 0xE) {
            if (team(D_8007FC30) != team(old)) {
                cur = 0xD;
                D_800E7934 = 0;
                if (D_80038A90 == 0xD) {
                    func_800B1484(0xD, -1);
                    D_80038A90 = 0xE;
                }
                func_800B1484(0xE, 1);
            } else if (D_8007EF30.pl[D_8007FC30].f4C != D_8007EF30.f10) {
                D_800E7934 = 1;
                if (p == m) {
                    cur = 0xD;
                    if (D_80038A90 == 0xD) {
                        cur = 0xE;
                    }
                }
            } else {
                cur = D_80038A90;
            }
        } else {
            func_800B1484(0xD, 0);
            cur = 0xD;
            if (D_8007EF30.mode & 0x8000) {
                for (i = 1; i < 8; i++) {
                    func_800A9E74(i * 2, -1, -1, 0, 5);
                    func_800A9E74(i * 2 + 1, -1, -1, 0, 5);
                    XX[i * 2].b[0] = 0xFF;
                    XX[i * 2].b[5] = 0x32;
                    XX[i * 2].b[4] = 0x32;
                    XX[i * 2].b[3] = 0x32;
                    XX[i * 2].b[2] = 0x32;
                    XX[i * 2].b[1] = 0x32;
                    XX[i * 2].b[7] = 0;
                    XX[i * 2].b[6] = 0;
                    XX[i * 2 + 1].b[0] = 0xFF;
                    XX[i * 2 + 1].b[5] = 0x32;
                    XX[i * 2 + 1].b[4] = 0x32;
                    XX[i * 2 + 1].b[3] = 0x32;
                    XX[i * 2 + 1].b[2] = 0x32;
                    XX[i * 2 + 1].b[1] = 0x32;
                    XX[i * 2 + 1].b[7] = 0;
                    XX[i * 2 + 1].b[6] = 0;
                }
            }
        }
        p = &D_800E8230[cur];
        if ((D_8007EF30.mode & 0x8000) && (D_8007EF30.f30->f6 & 0x2000)) {
            setId((s16)(D_8007EF30.pl[D_8007FC30].f4E | 0x1000));
        } else {
            setId(D_8007EF30.pl[D_8007FC30].f4E);
        }
        D_8007EF30.f2C = &lookupSubTables[D_8007EF30.f10];
        if (D_8007FC30 == 0) {
            func_800A9108();
        } else if (D_8007EF30.pl[D_8007FC30].f4E > 0) {
            D_8007EF30.pl[D_8007FC30].f4E = -D_8007EF30.pl[D_8007FC30].f4E;
        }
        func_800B1484(cur, 0);
        func_800A9210(D_800E7934);
        p->cur = D_8007EF30.fE + 1;
        p->el[10].f22 = p->el[p->cur].f22;
        if (D_8007EF30.mode & 0x60) {
            D_800EA31C = D_8007FC30 & 2;
        } else {
            D_800EA31C = D_8007FC30;
        }
        D_800E9F7C = 1;
        break;
    case 0xC:
        if (el->f24->f12 == 0xB) {
            D_8007FC30 = D_8007EF30.fC;
            func_800AEF28(0);
            D_800E8230[12].el[2].flags &= ~1;
        } else if (D_80038A90 != 0xC && D_8007FC30 == 0) {
            func_800AEF28(1);
        }
        break;
    case 1:
        func_800AD840();
        D_800E7CB8 = 0;
        func_800A9108();
        break;
    }
    if (cur != D_80038A90) {
        D_800E8230[cur].fE = 0x88;
        D_800E8230[cur].f12 = 0x10;
    }
    return cur;
}
