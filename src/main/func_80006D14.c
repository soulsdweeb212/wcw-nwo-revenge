/* @header
 * func_80006D14
 * VRAM 0x80006D14 | ROM 0x7914 | size 0x50
 * asm: asm/nonmatchings/main/func_80006D14.s
 */
#include "common.h"

s32 releaseHeapBlock(s32);

/* Release the two heap allocations referenced by arg0 (+0xC and +0x10) and clear
 * the pointers. */
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
