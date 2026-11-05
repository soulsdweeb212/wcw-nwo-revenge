/* @header
 * guTranslateF  (originally func_8001C0F0)
 * VRAM 0x8001C0F0 | ROM 0x1CCF0 | size 0x54
 * asm: asm/nonmatchings/main/guTranslateF.s
 */
/* SDK: libultra 2.0I, ultralib src/gu/translate.c (same code as the SDK source). */
#include "common.h"

extern u32 D_80037230;

typedef struct {
    f32 m[12];
    f32 x, y, z;
} Xform;

void guMtxF2L(void *, void *);
s32 __osDisableInt(void);
void __osRestoreInt(s32);

typedef struct {
    s32 f0;
    s32 f4;
} Tbl;

extern Tbl D_8007DF30[];

/* Initialize arg0 as an identity matrix translated to (arg1,arg2,arg3). */
void guTranslateF(void *arg0, f32 arg1, f32 arg2, f32 arg3) {
    Xform *s = arg0;
    guMtxIdentF(arg0);
    s->x = arg1;
    s->y = arg2;
    s->z = arg3;
}
