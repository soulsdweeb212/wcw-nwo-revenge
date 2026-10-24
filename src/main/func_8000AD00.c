#include "common.h"

typedef struct { f32 v; u8 pad[0x78]; } Part;
typedef struct { Part p[23]; } Ent;
extern s16 D_800706AC[];
extern s32 D_8007BD38;
extern s16 D_8006E440;
extern u8 D_80030810[];
extern s8 D_80030828[];
extern f64 D_8003B198;
extern f64 D_8003B1A0;
extern f64 D_8003B1A8;
extern f64 D_8003B1B0;
extern s8 D_800485B0[][8];
extern s8 D_800485D0[][8];
extern Ent D_80070D10[];
extern Ent D_80070D18[];
extern Ent D_80070CB8[];
extern Ent D_80070C94[];
extern Ent D_80070C9C[];
void func_8000B248(s16, s16);
void playEntitySound(s16, s16);
s32 func_8000E4FC(s16, s32);
void setIndexedS16Pair(s16, s16, s16, s16);
void func_80010200(s16, s16, f32);
void func_8000AD00(s32 arg0, u16 arg1)
{
  s16 entity;
  u32 count;
  s32 idx;
  s32 off;
  u8 *s4;
  s32 a1;
  u32 a0;
  s32 s1;
  s32 sh;
  s32 bias;
  f32 ft0;
  f32 ft1;
  f32 fv0;
  u32 tq, tr, tu, tv;
  bias = -0x20004;
  count = 0;
  sh = arg0 << 16;
  entity = sh >> 16;
  idx = D_800706AC[entity * 126];
  off = (idx * 0x24) + bias;
  s4 = (((u8 *) D_8007BD38) + off) + 0x14;
  for (count = 0; count < 8; s4 += 2, count++)
  {
    a1 = s4[1];
    a0 = (u8) a1;
    if (a0 == 0) continue;
    if (s4[0] != ((s16) arg1)) continue;
    if (a0 < 0xBE)
    {
      if (D_8006E440 != 0) playEntitySound(sh >> 16, a1 | 0x100);
      continue;
    }
    if (a0 < 0xC8)
    {
      if (D_8006E440 != 0) playEntitySound(entity, func_8000E4FC(entity, a1 - 0xBE));
      continue;
    }
    a1 &= 0xFF;
    {
      s32 v1 = a1 - 0xC8;
      if (v1 < 0x14)
      {
        s16 val = (s8)D_80030810[v1];
        do
        {
          if (val > 0)
          {
            ft0 = D_80070D10[entity].p[0].v;
            ft1 = D_80070D18[entity].p[0].v;
            fv0 = -((double) ft1);
            if (ft1 <= ft0) { if (fv0 <= ft0) s1 = 1; else s1 = 2; }
            else if (fv0 <= ft0) s1 = 0; else s1 = 3;
            {
              s32 av = (s32) (((-D_80070CB8[entity].p[0].v) + D_8003B198) * D_8003B1A0);
              s32 a2 = av + 2;
              if (val == 9) s1 = av + 3;
              else if ((s1 & 1) != (a2 & 1))
              {
                if (s1 & 1) { if (ft1 >= 0.0f) s1 = 0; else s1 = 2; }
                else if (ft0 >= 0.0f) s1 = 1; else s1 = 3;
              }
            }
            {
              s32 m = (s16) s1;
              f32 fv0b;
              m %= 4;
              fv0b = ft0;
              if (m & 1) fv0b = ft1;
              func_80010200(val, (s16) m, fv0b);
            }
          }
        } while (0);
      }
      else
      {
        s16 t = (s16) (a1 - 0xDC);
        if (t >= 0x14)
        {
          func_8000B248(sh >> 16, (s8) D_80030810[t]);
          continue;
        }
        if ((t % 10) == 0)
        {
          if (t < 10)
          {
            func_8000B248(entity, 1);
            func_8000B248(entity, 2);
            func_8000B248(entity, 3);
          }
          else
          {
            func_8000B248(entity, 5);
            func_8000B248(entity, 6);
            func_8000B248(entity, 7);
          }
          continue;
        }
        else
        {
          s32 s2;
          s32 s0;
          s32 k;
          if (t < 10)
          {
            s2 = 2 - ((t - 1) % 3);
            s0 = ((s32) ((t - 1) * D_8003B1A8)) + 1;
          }
          else
          {
            s2 = 2 - ((t - 0xB) % 3);
            s0 = ((s32) ((t - 0xB) * D_8003B1B0)) + 5;
          }
          k = (s8) D_80030828[(s16) s0];
          ft0 = D_80070C94[entity].p[k].v;
          ft1 = D_80070C9C[entity].p[k].v;
          fv0 = -ft1;
          if (ft1 <= ft0) { if (fv0 <= ft0) s1 = 1; else s1 = 2; }
          else if (fv0 <= ft0) s1 = 0; else s1 = 3;
          setIndexedS16Pair(entity, s0, s1, s2);
          s0 <<= 16;
          s0 >>= 16;
          func_8000B248(entity, s0);
          D_800485B0[entity][s0] = s2;
          D_800485D0[entity][s0] = s1;
          tq = (u32)s4 & 1;
          tr = (u32)s4 & 2;
          tu = (u32)s4 & 4;
          tv = (u32)s4 & 8;
          if ((tq >> 1) | (tr >> 2) | (tu >> 3) | (tv >> 4)) D_8006E440 = 0;
        }
      }
    }
  }
}
