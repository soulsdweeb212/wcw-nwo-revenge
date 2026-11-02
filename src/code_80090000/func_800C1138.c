/* @header
 * func_800C1138
 * VRAM 0x800C1138 | ROM 0x6D8A8 | size 0x198
 * asm: asm/nonmatchings/code_80090000/func_800C1138.s
 */
#include "common.h"

typedef struct {
    s32 f0;
    u8 pad4[4];
    void *f8;
    void *fC;
    void *f10;
    u8 *f14;
    u8 pad18[0xCC];
    s16 fE4, fE6, fE8, fEA;
} N;
extern N D_800E7558[];
extern u8 D_800D5758[], D_800D5768[];
extern s32 D_800E81F8, D_800E81E4, D_800E79C4;
void buildScaledRotationTranslationMatrix(void *, f32, f32, f32, f32, f32, f32, f32);
void initializeTransformNode(void *, u8, f32, f32, f32);

void func_800C1138(s32 a, void *b) {
    u8 m[0x40];
    s32 i;
    N *p;

    buildScaledRotationTranslationMatrix(m, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
    D_800E81F8 = 0;
    for (i = 0; i < 4; i++) {
        p = &D_800E7558[i];
        D_800E7558[i].fE8 = 0;
        D_800E7558[i].fE6 = 0;
        D_800E7558[i].fEA = 0;
        D_800E7558[i].fE4 = 0x100;
        initializeTransformNode(p, 0, 0.0f, 0.0f, 0.0f);
        p->fC = D_800D5758;
        p->f10 = D_800D5768;
        func_800015AC(p, 1);
        func_80001544(p);
        p->f0 = a;
        if (i < 3) {
            p->f8 = &D_800E7558[i + 1];
        } else {
            p->f8 = b;
        }
        func_80021C40(m, p->pad18 + 4, 0x40);
        *(f32 *)(p->f14 + 0x24) = 8192.0f;
    }
    D_800E81E4 = 0;
    D_800E79C4 = 0;
}
