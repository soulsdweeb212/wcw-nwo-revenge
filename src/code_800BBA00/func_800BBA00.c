/* @header
 * func_800BBA00
 * VRAM 0x800BBA00 | ROM 0xAEEA0 | size 0x5D8
 * asm: asm/nonmatchings/code_800BBA00/func_800BBA00.s
 */
#include "common.h"

typedef struct {
  u8 p0[0x10];
  u64 flags;
  u8 p18[0x32B];
  u8 f343;
  u8 p344[0xE];
  s8 links[2];
  u8 p354[0x5C];
} RecBBA00;
extern RecBBA00 D_800F9D20[];
extern u8 D_800F9D10[];
extern u8 D_8006A2A0[];
extern u8 D_800EB466;
extern u8 D_800FABE4;
extern s8 D_800FADB8;
void func_800BBFD8(void);
void func_800D43DC(void);
void func_800D54A0(void);
void updateFieldRecordMotion(void);
void updatePlayerEntryStates(void);
void func_800A712C(void *, void *, s32 *, f32 *);
void func_800A7240(void *, s32, s32, u64);
void func_800BBA00(void)
{
  s16 i;
  s16 k;
  s16 seq;
  s32 angle[2];
  s32 o;
  u32 tq;
  for (i = 0; i < 4; i++)
  {
    o = i;
    if (D_800F9D20[o].flags & 0x40000000ULL)
    {
      tq = (u32)o & 1;
      if (tq >> 1)
      {
        D_800FADB8 = 0;
      }
      if (D_800F9D20[o].links[0] != (-1))
      {
        for (k = 0; k < 4; k++)
        {
          ;
        }
      }
    }
  }

  func_800D49A0();
  seq = (s8) D_800EB466;
  D_800F9D20[0].flags &= ~0x20000000ULL;
  D_800F9D20[1].flags &= ~0x20000000ULL;
  D_800F9D20[2].flags &= ~0x20000000ULL;
  D_800F9D20[3].flags &= ~0x20000000ULL;
  do
  {
    if ((D_800F9D20[seq].flags & 0x40000000ULL) && (!(D_800F9D20[seq].flags & 0x20000000ULL)))
    {
      D_800FADB8 = seq;
      D_800FABE4 = D_800F9D20[seq].f343;
      func_800BBFD8();
      for (i = 0; i < 2; i++)
      {
        s8 link = D_800F9D20[seq].links[i];
        if (!(D_800F9D20[link].flags & 0x20000000ULL))
        {
          D_800FADB8 = link;
          D_800FABE4 = D_800F9D20[D_800F9D20[seq].links[i]].f343;
          if (link != (-1))
          {
            func_800BBFD8();
          }
        }
      }
    }
    seq = (seq + 1) & 3;
  }
  while (seq != ((s8) D_800EB466));
  seq = (s8) D_800EB466;
  do
  {
    if (!(D_800F9D20[seq].flags & 0x20000000ULL))
    {
      D_800FADB8 = seq;
      D_800FABE4 = D_800F9D20[seq].f343;
      func_800BBFD8();
    }
    seq = (seq + 1) & 3;
  }
  while (seq != ((s8) D_800EB466));
  seq = (s8) D_800EB466;
  do
  {
    if (D_800F9D20[seq].flags & 0x10000000ULL)
    {
      D_800FADB8 = seq;
      D_800FABE4 = D_800F9D20[seq].f343;
      func_800BBFD8();
    }
    seq = (seq + 1) & 3;
  }
  while (seq != (*((s8 *) (&D_800EB466))));
  seq = 0;
  for (; seq < 4; seq++)
  {
    o = ((s32) seq) * 944;
    if (D_800F9D20[seq].flags & 0x100000000ULL)
    {
      s8 v = (s8)D_800F9D20[seq].f343;
      func_800A712C(D_800F9D10 + o, D_800F9D10 + (((s32) v) * 944), angle, NULL);
      do
      {
      }
      while (0);
      func_800A7240(D_800F9D10 + o, angle[0], 0x155, 0ULL);
    }
  }

  D_800EB466 = (D_800EB466 + 1) & 3;
  i = 0;
  updateFieldRecordMotion();
  updatePlayerEntryStates();
  for (; i < 4; i++)
  {
    if (D_800F9D20[i].flags & 4)
    {
      D_8006A2A0[i] = 0;
    }
    else
    {
      D_8006A2A0[i] = 1;
    }
  }

  func_800D43DC();
  func_800D54A0();
}
