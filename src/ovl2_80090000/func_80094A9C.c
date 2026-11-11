/* @header
 * func_80094A9C
 * VRAM 0x80094A9C | ROM 0x87F3C | size 0x1154
 * asm: asm/nonmatchings/ovl2_80090000/func_80094A9C.s
 */
#include "common.h"

typedef struct {
    s32 flags;
} Node;

#ifdef TARGET_PC
/* PC: a scene object (common.h's Nw2SceneObj), which keeps its N64 layout on PC: node, its work block, is a 4-byte
 * handle (port.h's PTR_TO_SLOT). NODE(o) gives o's work block, whose kind word is Node's flags. */
typedef struct {
    u8 pad0[0x14];
    u32 node;
    u8 pad18[0xC4];
} ObjDC;
_Static_assert(offsetof(ObjDC, node) == offsetof(Nw2SceneObj, work) && sizeof(ObjDC) == sizeof(Nw2SceneObj),
               "ObjDC must follow Nw2SceneObj");
_Static_assert(offsetof(Node, flags) == offsetof(Nw2SceneWork, kind), "Node must follow Nw2SceneWork");
#define NODE(o) ((Node *)SLOT_TO_PTR((o).node))

/* PC: the display record and the picture pairs are common.h's PC layouts, the types port_decls.h declares the arrays
 * with. The record's picture is its f18 (texture) and f1C (palette); a pair's are img and pal, both void *, which the
 * palette copy below assigns to its u32 pointers. */
typedef Nw2Descr4BA8 Rec2C;
typedef Nw2TexPair Tex8;
typedef Nw2TexPair Pal8;
#else
typedef struct {
    u8 pad0[0x14];
    Node *node;
    u8 pad18[0xC4];
} ObjDC;

typedef struct {
    u8 pad0[0x18];
    void *img;
    void *pal;
    u8 pad20[0xC];
} Rec2C;

typedef struct {
    void *img;
    void *pal;
} Tex8;

typedef struct {
    u32 *img;
    u32 *pal;
} Pal8;
#endif

typedef struct {
    u8 id;
    u8 b1;
    u8 b2;
    u8 b3;
    s16 hp;
    s16 f6;
    s16 x;
    s16 y;
} Rec0C;

extern u8 D_80075468[];
extern s32 D_8007E8C0[];
extern s16 D_800E2BF8[];
extern s16 D_800E2C00[];
extern s16 D_800E2C0C[];
extern s16 D_800E2C5C[];
extern s16 D_800E2C64[];
extern u8 D_800E2C6C[];
extern s32 D_800E77B4;
extern ObjDC D_800E9878[];
#ifndef TARGET_PC /* on PC no symbol: D_800E9BE0 is the pair before D_800E9BE8, D_800E9C30 is its pair 9 */
extern Tex8 D_800E9BE0[];
extern Tex8 D_800E9C30[];
#endif
extern Rec2C D_800E9C88[];
extern s8 D_800E9D38[];
extern Rec0C D_800E9D40[];
extern ObjDC D_800E9D70[];
extern Pal8 D_800EA0E0[];
extern Pal8 D_800EA110[];
extern u8 D_800EA260[];
extern ObjDC D_800EA268[];
extern Rec2C D_800EA5E8[];
extern Rec2C D_800EA698[];
extern ObjDC D_800EA758[];
extern Rec2C D_800EAAC8[];
extern ObjDC D_800EAC88[];
extern Rec2C D_800EAFF8[];
extern u16 D_800EB0A8;
extern u16 D_800EB0AA;

void func_80004F80(void *, s16, s16);
void func_800907A0(void *, Rec2C *, s16, s16, f32, f32, f32, f32, u8, u8, u8, u8);
s16 func_800AD730(s16);
u16 func_800B8278(void);
s8 func_800BFC90(s8);
s8 isEntityEligibleForSpecialAction(s8);
f32 nw2Sqrtf(f32);
s8 readEntityStunState(s8, s16 *, s16 *);

static inline void func_8009075C(Rec2C *r, Tex8 *t) {
#ifdef TARGET_PC
    /* PC: the pair's texture and palette go into the record's f18 and f1C, by name, then are cleared. */
    r->f18 = t->img;
    r->f1C = t->pal;
    func_80004F80(r, 0, 0);
    r->f18 = NULL;
    r->f1C = NULL;
#else
    r->img = t->img;
    r->pal = t->pal;
    func_80004F80(r, 0, 0);
    r->img = NULL;
    r->pal = NULL;
#endif
}

void func_80094A9C(void) {
    u32 i;
    u32 j;
    s16 bits;
    u8 pal;
    u32 *src;
    u32 *dst;
    s16 old;
    u8 r;
    u8 g;
    u8 b;
    f32 t;
    f32 w;
    s16 speed;
    s16 off;
    s8 n;

    if (D_800EB0AA >= 3) {
        bits = func_800B8278() & 0xF;
        if (bits != D_800EB0A8) {
            D_800EB0A8 = bits;
        }
        for (i = 0; i < D_800EB0AA; i++) {
            if (D_8007E280 & 0x400) {
                pal = ((bits >> i) & 1) | (D_8007E8C0[i] * 2);
            } else {
                pal = ((D_800E9D40[i].id & 2) | ((bits >> i) & 1)) + 2;
            }
            if (D_800E9D40[i].b2 < 2 && (func_800BFC90(i) || D_800E9D40[i].hp == 100)) {
                pal += 10;
            }
            if (pal != D_800EA260[i]) {
                src = D_800EA110[pal].pal;
                dst = D_800EA0E0[i].pal;
                for (j = 0; j < 8; j++) {
                    *dst++ = *src++;
                }
                D_800EA260[i] = pal;
            }
        }
    } else {
        for (i = 0; i < D_800EB0AA; i++) {
            pal = (D_800E9D40[i].id & 2) + 3;
            if (D_800E9D40[i].b2 < 2 && (func_800BFC90(i) || D_800E9D40[i].hp == 100)) {
                pal += 10;
            }
            if (pal != D_800EA260[i]) {
                src = D_800EA110[pal].pal;
                dst = D_800EA0E0[i].pal;
                for (j = 0; j < 8; j++) {
                    *dst++ = *src++;
                }
                D_800EA260[i] = pal;
            }
        }
    }

    for (i = 0; i < D_800EB0AA; i++) {
        old = D_800E9D40[i].hp;
        if (readEntityStunState(i, &D_800E9D40[i].hp, &D_800E9D40[i].f6)) {
            if (D_800E9D40[i].hp != old) {
                if (old < D_800E9D40[i].hp) {
                    D_800E9D40[i].id |= 0x40;
                } else {
                    D_800E9D40[i].id |= 0x80;
                }
                D_800E9D40[i].b3 = 6;
            }
        }
        D_80075468[i] = D_800E9D40[i].hp;
        if (D_800E9D40[i].hp < 40) {
            r = 0;
            g = nw2Sqrtf((f32)D_800E9D40[i].hp * 0.025) * 255.0f;
            b = nw2Sqrtf((f32)(40 - D_800E9D40[i].hp) * 0.025) * 255.0f;
        } else {
            r = nw2Sqrtf((f32)(D_800E9D40[i].hp - 40) * 0.016666666666666666) * 255.0f;
            g = nw2Sqrtf((f32)(100 - D_800E9D40[i].hp) * 0.016666666666666666) * 255.0f;
            b = 0;
        }
        if (D_800E9D40[i].id & 0xC0) {
            t = (f32)D_800E9D40[i].b3 * 0.16666666666666666;
            if (D_800E9D40[i].id & 0x40) {
                r = r * (1.0 - t) + t * 255.0f;
                g = g * (1.0 - t) + t * 223.0f;
                b = b * (1.0 - t) + t * 191.0f;
            } else {
                r = r * (1.0 - t) + t * 64.0f;
                g = g * (1.0 - t) + t * 64.0f;
                b = b * (1.0 - t) + t * 127.0f;
            }
            D_800E9D40[i].b3--;
            if (D_800E9D40[i].b3 == 0) {
                D_800E9D40[i].id &= 0x3F;
            }
        }
        if (D_800EB0AA >= 3 && !((D_800EB0A8 >> i) & 1)) {
            r = r * 0.5;
            g = g * 0.5;
            b = b * 0.5;
        }
        if (D_800E9D40[i].hp < 100) {
            speed = (100 - D_800E9D40[i].hp) * 0.5 + 3.0;
        } else {
            speed = 5;
        }
        if (D_800E9D40[i].b2 <= speed * 0.15) {
            off = (D_800E9D40[i].b2 * 10) / (speed * 0.15);
        } else {
            off = ((speed - D_800E9D40[i].b2) * 10) / (speed * 0.85);
        }
        if (!(D_800E9D40[i].id & 0xC0)) {
            D_800E9D40[i].b2++;
            if (D_800E9D40[i].b2 > speed) {
                D_800E9D40[i].b2 = 0;
            }
        }
        if (D_800E9D40[i].hp == 100 || D_800E9D40[i].hp == 0) {
#ifdef TARGET_PC
            /* PC: the work block through its handle (NODE). */
            NODE(D_800EA268[i])->flags &= ~0x80;
#else
            D_800EA268[i].node->flags &= ~0x80;
#endif
            if (D_800E9D40[i].hp == 100) {
                func_800907A0(&D_800EA268[i], &D_800EA5E8[i], D_800E2C5C[D_800E9D40[i].id & 3], D_800E2C64[D_800E9D40[i].id & 3] + 2,
                              0.47f, 0.5f, off * 0.03 + 1.2, off * 0.015 + 0.6, 0xFF, 0xFF, 0xFF, 0xFF);
                off = 10;
                if (D_800E9D40[i].f6 < 150) {
                    if (D_800E9D40[i].b1 == 0) {
#ifdef TARGET_PC
                        /* PC: as above. */
                        NODE(D_800EA268[i])->flags |= 0x80;
#else
                        D_800EA268[i].node->flags |= 0x80;
#endif
                    }
                    D_800E9D40[i].b1++;
                    if (D_800E9D40[i].b1 > D_800E2C6C[(s16)(D_800E9D40[i].f6 / 60)]) {
                        D_800E9D40[i].b1 = 0;
                    }
                }
            } else {
                func_800907A0(&D_800EA268[i], &D_800EA698[i], D_800E2C5C[D_800E9D40[i].id & 3], D_800E2C64[D_800E9D40[i].id & 3] - 5,
                              0.47f, 0.0f, 1.1 - off * 0.02, off * 0.02 + 0.7, 0xFF, 0xFF, 0xFF, 0xFF);
                off = 0;
            }
        } else {
#ifdef TARGET_PC
            /* PC: as above. */
            NODE(D_800EA268[i])->flags |= 0x80;
#else
            D_800EA268[i].node->flags |= 0x80;
#endif
        }
        w = D_800E9D40[i].hp * 0.5f + off;
        func_800907A0(&D_800EAC88[i], &D_800EAFF8[i], D_800E2C5C[D_800E9D40[i].id & 3], D_800E2C64[D_800E9D40[i].id & 3],
                      0.5f, 0.0f, w, 4.0f, r, g, b, 0xFF);
#ifdef TARGET_PC
        /* PC: as above. */
        if (NODE(D_800E9D70[i])->flags & 0x80) {
            NODE(D_800E9D70[i])->flags &= ~0x80;
            NODE(D_800EAC88[i])->flags &= ~0x80;
#else
        if (D_800E9D70[i].node->flags & 0x80) {
            D_800E9D70[i].node->flags &= ~0x80;
            D_800EAC88[i].node->flags &= ~0x80;
#endif
            func_800907A0(&D_800EA758[i], &D_800EAAC8[i], D_800E2C0C[D_800E9D40[i].id & 3], D_800E9D40[i].y,
                          0.0f, 0.0f, 2.0f, 1.0f, 0xFF, 0xFF, 0xFF, 0xFF);
        }
#ifdef TARGET_PC
        /* PC: as above. */
        if (!(D_800E77B4 & 8) && isEntityEligibleForSpecialAction(i)) {
            NODE(D_800EA758[i])->flags &= ~0x80;
        } else {
            NODE(D_800EA758[i])->flags |= 0x80;
        }
#else
        if (!(D_800E77B4 & 8) && isEntityEligibleForSpecialAction(i)) {
            D_800EA758[i].node->flags &= ~0x80;
        } else {
            D_800EA758[i].node->flags |= 0x80;
        }
#endif
        if (func_800AD730(i) != D_800E9D38[i]) {
            n = D_800E9D38[i] = func_800AD730(i);
            if (n > 0) {
#ifdef TARGET_PC
                /* PC: the N64 labels D_800E9BE0 (one pair before D_800E9BE8) and D_800E9C30 (D_800E9BE8's pair 9),
                 * indexed from 1, become D_800E9BE8's own pairs n - 1 and n + 9. The work block through its handle,
                 * as above. */
                if ((D_800E9D40[i].id & 3) < 2) {
                    func_8009075C(&D_800E9C88[i], &D_800E9BE8[n - 1]);
                } else {
                    func_8009075C(&D_800E9C88[i], &D_800E9BE8[n + 9]);
                }
                if (NODE(D_800E9878[i])->flags & 0x80) {
#else
                if ((D_800E9D40[i].id & 3) < 2) {
                    func_8009075C(&D_800E9C88[i], &D_800E9BE0[n]);
                } else {
                    func_8009075C(&D_800E9C88[i], &D_800E9C30[n]);
                }
                if (D_800E9878[i].node->flags & 0x80) {
#endif
                    func_800907A0(&D_800E9878[i], &D_800E9C88[i], D_800E2BF8[D_800E9D40[i].id & 3], D_800E2C00[D_800E9D40[i].id & 3],
                                  0.0f, 0.0f, 1.0f, 1.0f, 0xFF, 0xFF, 0xFF, 0xFF);
#ifdef TARGET_PC
                    /* PC: as above. */
                    NODE(D_800E9878[i])->flags &= ~0x80;
#else
                    D_800E9878[i].node->flags &= ~0x80;
#endif
                }
            } else {
#ifdef TARGET_PC
                /* PC: as above. */
                NODE(D_800E9878[i])->flags |= 0x80;
#else
                D_800E9878[i].node->flags |= 0x80;
#endif
            }
        }
    }
    D_800E77B4++;
}
