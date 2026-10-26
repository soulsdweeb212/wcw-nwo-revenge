#include "common.h"

typedef struct 
{
  s8 id;
  u8 pad[3];
  f32 f4;
  s32 f8;
} TgtCandidate;
void collectLinkedTargets(void *, void *, void *, u64);
s32 func_800D3550(s32);
s32 func_800D3684(s32, s32);
s32 func_800D35B0(s32, s32);
void func_800D37C0(s32, f32, void *);
f32 func_800D3EEC(void *, void *, s32);
void translateEntityXZ(void *, void *);
extern const f64 D_800E6B28;
extern const f64 D_800E6B30;
extern u8 D_800F9D30[];
extern u8 D_800F9D5C[];
extern u8 D_800F9D68[];
s8 func_800D2758(u8 *arg0, f32 arg1, u16 arg2, s8 arg3, s16 arg4)
{
  f32 vec[4];
  TgtCandidate buf[4];
  s8 s5;
  s16 s1;
  f32 fs0;
  s8 id;
  s32 off;
  if (!arg2)
  {
    arg2 = 0xF00;
  }
  collectLinkedTargets(arg0, arg0 + 0x6C, buf, (*((u64 *) (arg0 + 0x20))) & 0x1C0ULL);
  s5 = -1;
  for (s1 = 0; s1 < 4; s1++)
  {
    id = buf[s1].id;
    if (id == (-1))
    {
      continue;
    }
    if (id == arg3)
    {
      continue;
    }
    off = id * 0x3B0;
    fs0 = -1.0f;
    if ((*((u64 *) (D_800F9D30 + off))) & 0x400000ULL)
    {
      f32 r = func_800D3EEC(D_800F9D5C + off, arg0 + 0x6C, *((s32 *) (D_800F9D68 + off)));
      f64 k = D_800E6B28;
      f32 t = buf[s1].f4;
      f64 d = r + k;
      if (((f64) t) <= d)
      {
        fs0 = (f32) (d - ((f64) t));
      }
    }
    else
    {
      off = s1;
      if (((f64) buf[off].f4) <= 100.0)
      {
        fs0 = (f32) (100.0 - ((f64) buf[s1].f4));
      }
    }
    if (((f64) fs0) == D_800E6B30)
    {
      continue;
    }
    if (arg4 != 0)
    {
      s32 a0;
      if (func_800D3550(func_800D3684(*((s32 *) (arg0 + 0x58)), buf[s1].f8)) < 0x200)
      {
        a0 = *((s32 *) (arg0 + 0x58));
      }
      else
      {
        a0 = buf[s1].f8;
      }
      if (arg4 == 2)
      {
        s32 off2 = buf[s1].id * 0x3B0;
        if ((*((u64 *) (D_800F9D30 + off2))) & 0x200ULL)
        {
          a0 = buf[s1].f8;
        }
        else
        {
          a0 = func_800D35B0(buf[s1].f8, -0x200);
        }
      }
      func_800D37C0(func_800D35B0(a0, 0x800), fs0, vec);
      if (arg2 & 0x300)
      {
        vec[0] /= arg1;
      }
      else
      {
        vec[0] = 0.0f;
      }
      if (arg2 & 0xC00)
      {
        vec[2] /= arg1;
      }
      else
      {
        vec[2] = 0.0f;
      }
      translateEntityXZ(arg0, vec);
    }
    if (s5 == (-1))
    {
      s5 = buf[s1].id;
    }
  }

  return s5;
}
