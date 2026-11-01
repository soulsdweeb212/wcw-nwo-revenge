/* @header
 * func_800B830C
 * VRAM 0x800B830C | ROM 0x64A7C | size 0x5C
 * asm: asm/nonmatchings/code_80090000/func_800B830C.s
 */
#include "common.h"

extern f32 D_800DC8B4, D_800DC8B8, D_800DC8BC;
void buildScaledRotationTranslationMatrix(void *, f32, f32, f32, f32, f32, f32, f32);

void func_800B830C(void *m) {
    buildScaledRotationTranslationMatrix(m, 0.0f, 0.0f, 0.0f, 1.0f, D_800DC8B4, D_800DC8B8, D_800DC8BC);
}
