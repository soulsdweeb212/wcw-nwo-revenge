/* @header
 * func_80001EA8
 * VRAM 0x80001EA8 | ROM 0x2AA8 | size 0x268
 * asm: asm/nonmatchings/main/func_80001EA8.s
 */
#include "common.h"

extern void *D_80046860[];
extern s16 D_80047062;
extern f32 D_80048288[][4];
f32 nw2Sqrtf(f32);
void func_8001B3EC(void *, s32, s32, s32, void *, void *, void *);
void func_80001EA8(s32 arg0)
{
  volatile u64 pad;
  u32 s1;
  u32 k;
  void *s0;
  void *a0p;
  u32 t4;
  u32 j;
  f32 (*src)[4];
  f32 (*dst)[4];
  f32 (*mm)[4];
  f32 sum;
  void **a1;
  s16 cnt;
  s1 = 0;
  if (D_80047062 != 0)
  {
    do
    {
      s0 = D_80046860[s1];
      ((f32 *) s0)[0xA] = ((f32 *) s0)[9] * 1024.0f;
      a0p = *((void **) (((u8 *) s0) + 4));
      t4 = 0;
      if ((*((u8 *) (((u8 *) a0p) + 0x19))) == 0)
      {
        mm = D_80048288;
        src = (f32 (*)[4]) (((u8 *) a0p) + 0x5C);
        dst = (f32 (*)[4]) (((u8 *) a0p) + 0x9C);
        for (t4 = 0; t4 < 4; t4++)
        {
          for (j = 0; j < 4; j++)
          {
            sum = 0.0f;
            for (k = 0; k < 4; k++)
            {
              sum += src[t4][k] * mm[k][j];
            }

            dst[t4][j] = sum;
          }

        }

        func_8001B3EC(((u8 *) a0p) + 0x9C, *((s32 *) (((u8 *) s0) + 0xC)), *((s32 *) (((u8 *) s0) + 0x10)), *((s32 *) (((u8 *) s0) + 0x14)), ((u8 *) s0) + 0x18, ((u8 *) s0) + 0x1C, ((u8 *) s0) + 0x20);
        ((f32 *) s0)[0xA] = ((f32 *) s0)[0xA] + (((f32 *) s0)[8] * 1024.0f);
        ((f32 *) s0)[0xA] = ((f32 *) s0)[0xA] + nw2Sqrtf((((f32 *) s0)[6] * ((f32 *) s0)[6]) + (((f32 *) s0)[7] * ((f32 *) s0)[7]));
      }
      s1 += 1;
    }
    while (s1 < ((u32) D_80047062));
  }
  s1 = 1;
  if (((s16) arg0) != 0)
  {
    u32 v0;
    cnt = D_80047062;
    a1 = D_80046860;
    for (; s1 < cnt; s1++)
    {
      s0 = a1[s1];
      for (v0 = s1; v0 != 0; v0--)
      {
        void *v1p = a1[v0 - 1];
        if (!(((f32 *) v1p)[10] < ((f32 *) s0)[10]))
        {
          break;
        }
        a1[v0] = v1p;
      }
      a1[v0] = s0;
    }
  }
  else
  {
    cnt = D_80047062;
    a1 = D_80046860;
    for (; s1 < cnt; s1++)
    {
      void *x = a1[s1 - 1];
      void *y = a1[s1];
      if (((f32 *) x)[10] < ((f32 *) y)[10])
      {
        a1[s1] = x;
        a1[s1 - 1] = y;
      }
    }
  }
}
