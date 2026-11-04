/* @header
 * func_800AF218
 * VRAM 0x800AF218 | ROM 0x5B988 | size 0x190
 * asm: asm/nonmatchings/code_80090000/func_800AF218.s
 */
#include "common.h"

typedef struct { f32 f0; f32 f4; u8 pad8[2]; u16 flags; u8 padC[0x16]; s16 f22; u8 pad24[0x148 - 0x24]; } El;
typedef struct { void *items; s16 cur; u8 pad6[0xE]; El *el; u8 pad18[0x138 - 0x18]; } Menu;

extern Menu D_800E8230[];
extern s32 D_8007E838[];
extern s32 D_8007E8C0[];
extern s32 D_800E7BF0[];

/* Steps from slot `cur` in direction `d` (wrapping 0..3) to the slot player i owns in D_8007E8C0; player 1 may
 * also take a free slot (0). Same inline as in func_800AF3A8. */
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

void func_800AF218(void) {
    Menu *m = &D_800E8230[12];
    s32 n, i;
    El *p;
    f32 f, g;

    m->el[2].flags &= ~1;
    /* p walks the players' element triples; no access is at p+0, so gcc folds every field into one register */
    p = &m->el[3];
    for (i = 0; i < 4; i++, p += 3) {
        if (!(p->flags & 1)) {
            f = p[2].f0;
            p[1].flags &= ~0x20;
            p[1].f22 = 1;
            p[1].flags |= 1;
            if (f < 0.0f) {
                g = f + 49.0f;
            } else {
                g = f + -49.0f;
            }
            p[1].f0 = g;
            p[1].f4 = p[2].f4;
            p[2].flags &= 0xFFDE;
            p[2].f22 = D_8007E838[i];
        }
    }
    for (i = 0; i < 4; i++) {
        n = findSlot(i, -1, 1);
        D_800E7BF0[i] = n;
        if (n >= 0) {
            m->el[n * 3 + 4].flags &= ~1;
        }
    }
    D_800E8230[12].cur = 5; /* through the symbol: m->cur would use m's register */
}
