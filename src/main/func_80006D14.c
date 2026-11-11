/* @header
 * func_80006D14
 * VRAM 0x80006D14 | ROM 0x7914 | size 0x50
 * asm: asm/nonmatchings/main/func_80006D14.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: releaseHeapBlock takes the block's address (u8 *arg0, releaseHeapBlock.c); the N64 declaration passes it as an
 * s32, which would cut a 64-bit address in half. */
void releaseHeapBlock(u8 *);
#else
s32 releaseHeapBlock(s32);
#endif

/* Release the two heap allocations referenced by arg0 (+0xC and +0x10) and clear
 * the pointers. */
#ifdef TARGET_PC
/* PC: arg0 is a 0xDC-byte object (Nw2SceneObj, common.h), which keeps its N64 layout, so its vertices (+0xC) and
 * display list (+0x10) are 4-byte handles of the heap blocks (port.h's PTR_TO_SLOT; 0 for none). This frees the
 * blocks they stand for and clears the handles. */
void func_80006D14(void *arg0) {
    Nw2SceneObj *obj = arg0;
    u8 *a;
    u8 *b;

    a = SLOT_TO_PTR(obj->vtx);
    if (a != NULL) {
        releaseHeapBlock(a);
        obj->vtx = 0;
    }
    b = SLOT_TO_PTR(obj->dl);
    if (b != NULL) {
        releaseHeapBlock(b);
        obj->dl = 0;
    }
}
#else
void func_80006D14(void *arg0) {
    s32 a;
    s32 b;

    a = *(s32 *)((s8 *)arg0 + 0xC);
    if (a != 0) {
        releaseHeapBlock(a);
        *(s32 *)((s8 *)arg0 + 0xC) = 0;
    }
    b = *(s32 *)((s8 *)arg0 + 0x10);
    if (b != 0) {
        releaseHeapBlock(b);
        *(s32 *)((s8 *)arg0 + 0x10) = 0;
    }
}
#endif
