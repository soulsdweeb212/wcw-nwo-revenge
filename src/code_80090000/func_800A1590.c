/* @header
 * func_800A1590
 * VRAM 0x800A1590 | ROM 0x4DD00 | size 0xEC
 * asm: asm/nonmatchings/code_80090000/func_800A1590.s
 */
#include "common.h"


typedef struct { void *a; s32 b; void *c; u8 pad[0x12C]; } N;
typedef struct { s16 f; u8 pad[0x136]; } M;
extern s16 D_800DC824;
extern s32 D_800DC74C;
extern u8 D_800DC748[];
extern N D_800E8288[];
extern u8 *D_800E8230;
extern M D_800E8236[];
void func_8009F9A0(void);
void initializeTransformNode(void *, s32, f32, f32, f32);
s32 initPairedTransformNodes(void *, void *);

void func_800A1590(void) {
    N *n;
    s32 i, j;
    D_800DC824 = 0;
    func_8009F9A0();
    initializeTransformNode(D_800DC748, 0, 0.0f, 0.0f, 0.0f);
    D_800DC74C = initPairedTransformNodes(D_800DC748, D_800E8288);
    for (i = 0, n = &D_800E8288[1]; i < 0x18; i++) {
        D_800E8288[i].a = D_800DC748;
        if (i < 0x17) {
            D_800E8288[i].c = n;
        }
        n++;
    }
    D_800E8236[0].f = D_800E8230[4];
    for (j = 1; j < 0x18; j++) {
        D_800E8236[j].f = 0;
    }
}
