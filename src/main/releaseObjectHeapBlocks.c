/* @header
 * releaseObjectHeapBlocks  (originally func_80006D64)
 * VRAM 0x80006D64 | ROM 0x7964 | size 0xC8
 * asm: asm/nonmatchings/main/func_80006D64.s
 */
#include "common.h"

s32 releaseHeapBlock(s32);

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
