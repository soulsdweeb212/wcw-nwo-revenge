/* @header
 * func_80011264
 * VRAM 0x80011264 | ROM 0x11E64 | size 0x58
 * asm: asm/nonmatchings/main/func_80011264.s
 */
#include "common.h"

extern u8 D_80059D90[];
#ifdef TARGET_PC
/* PC: the type of releaseHeapBlock's definition (releaseHeapBlock.c), which takes the block's address. */
void releaseHeapBlock(u8 *);
#else
void releaseHeapBlock(s32);
#endif

/* Frees the two heap buffers of each of the four D_80059D90 records. */
void func_80011264(void) {
    u32 i;

    for (i = 0; i < 4; i++) {
        u8 *p = D_80059D90 + i * 0xDC;

#ifdef TARGET_PC
        /* PC: the records are scene objects, which keep their N64 layout (Nw2SceneObj, common.h): their vertices
         * (+0xC) and display list (+0x10) are handles, so the PC frees the blocks they name and clears both. */
        Nw2SceneObj *o = (Nw2SceneObj *)p;

        releaseHeapBlock(SLOT_TO_PTR(o->vtx));
        o->vtx = 0;
        releaseHeapBlock(SLOT_TO_PTR(o->dl));
        o->dl = 0;
#else
        releaseHeapBlock(*(s32 *)(p + 0xC));
        *(s32 *)(p + 0xC) = 0;
        releaseHeapBlock(*(s32 *)(p + 0x10));
        *(s32 *)(p + 0x10) = 0;
#endif
    }
}
