/* @header
 * func_80007A74
 * VRAM 0x80007A74 | ROM 0x8674 | size 0x88
 * asm: asm/nonmatchings/main/func_80007A74.s
 */
#include "common.h"

s32 allocateHeap(s32);
void releaseHeapBlock(s32);

/* Reinitializes the descriptor's two pools: frees the old buffers and allocates
 * new ones sized for arg1 0x10-byte and arg2 8-byte records. */
void func_80007A74(void *arg0, s32 arg1, s32 arg2) {
    s32 old;

    old = *(s32 *)((u8 *)arg0 + 0);
    if (old != 0) {
        releaseHeapBlock(old);
    }
    *(s16 *)((u8 *)arg0 + 6) = 0;
    *(s16 *)((u8 *)arg0 + 4) = arg1;
    *(s32 *)((u8 *)arg0 + 0) = allocateHeap((arg1 & 0xFFFF) * 0x10);
    old = *(s32 *)((u8 *)arg0 + 8);
    if (old != 0) {
        releaseHeapBlock(old);
    }
    *(s16 *)((u8 *)arg0 + 0xE) = 0;
    *(s16 *)((u8 *)arg0 + 0xC) = arg2;
    *(s32 *)((u8 *)arg0 + 8) = allocateHeap((arg2 & 0xFFFF) * 8);
}
