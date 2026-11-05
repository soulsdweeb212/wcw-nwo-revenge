/* @header
 * func_800984C8
 * VRAM 0x800984C8 | ROM 0x8B968 | size 0x98
 * asm: asm/nonmatchings/ovl2_80090000/func_800984C8.s
 */
#include "common.h"

void releaseHeapBlock(void *);
void func_8002A5F4(void *);
void releaseResourcePool(void);

extern s32 D_800EB0C0;
extern void *D_800EB18C[3];
extern void *D_800EB1A4;
extern void *D_800EB1B4;
extern void *D_800EB1B8;

void func_800984C8(void) {
    u32 i;

    D_800EB0C0 = 0;
    for (i = 0; i < 3; i++) {
        releaseHeapBlock(D_800EB18C[i]);
        D_800EB18C[i] = 0;
    }
    if (D_800EB1A4 != 0) {
        func_8002A5F4(D_800EB1A4);
    }
    if (D_800EB1B4 != 0) {
        func_8002A5F4(D_800EB1B4);
    }
    releaseHeapBlock(D_800EB1B8);
    releaseResourcePool();
}
