/* @header
 * func_8009608C
 * VRAM 0x8009608C | ROM 0x8952C | size 0x184
 * asm: asm/nonmatchings/ovl2_80090000/func_8009608C.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: Rec2C is the game's display record of a picture, whose PC layout is common.h's Nw2Descr4BA8 (0x50 bytes, its
 * addresses as pointers). port_decls.h declares D_800E7FB8 and D_800E8040 with that type, and &X[i] steps by whole
 * records. */
typedef Nw2Descr4BA8 Rec2C;
#else
typedef struct {
    u8 data[0x2C];
} Rec2C;
#endif

typedef struct {
    s32 flags;
} Node;

#ifdef TARGET_PC
/* PC: ObjDC is the game's 0xDC-byte scene object, common.h's Nw2SceneObj, which keeps its N64 layout on PC: the address
 * of its first work block at +0x14 is a 4-byte handle (port.h's PTR_TO_SLOT), and Node is the start of that work block
 * (its kind word, Nw2SceneWork's kind). Code reaches the work block through SLOT_TO_PTR. The asserts check the view
 * against both records. */
typedef struct {
    u8 pad0[0x14];
    u32 node;
    u8 pad18[0xC4];
} ObjDC;
_Static_assert(sizeof(ObjDC) == sizeof(Nw2SceneObj) && offsetof(ObjDC, node) == offsetof(Nw2SceneObj, work) &&
                   offsetof(Node, flags) == offsetof(Nw2SceneWork, kind),
               "ObjDC must follow Nw2SceneObj, and Node Nw2SceneWork");
#else
typedef struct {
    u8 pad0[0x14];
    Node *node;
    u8 pad18[0xC4];
} ObjDC;
#endif

extern s16 D_800E2D8E[];
extern ObjDC D_800E7DF8;
extern ObjDC D_800E7ED8;
#ifndef TARGET_PC /* on PC these labels, one record before D_800E7FB8 and D_800E8040, have no symbol */
extern Rec2C D_800E7F8C[];
extern Rec2C D_800E8014[];
#endif
extern s16 D_800E80C4;
extern s16 D_800E80C6;
extern s16 D_800F99B6;
void func_8000DEE4(s16);
void func_800907A0(void *, Rec2C *, s16, s16, f32, f32, f32, f32, u8, u8, u8, u8);
void func_8009786C(s32);

void func_8009608C(s16 arg0) {
    if (D_800F99B6 != 0) {
        return;
    }
    if ((u16)(arg0 - 1) < 3) {
#ifdef TARGET_PC
        /* PC: the object's work block through its handle (see ObjDC above). */
        if (((Node *)SLOT_TO_PTR(D_800E7DF8.node))->flags & 0x80) {
#else
        if (D_800E7DF8.node->flags & 0x80) {
#endif
            D_800E80C4 = 0;
        }
        if (D_800E80C4 != arg0) {
            func_8000DEE4(D_800E2D8E[arg0]);
            D_800E80C4 = arg0;
            D_800E80C6 = 0;
#ifdef TARGET_PC
            /* PC: the labels D_800E7F8C and D_800E8014 have no symbol. arg0 and D_800E80C4 are 1 to 3 here, so the
             * records are the base arrays' elements arg0 - 1 and D_800E80C4 - 1. */
            func_800907A0(&D_800E7DF8, &D_800E7FB8[arg0 - 1], 0xF0, 0xA, 0.5f, 0.0f, 1.0f, 1.0f, 0xFF, 0xFF, 0xFF,
                          0xF);
            func_800907A0(&D_800E7ED8, &D_800E8040[D_800E80C4 - 1], 0xF0, 0xA, 0.5f, 0.0f, 1.0f, 1.0f, 0xFF, 0, 0,
                          0);
#else
            func_800907A0(&D_800E7DF8, &D_800E7F8C[arg0], 0xF0, 0xA, 0.5f, 0.0f, 1.0f, 1.0f, 0xFF, 0xFF, 0xFF, 0xF);
            func_800907A0(&D_800E7ED8, &D_800E8014[D_800E80C4], 0xF0, 0xA, 0.5f, 0.0f, 1.0f, 1.0f, 0xFF, 0, 0, 0);
#endif
        }
    }
    func_8009786C(1);
}
