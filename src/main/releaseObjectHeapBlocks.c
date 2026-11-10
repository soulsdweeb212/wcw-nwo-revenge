/* @header
 * releaseObjectHeapBlocks  (originally func_80006D64)
 * VRAM 0x80006D64 | ROM 0x7964 | size 0xC8
 * asm: asm/nonmatchings/main/releaseObjectHeapBlocks.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: releaseHeapBlock takes the block's address (u8 *arg0, releaseHeapBlock.c); the N64 declaration passes it as an
 * s32, which would cut a 64-bit address in half. */
void releaseHeapBlock(u8 *);
#else
s32 releaseHeapBlock(s32);
#endif

typedef struct {
    u8 active;    /* @0x0: object-in-use flag */
    u8 pad1[0xB];
    s32 fC;       /* @0xC */
    s32 f10;      /* @0x10 */
    s32 f14;      /* @0x14 */
    s32 f18;      /* @0x18 */
    s32 f1C;      /* @0x1C */
    u8 pad20[8];
    s32 f28;      /* @0x28: shared-ownership flag */
} HeapBlockOwner;

/* If the object is active, deactivate it and free each of its five heap buffer
 * pointers (+0xC/+0x10/+0x14/+0x18/+0x1C), clearing each as it goes. The first
 * three are skipped when the shared-ownership flag +0x28 is set. */
#ifdef TARGET_PC
/* PC: the object is a display record (overlay 2's func_80094424 hands it the records of D_800E7FB8, D_800E8040 and
 * the other 0x2C-byte arrays it frees), whose PC layout is Nw2Descr4BA8 (common.h): the five buffers are 8-byte
 * pointers from +0x10 on, and +0x28 is the arena pointer f28 rather than an s32 flag. So this version reads the record
 * through that struct by name, and frees whole addresses. The in-use flag stays the byte at +0. */
void releaseObjectHeapBlocks(void *arg0) {
    Nw2Descr4BA8 *obj = arg0;
    void *temp;

    if (obj->pad0[0] != 0) {
        temp = obj->fC;
        obj->pad0[0] = 0;
        if (temp != NULL) {
            if (obj->f28 == NULL) {
                releaseHeapBlock(temp);
            }
            obj->fC = NULL;
        }
        temp = obj->f10;
        if (temp != NULL) {
            if (obj->f28 == NULL) {
                releaseHeapBlock(temp);
            }
            obj->f10 = NULL;
        }
        temp = obj->f14;
        if (temp != NULL) {
            if (obj->f28 == NULL) {
                releaseHeapBlock(temp);
            }
            obj->f14 = NULL;
        }
        temp = obj->f18;
        if (temp != NULL) {
            releaseHeapBlock(temp);
            obj->f18 = NULL;
        }
        temp = obj->f1C;
        if (temp != NULL) {
            releaseHeapBlock(temp);
            obj->f1C = NULL;
        }
    }
}
#else
void releaseObjectHeapBlocks(void *arg0) {
    HeapBlockOwner *obj = arg0;
    s32 temp;

    if (obj->active != 0) {
        temp = obj->fC;
        obj->active = 0;
        if (temp != 0) {
            if (obj->f28 == 0) {
                releaseHeapBlock(temp);
            }
            obj->fC = 0;
        }
        temp = obj->f10;
        if (temp != 0) {
            if (obj->f28 == 0) {
                releaseHeapBlock(temp);
            }
            obj->f10 = 0;
        }
        temp = obj->f14;
        if (temp != 0) {
            if (obj->f28 == 0) {
                releaseHeapBlock(temp);
            }
            obj->f14 = 0;
        }
        temp = obj->f18;
        if (temp != 0) {
            releaseHeapBlock(temp);
            obj->f18 = 0;
        }
        temp = obj->f1C;
        if (temp != 0) {
            releaseHeapBlock(temp);
            obj->f1C = 0;
        }
    }
}
#endif
