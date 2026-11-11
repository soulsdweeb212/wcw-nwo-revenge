/* @header
 * func_80091DF4
 * VRAM 0x80091DF4 | ROM 0x85294 | size 0x4CC
 * asm: asm/nonmatchings/ovl2_80090000/func_80091DF4.s
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
s32 func_8000DEE4(s32 arg0);

extern Spr D_800E9450[2];
extern Spr D_800E9608[2];
extern SprTex D_800E97C0[2];
extern SprTex D_800E9818[2];
extern s16 D_800E9870;
extern s16 D_800F9A9C;
extern s16 D_800F9AFA;

void func_80091DF4(void) {
    u32 x;
#ifndef TARGET_PC /* n exists only for the N64 placeholder below, which the PC leaves out */
    s32 n;
#endif

    if (D_800E9870 < 0) {
        return;
    }
    if (D_800E9870 == 0x10) {
        func_8000DEE4(2);
        func_8000DEE4(0x4C);
    }
    if (D_800E9870 < 4) {
        x = D_800E9870 * 63;
        func_800907A0(&D_800E9608[0], &D_800E9818[0], 0xF0, 0x64, 0.5f, 0.5f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, x);
        func_800907A0(&D_800E9608[1], &D_800E9818[1], 0xF0, 0x64, 0.5f, 0.5f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0);
    } else if (D_800E9870 < 6) {
        x = (D_800E9870 - 4) * 127;
        func_800907A0(&D_800E9608[0], &D_800E9818[0], 0xF0, 0x64, 0.5f, 0.5f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0xFF - x);
        func_800907A0(&D_800E9608[1], &D_800E9818[1], 0xF0, 0x64, 0.5f, 0.5f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, x);
    } else if (D_800E9870 < 8) {
        x = (D_800E9870 - 6) * 127;
        func_800907A0(&D_800E9608[0], &D_800E9818[0], 0xF0, 0x64, 0.5f, 0.5f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0);
        func_800907A0(&D_800E9608[1], &D_800E9818[1], 0xF0, 0x64, 0.5f, 0.5f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0xFF - x);
        func_800907A0(&D_800E9450[0], &D_800E97C0[0], 0xF0, 0x64, 0.5f, 0.5f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, x);
    } else if (D_800E9870 < 10) {
        x = (D_800E9870 - 8) * 127;
        func_800907A0(&D_800E9608[1], &D_800E9818[1], 0xF0, 0x64, 0.5f, 0.5f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0);
        func_800907A0(&D_800E9450[0], &D_800E97C0[0], 0xF0, 0x64, 0.5f, 0.5f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0xFF - x);
        func_800907A0(&D_800E9450[1], &D_800E97C0[1], 0xF0, 0x64, 0.5f, 0.5f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, x);
    } else if (D_800E9870 < 0x14) {
        func_800907A0(&D_800E9450[1], &D_800E97C0[1], 0xF0, 0x64, 0.5f, 0.5f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0xFF);
        func_800907A0(&D_800E9450[0], &D_800E97C0[0], 0xF0, 0x64, 0.5f, 0.5f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0);
    } else if (D_800E9870 < 0x18) {
        /* placeholder: a condition only cse1 folds; it keeps a label inside this arm
           through jump1 so "if (foo) bar; else break;" does not swap it with the
           else arm below (the ROM keeps this arm first and all arms jump to the ++) */
#ifdef TARGET_PC
        /* PC: x is set here directly. The placeholder (n is always 0, so its if always runs) only steers the N64
         * compiler's block order, and the ROM sets x unconditionally in this arm (x = (D_800E9870 - 0x14) * 63 at
         * 0x80092160 to 0x80092168); the compilers here cannot see that and warn that x might be read unset. */
        x = (D_800E9870 - 0x14) * 63;
#else
        n = 0;
        if (n == 0) {
            x = (D_800E9870 - 0x14) * 63;
        }
#endif
        func_800907A0(&D_800E9450[1], &D_800E97C0[1], 0xF0, 0x64, 0.5f, 0.5f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0xFF - x);
        func_800907A0(&D_800E9450[0], &D_800E97C0[0], 0xF0, 0x64, 0.5f, 0.5f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0);
    } else {
#ifdef TARGET_PC
        /* PC: the objects' work blocks through their handles (see Spr above). */
        ((Node *)SLOT_TO_PTR(D_800E9450[0].node))->flags |= 0x80;
        ((Node *)SLOT_TO_PTR(D_800E9608[0].node))->flags |= 0x80;
        ((Node *)SLOT_TO_PTR(D_800E9450[1].node))->flags |= 0x80;
        ((Node *)SLOT_TO_PTR(D_800E9608[1].node))->flags |= 0x80;
#else
        D_800E9450[0].node->flags |= 0x80;
        D_800E9608[0].node->flags |= 0x80;
        D_800E9450[1].node->flags |= 0x80;
        D_800E9608[1].node->flags |= 0x80;
#endif
        D_800F9A9C = 0;
        D_800E9870 = -1;
        D_800F9AFA = 1;
        return;
    }
    D_800E9870++;
}
