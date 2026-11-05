/* @header
 * func_800B8994
 * VRAM 0x800B8994 | ROM 0x65104 | size 0x1B0
 * asm: asm/nonmatchings/code_80090000/func_800B8994.s
 */
#include "common.h"

extern s32 D_800DCFC4;

void func_800B8994(void) {
    u8 *b;
    u8 *q;
    s32 i;
    s32 j;

    D_800DCFC4 = func_8000424C();
    b = allocateHeap(0x100);
    osInvalDCache(b, 0x100);
    for (i = 0, q = b; i < 8; i++, q += 0x20) {
        __osContRamRead(D_800DCFC4, 0, (u16)i, q);
    }
    releaseHeapBlock(b);
    b = allocateHeap(0x100);
    osInvalDCache(b, 0x100);
    for (i = 0, q = b; i < 8; i++, q += 0x20) {
        __osContRamRead(D_800DCFC4, 0, (u16)i, q);
    }
    for (j = 0; j < 0x100; j++) {
        b[j]++;
    }
    osWritebackDCache(b, 0x100);
    for (i = 0, q = b; i < 8; i++, q += 0x20) {
        __osContRamWrite(D_800DCFC4, 0, (u16)i, q, 1);
    }
    releaseHeapBlock(b);
    func_800B9474();
    b = allocateHeap(0x100);
    osInvalDCache(b, 0x100);
    for (i = 0, q = b; i < 8; i++, q += 0x20) {
        __osContRamRead(D_800DCFC4, 0, (u16)i, q);
    }
    releaseHeapBlock(b);
    func_80004290();
}
