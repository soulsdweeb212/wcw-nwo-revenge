/* @header
 * func_800998EC
 * VRAM 0x800998EC | ROM 0x8CD8C | size 0x7C
 * asm: asm/nonmatchings/ovl2_80090000/func_800998EC.s
 */
#include "common.h"

void releaseHeapBlock(void *);
#ifndef TARGET_PC /* on PC D_800EB1D0 has no symbol: it is the dl of D_800EB1C0, which port_decls.h declares */
extern s32 D_800EB1D0;
#endif
extern void *D_800EB29C[3];
extern void *D_800EB2B8[35];

void func_800998EC(void) {
    u32 i;

#ifdef TARGET_PC
    D_800EB1C0.dl = 0; /* PC: the object's dl (+0x10, the N64 label D_800EB1D0), a handle; 0 stands for NULL */
#else
    D_800EB1D0 = 0;
#endif
    for (i = 0; i < 3; i++) {
        releaseHeapBlock(D_800EB29C[i]);
        D_800EB29C[i] = 0;
    }
    for (i = 0; i < 35; i++) {
        releaseHeapBlock(D_800EB2B8[i]);
        D_800EB2B8[i] = 0;
    }
}
