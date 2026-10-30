/* @header
 * func_800D3EEC
 * VRAM 0x800D3EEC | ROM 0xC738C | size 0x13C
 * asm: asm/nonmatchings/code_800BBA00/func_800D3EEC.s
 */
#include "common.h"

f32 cosf(f32);
f32 sinf(f32);
f32 nw2Sqrtf(f32);
extern f64 D_800E6BD8;
extern f64 D_800E6BE0;
extern f64 D_800E6BE8;
extern f64 D_800E6BF0;
extern f64 D_800E6BF8;
typedef union 
{
  f32 f;
  s32 i;
} NwFI;
typedef struct 
{
  NwFI e[4];
} NwV4;
/* Ellipse boundary distance: rotate the XZ delta from arg0 to arg1 by the
 * heading arg2, then evaluate a rotated-ellipse distance using the f64 shape
 * constants (D_800E6BE0/E8/F0/F8); angle scaling constant D_800E6BD8. */
f32 func_800D3EEC(void *arg0, void *arg1, s32 arg2)
{
  f32 *from = arg0;
  f32 *to = arg1;
  NwFI bound[4];
  NwFI delta[4];
  NwFI center[4];
  f32 ang;
  f32 cosA;
  f32 sinA;
  f32 ratio;
  f32 shape;
  s32 heading;
  delta[0].f = to[0] - from[0];
 do { delta[2].f = to[2] - from[2]; delta[1].f = to[1] - from[1]; heading = -arg2; if (heading >= 0) { arg2 = heading; } if (arg2 >= 0x801) { if (heading < 0) { heading += 0x1000; } else { heading -= 0x1000; } } } while (0);
  center[0].f = 0.0f;
  center[2].f = 0.0f;
  ang = (f32) (((f64) heading) * D_800E6BD8);
  cosA = cosf(ang);
  sinA = sinf(ang);
  {
    f32 q0 = delta[0].f * sinA;
    f32 q1 = delta[2].f * cosA;
    f32 q2 = delta[0].f * cosA;
    f32 q3 = delta[2].f * sinA;
    bound[0].f = center[0].f + (q2 + q3);
    bound[2].f = center[2].f + (q1 - q0);
  }
  ratio = bound[2].f / bound[0].f;
  shape = (f32) (D_800E6BE8 / (((f64) (ratio * ratio)) + D_800E6BE0));
  return nw2Sqrtf(shape + ((f32) ((D_800E6BF8 - (((f64) shape) * D_800E6BF0)) * D_800E6BE8)));
}
