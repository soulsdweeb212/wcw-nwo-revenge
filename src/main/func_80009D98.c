#include "common.h"

typedef struct 
{
  f32 a;
  f32 b;
  f32 c;
  f32 x;
  f32 y;
  f32 z;
  f32 da;
  f32 db;
  f32 dc;
  f32 tx;
  f32 ty;
  f32 tz;
  u8 pad30[0x4C];
} Part09D;
extern Part09D D_80070C40[][23];
extern s8 D_800307FC[];
extern f32 D_80030834[];
f32 func_80003CF0(f32);
inline static f32 wrap09D(f32 value)
{
  if (value >= 0.0)
  {
    while (value > 180.0)
      value -= 360.0;
  }
  else
  {
    while (value <= (-180.0))
      value += 360.0;
  }
  return value;
}

void func_80009D98(s16 arg0, s16 arg1, s32 flags)
{
  u32 i;
  Part09D *p;
  f32 t;
  if ((arg1 == 0) && (!(flags & 4)))
  {
    f32 x = D_80070C40[arg0][1].tx;
    f32 z = D_80070C40[arg0][1].tz;
    for (i = 1; i < 20; i++)
    {
      p = &D_80070C40[arg0][i];
      p->tx -= x;
      p->tz -= z;
    }
  }
  for (i = 1; i < 20; i++)
  {
    p = &D_80070C40[arg0][i];
    if (!D_800307FC[i])
    {
      p->x += (p->tx - p->x) * (*(&D_80030834[arg1]));
      p->y += (p->ty - p->y) * (*(&D_80030834[arg1]));
      p->z += (p->tz - p->z) * (*(&D_80030834[arg1]));
    }
    t = p->a;
    p->da = wrap09D(p->da - t);
    t = p->b;
    p->db = wrap09D(p->db - t);
    t = p->c;
    p->dc = wrap09D(p->dc - t);
    if ((func_80003CF0(p->da) > 110.0) && (func_80003CF0(p->dc) > 110.0))
    {
      p->da = wrap09D(p->da + 180.0f);
      p->dc = wrap09D(p->dc + 180.0f);
    }
    p->a += p->da * (*(&D_80030834[arg1]));
    p->b += p->db * (*(&D_80030834[arg1]));
    p->c += p->dc * (*(&D_80030834[arg1]));
  }
}
