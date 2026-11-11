/* @header
 * func_80091CB4
 * VRAM 0x80091CB4 | ROM 0x85154 | size 0x140
 * asm: asm/nonmatchings/ovl2_80090000/func_80091CB4.s
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
 * addresses as pointers). port_decls.h declares D_800E97C0 and D_800E9818 with that type, and &X[i] steps by whole
 * records. */
typedef Nw2Descr4BA8 SprTex;
#else
typedef struct {
    u8 pad0[0x2C];
} SprTex;
#endif

void func_800907A0(Spr *s, SprTex *t, s16 x, s16 y, f32 a, f32 b, f32 c, f32 d, u8 r, u8 g, u8 bl, u8 al);

extern Spr D_800E9450[2];
extern Spr D_800E9608[2];
extern SprTex D_800E97C0[2];
extern SprTex D_800E9818[2];
extern s16 D_800E9870;

void func_80091CB4(void) {
    u32 i;

    for (i = 0; i < 2; i++) {
#ifdef TARGET_PC
        /* PC: the objects' work blocks through their handles (see Spr above). */
        ((Node *)SLOT_TO_PTR(D_800E9450[i].node))->flags &= ~0x80;
        ((Node *)SLOT_TO_PTR(D_800E9608[i].node))->flags &= ~0x80;
#else
        D_800E9450[i].node->flags &= ~0x80;
        D_800E9608[i].node->flags &= ~0x80;
#endif
        func_800907A0(&D_800E9450[i], &D_800E97C0[i], 0xF0, 0x64, 0.5f, 0.5f, 0.5f, 0.5f, 0xFF, 0xFF, 0xFF, 0);
        func_800907A0(&D_800E9608[i], &D_800E9818[i], 0xF0, 0x64, 0.5f, 0.5f, 0.5f, 0.5f, 0xFF, 0, 0, 0);
    }
    D_800E9870 = 0;
}
