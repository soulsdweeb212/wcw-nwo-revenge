/* @header
 * func_8001A65C
 * VRAM 0x8001A65C | ROM 0x1B25C | size 0x1D4
 * asm: asm/nonmatchings/main/func_8001A65C.s
 */
#include "common.h"

f32 cosf(f32);
f32 sinf(f32);
f32 sqrtf(f32);
f32 nw2Sqrtf(f32);
void func_8001B4A0(f32 *, f32 *, f32 *);
extern f32 D_80037200;
void initIdentityMatrix4x4(void *);
void func_8001B090(void *, void *);
void func_8001A65C(void *out, f32 ang, f32 x, f32 y, f32 z)
{
  f32 m[16];
  float new_var;
  f32 pad[2];
  f32 *mp;
  f32 sx;
  f32 sz;
  f32 sy;
  f32 L;
  f32 sinV;
  f32 cosV;
  f32 invL;
  mp = m;
  sx = x;
  sy = y;
  sz = z;
  func_8001B4A0(&sx, &sy, &sz);
  ang *= D_80037200;
  sinV = sinf(ang);
  cosV = cosf(ang);
  L = sqrtf((sx * sx) + (sz * sz));
  initIdentityMatrix4x4(mp);
  if (L != 0.0f)
  {
    invL = 1.0f / L;
    m[0] = (((-sz) * cosV) - ((sinV * sy) * sx)) * invL;
    m[4] = ((sz * sinV) - ((cosV * sy) * sx)) * invL;
    m[8] = -sx;
    new_var = 0.0f;
    m[12] = 0.0f;
    m[1] = sinV * L;
    m[5] = cosV * L;
    m[9] = -sy;
    m[13] = 0.0f;
    m[2] = ((cosV * sx) - ((sinV * sy) * sz)) * invL;
    m[6] = (((-sinV) * sx) - ((cosV * sy) * sz)) * invL;
    m[10] = -sz;
    m[14] = 0.0f;
    m[3] = 0.0f;
    m[7] = new_var;
    m[11] = 0.0f;
    m[15] = 1.0f;
  }
  func_8001B090(mp, out);
}
