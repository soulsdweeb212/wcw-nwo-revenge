/* @header
 * func_80095BF0
 * VRAM 0x80095BF0 | ROM 0x89090 | size 0xC0
 * asm: asm/nonmatchings/ovl2_80090000/func_80095BF0.s
 */
#include "common.h"

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

extern ObjDC D_800E9878[];
extern ObjDC D_800E9D70[];
extern ObjDC D_800EA268[];
extern ObjDC D_800EA758[];
extern ObjDC D_800EAC88[];
extern u8 D_800E9D38[];
extern u16 D_800EB0AA;

void func_80095BF0(void) {
    u32 i;

    for (i = 0; i < D_800EB0AA; i++) {
#ifdef TARGET_PC
        /* PC: the objects' work blocks through their handles (see ObjDC above). */
        ((Node *)SLOT_TO_PTR(D_800EA268[i].node))->flags |= 0x80;
        ((Node *)SLOT_TO_PTR(D_800E9D70[i].node))->flags |= 0x80;
        ((Node *)SLOT_TO_PTR(D_800EAC88[i].node))->flags |= 0x80;
        ((Node *)SLOT_TO_PTR(D_800EA758[i].node))->flags |= 0x80;
        ((Node *)SLOT_TO_PTR(D_800E9878[i].node))->flags |= 0x80;
#else
        D_800EA268[i].node->flags |= 0x80;
        D_800E9D70[i].node->flags |= 0x80;
        D_800EAC88[i].node->flags |= 0x80;
        D_800EA758[i].node->flags |= 0x80;
        D_800E9878[i].node->flags |= 0x80;
#endif
        D_800E9D38[i] = 0;
    }
}
