/* @header
 * func_800998EC
 * VRAM 0x800998EC | ROM 0x8CD8C | size 0x7C
 * asm: asm/nonmatchings/ovl2_80090000/func_800998EC.s
 */
#include "common.h"

void releaseHeapBlock(void *);
extern s32 D_800EB1D0;
extern void *D_800EB29C[3];
extern void *D_800EB2B8[35];

void func_800998EC(void) {
    u32 i;

    D_800EB1D0 = 0;
    for (i = 0; i < 3; i++) {
        releaseHeapBlock(D_800EB29C[i]);
        D_800EB29C[i] = 0;
    }
    for (i = 0; i < 35; i++) {
        releaseHeapBlock(D_800EB2B8[i]);
        D_800EB2B8[i] = 0;
    }
}
