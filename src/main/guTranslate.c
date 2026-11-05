/* @header
 * guTranslate  (originally func_8001C144)
 * VRAM 0x8001C144 | ROM 0x1CD44 | size 0x70
 * asm: asm/nonmatchings/main/guTranslate.s
 */
/* SDK: libultra 2.0I, ultralib src/gu/translate.c (same code as the SDK source). */
#include "common.h"

extern u32 D_80037230;

typedef struct {
    f32 m[12];
    f32 x, y, z;
} Xform;

void guMtxF2L(void *, void *);

/* Builds a translation matrix (arg1/arg2/arg3) and converts it to fixed point
 * at arg0. */
void guTranslate(void *arg0, f32 arg1, f32 arg2, f32 arg3) {
    Xform s;
    Xform *p = &s;

    guMtxIdentF(p);
    p->x = arg1;
    p->y = arg2;
    p->z = arg3;
    guMtxF2L(p, arg0);
}
