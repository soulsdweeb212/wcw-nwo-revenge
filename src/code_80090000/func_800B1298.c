/* @header
 * func_800B1298
 * VRAM 0x800B1298 | ROM 0x5DA08 | size 0x1EC
 * asm: asm/nonmatchings/code_80090000/func_800B1298.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: W is a menu element and D_800E8244 the N64's label of D_800E8230[0].el (T steps through the menus by 0x138):
 * the menus and their elements hold addresses, so they are common.h's Nw2Menu and Nw2MenuEl, which W follows (the
 * assert checks), and the label has no PC symbol: the menus are read by name. */
typedef struct {
    u8 p0[0xA];
    u16 f;
    u8 p1[0x8];
    u16 d;
    u8 p2[0xA];
    u16 c;
    s16 id;
    u8 p3[sizeof(Nw2MenuEl) - 0x24];
} W;
_Static_assert(offsetof(W, f) == offsetof(Nw2MenuEl, fA) && offsetof(W, d) == offsetof(Nw2MenuEl, f14) &&
                   offsetof(W, c) == offsetof(Nw2MenuEl, f20) && offsetof(W, id) == offsetof(Nw2MenuEl, f22) &&
                   sizeof(W) == sizeof(Nw2MenuEl),
               "W must follow common.h's Nw2MenuEl");
typedef struct { s16 a; u8 b; u8 c; u8 p[0xC]; } S;
extern u8 D_8007EF30[], D_8007EF38[];
extern Nw2Menu D_800E8230[];
#else
typedef struct { u8 p0[0xA]; u16 f; u8 p1[0x8]; u16 d; u8 p2[0xA]; u16 c; s16 id; u8 p3[0x124]; } W;
typedef struct { s16 a; u8 b; u8 c; u8 p[0xC]; } S;
typedef struct { W *w; u8 p[0x134]; } T;
extern u8 D_8007EF30[], D_8007EF38[];
extern T D_800E8244[];
#endif
#ifdef TARGET_PC
/* PC: the type of func_8002B668's definition, which returns a u16: read as an s32, the PC result's upper bits would
 * be unset. */
u16 func_8002B668(u32, s32);
#else
s32 func_8002B668(s32, s32);
#endif
s32 func_8002B710(s32);
s32 func_800A9B90(s32);

#define F(t, o, i) (*(t *)(D_8007EF30 + (o) + ((i) << 4)))

static inline s32 ok(s32 x) {
    if (x) {
        return -((D_8007EF30[0x14C] >> (x - 1)) & 1);
    }
    return -1;
}

void func_800B1298(s32 n) {
#ifdef TARGET_PC
    W *t = (W *)D_800E8230[n].el; /* PC: by name (see above) */
#else
    W *t = D_800E8244[n].w;
#endif
    W *w = t + 1;
    W *e = t + 1;
    u8 *g;
    s32 i = 0;
    s32 c = 0;
    s32 id, q, k, v;
    s32 pad[2];

#ifdef TARGET_PC
    /* PC: D_8007EF30 keeps its N64 layout, so its +0x2C holds the name table's handle (port.h's PTR_TO_SLOT), and
     * the table (common.h's Nw2IdSubTable, 16 bytes on PC) has its count at +8, not +4. */
    if (((Nw2IdSubTable *)SLOT_TO_PTR(*(u32 *)(D_8007EF30 + 0x2C)))->count != 0) {
#else
    if (*(u16 *)(*(u8 **)(D_8007EF30 + 0x2C) + 4) != 0) {
#endif
        g = D_8007EF38;
        do {
            id = func_8002B668(*(s16 *)(D_8007EF30 + 0x10), i);
            e->c = ((i & 0xF) << 4) | 0x5000;
            if (ok(func_8002B710(id))) {
                if ((*(u16 *)g & 0xF) == 8) {
                    q = *(s16 *)(g + 0xA);
                } else {
                    q = func_800A9B90(id);
                }
                if (q < 0) {
                    e->f |= 0x40;
                    for (k = 3; k >= 0; k--) {
                        if (F(s16, 0x4E, k) == id) {
                            v = F(u8, 0x50, k);
                            goto found;
                        }
                    }
                    v = 0;
found:
                    e->c |= v;
                } else {
                    e->f &= ~0x40;
                    e->c |= q;
                }
                w++;
                c++;
                e->id = id;
                e->d = 0xFF;
                e->f &= ~1;
                e++;
            }
            i++;
            if (c >= 9) {
                return;
            }
#ifdef TARGET_PC
        } while (i < ((Nw2IdSubTable *)SLOT_TO_PTR(*(u32 *)(D_8007EF30 + 0x2C)))->count);
#else
        } while (i < *(u16 *)(*(u8 **)(D_8007EF30 + 0x2C) + 4));
#endif
    }
    for (; c < 9; c++) {
        w->f |= 1;
        w++;
    }
}
