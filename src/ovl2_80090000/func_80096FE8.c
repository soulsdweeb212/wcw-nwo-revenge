/* @header
 * func_80096FE8
 * VRAM 0x80096FE8 | ROM 0x8A488 | size 0x884
 * asm: asm/nonmatchings/ovl2_80090000/func_80096FE8.s
 */
#include "common.h"

typedef struct { s32 flags; } St;

#ifdef TARGET_PC
/* PC: a scene object (common.h's Nw2SceneObj), which keeps its N64 layout on PC: dl (its display list) and st (its
 * work block) are 4-byte handles (port.h's PTR_TO_SLOT). ST(o) gives o's work block, whose kind word is St's flags. */
typedef struct {
    u8 pad0[0x10];
    u32 dl;
    u32 st;
    u8 pad18[0xC4];
} Sprite;
_Static_assert(offsetof(Sprite, dl) == offsetof(Nw2SceneObj, dl) &&
                   offsetof(Sprite, st) == offsetof(Nw2SceneObj, work) && sizeof(Sprite) == sizeof(Nw2SceneObj),
               "Sprite must follow Nw2SceneObj");
_Static_assert(offsetof(St, flags) == offsetof(Nw2SceneWork, kind), "St must follow Nw2SceneWork");
#define ST(o) ((St *)SLOT_TO_PTR((o).st))

/* PC: the display record and the picture pair are common.h's PC layouts, the types port_decls.h declares the arrays
 * with. */
typedef Nw2Descr4BA8 Frame;
typedef Nw2TexPair Tex;
#else
typedef struct {
    u8 pad0[0x10];
    void *dl;
    St *st;
    u8 pad18[0xC4];
} Sprite;

typedef struct {
    u8 b[0x2C];
} Frame;

typedef struct {
    void *meta;
    u32 addr;
} Tex;
#endif

void func_80006814(Sprite *, Tex *, f32, f32);
void func_800907A0(void *a, void *b, s16 x, s16 y, f32 f0, f32 f1, f32 sx, f32 sy, u8 r, u8 g, u8 bl, u8 al);
void func_80097BB4(void);
s8 func_800D633C(void);
extern s16 *D_800E2CF4[];
extern u8 *D_800E2D58[];
extern Sprite D_800E77C0;
extern void *D_800E789C[];
extern Tex D_800E78A8[];
extern s16 D_800E7940;
extern u16 D_800E7942;
extern Sprite D_800E8B28;
extern Sprite D_800E8C08;
extern Frame D_800E8CE8[];
extern Frame D_800E8D40[];
extern s16 D_800E8D98;
extern s16 D_800E8D9A;
extern s8 D_800F99B4;
extern s8 D_800F99B5;
extern s16 D_800F99B8;
extern s8 D_800F9A9E;
extern s16 D_800F9AA0;
extern s8 D_800F9AF8;

/* body of func_80096F64, inlined here */
static inline void setNote(void) {
    s32 v;

    v = (s8)(D_800E2CF4[D_800F99B4][D_800F9A9E] + 0x5C) / 2;
    D_800F9AF8 = v;
    D_800F99B5 = D_800E2D58[D_800F99B4][D_800F9A9E];
    if (v >= 5) {
        D_800F9AA0 = 0x6F;
    } else {
        D_800F9AA0 = 0x50;
    }
}

void func_80096FE8(void) {
    s32 d;

    if (!(D_800E7942 & 0x80) || D_800F99B8 > 0) {
        if (D_800F99B5 > 0) {
            D_800F99B5--;
            if (D_800F99B5 == 0) {
                D_800F9A9E++;
                if (D_800E2CF4[D_800F99B4][D_800F9A9E] == -1) {
                    D_800F9A9E = 0;
                }
                if (D_800E2CF4[D_800F99B4][D_800F9A9E] != 0) {
                    setNote();
                } else {
                    func_80097BB4();
                }
            }
        }
#ifdef TARGET_PC
        /* PC: the work block through its handle (ST). */
        if (func_800D633C()) {
            ST(D_800E77C0)->flags |= 0x80;
        } else {
            ST(D_800E77C0)->flags &= ~0x80;
        }
#else
        if (func_800D633C()) {
            D_800E77C0.st->flags |= 0x80;
        } else {
            D_800E77C0.st->flags &= ~0x80;
        }
#endif
        if (D_800F99B4 != 0) {
            d = 0x80 - D_800F99B8;
            if (d >= 2) {
                D_800F99B8 += d / 2;
            } else {
                D_800F99B8 = 0x80;
            }
        } else if (D_800F99B8 >= 20) {
            D_800F99B8 -= 20;
        } else {
            D_800F99B8 = 0;
            D_800E7942 = 0x80;
#ifdef TARGET_PC
            /* PC: as above. */
            ST(D_800E77C0)->flags |= 0x80;
#else
            D_800E77C0.st->flags |= 0x80;
#endif
        }
#ifdef TARGET_PC
        /* PC: the object keeps the next of the three lists (func_800922C0 allocates them) as a handle, which
         * func_80006814 turns back into the list it writes. */
        D_800E77C0.dl = PTR_TO_SLOT(D_800E789C[D_800E7940++]);
#else
        D_800E77C0.dl = D_800E789C[D_800E7940++];
#endif
        D_800E7940 %= 3;
        func_80006814(&D_800E77C0, &D_800E78A8[D_800F9AF8], 0x1E0 - D_800F99B8, D_800F9AA0);
    }
    if (D_800E8D9A >= 0) {
#ifdef TARGET_PC
        /* PC: the work blocks through their handles, as above. */
        ST(D_800E8B28)->flags &= ~0x80;
        ST(D_800E8C08)->flags &= ~0x80;
#else
        D_800E8B28.st->flags &= ~0x80;
        D_800E8C08.st->flags &= ~0x80;
#endif
        if (D_800E8D9A < 12) {
            func_800907A0(&D_800E8B28, &D_800E8CE8[D_800E8D98], 0x21C - D_800E8D9A * 25, 0x82, 0.5f, -0.2f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0xFF);
            func_800907A0(&D_800E8C08, &D_800E8D40[D_800E8D98], 0x21C - D_800E8D9A * 25, 0x82, 0.5f, -0.2f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0xFF);
        } else if (D_800E8D9A < 15) {
            func_800907A0(&D_800E8B28, &D_800E8CE8[D_800E8D98], 0xF0, 0x82, 0.5f, -0.2f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0xFF);
            func_800907A0(&D_800E8C08, &D_800E8D40[D_800E8D98], 0xF0, 0x82, 0.5f, -0.2f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0xFF);
        } else if (D_800E8D9A < 24) {
            func_800907A0(&D_800E8B28, &D_800E8CE8[D_800E8D98], 0xF0, 0x82, 0.5f, -0.2f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0xFF);
            func_800907A0(&D_800E8C08, &D_800E8D40[D_800E8D98], 0xF0, 0x82, 0.5f, -0.2f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0xFF - (D_800E8D9A - 15) * 30);
        } else if (D_800E8D9A < 42) {
            func_800907A0(&D_800E8B28, &D_800E8CE8[D_800E8D98], 0xF0, 0x82, 0.5f, -0.2f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0xFF);
            func_800907A0(&D_800E8C08, &D_800E8D40[D_800E8D98], 0xF0, 0x82, 0.5f, -0.2f, 2.0f, 1.5f, 0, 0x57, 0xFF, 0);
        } else if (D_800E8D9A < 63) {
            func_800907A0(&D_800E8B28, &D_800E8CE8[D_800E8D98], 0xF0, 0x82, 0.5f, -0.2f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0xFF - (D_800E8D9A - 42) * 12);
            func_800907A0(&D_800E8C08, &D_800E8D40[D_800E8D98], 0xF0, 0x82, 0.5f, -0.2f, 2.0f, 1.5f, 0, 0x57, 0xFF, 0);
        } else {
#ifdef TARGET_PC
            /* PC: as above. */
            ST(D_800E8B28)->flags |= 0x80;
            ST(D_800E8C08)->flags |= 0x80;
#else
            D_800E8B28.st->flags |= 0x80;
            D_800E8C08.st->flags |= 0x80;
#endif
        }
#ifdef TARGET_PC
        /* PC: as above. */
        if (func_800D633C()) {
            ST(D_800E8B28)->flags |= 0x80;
            ST(D_800E8C08)->flags |= 0x80;
        } else {
            D_800E8D9A = (ST(D_800E8B28)->flags & 0x80) ? -1 : D_800E8D9A + 1;
        }
#else
        if (func_800D633C()) {
            D_800E8B28.st->flags |= 0x80;
            D_800E8C08.st->flags |= 0x80;
        } else {
            D_800E8D9A = (D_800E8B28.st->flags & 0x80) ? -1 : D_800E8D9A + 1;
        }
#endif
    }
}
