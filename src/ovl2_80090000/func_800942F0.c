/* @header
 * func_800942F0
 * VRAM 0x800942F0 | ROM 0x87790 | size 0x134
 * asm: asm/nonmatchings/ovl2_80090000/func_800942F0.s
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

extern u8 D_8007E8C0[];
extern s32 D_800E77B0;
extern ObjDC D_800E7950[];
extern ObjDC D_800EAB78;
extern u16 D_800EB0AA;
extern s16 D_800F9AFA;
void func_80091DF4(void);
void func_80094A9C(void);
void func_80095BF0(void);
void func_80096210(void);
void func_80096FE8(void);
s8 func_800D633C(void);

void func_800942F0(s16 arg0) {
    u32 i;

    if (arg0 == 0) {
        if (D_800EB0AA < 3) {
            func_80096FE8();
        }
        func_80096210();
        func_80091DF4();
    }
#ifdef TARGET_PC
    /* PC: the object's work block through its handle (see ObjDC above). */
    ((Node *)SLOT_TO_PTR(D_800EAB78.node))->flags |= 0x80;
#else
    D_800EAB78.node->flags |= 0x80;
#endif
    if (func_800D633C()) {
        func_80095BF0();
#ifdef TARGET_PC
        /* PC: as above, the work block through its handle. */
        if (!(((Node *)SLOT_TO_PTR(D_800E7950[0].node))->flags & 0x80)) {
#else
        if (!(D_800E7950[0].node->flags & 0x80)) {
#endif
            for (i = 0; i < 5; i++) {
#ifdef TARGET_PC
                /* PC: as above, the work block through its handle. */
                ((Node *)SLOT_TO_PTR(D_800E7950[i].node))->flags |= 0x80;
#else
                D_800E7950[i].node->flags |= 0x80;
#endif
            }
        }
        if (D_800E77B0 & 0xC) {
#ifdef TARGET_PC
            /* PC: as above, the work block through its handle. */
            ((Node *)SLOT_TO_PTR(D_800EAB78.node))->flags &= ~0x80;
#else
            D_800EAB78.node->flags &= ~0x80;
#endif
        }
    } else if (D_8007E8C0[0x66F] == 0 && D_800F9AFA != 0) {
        func_80094A9C();
    } else {
        func_80095BF0();
    }
    D_800E77B0++;
}
