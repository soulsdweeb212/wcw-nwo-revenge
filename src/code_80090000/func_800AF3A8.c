/* @header
 * func_800AF3A8
 * VRAM 0x800AF3A8 | ROM 0x5BB18 | size 0x5D0
 * asm: asm/nonmatchings/code_80090000/func_800AF3A8.s
 */
#include "common.h"

typedef struct { u8 pad0[0xA]; u16 flags; u8 padC[0xA]; u8 f16; u8 pad17[0xB]; u16 f22; u8 pad24[0x148 - 0x24]; } El;
typedef struct { void *items; s16 cur; u8 pad6[0xE]; El *el; u8 pad18[0x138 - 0x18]; } Menu;
typedef struct { u8 pad0[4]; u16 held; u16 pressed; u8 pad8[4]; } Pad;
typedef struct { s16 f0; s16 id; u8 f4; u8 f5; u8 f6; u8 pad7[9]; } Pl;
typedef struct { u8 pad0[0x4C]; Pl pl[4]; } Game;
typedef struct { u8 pad0[8]; s32 type[4]; } Cfg;

extern s16 D_80038A90;
extern Pad D_8006E178[];
extern Cfg D_8007E228;
extern s32 D_8007E838[]; /* D_8007E228 + 0x610: its own symbol, or CSE derives its address from type[] */
extern s32 D_8007E8C0[];
extern Game D_8007EF30;
extern s32 D_800E7BF0[];
extern Menu D_800E8230[];
extern u16 D_800EA0C8[];
extern s32 D_800EA318;
s32 func_8000DEE4(s32);

/* Steps from slot `cur` in direction `d` (wrapping 0..3) to the slot player i owns in D_8007E8C0; player 1 may
 * also take a free slot (0). Gives back `cur`, or for cur < 0 the first free slot seen, when none is found. */
static inline s32 findSlot(s32 i, s32 cur, s32 d) {
    s32 r = cur;
    s32 j = cur;
    s32 v;

    do {
        j += d;
        if (j < 0) {
            j = 3;
        }
        if (j >= 4) {
            j = 0;
        }
        v = D_8007E8C0[j];
        if (v == i + 1) {
            return j;
        }
        if (i == 0) {
            if (v == 0) {
                if (cur >= 0) {
                    return j;
                }
                if (r < 0) {
                    r = j;
                }
            }
        }
    } while (j != (cur & 3));
    return r;
}

static inline void take(Menu *m, s32 i, s32 n) {
    m->el[D_800E7BF0[i] * 3 + 4].flags |= 1;
    m->el[n * 3 + 5].flags &= ~1;
    m->el[n * 3 + 4].flags &= ~1;
    m->el[n * 3 + 4].f16 = 0xFF;
    m->el[n * 3 + 5].f16 = 0xFF;
    D_800E7BF0[i] = n;
}

s32 func_800AF3A8(void) {
    Menu *m = &D_800E8230[12];
    s32 r = D_80038A90;
    s32 i, s, n, j;
    El *e;
    El *p;
    s32 x;

    for (i = 0; i < 4; i++) {
        s = -1;
        if (D_800E7BF0[i] >= 0) {
            n = D_800E7BF0[i];
            e = &m->el[n * 3 + 5];
            if ((D_800EA0C8[i] & 0x100) && e->f22 < 8) {
                e->f22++;
                s = 0x404;
            } else if ((D_800EA0C8[i] & 0x200) && e->f22 >= 2) {
                e->f22--;
                s = 0x404;
            } else if (D_8006E178[i].pressed & 0x8000) {
                m->el[D_800E7BF0[i] * 3 + 4].flags |= 1;
                m->el[D_800E7BF0[i] * 3 + 5].flags |= 1;
                n = findSlot(i, D_800E7BF0[i], 1);
                if (n == findSlot(i, -1, 1)) {
                    D_800E7BF0[i] = -1;
                } else {
                    m->el[n * 3 + 4].flags &= ~1;
                    m->el[n * 3 + 4].f16 = 0xFF;
                    D_800E7BF0[i] = n;
                }
                s = 0x42A;
            } else if (D_8006E178[i].pressed & 0x4000) {
                n = findSlot(i, D_800E7BF0[i], -1);
                if (m->el[n * 3 + 5].flags & 1) {
                    take(m, i, n);
                } else {
                    r = 0x200;
                }
                s = 0x403;
            }
        } else if (findSlot(i, -1, 1) >= 0 && (D_8006E178[i].pressed & 0x4000)) {
            n = findSlot(i, 4, -1);
            if (m->el[n * 3 + 5].flags & 1) {
                take(m, i, n);
            } else {
                r = 0x200;
            }
            s = 0x403;
        }
        if (s >= 0) {
            func_8000DEE4(s);
        }
    }
    if ((D_8006E178[0].pressed & 0x1000) ||
        (D_800E7BF0[0] < 0 && D_800E7BF0[1] < 0 && D_800E7BF0[2] < 0 && D_800E7BF0[3] < 0)) {
        p = &D_800E8230[12].el[5];
        D_800EA318 = 0x42A;
        for (j = 0; j < 4; j++, p += 3) {
            if (!(p[-2].flags & 1) && D_8007E228.type[j] >= 0) {
                p[-1].flags |= 0x20;
                p->flags |= 0x20;
                x = p->f22;
                D_8007E838[j] = x;
                D_8007EF30.pl[D_8007E228.type[j]].f6 = x;
            }
        }
        r = 0xB;
    }
    return r;
}
