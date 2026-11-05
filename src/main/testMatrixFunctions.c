/* @header
 * testMatrixFunctions  (originally func_80007BB8)
 * VRAM 0x80007BB8 | ROM 0x87B8 | size 0xD0
 * asm: asm/nonmatchings/main/testMatrixFunctions.s
 */
#include "common.h"

void guAlignF(void *, f32, f32, f32, f32);
void guRotateRPYF(void *, f32, f32, f32);
void guPositionF(void *, f32, f32, f32, f32, f32, f32, f32);
void guScaleF(void *, f32, f32, f32);
void guOrthoF(void *, f32, f32, f32, f32, f32, f32, f32);
/* Exercises the matrix builders on a single 4x4 float matrix: the identity-ish
 * rotation/translation calls and finally a 320x240 orthographic projection. */
void testMatrixFunctions(void) {
    f32 matrix[4][4];
    guAlignF(matrix,0.0f,0.0f,0.0f,0.0f);
    guRotateRPYF(matrix,0.0f,0.0f,0.0f);
    guPositionF(matrix,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f);
    guScaleF(matrix,0.0f,0.0f,0.0f);
    guOrthoF(matrix,-160.0f,160.0f,-120.0f,120.0f,100.0f,4000.0f,1.0f);
}
