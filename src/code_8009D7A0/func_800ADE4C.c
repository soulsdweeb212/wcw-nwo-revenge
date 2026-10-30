/* @header
 * func_800ADE4C
 * VRAM 0x800ADE4C | ROM 0xA12EC | size 0xF4
 * asm: asm/nonmatchings/code_8009D7A0/func_800ADE4C.s
 */
#include "common.h"

extern s16 *D_800FABD0;
extern f64 D_800E5198;
extern f64 D_800E51A0;
extern f64 D_800E51A8;
s16 func_800D4148(void);
f32 func_800ADE4C(f32 arg0, f32 arg1)
{
  f64 c = D_800E5198;
  f32 t;
  f32 u;
  f32 r;
  s16 v;
  t = arg0 * ((f32) (D_800E51A0 - (((f64) D_800FABD0[9]) * c)));
  u = arg0 * arg1;
  if (u < t)
  {
    t = u;
  }
  v = func_800D4148();
  r = (f32) ((((f64) arg0) + ((((f64) t) * c) * ((f64) v))) - (((f64) t) * D_800E51A8));
  if (((f64) r) < 0.0)
  {
    r = 0.0f;
  }
  arg0 = r;
  return arg0;
}
