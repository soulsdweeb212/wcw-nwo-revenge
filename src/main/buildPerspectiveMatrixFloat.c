/* @header
 * buildPerspectiveMatrixFloat  (originally func_8001B7D0)
 * VRAM 0x8001B7D0 | ROM 0x1C3D0 | size 0x1B0
 * asm: asm/nonmatchings/main/buildPerspectiveMatrixFloat.s
 */
#include "common.h"

/* Build a float 4x4 perspective projection matrix (OpenGL-style) for the given
 * field of view (degrees, scaled by D_8003B5B0), aspect, near and far planes,
 * pre-scaled by `scale`; also returns the 16-bit perspective-normalisation
 * factor in *perspNorm (0xFFFF / 1 / clamped). */
f32 cosf(f32); f32 sinf(f32);
extern const f64 D_8003B5B0,D_8003B5B8,D_8003B5C0;
void buildPerspectiveMatrixFloat(f32 mf[4][4],u16 *perspNorm,f32 fovy,f32 aspect,f32 near,f32 far,f32 scale) {
 f32 cot; s32 row,col;
 initIdentityMatrix4x4(mf);
 fovy *= D_8003B5B0;
 cot=cosf(fovy/2.0f)/sinf(fovy/2.0f);
 mf[0][0]=cot/aspect; mf[1][1]=cot;
 mf[2][2]=(near+far)/(near-far);
 mf[2][3]=-1.0f;
 mf[3][2]=(2*near*far)/(near-far);
 mf[3][3]=0;
 for(row=0;row<4;row++) for(col=0;col<4;col++) mf[row][col]*=scale;
 if(perspNorm) {
 if(near+far<=D_8003B5B8) *perspNorm=0xFFFF;
 else { *perspNorm=(u16)(D_8003B5C0/(near+far)); if(*perspNorm==0) *perspNorm=1; }
 }
}
