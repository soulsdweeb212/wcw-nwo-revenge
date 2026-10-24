#include "common.h"

extern u8 D_800F9D10[];
extern u8 D_800F9D12[];
extern u8 D_800F9D1A[];
extern u8 D_800F9D1C[];
extern u8 D_800F9D20[];
extern u8 D_800F9D22[];
extern u8 D_800F9D24[];
extern u8 D_800F9D28[];
extern u8 D_800F9D47[];
extern u8 D_800F9D53[];
extern u8 D_800F9D60[];
extern u8 D_800FA05C[];
extern u8 D_800FA05D[];
extern u8 D_800FA05E[];
extern u8 D_800FA05F[];
extern u8 D_800FA060[];
extern u8 D_800FA062[];
extern s8 D_800FA064[];
extern s8 D_800FA072[];
extern s8 D_800FA073[];
extern u8 D_800FA074[];
extern u8 D_800FADB9[];
extern u16 D_800FADD2[];
extern u16 D_800F9B80[];
extern u16 D_800F9B68[];
extern u16 D_800FADC6[];
extern u16 D_800F9B78[];
extern u8 D_8007E228[];
extern u8 D_80070494[];
extern u8 D_8007EF30[];
void func_800BF548(void *, s16);
void updateEntityStunTimer(void *, s32, s32);
void func_800C2B20(s8);
void func_800A97A0(s32);
void func_800D9234(s32);
void func_800BF254(s32);
void func_800D43B4(void *, s32, s32);
void func_800BA770(s8 arg0, s16 arg1, s32 arg2)
{
  s32 a1off;
  s32 base;
  s32 base2;
  s32 key;
  u8 *ent;
  s8 idx;
  u8 *p;
  s32 off;
  key = arg2 << 16;
  idx = arg0;
  base = idx * 0x3B0;
  D_800F9D10[base] = arg0;
  *((u16 *) (D_800F9D24 + base)) = 0x32;
  *((u16 *) (D_800F9D12 + base)) = arg1;
  D_800F9D53[base] = 0;
  *((u16 *) (D_800F9D28 + base)) = 0;
  D_800FA061[base] = 0;
  D_800FA062[base] = 0;
  D_800FA072[base] = -1;
  D_800FA073[base] = -1;
  D_800FA064[base] = -1;
  D_800F9D47[base] = 0;
  *((f32 *) (D_800F9D60 + base)) = 90.0f;
  do
  {
  }
  while (0);
  if (key == 0)
  {
    s32 v1 = idx * 8;
    *((u16 *) (D_800F9D1A + base)) = 0;
    *((u16 *) (D_800F9D1C + base)) = 0;
    *((u16 *) (D_800F9D22 + base)) = D_8007E228[v1 + 0x60];
    *((u16 *) (D_800F9D20 + base)) = D_8007E228[v1 + 0x60];
    D_800FA05C[base] = D_8007E228[v1 + 0x61];
    D_800FA05D[base] = D_8007E228[v1 + 0x64];
    D_800FA05E[base] = D_8007E228[v1 + 0x62];
    D_800FA05F[base] = D_8007E228[v1 + 0x63];
    D_800FA060[base] = D_8007E228[v1 + 0x65];
    D_800FADB9[idx] = D_8007E228[v1 + 0x67];
  }
  else
  {
    *((u16 *) (D_800F9D22 + base)) = 0xFF;
    *((u16 *) (D_800F9D20 + base)) = 0xFF;
    D_800FA05C[base] = 0x32;
    D_800FA05D[base] = 0x32;
    D_800FA05E[base] = 0x32;
    D_800FA05F[base] = 0x32;
    D_800FA060[base] = 0x32;
    D_800FADB9[idx] = 0;
    do
    {
      *((u64 *) (D_800F9D30 + base)) &= 0x200000204ULL;
    }
    while (0);
  }
  idx = arg0;
  base2 = idx * 0x3B0;
  ent = D_800F9D10 + base2;
  *((u32 *) (D_800FA074 + base2)) = (u32) ((D_80070494 + 0x10C) + (idx << 6));
  D_800FADD2[idx] = 0;
  D_800F9B80[idx] = 0;
  D_800F9B68[idx] = 0;
  D_800FADC6[idx] = 0;
  D_800F9B78[idx] = 0x1E;
  func_800BF548(ent, 0);
  updateEntityStunTimer(ent, 0, 0);
  func_800C2B20(idx);
  func_800A97A0(idx);
  func_800D9234(idx);
  func_800BF254(idx);
  func_800D43B4(ent, 0xE39, 0);
  p = *((u8 **) (D_800FA074 + base2));
  if ((*((u64 *) (p + 0x38))) & 0x20000000000ULL)
  {
    *((u64 *) (D_800F9D30 + base2)) |= 1ULL;
  }
  base2 = (a1off = ((s8) arg0) * 0x3B0);
  p = *((u8 **) (D_800FA074 + base2));
  if ((*((u64 *) (p + 0x38))) & 2ULL)
  {
    *((u64 *) (D_800F9D30 + base2)) |= 8ULL;
  }
  arg1 = 0;
  a1off = ((s8) arg0) * 0x2B8;
  off = a1off;
  do
  {
    s32 o = (arg1 * 8) + off;
    *((u32 *) ((D_8007EF30 + 0x1B0) + o)) = 0;
    *((u32 *) ((D_8007EF30 + 0x1B4) + o)) = 0;
    arg1 += 1;
  }
  while (arg1 < 0x57);
}
