/* @header
 * func_80011264
 * VRAM 0x80011264 | ROM 0x11E64 | size 0x58
 * asm: asm/nonmatchings/main/func_80011264.s
 */
#include "common.h"

extern u8 D_80059D90[];
void releaseHeapBlock(s32);

/* Frees the two heap buffers of each of the four D_80059D90 records. */
void func_80011264(void) {
    u32 i;

    for (i = 0; i < 4; i++) {
        u8 *p = D_80059D90 + i * 0xDC;

        releaseHeapBlock(*(s32 *)(p + 0xC));
        *(s32 *)(p + 0xC) = 0;
        releaseHeapBlock(*(s32 *)(p + 0x10));
        *(s32 *)(p + 0x10) = 0;
    }
}
