/* @header
 * func_80007818
 * VRAM 0x80007818 | ROM 0x8418 | size 0x5C
 * asm: asm/nonmatchings/main/func_80007818.s
 */
#include "common.h"

void func_800015AC(void *, s8);

/* Initialize `obj` from the 0x2C-byte descriptor `index` in the table at
 * descriptorBase: copy the descriptor's +0xC into the object's +0xC, set the
 * object's +0x10 to arg2, attach the work block with the descriptor's mode byte,
 * then clear the work block's first word. */
#ifdef TARGET_PC
/* PC: the types of port_decls.h's line. recs is an array of display records in their PC layout (Nw2Descr4BA8,
 * common.h), so index picks a record by the array's own step. The object keeps its N64 layout (Nw2SceneObj), so its
 * vertices and display list are stored as handles (port.h's PTR_TO_SLOT), and its work block is reached through its
 * handle. The order is the N64's: func_800015AC copies the object's display list into the work block. */
void func_80007818(void *obj, void *recs, void *dl, s16 index) {
    Nw2SceneObj *o = obj;
    Nw2Descr4BA8 *t = (Nw2Descr4BA8 *)recs + index;

    o->dl = PTR_TO_SLOT(dl);
    o->vtx = PTR_TO_SLOT(t->fC);
    func_800015AC(o, t->f2);
    ((Nw2SceneWork *)SLOT_TO_PTR(o->work))->kind = 0;
}
#else
void func_80007818(u8 *obj, s32 descriptorBase, s32 arg2, s16 index) {
    u8 *t = (u8 *)(index * 0x2C + descriptorBase);
    s32 v = *(s32 *)(t + 0xC);

    *(s32 *)(obj + 0x10) = arg2;
    *(s32 *)(obj + 0xC) = v;
    func_800015AC(obj, t[2]);
    *(s32 *)(*(s32 **)(obj + 0x14)) = 0;
}
#endif
