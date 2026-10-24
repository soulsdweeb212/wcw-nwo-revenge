#include "common.h"

extern s8 D_80036D18[];
extern s8 D_80036D1C[];
extern u8 D_80036D2C[];
extern f32 D_8005A1A4[];
extern f32 D_8005A1A8[];
extern f32 D_8005A1AC[];
typedef struct 
{
  f32 *e[6];
  s16 v[8];
} Tab;
extern Tab D_8005A100[];
void func_8000F710(u8 *arg0, s32 side)
{
  u8 *out = arg0;
  s16 row = 0;
  u32 j;
  u32 k;
  s32 off;
  s32 base;
  f32 lo;
  f32 hi;
  f32 z;
  f32 x;
  f32 y;
  f32 a;
  f32 b;
  f32 x2;
  f32 w;
  u16 h;
  s16 h2;
  u16 *p;
  s32 *r;
  f32 *ep;
  u8 *tb;
  s32 q;
  s32 c;
  base = side * 120;
  lo = -224.0f;
  hi = 224.0f;
  loop:
  y = (f32) ((row * 74) - 224);

  j = 0;
  off = base;
  do
  {
    a = *((f32 *) (((u8 *) D_8005A1A4) + off));
    if (y < a)
    {
      b = y - lo;
      a = a - lo;
    }
    else
    {
      b = hi - y;
      a = hi - a;
    }
    z = b / a;
    x = (*((f32 *) (((u8 *) D_8005A1A8) + off))) * z;
    k = 0;
    w = (*((f32 *) (((u8 *) D_8005A1AC) + off))) * z;
    x2 = x + D_80036D2C[j];
    do
    {
      *((s16 *) (out + 2)) = (s32) (x2 + D_80036D18[k]);
      *((s16 *) (out + 4)) = (s32) (w + D_80036D1C[k]);
      out += 16;
      k++;
    }
    while (k < 4);
    z = w;
    j++;
    off += 40;
  }
  while (j < 3);
  D_8005A100[side].v[row] = (u32) z;
  row++;
  if (row < 7)
  {
    if (j || k)
    {
      goto loop;
    }
    else
    {
      goto loop;
    }
  }
  j = 0;
  base = (20 * side) * 2;
  tb = (u8 *) D_8005A100;
  q = (s32) (tb + 24);
  p = (u16 *) (q + base);
  out = tb + 26;
  r = (s32 *) (base + tb);
  loop2:
  h = *p;
  h2 = *((s16 *) (out + base));
  c = ((s16) (*p)) < h2;
  ep = (f32 *) (*r);
  if (c)
  {
 do { h = h2; } while (0);
  }
  ep += 5;
  *ep = (f32) ((s16) h);
  p++;
  out += 2;
  j++;
  r++;
  if (j < 6)
  {
    goto loop2;
  }
}
