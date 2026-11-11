/* @header
 * func_80091748
 * VRAM 0x80091748 | ROM 0x84BE8 | size 0x56C
 * asm: asm/nonmatchings/ovl2_80090000/func_80091748.s
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

s32 func_80091748(Spr *a, SprTex *at, Spr *b, SprTex *bt, s16 t) {
    s32 r = 1;

#ifdef TARGET_PC
    /* PC: the object's work block through its handle (see Spr above). */
    if (!(((Node *)SLOT_TO_PTR(a->node))->flags & 0x80)) {
#else
    if (!(a->node->flags & 0x80)) {
#endif
        r = 0;
        if (t < 6) {
            func_800907A0(a, at, 0xF0, 0xC2, 0.5f, 0.5f, 1.2f, 1.2f, 0xFF, 0xFF, 0xFF, t * 32 + 0x5F);
            func_800907A0(b, bt, 0xF0, 0xC2, 0.5f, 0.5f, 1.2f, 1.2f, 0xFF, 0xFF, 0xFF, t * 32 + 0x5F);
        } else if (t < 9) {
            func_800907A0(a, at, 0xF0, 0xC2, 0.5f, 0.5f, 1.2f, 1.2f, 0xFF, 0xFF, 0xFF, 0xFF);
            func_800907A0(b, bt, 0xF0, 0xC2, 0.5f, 0.5f, 1.2f, 1.2f, 0xFF, 0xFF, 0xFF, 0xFF);
        } else if (t < 0x12) {
            func_800907A0(a, at, 0xF0, 0xC2, 0.5f, 0.5f, 1.2f, 1.2f, 0xFF, 0xFF, 0xFF, 0xFF);
            func_800907A0(b, bt, 0xF0, 0xC2, 0.5f, 0.5f, 1.2f, 1.2f, 0xFF, 0xFF - (t - 9) * 30, 0xFF - (t - 9) * 30, 0xFF);
        } else if (t < 0x4E) {
            func_800907A0(a, at, 0xF0, 0xC2, 0.5f, 0.5f, 1.2f, 1.2f, 0xFF, 0xFF, 0xFF, 0xFF);
            func_800907A0(b, bt, 0xF0, 0xC2, 0.5f, 0.5f, 1.2f, 1.2f, 0xFF, 0, 0, 0xFF);
        } else if (t < 0x51) {
            func_800907A0(a, at, 0xF0, 0xC2, 0.5f, 0.5f, 1.2f, 1.2f, 0xFF, 0xFF, 0xFF, 0xFF);
            func_800907A0(b, bt, 0xF0, 0xC2, 0.5f, 0.5f, 1.2f, 1.2f, 0xFF, 0xFF, 0xFF, 0xFF);
        } else if (t < 0x5A) {
            func_800907A0(a, at, 0xF0, 0xC2, 0.5f, 0.5f, 1.2f, 1.2f, 0xFF, 0xFF, 0xFF, 0xFF);
            func_800907A0(b, bt, 0xF0, 0xC2, 0.5f, 0.5f, 1.2f, 1.2f, 0xFF, 0xFF - (t - 0x51) * 30, 0xFF - (t - 0x51) * 30, 0xFF);
        } else if (t < 0x78) {
            func_800907A0(a, at, 0xF0, 0xC2, 0.5f, 0.5f, 1.2f, 1.2f, 0xFF, 0xFF, 0xFF, 0xFF);
            func_800907A0(b, bt, 0xF0, 0xC2, 0.5f, 0.5f, 1.2f, 1.2f, 0xFF, 0, 0, 0xFF);
        } else if (t < 0x7B) {
            func_800907A0(a, at, 0xF0, 0xC2, 0.5f, 0.5f, 1.2f, 1.2f, 0xFF, 0xFF, 0xFF, 0xFF - (t - 0x78) * 90);
            func_800907A0(b, bt, 0xF0, 0xC2, 0.5f, 0.5f, 1.2f, 1.2f, 0xFF, 0, 0, 0xFF - (t - 0x78) * 90);
        } else {
            func_800907A0(a, at, 0xF0, 0xC2, 0.5f, 0.5f, 1.2f, 1.2f, 0xFF, 0xFF, 0xFF, 0);
            func_800907A0(b, bt, 0xF0, 0xC2, 0.5f, 0.5f, 1.2f, 1.2f, 0xFF, 0, 0, 0);
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
