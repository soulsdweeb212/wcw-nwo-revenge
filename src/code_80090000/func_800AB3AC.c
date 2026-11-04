/* @header
 * func_800AB3AC
 * VRAM 0x800AB3AC | ROM 0x57B1C | size 0xA30
 * asm: asm/nonmatchings/code_80090000/func_800AB3AC.s
 */
#include "common.h"

typedef struct { u8 pad0[7]; u8 next; u8 pad8[0xE]; } Item;
typedef struct {
    u8 pad0[0xA];
    u16 flags;
    u8 padC[2];
    s8 fE;
    u8 padF[3];
    s16 f12;
    u8 pad14[0xC];
    u16 f20;
    u16 f22;
    u8 pad24[0x148 - 0x24];
} El;
typedef struct {
    Item **items;
    s16 cur;
    u8 pad6[4];
    u16 fA;
    u8 padC[8];
    El *el;
} Menu;

typedef struct { s16 f4C; s16 f4E; u8 f50; u8 pad51; u8 f52; u8 pad53[9]; } Pl;
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
    u8 pad14[4];
    s16 f18;
    s16 f1A;
    u8 pad1C[0x30];
    Pl pl[4];
    u8 pad8C[0xC90 - 0x8C];
    u16 fC90[40];
} Game;
extern s16 D_80038A90;
extern s32 D_80038AA8;
extern Game D_8007EF30;
extern u16 D_8007EF38;
extern s32 D_8007FC30;
extern s16 D_800E7CB8;
extern u8 D_800E7B67[];
extern s32 D_800EA318, D_800E74D8, D_800E8204, D_800E8200, D_800E7934, D_800E7C90, D_800E9F90, D_800E74E0;
extern s32 D_800E9F8C, D_800E7B58, D_800E6B90, D_800E798C;
extern s16 D_800E8F9C, D_800E995C, D_800E8D2C, D_800E90D4;

s32 func_8002B4A4(s32);
void func_800B5300(s32);
void func_800A9108(void);
void func_800B0DD4(s32);
void func_800B9F18(void);
s32 func_800ADBFC(s32);
s32 func_800ADD80(s32);
void func_800B5704(s32);
void func_800AE124(void);
s32 func_800AE0C0(void);
s32 func_800B4A24(void);
void func_800AF978(void);
s32 func_800A9780(void);
void func_800AEF28(s32);
s32 func_800AFEF0(s32);
s32 func_800A9610(s32);
s32 func_800B4DA0(s32);
s32 func_800B4EFC(void);
void func_800B1484(s32, s32);
void func_800A9210(s32);
void func_800B4E18(void);
s32 func_800BA058(void);
s32 func_800BA4B4(void);
void func_800AD840(void);
s32 func_800BB360(void);
s32 func_800AAC2C(s32);
s32 func_800AA508(Menu *);

static inline s32 taken(s32 a, s32 i) {
    s32 j;
    if (i < 0 || i >= func_8002B4A4(a)) {
        return 0;
    }
    for (j = 0; j < 4; j++) {
        if (D_8007EF30.pl[j].f4E == a && (D_8007EF30.pl[j].f50 == i || (D_8007EF30.mode & 0x8000))) {
            return -1;
        }
    }
    return 0;
}

/* the bodies of func_800A8FE4 and func_800A9B90, inlined here */
static inline void clearC90(void) {
    s32 i;
    D_80038AA8 = 0;
    for (i = 0x27; i >= 0; i--) {
        D_8007EF30.fC90[i] = 0;
    }
}

static inline void rec(s32 k, s32 a, s32 c, s32 b) {
    D_8007EF30.pl[k].f4C = a;
    D_8007EF30.pl[k].f4E = c;
    D_8007EF30.pl[k].f50 = b;
    D_8007EF30.pl[k].f52 = 5;
}

static inline s32 freeSlot(s32 a) {
    s32 n, i;
    if ((D_8007EF30.mode & 0x8000) && D_8007EF30.pl[0].f4E == a) {
        return -1;
    }
    n = func_8002B4A4(a);
    for (i = 0; i < n; i++) {
        if (!taken(a, i)) {
            return i;
        }
    }
    return -1;
}

s32 func_800AB3AC(Menu *m, s32 ev) {
    s32 r = D_80038A90;
    El *el = m->el;
    s32 i, id, start, v, x;
    El *e;
    Item *p;

    func_800B5300(ev);
    switch (ev) {
    case 0x401:
        r = 4;
        D_8007EF38 = 0;
        clearC90();
        func_800A9108();
        break;
    case 0x402:
        D_8007EF30.mode = 1;
        func_800A9108();
        r = 5;
        break;
    case 0x404:
        D_8007EF30.mode = 0x83;
        func_800A9108();
        r = 6;
        break;
    case 0x408:
        D_8007EF30.mode = 8;
        D_8007EF30.fC = D_8007EF30.f18 = 1;
        func_800A9108();
        r = 0xD;
        break;
    case 0x409:
        D_8007EF30.mode = 7;
        r = 9;
        break;
    case 0x40D:
        func_800A9108();
        func_800B0DD4(m->cur);
        D_800E8200 = D_800E8204 = D_800E74D8 = -1;
        r = 2;
        break;
    case 0x416:
        D_8007EF30.f4 = m->cur;
        func_800B9F18();
        r = func_800ADBFC(0);
        break;
    case 0x417:
        id = el[m->cur].f22;
        if (!(el[m->cur].flags & 0x53) && !taken(id, D_8007EF30.f12)) {
            rec(D_8007FC30, D_8007EF30.f10, id, D_8007EF30.f12);
            e = &el[m->cur];
            D_8007EF30.f12 = freeSlot(id);
            if (D_8007EF30.f12 < 0) {
                e->flags |= 0x40;
                i = m->cur;
                start = i;
                for (p = &(*m->items)[i]; ; p = &(*m->items)[i]) {
                    i = p->next;
                    if (start == i || !(m->el[i].flags & 0x53)) break;
                }
                m->cur = i;
                D_8007EF30.f12 = freeSlot(m->el[m->cur].f22);
            } else {
                e->f20 &= ~3;
                e->f20 |= D_8007EF30.f12 & 3;
            }
            r = func_800AAC2C(0);
            func_800A9210(D_800E7934);
            D_800EA318 = 0x42A;
        } else if (D_800E7CB8 > 0) {
            D_800E7CB8--;
        }
        break;
    case 0x40A:
        switch (m->cur) {
        case 0:
            D_8007EF30.mode = 0x11;
            D_8007EF30.fC = 2;
            break;
        case 1:
            D_8007EF30.mode = 0x21;
            D_8007EF30.fC = 4;
            break;
        }
        r = 2;
        break;
    case 0x411:
        switch (m->cur) {
        case 1:
            D_8007EF30.mode = 0x43;
            D_8007EF30.fC = 3;
            break;
        case 0:
            D_8007EF30.mode = 0x83;
            D_8007EF30.f1A = D_8007EF30.fC = 4;
            break;
        }
        r = 2;
        break;
    case 0x412:
        D_8007EF30.mode = 0x283;
        r = 0xD;
        break;
    case 0x413:
        D_8007EF30.mode = 0x183;
        r = 0xD;
        break;
    case 0x414:
        D_8007EF30.f1A = el->fE * 4;
        r = 7;
        break;
    case 0x40B:
        r = func_800ADD80(el[m->cur].f20);
        break;
    case 0x41B:
        switch (D_80038A90) {
        case 0xB:
            D_800E8F9C = 0x16;
            break;
        case 0x13:
            D_800E995C = 0xA;
            break;
        default:
            D_800E8D2C = 0x10;
            break;
        }
        D_800EA318 = 0x401;
        if (D_800E7CB8 > 0) {
            D_800E7CB8--;
        }
        break;
    case 0x41D:
        D_800EA318 = 0x42A;
        if (D_8007EF30.mode & 0x8000) {
            func_800B5704(-1);
            func_800AF978();
            r = 0x17;
        } else {
            func_800AE124();
            if (func_800AE0C0() == 0) {
                func_800B5704(-1);
                func_800AF978();
                r = 0x17;
            } else {
                D_800E7C90 = 0x3F;
                D_800E9F90 = 0x17;
                D_800E74E0 = 0;
                D_800EA318 = 0x410;
            }
        }
        break;
    case 0x41E:
        r = 0xA;
        break;
    case 0x41F:
        r = func_800B4A24();
        break;
    case 0x420:
        if (D_800E7CB8 > 0) {
            D_800E7CB8--;
        }
        r = 0x200;
        break;
    case 0x428:
        if (el[m->cur].f12 == 0) {
            func_800AF978();
            r = 0x17;
        }
        break;
    case 0x435:
        r = func_800A9780();
        D_800EA318 = 0x42A;
        break;
    case 0x434:
        func_800AEF28(0);
        func_800AFEF0(0);
        r = 0xC;
        D_800E90D4 = 2;
        D_800EA318 = 0x42A;
        break;
    case 0x433:
        if (D_800E7CB8 > 0) {
            D_800E7CB8--;
        }
        if (D_800E7CB8 > 0) {
            v = D_800E7B67[D_800E7CB8 * 2];
        } else {
            v = -1;
        }
        if (v == 9) {
            r = func_800A9610(1);
            D_800EA318 = 0x401;
        } else {
            r = func_800A9780();
        }
        break;
    case 0x422:
    case 0x423:
        D_800E8200 = D_800E8204 = D_800E74D8 = -1;
        r = func_800B4DA0(ev);
        break;
    case 0x425:
        if (func_800B4EFC() != 0 && D_8007EF30.pl[m->fA].f50 == 0) {
            D_800E74E0 = 0;
            D_800E7C90 = 0x32;
            D_800E9F8C = D_8007EF30.pl[m->fA].f4E;
            if (D_800E7CB8 > 0) {
                D_800E7CB8--;
            }
            D_800E9F90 = func_800AA508(m);
            func_800B1484(D_800E9F90, 0);
            D_800E7934 = 0;
            if (D_800E9F90 == 0xD) {
                x = 0x30;
            } else {
                x = -0x30;
            }
            D_800E7B58 = x;
            func_800A9210(0);
            D_800EA318 = 0x410;
        } else {
            if ((D_8007EF30.mode & 0xF) != 8) {
                func_800B5300(0x13);
            }
            if (D_800E7CB8 > 0) {
                D_800E7CB8--;
            }
            r = 0x200;
        }
        break;
    case 0x426:
        func_800B4E18();
        if (D_800E7CB8 > 0) {
            D_800E7CB8--;
        }
        break;
    case 0x400:
        D_800E6B90 = 0;
        func_800BA058();
        func_800BA4B4();
        D_800E9F90 = 1;
        func_800AD840();
        D_800E7CB8 = 0;
        func_800A9108();
        D_800E798C = func_800BB360();
        D_800E7C90 = 0x2B;
        D_800E74E0 = 0;
        break;
    }
    return r;
}
