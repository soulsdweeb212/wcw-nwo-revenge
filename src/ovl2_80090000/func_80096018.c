/* @header
 * func_80096018
 * VRAM 0x80096018 | ROM 0x894B8 | size 0x74
 * asm: asm/nonmatchings/ovl2_80090000/func_80096018.s
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

extern ObjDC D_800E7DF8;
extern ObjDC D_800E7ED8;
extern s16 D_800E80C4;
extern s8 D_800F99B4;
void func_80097BB4(void);

void func_80096018(void) {
#ifdef TARGET_PC
    /* PC: the object's work block through its handle (see ObjDC above). */
    s32 f = ((Node *)SLOT_TO_PTR(D_800E7DF8.node))->flags;
#else
    s32 f = D_800E7DF8.node->flags;
#endif

    if (!(f & 0x80) && D_800E80C4 < 3) {
#ifdef TARGET_PC
        /* PC: as above, the work block through its handle. */
        ((Node *)SLOT_TO_PTR(D_800E7DF8.node))->flags = f | 0x80;
        ((Node *)SLOT_TO_PTR(D_800E7ED8.node))->flags |= 0x80;
#else
        D_800E7DF8.node->flags = f | 0x80;
        D_800E7ED8.node->flags |= 0x80;
#endif
    }
    if (D_800F99B4 == 1) {
        func_80097BB4();
    }
}
