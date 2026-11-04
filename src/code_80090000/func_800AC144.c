/* @header
 * func_800AC144
 * VRAM 0x800AC144 | ROM 0x588B4 | size 0x16FC
 * asm: asm/nonmatchings/code_80090000/func_800AC144.s
 */
#include "common.h"



typedef struct { u8 pad0[6]; u8 up; u8 down; u8 left; u8 right; u8 padA[0xC]; } Item;
typedef struct { u8 pad0[0xF]; u8 fF; u8 pad10[2]; s16 f12; } Sub;
typedef struct {
    u8 pad0[8];
    s16 f8;
    u16 flags;
    s8 fC;
    s8 fD;
    s8 fE;
    u8 fF;
    s16 f10;
    s16 f12;
    u8 pad14[2];
    u8 f16;
    u8 pad17[9];
    u16 f20;
    u16 f22;
    Sub *f24;
    u8 pad28[0x148 - 0x28];
} El;
typedef struct {
    Item **items;
    s16 cur;
    u8 pad6[4];
    u16 fA;
    u8 padC[8];
    El *el;
    u8 pad18[0x138 - 0x18];
} Menu;
typedef struct { s16 f4C; s16 f4E; u8 f50; u8 pad51; u8 f52; u8 pad53[9]; } Pl;
typedef struct { u8 pad0[8]; } L;
typedef struct {
    u8 pad0[2];
    u8 f2;
    u8 pad3;
    u8 f4;
    u8 pad5[3];
    u16 mode;
    u16 fA;
    s16 fC;
    s16 fE;
    s16 f10;
    s16 f12;
    u8 pad14[6];
    s16 f1A;
    u8 pad1C[0x10];
    L *f2C;
    u8 pad30[0x1C];
    Pl pl[4];
    u8 pad8C[0x14E - 0x8C];
    u16 f14E[5];
    u16 f158;
} Game;

extern s16 D_80038A90;
extern s32 D_80038A98, D_80038A9C, D_80038A8C, D_80038AA8;
extern Game D_8007EF30;
extern s32 D_8007FC30;
extern struct { u8 pad0[0x688]; s32 f688; s32 f68C; s32 f690; s32 f694; } D_8007E228;
extern struct { u8 pad0[8]; s32 f8; s32 fC; u8 pad10[0x68]; s32 f78; s32 f7C; } D_8007E8C0;
extern Menu D_800E8230[];
extern El *D_800E9AA4;
extern s32 D_800E74D8, D_800E7C90, D_800E74E0, D_800D5F1C, D_800E7B58, D_800E7908, D_800E7934;
extern s32 D_800EA318, D_800E6B90, D_800E752C, D_800E6B7C, D_800E9F70, D_800EA31C;
extern s32 D_800EA348, D_800E74D4, D_800E7920, D_800E8214;
extern s32 D_800E8200[], D_800E73A8[];
extern u16 D_800EA0C0, D_800EA0C2, D_800EA0C4;
extern s16 D_800E9212, D_800E934A, D_800E9F7C, D_800E7CB8, D_800E947C, D_800E95B4, D_800E8D2C;
extern s16 D_800E8F9C, D_800E995C, D_800E90D4, D_800E9E3C;
extern s16 D_800E7B68[];
extern s8 D_800CC8F5[];
extern L lookupSubTables[];

void func_800ABE60(void);
void func_800BCDF4(void);
void func_800C12D0(s32);
void func_800B58EC(El *);
s32 func_800B807C(s32, s32);
void func_800A9210(s32);
void findOrAddCacheEntryRaw(s32, s32, s32, s32, s32);
s16 func_800033F8(void);
void func_800AD970(Menu *);
s32 func_800AF3A8(void);
s32 func_800A9C80(s32, s32, s32);
s32 func_800A946C(s32);
s32 func_800AE680(void);
s32 func_800B20A4(void);
s32 func_800B469C(void);
s32 func_800A9610(s32);
s32 func_800AAF5C(Menu *, s32);
s32 func_800AB3AC(Menu *, s32);
s32 func_800A9780(void);
void func_800B5300(s32);
void func_8000DEE4(s32);
s32 func_800AA508(Menu *);
void func_800B511C(s32);
void func_800AD840(void);
void func_800B1484(s32, s32);
void func_800B0408(void);
void func_800ADFE4(void);
void func_8000333C(s32);
void func_800AE2C8(void);
void func_800AE5C4(void);
void func_800AF218(void);
s32 func_8002B4A4(s32);
s32 func_800AA1E0(s32, s32, s32, s32);
void func_800C3094(s32, s32, s32, s32, s32, s32);
s32 func_800B0EC4(s32);
void func_800ABFC8(Menu *);
s32 func_8002B1D0(s32);
void func_800AFEF0(s32);

static inline void push(s32 id, s32 n) {
    if (D_800E7CB8 < 0) {
        D_800E7CB8 = 0;
    }
    D_800E7B68[D_800E7CB8++] = id | (n << 8);
    if (D_800E7CB8 >= 0x40) {
        D_800E7CB8 = 0;
    }
}

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

static inline s32 step(Menu *m, s32 dir) {
    s32 n = m->cur;
    Item *it = &m->items[0][n];
    for (;;) {
        if (dir & 0x800) {
            n = it->up;
        } else if (dir & 0x400) {
            n = it->down;
        } else if (dir & 0x200) {
            n = it->left;
        } else if (dir & 0x100) {
            n = it->right;
        } else {
            break;
        }
        if (m->cur == n || !(m->el[n].flags & 0x53)) {
            break;
        }
        it = &m->items[0][n];
    }
    return n;
}

static inline void go(s32 x) {
    D_800E7C90 = x;
    D_800E74E0 = 0;
}

static inline void scroll(void) {
    s32 t, x;

    switch (D_80038A90) {
    case 0xD:
        t = -0x30;
        break;
    case 0xE:
        t = 0x30;
        break;
    default:
        return;
    }
    x = D_800E7B58;
    if (x != t) {
        if (x < t) {
            D_800E7908 += 6;
            D_800E7B58 = x + D_800E7908;
            if (D_800E7B58 >= t) {
                D_800E7B58 = t;
                D_800E7908 = 0;
            }
        } else {
            D_800E7908 -= 6;
            D_800E7B58 = x + D_800E7908;
            if (D_800E7B58 <= t) {
                D_800E7B58 = t;
                D_800E7908 = 0;
            }
        }
    }
    if (D_800E7908 != 0) {
        D_800E9212 = 1;
        D_800E934A = 1;
    } else {
        D_800E9212 = 0;
        D_800E934A = 0;
    }
    func_800A9210(D_800E7934);
}

void func_800AC144(void) {
    Menu *m;
    El *e;
    Menu *p;
    s32 r;
    s32 t, d, i, n;
    s32 old;
    s32 c;
    s16 *f;
    s32 lo;

    D_8007EF30.fA++;
    D_800E74D8 = -1;
    if (D_80038A98 != 0 || D_800E7C90 != 0) {
        func_800ABE60();
    }
    m = &D_800E8230[D_80038A90];
    e = &m->el[m->cur];
    if (D_80038A9C == 0) {
        if (D_800D5F1C == 0) {
            go(0x3C);
        } else if (D_800EA0C0 & 0x1000) {
            go(0x2F);
        }
    }
    D_80038A9C = 1;
    if (D_800E7C90 != 0) {
        D_800E74E0++;
        func_800BCDF4();
        if (D_80038A98 != 0) {
            func_800C12D0(0);
            func_800B58EC(0);
        }
        return;
    }
    if (func_800B807C(-1, -1) != 0) {
        return;
    }
    if (D_80038A98 != 1) {
        return;
    }
    if (D_80038A8C != 0) {
        return;
    }
    func_800B58EC(e);
    switch (D_80038A90) {
    case 0:
        m->el[1].f16 = 0xFF;
        break;
    case 0xD:
    case 0xE:
        scroll();
        break;
    }
    if (!(e->flags & 1) && e->f16 != 0xFF) {
        return;
    }
    r = -1;
    if (e->f12 == 0) {
        c = e->fC;
        switch (e->f24->fF & 0xF) {
        case 3:
        case 4:
            if (D_800EA0C2 & 0x100) {
                e->fC++;
            } else if (D_800EA0C2 & 0x200) {
                e->fC--;
            }
            break;
        case 7:
            if (D_800EA0C4 & 0x200) {
                if (--e->fC < 0) {
                    e->fC = 0xF;
                }
            } else if (D_800EA0C4 & 0x100) {
                if (++e->fC >= 0x10) {
                    e->fC = 0;
                }
            }
            break;
        case 8:
            d = e->f20 & 0xFF;
            if (D_800EA0C4 & 0x200) {
                d--;
            } else if (D_800EA0C4 & 0x100) {
                d++;
            } else if (D_800EA0C4 & 0x20) {
                d -= 10;
            } else if (D_800EA0C4 & 0x10) {
                d += 10;
            }
            if (d > e->f22) {
                d = 0;
            }
            if (d < 0) {
                d = e->f22;
            }
            if (d != (e->f20 & 0xFF)) {
                e->f20 = (e->f20 & 0xFF00) | d;
                e->fC ^= 1;
            }
            break;
        case 5:
            if (D_800EA0C4 & 0x400) {
                e->fC--;
            } else if (D_800EA0C4 & 0x800) {
                e->fC++;
            }
            break;
        }
        if (c != e->fC) {
            n = e->fC;
            if ((e->flags >> 8) == 0xF0) {
                e->fE = e->fC;
            } else {
                i = (e->flags >> 8) & 0xF;
                if (i < n) {
                    /* SImode temp: both arms then compute the same `srl`, and reorg
                       puts one copy in the branch delay slot for both paths */
                    lo = e->flags >> 12;
                    e->fE = lo;
                } else if (n < (e->flags >> 12)) {
                    e->fE = i;
                } else {
                    e->fE = e->fC;
                }
            }
            D_800EA318 = 0x404;
        }
    }
    switch (D_80038A90) {
    case 0:
        if (D_800E6B90 >= 0) {
            D_800E6B90++;
            if (!(D_800E6B90 & 0x10)) {
                findOrAddCacheEntryRaw(0x120, 0xF0, 0xB4, 0x60000, 1);
            }
            if (D_800E6B90 >= 0x384 && func_800033F8() == 0) {
                D_80038A8C = 1;
                D_800E6B90 = -1;
                return;
            }
        }
        break;
    case 0x16:
        D_800E74E0 = 0;
        D_800E7C90 = m->fA;
        return;
    case 3:
        func_800AD970(m);
        break;
    case 0xC:
        switch (m->cur) {
        case 5:
        case 8:
        case 0xB:
        case 0xE:
            r = func_800AF3A8();
            if (r != D_80038A90) {
                D_800E9AA4[3].flags &= ~0x20;
            }
            break;
        }
        break;
    case 0xD:
    case 0xE:
        if (D_800EA0C2 & 0xF) {
            f = &D_8007EF30.f12;
            d = *f;
            if (D_800EA0C2 & 9) {
                *f = func_800A9C80(e->f22, d, 1);
            } else {
                *f = func_800A9C80(e->f22, d, -1);
            }
            if (d != D_8007EF30.f12) {
                D_800E752C = 0;
                D_800EA318 = 0x401;
            }
        } else if (!(D_800EA0C2 & 0xDC00)) {
            d = 0;
            if (D_800EA0C4 & 0x220) {
                d = -1;
            }
            if (D_800EA0C4 & 0x110) {
                d = 1;
            }
            if (d != 0) {
                D_800E7934 = 1;
                r = func_800A946C(d);
                D_8007EF30.f2C = &lookupSubTables[D_8007EF30.f10];
                m = &D_800E8230[D_80038A90];
                e = &m->el[m->cur];
                D_800E9F7C = 1;
                D_800EA318 = 0x423;
                D_800E74D8 = -2;
                D_800E8200[D_800E6B7C] = -2;
            }
        }
        break;
    case 0xA:
        r = func_800AE680();
        break;
    case 0x12:
        r = func_800B20A4();
        break;
    case 0xF:
        if (m->cur == 0x12) {
            r = func_800B469C();
        }
        break;
    case 0x10:
    case 0x11:
        if (m->cur == 0xA) {
            d = 0;
            if (D_800EA0C2 & 0x220) {
                d = -1;
            } else if (D_800EA0C2 & 0x110) {
                d = 1;
            }
            if (d != 0) {
                r = func_800A9610(d);
                D_800EA318 = 0x401;
            }
        }
        break;
    }
    if (r < 0) {
        u16 b = D_800EA0C2;
        s32 ev;
        if ((b & 0x9000) && (ev = e->f24->f12) >= 0) {
            if (b & 0x1000) {
                r = func_800AAF5C(m, ev);
            } else {
                old = D_800E7CB8;
                push(D_80038A90, m->cur);
                r = e->f24->f12;
            }
            if (r >= 0x18) {
                switch (r & 0x7F00) {
                case 0x400:
                    do {
                        r = func_800AB3AC(m, r);
                    } while (r & 0x400);
                    break;
                case 0x100:
                    m->cur = e->f24->f12 & 0xFF;
                    r = -1;
                    break;
                case 0x200:
                    if (D_800E7CB8 > 0) {
                        D_800E7CB8--;
                        D_800EA318 = 0x403;
                        r = 0x200;
                    } else {
                        r = -1;
                    }
                    break;
                case 0:
                    r = -1;
                    break;
                default:
                    r = 0x17;
                    break;
                }
            }
            if (!(D_800EA0C2 & 0x1000) && D_800E7CB8 != old && D_800EA318 < 0) {
                D_800EA318 = 0x402;
            }
            D_800E9F7C = 1;
        } else if (D_800EA0C2 & 0x4000) {
            switch (D_80038A90) {
            case 0xF:
                if (m->cur == 0x13) {
                    D_800E947C = 0x14;
                } else if (m->cur == 0x14) {
                    r = func_800A9780();
                }
                break;
            case 0x10:
            case 0x11:
                if (m->cur == 0xC) {
                    D_800E95B4 = 0xD;
                } else if (m->cur == 0xD) {
                    r = func_800A9780();
                } else {
                    r = 0x200;
                }
                break;
            case 9:
                if (m->cur == 0x10) {
                    r = 0x200;
                } else {
                    D_800E8D2C = 0x10;
                    D_800EA318 = 0x401;
                }
                break;
            case 0xB:
                if (m->cur == 0x16 || m->cur == 0x17) {
                    r = 0x200;
                } else {
                    D_800E8F9C = 0x16;
                    D_800EA318 = 0x401;
                }
                break;
            case 0x13:
                if (m->cur == 0xA) {
                    if ((D_8007EF30.mode & 0xF) != 8) {
                        func_800B5300(0x13);
                    }
                    r = 0x200;
                } else {
                    D_800E995C = 0xA;
                    D_800EA318 = 0x401;
                }
                break;
            case 0xA:
            case 0x12:
            case 0x16:
            case 0x17:
                break;
            default:
                r = 0x200;
                break;
            }
            if (r == 0x200 && D_800E7CB8 > 0) {
                D_800EA318 = 0x403;
            }
            if (r != 0x200 && r >= 0 && r != D_80038A90) {
                D_800E9F7C = 1;
            }
        } else {
            c = step(m, D_800EA0C4);
            if (m->cur != c) {
                func_8000DEE4(0x401);
                m->cur = c;
                m->el[c].flags |= 8;
                m->el[c].fF = 0;
                m->el[c].f8 = 8;
            }
        }
    }
    if (r == 0x200) {
        if (D_800E7CB8 > 0) {
            r = func_800AA508(m);
            m = &D_800E8230[D_80038A90];
            /* do-while(0) placeholder: its loop notes are a scheduling barrier, so
               `move s1,v0` fills the D_80038A90 load delay (letting the index math
               use v0) and m->el, loaded before the multiply, fills the m->cur delay */
            do {
                s32 k = m->cur;
                El *q = m->el;
                e = &q[k];
            } while (0);
        } else {
            r = -1;
        }
    }
    if (r >= 0 && r != D_80038A90) {
        p = &D_800E8230[r];
        func_800B511C(D_800CC8F5[r * 12]);
        if (D_800E9F7C != 0) {
            switch (r) {
            case 1:
                func_800AD840();
                D_800E7CB8 = 0;
                break;
            case 0xD:
            case 0xE:
                D_8007EF30.f2C = &lookupSubTables[D_8007EF30.f10];
                func_800B1484(r, 0);
                if (D_80038A90 != 0xD && D_80038A90 != 0xE) {
                    D_800E9AA4[3].f20 = D_8007FC30 | 0x1200;
                    if (r == 0xD) {
                        D_800E7B58 = -0x30;
                    } else {
                        D_800E7B58 = 0x30;
                    }
                }
                break;
            case 4:
                func_800B0408();
                D_8007EF30.mode = 0;
                break;
            case 8:
                p->el->f22 = p->el->fE = p->el->fC = p->el->fD = D_8007EF30.f1A / 4;
                p->el->f10 = p->el->fE * 128;
                break;
            case 9:
                func_800ADFE4();
                D_800E8214 = D_8007EF30.f2;
                if (D_8007EF30.f2 == 0) {
                    func_8000333C(1);
                } else {
                    func_8000333C(0);
                }
                break;
            case 0xB:
                func_800AE2C8();
                break;
            case 0xA:
                func_800AE5C4();
                break;
            case 0xC:
                D_800E9AA4[3].flags |= 0x20;
                if (D_800E8230[12].cur == 5) {
                    func_800AF218();
                }
                break;
            case 0x17:
                D_800E9E3C = 0;
                break;
            case 2:
                D_800E9F70 = D_8007EF30.f4;
                p->cur = D_8007EF30.f4;
                break;
            }
        }
        D_80038A90 = r;
    } else {
        switch (D_80038A90) {
        case 0xD:
        case 0xE:
            D_800E6B7C = D_8007FC30 - D_800EA31C;
            if (e != &m->el[m->cur]) {
                d = freeSlot(e->f22);
                if (d >= 0) {
                    e->f20 = (e->f20 & 0xFFFC) | d;
                }
                D_8007EF30.f12 = freeSlot(m->el[m->cur].f22);
                m->el[m->cur].f20 &= 0xFFFC;
                m->el[m->cur].f20 |= D_8007EF30.f12;
                D_800E752C = 0;
            } else {
                D_800E8200[D_800E6B7C] = -2;
                D_800E74D8 = -2;
                if (D_8007EF30.f12 >= 0) {
                    e->f20 &= 0xFFFC;
                    e->f20 |= D_8007EF30.f12 & 3;
                }
                D_800E752C++;
            }
            D_8007EF30.fE = m->cur - 1;
            if (e->f22 != 0) {
                D_800E752C = func_800AA1E0(D_800E6B7C, e->f22, D_8007EF30.f12 | 0x80, D_800E752C);
                if (D_800E6B7C != 0) {
                    func_800AA1E0(0, D_8007EF30.pl[D_8007FC30 - 1].f4E, D_8007EF30.pl[D_8007FC30 - 1].f50 | 0x80, 6);
                }
            }
            break;
        case 2:
            D_800E9F70 = m->cur;
            break;
        case 4:
            if (e != &m->el[m->cur]) {
                D_800E752C = 0;
            } else {
                D_800E752C++;
            }
            D_800E74D8 = -7;
            D_800E8200[1] = -7;
            D_800E8200[0] = -7;
            func_800C3094(-1, 0, 1000, 1000, 0xFF, 0x20);
            d = func_800B0EC4(D_8007EF30.f14E[m->cur]) ? 4 : 0xC;
            d |= (D_8007EF30.f14E[m->cur] >> 12) & 3;
            D_800E752C = func_800AA1E0(0, D_8007EF30.f14E[m->cur] & 0xFFF, d | (m->cur << 4), D_800E752C);
            if (m->cur == 2) {
                d = func_800B0EC4(D_8007EF30.f158) ? 4 : 0xC;
                d |= (D_8007EF30.f158 >> 12) & 3;
                func_800AA1E0(1, D_8007EF30.f158 & 0xFFF, d | (m->cur << 4), D_800E752C);
            }
            break;
        case 0x13:
            D_800E8200[1] = -3;
            D_800E8200[0] = -3;
            D_800E752C = 6;
            D_800E74D8 = -3;
            func_800AA1E0(0, D_8007EF30.pl[m->fA].f4E, D_8007EF30.pl[m->fA].f50, 6);
            if ((m->el[4].f20 & 0xFF) != D_800EA348) {
                D_800EA348 = m->el[4].f20 & 0xFF;
            }
            if ((m->el[6].f20 & 0xFF) != D_800E74D4) {
                D_800E74D4 = m->el[6].f20 & 0xFF;
            }
            for (d = 0; d < 2; d++) {
                if (D_800E7920 & (2 << d)) {
                    m->el[d + 8].flags &= ~0x40;
                    m->el[d + 8].f16 = 0xFF;
                    if (m->el[d + 8].fC != D_800E73A8[d]) {
                        D_800E73A8[d] = m->el[d + 8].fC;
                    }
                } else {
                    m->el[d + 8].flags |= 0x40;
                    m->el[d + 8].f16 = 0x80;
                    if (m->cur == d + 8) {
                        m->cur = step(m, 0x400);
                    }
                }
            }
            break;
        case 0xB:
            func_800ABFC8(m);
            break;
        case 9:
            if (m->el[12].fE == 0) {
                func_8000333C(1);
            } else {
                func_8000333C(0);
            }
            break;
        case 0x17:
            if ((D_8007EF30.mode & 0xF0) == 0x10) {
                d = func_8002B1D0(D_8007E228.f688);
                if (d != 0) {
                    D_8007E228.f690 = d;
                    D_8007E8C0.f8 = 3;
                    D_8007E8C0.f78 = 0;
                }
                d = func_8002B1D0(D_8007E228.f68C);
                if (d != 0) {
                    D_8007E228.f694 = d;
                    D_8007E8C0.fC = 4;
                    D_8007E8C0.f7C = 0;
                }
            }
            if (D_8007EF30.mode & 0x8000) {
                func_800AFEF0(0);
                if (D_80038AA8 == 8) {
                    go(0x16);
                } else {
                    go(1);
                }
            } else {
                go(1);
            }
            break;
        }
    }
    if (D_800EA318 >= 0) {
        func_8000DEE4((s16)D_800EA318);
    }
    D_800EA318 = -1;
}
