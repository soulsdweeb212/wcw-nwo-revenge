/* @header
 * func_80091108
 * VRAM 0x80091108 | ROM 0x845A8 | size 0x640
 * asm: asm/nonmatchings/ovl2_80090000/func_80091108.s
 */
#include "common.h"

typedef struct {
    s32 flags;
} Node;

#ifdef TARGET_PC
/* PC: Spr is the game's 0xDC-byte scene object, common.h's Nw2SceneObj, which keeps its N64 layout on PC: the address
 * of its first work block at +0x14 is a 4-byte handle (port.h's PTR_TO_SLOT), and Node is the start of that work block
 * (its kind word, Nw2SceneWork's kind). Code reaches the work block through SLOT_TO_PTR. The asserts check the view
 * against both records. */
typedef struct {
    u8 pad0[0x14];
    u32 node;
    u8 pad18[0xDC - 0x18];
} Spr;
_Static_assert(sizeof(Spr) == sizeof(Nw2SceneObj) && offsetof(Spr, node) == offsetof(Nw2SceneObj, work) &&
                   offsetof(Node, flags) == offsetof(Nw2SceneWork, kind),
               "Spr must follow Nw2SceneObj, and Node Nw2SceneWork");
#else
typedef struct {
    u8 pad0[0x14];
    Node *node;
    u8 pad18[0xDC - 0x18];
} Spr;
#endif

#ifdef TARGET_PC
/* PC: SprTex is the game's display record of a picture, whose PC layout is common.h's Nw2Descr4BA8 (0x50 bytes, its
 * addresses as pointers). This file only passes pointers to records on. */
typedef Nw2Descr4BA8 SprTex;
#else
typedef struct {
    u8 pad0[0x2C];
} SprTex;
#endif

void func_800907A0(Spr *s, SprTex *t, s16 x, s16 y, f32 a, f32 b, f32 c, f32 d, u8 r, u8 g, u8 bl, u8 al);

extern u8 D_8007EF30[];
extern s16 D_800F9AA2;

s32 func_80091108(Spr *a, SprTex *at, Spr *b, SprTex *bt, f32 x, s16 t, s16 k) {
    f32 y;
    s32 r = 1;
    s32 cr = 0;
    s32 cg = 0xFF;
    s32 cb = 0xAF;
    s32 dur;
    f32 step;

    if (D_800F9AA2 != 0) {
        y = 52.0f;
    } else {
        y = 16.0f;
        x -= 160.0f;
    }
    if (D_8007EF30[0x1A1] == 1) {
        if (k >= 0x13) {
            cr = 0xFF;
            cg = 0;
            cb = 0;
        } else if (k >= 0x10) {
            cr = 0xFF;
            cg = 0xFF;
            cb = 0;
        }
        if (k < 0xF || k == 0x14) {
            dur = 0x1C;
        } else if (k < 0x12) {
            dur = 0x3A;
        } else {
            dur = 0x58;
        }
    } else {
        if (k >= 9) {
            cr = 0xFF;
            cg = 0;
            cb = 0;
        } else if (k >= 6) {
            cr = 0xFF;
            cg = 0xFF;
            cb = 0;
        }
        if (k < 5 || k == 0xA) {
            dur = 0x1C;
        } else if (k < 8) {
            dur = 0x3A;
        } else {
            dur = 0x58;
        }
    }
#ifdef TARGET_PC
    /* PC: the object's work block through its handle (see Spr above). */
    if (!(((Node *)SLOT_TO_PTR(a->node))->flags & 0x80)) {
#else
    if (!(a->node->flags & 0x80)) {
#endif
        r = 0;
        if (t < 6) {
            func_800907A0(a, at, x, y, 0.5f, 0.0f, 1.5f, 1.5f, 0xFF, 0xFF, 0xFF, 0xFF);
            func_800907A0(b, bt, x, y, 0.5f, 0.0f, 1.5f, 1.5f, 0xFF, 0xFF, 0xFF, 0xFF);
        } else if (t < 0x1E) {
            step = 10.0f;
            func_800907A0(a, at, x, y, 0.5f, 0.0f, 1.5f, 1.5f, 0xFF, 0xFF, 0xFF, 0xFF);
            func_800907A0(b, bt, x, y, 0.5f, 0.0f, 1.5f, 1.5f,
                          0xFF - (0xFF - cr) / 24 * (t - 6),
                          0xFF - (0xFF - cg) / 24 * (t - 6),
                          0xFF - (0xFF - cb) / 24 * (t - 6),
                          255.0f - (t - 6) * step);
        } else if (t < dur + 0x1E) {
            step = 0xFFU / dur;
            func_800907A0(a, at, x, y, 0.5f, 0.0f, 1.5f, 1.5f, 0xFF, 0xFF, 0xFF, 255.0f - (t - 0x1E) * step);
            func_800907A0(b, bt, x, y, 0.5f, 0.0f, 1.5f, 1.5f, cr, cg, cb, 0);
        } else {
            func_800907A0(a, at, x, y, 0.5f, 0.0f, 1.5f, 1.5f, 0xFF, 0xFF, 0xFF, 0);
            func_800907A0(b, bt, x, y, 0.5f, 0.0f, 1.5f, 1.5f, cr, cg, cb, 0);
#ifdef TARGET_PC
            /* PC: as above, the work block through its handle. */
            ((Node *)SLOT_TO_PTR(a->node))->flags |= 0x80;
            ((Node *)SLOT_TO_PTR(b->node))->flags |= 0x80;
#else
            a->node->flags |= 0x80;
            b->node->flags |= 0x80;
#endif
            r = 1;
        }
    }
    return r;
}
