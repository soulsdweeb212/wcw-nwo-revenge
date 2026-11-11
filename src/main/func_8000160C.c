/* @header
 * func_8000160C
 * VRAM 0x8000160C | ROM 0x220C | size 0x54
 * asm: asm/nonmatchings/main/func_8000160C.s
 */
#include "common.h"

void *func_80001694();

/* Allocate a new scratch block, attach arg0 as its owner (+4), and append it to the
 * end of arg0's work-block chain (linked through +8). */
#ifdef TARGET_PC
/* PC: the object and its work blocks keep their N64 layout (Nw2SceneObj and Nw2SceneWork in common.h), so the owner,
 * the object's first block and each block's next hold handles (port.h's PTR_TO_SLOT). This version walks the chain
 * with SLOT_TO_PTR and stores the handles of the object and of the new block. */
void *func_8000160C(void *arg0) {
    Nw2SceneWork *block;
    Nw2SceneWork *tail;

    block = func_80001694();
    block->owner = PTR_TO_SLOT(arg0);
    tail = SLOT_TO_PTR(((Nw2SceneObj *)arg0)->work);
    while (tail->next != 0) {
        tail = SLOT_TO_PTR(tail->next);
    }
    tail->next = PTR_TO_SLOT(block);
    return block;
}
#else
void *func_8000160C(void *arg0) {
    void *block;
    void *tail;

    block = func_80001694();
    *(void **)((s8 *)block + 4) = arg0;
    tail = *(void **)((s8 *)arg0 + 0x14);
    if (*(s32 *)((s8 *)tail + 8) != 0) {
        do {
            tail = *(void **)((s8 *)tail + 8);
        } while (*(s32 *)((s8 *)tail + 8) != 0);
    }
    *(void **)((s8 *)tail + 8) = block;
    return block;
}
#endif
