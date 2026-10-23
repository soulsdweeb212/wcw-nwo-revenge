#include "common.h"

/* atan2(arg1, arg0) approximation. Handles the arg0==0 axis case (0 or pi),
 * reduces arg1/arg0 into [-1,1] (tracking the sign for the octant), evaluates
 * a continued-fraction polynomial in the loop, then applies the sign- and
 * quadrant-specific constants D_8003B0C0/B0C8/B0D0 (arg0>=0) or
 * D_8003B0D8/B0E0/B0E8 (arg0<0). */
extern f64 D_8003B0C0;
extern f64 D_8003B0C8;
extern f64 D_8003B0D0;
extern f64 D_8003B0D8;
extern f64 D_8003B0E0;
extern f64 D_8003B0E8;
f32 func_80003A3C(f32 arg0, f32 arg1)
{
  s32 sign;
  s32 i;
  int j;
  f32 value;
  f32 t;
  f32 u;
  if (((f64) arg0) == 0.0)
  {
    if (((f64) arg1) >= 0.0)
    {
      return 0.0f;
    }
    return 3.1415927f;
  }
  if (((f64) arg0) >= 0.0)
  {
    arg0 = arg1 / arg0;
    if (arg0 > 1.0f)
    {
      sign = 1;
      arg0 = 1.0f / arg0;
    }
    else
      if (arg0 < (-1.0f))
    {
      sign = -1;
      arg0 = 1.0f / arg0;
    }
    else
    {
      sign = 0;
    }
    value = 0.0f;
    for (i = 8, j = 17; i > 0; j -= 2, i--)
    {
      value = (((i * i) * arg0) * arg0) / (j + value);
    }

    if (sign > 0)
    {
      t = D_8003B0C0 - (arg0 / (value + 1.0f));
    }
    else
      if (sign < 0)
    {
      t = D_8003B0C8 - (arg0 / (value + 1.0f));
    }
    else
    {
      t = arg0 / (value + 1.0f);
    }
    return D_8003B0D0 - t;
  }
  else
  {
    arg0 = arg1 / arg0;
    i = -1;
    if (arg0 > 1.0f)
    {
      sign = 1;
      arg0 = 1.0f / arg0;
    }
    else
      if (arg0 < (-1.0f))
    {
      sign = i;
      arg0 = 1.0f / arg0;
    }
    else
    {
      sign = 0;
    }
    value = 0.0f;
    for (i = 8, j = 17; i > 0; j -= 2, i--)
    {
      value = (((i * i) * arg0) * arg0) / (j + value);
    }

    if (sign > 0)
    {
      u = D_8003B0D8 - (arg0 / (value + 1.0f));
    }
    else
      if (sign < 0)
    {
      u = D_8003B0E0 - (arg0 / (value + 1.0f));
    }
    else
    {
      u = arg0 / (value + 1.0f);
    }
    return -(u + D_8003B0E8);
  }
}
