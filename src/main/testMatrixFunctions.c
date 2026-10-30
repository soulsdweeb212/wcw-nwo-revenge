/* @header
 * testMatrixFunctions  (originally func_80007BB8)
 * VRAM 0x80007BB8 | ROM 0x87B8 | size 0xD0
 * asm: asm/nonmatchings/main/func_80007BB8.s
 */
#include "common.h"

void func_8001A490(void *, f32, f32, f32, f32);
void func_8001BB50(void *, f32, f32, f32);
void buildScaledRotationTranslationMatrix(void *, f32, f32, f32, f32, f32, f32, f32);
void func_8001BE70(void *, f32, f32, f32);
void buildOrthoMatrixFloat(void *, f32, f32, f32, f32, f32, f32, f32);
/* Exercises the matrix builders on a single 4x4 float matrix: the identity-ish
 * rotation/translation calls and finally a 320x240 orthographic projection. */
void testMatrixFunctions(void) {
 f32 matrix[4][4];
 func_8001A490(matrix,0.0f,0.0f,0.0f,0.0f);
 func_8001BB50(matrix,0.0f,0.0f,0.0f);
 buildScaledRotationTranslationMatrix(matrix,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f);
 func_8001BE70(matrix,0.0f,0.0f,0.0f);
 buildOrthoMatrixFloat(matrix,-160.0f,160.0f,-120.0f,120.0f,100.0f,4000.0f,1.0f);
}
