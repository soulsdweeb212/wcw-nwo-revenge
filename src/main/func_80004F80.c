/* @header
 * func_80004F80
 * VRAM 0x80004F80 | ROM 0x5B80 | size 0x40
 * asm: asm/nonmatchings/main/func_80004F80.s
 */
#include "common.h"

void func_80004E08(void *, s16, s16);
void buildCiTextureDisplayList(void *, s32);

/* Build the CI-texture node at the given size. */
void func_80004F80(void *arg0, s16 arg1, s16 arg2) {
    func_80004E08(arg0, arg1, arg2);
    buildCiTextureDisplayList(arg0, 0);
}

void initializeTransformNode(void *, s8, s32, f32, f32);

s32 func_80014140(s32, s16, s16, s16, s16, s16);
extern s32 D_800482D4;

extern s32 D_80147000;
extern s32 D_8017F400;
extern s32 D_801B7800;
