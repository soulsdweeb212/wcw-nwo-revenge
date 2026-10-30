/* @header
 * func_80008AF0
 * VRAM 0x80008AF0 | ROM 0x96F0 | size 0x6C
 * asm: asm/nonmatchings/main/func_80008AF0.s
 */
#include "common.h"

extern u8 *D_8007BD38;
extern void *D_800485A0[];

void releaseHeapBlock(void *);

/* Frees the animation source and the four D_800485A0 buffers. */
void func_80008AF0(void) {
    u32 i;
    void **p;

    i = 0;
    p = D_800485A0;
    releaseHeapBlock(D_8007BD38);
    D_8007BD38 = NULL;
    do {
        releaseHeapBlock(*p++);
        i++;
    } while (i < 4U);
    D_800485A0[i] = NULL;
}
