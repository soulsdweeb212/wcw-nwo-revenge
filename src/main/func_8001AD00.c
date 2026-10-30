/* @header
 * func_8001AD00
 * VRAM 0x8001AD00 | ROM 0x1B900 | size 0x384
 * asm: asm/nonmatchings/main/func_8001AD00.s
 */
#include "common.h"

f32 sqrtf(f32);
void func_8001B090(f32 mf[4][4], void *m);
inline static void guLookAtF(f32 mf[4][4], f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp, f32 yUp, f32 zUp)
{
  f32 len;
  f32 xLook;
  f32 yLook;
  f32 zLook;
  f32 xRight;
  f32 yRight;
  f32 zRight;
  initIdentityMatrix4x4(mf);
  xLook = xAt - xEye;
  yLook = yAt - yEye;
  zLook = zAt - zEye;
  len = (-1.0) / sqrtf(((xLook * xLook) + (yLook * yLook)) + (zLook * zLook));
  xLook *= len;
  yLook *= len;
  zLook *= len;
  xRight = (yUp * zLook) - (zUp * yLook);
  yRight = (zUp * xLook) - (xUp * zLook);
  zRight = (xUp * yLook) - (yUp * xLook);
  len = 1.0 / sqrtf(((xRight * xRight) + (yRight * yRight)) + (zRight * zRight));
  xRight *= len;
  yRight *= len;
  zRight *= len;
  xUp = (yLook * zRight) - (zLook * yRight);
  yUp = (zLook * xRight) - (xLook * zRight);
  zUp = (xLook * yRight) - (yLook * xRight);
  len = 1.0 / sqrtf(((xUp * xUp) + (yUp * yUp)) + (zUp * zUp));
  xUp *= len;
  yUp *= len;
  zUp *= len;
  mf[0][0] = xRight;
  mf[1][0] = yRight;
  mf[2][0] = zRight;
  mf[3][0] = -(((xEye * xRight) + (yEye * yRight)) + (zEye * zRight));
  mf[0][1] = xUp;
  mf[1][1] = yUp;
  mf[2][1] = zUp;
  mf[3][1] = -(((xEye * xUp) + (yEye * yUp)) + (zEye * zUp));
  mf[0][2] = xLook;
  mf[1][2] = yLook;
  mf[2][2] = zLook;
  mf[3][2] = -(((xEye * xLook) + (yEye * yLook)) + (zEye * zLook));
  mf[0][3] = 0;
  mf[1][3] = 0;
  mf[2][3] = 0;
  mf[3][3] = 1;
}

void func_8001AD00(void *m, f32 xEye, f32 yEye, f32 zEye, f32 xAt, f32 yAt, f32 zAt, f32 xUp, f32 yUp, f32 zUp)
{
  f32 mf[4][4];
  f32 new_var;
  new_var = xEye;
  guLookAtF(mf, new_var, yEye, zEye, xAt, yAt, zAt, xUp, yUp, zUp);
  func_8001B090(mf, m);
}
