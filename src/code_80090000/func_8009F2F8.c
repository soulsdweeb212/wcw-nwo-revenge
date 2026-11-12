/* @header
 * func_8009F2F8
 * VRAM 0x8009F2F8 | ROM 0x4BA68 | size 0x508
 * asm: asm/nonmatchings/code_80090000/func_8009F2F8.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: a command is port.h's 16-byte Gfx. */
typedef Gfx G;
#else
typedef struct { u32 w0, w1; } G;
#endif
typedef struct { u32 f0; s32 f4; s32 f8; } Q;
typedef struct { Q *list; u32 n; } P;
typedef struct { P *p; s16 t; u16 f6; s32 f8; } E;

#ifdef TARGET_PC
/* PC: D_800DC660 and D_800DC66C are labels of the scene object D_800DC650 (its display list at +0x10 and its matrices
 * from +0x1C), which have no PC symbol: the object keeps its N64 layout (Nw2SceneObj in common.h) and holds the list
 * as a handle (port.h's PTR_TO_SLOT). The display list at 0x800C9538 by its own address (port.h's DL_ADDR turns it
 * into the command word; D_C9538 is its N64 physical address, a link constant). */
extern Nw2SceneObj D_800DC650;
extern u8 D_800C9538[];
#else
extern G *D_800DC660;
extern u8 D_800DC66C[];
extern u8 D_C9538[];
#endif
extern E *D_800E7518;
extern s32 D_800E8208, D_800E7BEC, D_800D5F28, D_800DBD64;
extern u8 D_800E7BEF;
extern struct { u8 pad0[8]; u16 mode; } D_8007EF30;
extern u8 D_800C9530[], D_800C96C0[];
void func_800B830C(void *);
void func_80099748(G **, s32, s32, s32, s32);
void func_80098C40(G **, P *, s32, s32);
s32 func_800AA05C(s32);
s32 func_800AA0D8(s32);
u8 *func_800AA070(s32);
u8 *func_80028D18(u8 *, s32);
u8 *func_80028B5C(u8 *, u8 *);
void func_80095884(G **, s32, u8 *, u8 *);
void emitFullscreenOverlay99908(G **, s32);

static inline void fade(G **pg, s32 x) {
    G *g2 = *pg;
    if (x < -0xFF) {
        func_80099748(&g2, -x - 0x100, -x - 0x100, -x - 0x100, 0xFF);
    } else if (x < 0) {
        func_80099748(&g2, 0, 0, 0, -x);
    } else {
        func_80099748(&g2, 0xFF, 0xFF, 0xFF, x);
    }
    *pg = g2;
}

static inline u8 *teamName(u8 *name) {
    u8 *t;
    if (*name == 0) {
        return D_800C9530;
    }
    t = func_80028D18(name, 3);
    if (t == 0) {
        return D_800C9530;
    }
    if (*t == 0) {
        *func_80028B5C(func_80028B5C(t, D_800C96C0), name) = 0;
    }
    return t;
}

void func_8009F2F8(G **dl, s32 v) {
    G *g;
    E *e;
    s32 i;
    u32 j;
    P *p;
    Q *q;

    g = *dl;
#ifdef TARGET_PC
    /* PC: the object's fields by name, as above. */
    D_800DC650.dl = PTR_TO_SLOT(g);
    func_800B830C(D_800DC650.local);
#else
    D_800DC660 = g;
    func_800B830C(D_800DC66C);
#endif
    if (v >= 0x100) {
        v = 0xFF;
    }
#ifdef TARGET_PC
    /* PC: the branch target as the whole pointer (port.h's DL_ADDR). */
    { G *d = g++; d->w0 = 0xDE000000; d->w1 = DL_ADDR(D_800C9538); }
#else
    { G *d = g++; d->w0 = 0xDE000000; d->w1 = (u32)D_C9538; }
#endif
    if (v < -0xFF) {
        fade(&g, -0xFF);
    } else if (v < 0) {
        fade(&g, v);
    }
    e = D_800E7518;
    for (i = 0; i < 0x60; i++, e++) {
        if (e->p != 0) {
            if (e->t > 0) {
                if (e->f8 == 0 && (e->f6 & 8)) {
                    e->t = 0;
                }
                func_80098C40(&g, e->p, e->t, e->f6);
                if (e->f6 & 1) {
                    e->t = 0;
                } else if (e->f6 & 2) {
                    e->t -= 8;
                } else if (e->f6 & 4) {
                    e->t -= 0x10;
                } else {
                    e->t -= D_800E8208 * 16;
                }
                if (e->t < 0) {
                    e->t = 0;
                }
            } else {
                if (e->t < -4) {
                    p = e->p;
                    q = p->list;
                    for (j = 0; j < p->n; j++, q++) {
                        if (q->f0 & 0xF0000000) {
                            q->f8 = 0;
                            q->f0 = 0;
                        }
                    }
                    e->p = 0;
                    e->t = 0;
                }
                e->t--;
            }
            e->f8 = 0;
        }
    }
    if (D_800E7BEC & 0xFF) {
        i = D_800E7BEC >> 8;
#ifdef TARGET_PC
        /* PC: as above. */
        { G *d = g++; d->w0 = 0xDE000000; d->w1 = DL_ADDR(D_800C9538); }
#else
        { G *d = g++; d->w0 = 0xDE000000; d->w1 = (u32)D_C9538; }
#endif
        { G *d = g++; d->w0 = 0xE3000C00; d->w1 = 0x80000; }
        if ((D_8007EF30.mode & 0x10) && func_800AA05C(i + 2) >= 0) {
            func_80095884(&g, D_800E7BEF | 0x100, func_800AA070(i), teamName(func_800AA070(i + 2)));
        } else if ((D_8007EF30.mode & 0x60) && func_800AA0D8(i + 1) >= 0) {
            func_80095884(&g, D_800E7BEF, func_800AA070(i), func_800AA070(i + 1));
        } else {
            func_80095884(&g, D_800E7BEF, func_800AA070(i), 0);
        }
    }
    if (v > 0) {
        fade(&g, v);
    } else if (v < -0xFF) {
        fade(&g, -0x100 - v);
    }
    if (D_800D5F28 != 0) {
        emitFullscreenOverlay99908(&g, 0);
    }
    { G *d = g++; d->w0 = 0xDF000000; d->w1 = 0; }
    *dl = g;
    D_800DBD64 = 0;
}
