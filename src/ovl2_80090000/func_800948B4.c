/* @header
 * func_800948B4
 * VRAM 0x800948B4 | ROM 0x87D54 | size 0x1E8
 * asm: asm/nonmatchings/ovl2_80090000/func_800948B4.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: Rec2C is the game's display record of a picture, whose PC layout is common.h's Nw2Descr4BA8 (0x50 bytes, its
 * addresses as pointers). port_decls.h declares D_800EA1B0 with that type, and &X[i] steps by whole records. */
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
 * (its kind word, Nw2SceneWork's kind). This file only steps through D_800E9D70 by objects, so only the 0xDC size
 * matters here. The asserts check the view against both records. */
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

typedef struct {
    u8 id;
    u8 b1;
    u8 b2;
    u8 b3;
    u8 pad4[4];
    s16 x;
    s16 y;
} Rec0C;

extern u16 D_800E2C4C[];
extern u16 D_800E2C54[];
extern Rec0C D_800E9D40[];
extern ObjDC D_800E9D70[];
extern Rec2C D_800EA1B0[];
extern u8 D_800EA260[];
extern s16 D_800EB0A8;
extern u16 D_800EB0AA;
void func_800907A0(void *, Rec2C *, s16, s16, f32, f32, f32, f32, u8, u8, u8, u8);

void func_800948B4(void) {
    u32 i;

    if (D_800EB0AA < 3) {
        D_800E9D40[0].id = 1;
        D_800E9D40[1].id = 3;
    } else {
        for (i = 0; i < D_800EB0AA; i++) {
            D_800E9D40[i].id = i;
        }
    }
    for (i = 0; i < D_800EB0AA; i++) {
        D_800E9D40[i].b1 = 0;
        D_800E9D40[i].b2 = 0;
        D_800E9D40[i].b3 = 0;
        D_800E9D40[i].x = D_800E2C4C[D_800E9D40[i].id & 3];
        D_800E9D40[i].y = D_800E2C54[D_800E9D40[i].id & 3];
        func_800907A0(&D_800E9D70[i], &D_800EA1B0[i], D_800E9D40[i].x, D_800E9D40[i].y, 0.0f, 0.0f, 1.0f, 1.0f, 0xFF, 0xFF, 0xFF, 0xFF);
        D_800EA260[i] = 0x14;
    }
    D_800EB0A8 = 0;
}
