/* @header
 * func_800984C8
 * VRAM 0x800984C8 | ROM 0x8B968 | size 0x98
 * asm: asm/nonmatchings/ovl2_80090000/func_800984C8.s
 */
#include "common.h"

void releaseHeapBlock(void *);
void func_8002A5F4(void *);
void releaseResourcePool(void);

#ifndef TARGET_PC /* on PC D_800EB0C0 has no symbol: it is the dl of D_800EB0B0, which port_decls.h declares */
extern s32 D_800EB0C0;
#endif
extern void *D_800EB18C[3];
#ifndef TARGET_PC /* on PC these have no symbol: they are the tex of the icons D_800EB19C and D_800EB1AC */
extern void *D_800EB1A4;
extern void *D_800EB1B4;
#endif
extern void *D_800EB1B8;

void func_800984C8(void) {
    u32 i;

#ifdef TARGET_PC
    D_800EB0B0.dl = 0; /* PC: the object's dl (+0x10, the N64 label D_800EB0C0), a handle; 0 stands for NULL */
#else
    D_800EB0C0 = 0;
#endif
    for (i = 0; i < 3; i++) {
        releaseHeapBlock(D_800EB18C[i]);
        D_800EB18C[i] = 0;
    }
#ifdef TARGET_PC
    /* PC: the N64 labels D_800EB1A4 and D_800EB1B4 are the pictures of the two icons (Nw2HudIcon's tex). */
    if (D_800EB19C.tex != 0) {
        func_8002A5F4(D_800EB19C.tex);
    }
    if (D_800EB1AC.tex != 0) {
        func_8002A5F4(D_800EB1AC.tex);
    }
#else
    if (D_800EB1A4 != 0) {
        func_8002A5F4(D_800EB1A4);
    }
    if (D_800EB1B4 != 0) {
        func_8002A5F4(D_800EB1B4);
    }
#endif
    releaseHeapBlock(D_800EB1B8);
    releaseResourcePool();
}
