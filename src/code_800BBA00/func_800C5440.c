/* @header
 * func_800C5440
 * VRAM 0x800C5440 | ROM 0xB88E0 | size 0x5E8
 * asm: asm/nonmatchings/code_800BBA00/func_800C5440.s
 */
#include "common.h"

typedef struct 
{
  u8 p0[4];
  s16 f4;
  s16 f6;
  s16 f8;
  s16 fA;
  s16 fC;
  u8 pE[0x12];
  u64 flags;
  u8 p28[0x30];
  s32 f58;
  u8 p5C[0x315];
  u8 f371;
} E5440;
extern E5440 *D_800FAF5C;
extern E5440 *D_800F9B00;
extern s8 D_800FADB8;
extern s16 D_800F9B70[];
extern u16 D_800FAF8E[];
extern u16 D_800FABE6;
extern f32 D_800F9B0C;
extern s32 D_800F9B14;
extern s32 D_800E3F20[];
extern s32 D_800FABD8;
extern u8 D_800F9D10[];
void func_800D6658(void *, void *, u16, s32, f32);
void func_800A7240(void *, s32, s32, u64);
s8 func_800C7870(void *, void *, f32);
void func_800A7C40(void *, s8, s16);
s16 func_800D5438(void *, s32);
void func_800D427C(void *, s16, s32);
void func_800A7F6C(void *, s32);
s8 func_800C2CDC(void *, s32);
void func_800C3A78(void *, void *, s32);
void func_800D25D0(void *, f32);
void func_800D2B64(void *, f32, s32, s32);
void func_800A7188(void *);
void func_800C5440(void)
{
  E5440 *e = D_800FAF5C;
  s16 a;
  s32 m;
  s8 r;
  f32 two;
  E5440 *o;
  switch (e->fC)
  {
    case 0:
      D_800F9B70[D_800FADB8] = 0;
      D_800FAF8E[D_800FADB8] = 0;
      e->fC++;

    case 1:
      if ((D_800FAF5C->flags & 0x20000000000ULL) && (D_800FAF5C->f4 <= 0))
    {
      D_800FAF5C->flags &= ~0x20000000000ULL;
    }
      if (!(D_800FAF5C->flags & 0x20000000000ULL))
    {
      s32 t;
      func_800D6658(D_800FAF5C, D_800F9B00, D_800FABE6, 0, D_800F9B0C);
      t = D_800F9B14;
      func_800A7240(D_800FAF5C, t, 0x155, 0x100000000ULL);
    }
      D_800FAF8E[D_800FADB8] |= D_800FABE6 & 0xF00;
      m = (D_800FAF5C->flags & 0x100000000000000ULL) ? (0x8000) : (0x4000);
      if (m & D_800FABE6)
    {
      if ((++D_800F9B70[D_800FADB8]) >= 8)
      {
        if (D_800FAF5C->flags & 0x1000000000000ULL)
        {
          func_800A6C48(D_800FAF5C, 0x23);
        }
        else
        {
          func_800A6C48(D_800FAF5C, 0x1F);
        }
      }
      break;
    }
      if (D_800FAF5C->flags & 0x1000000000000ULL)
    {
      func_800A6C48(D_800FAF5C, 0x22);
      break;
    }
      if ((D_800F9B00->flags & 0x100000ULL) && (((D_800FAF5C->flags & D_800F9B00->flags) & 0x40) || ((D_800FAF5C->flags & D_800F9B00->flags) & 0x100)))
    {
      if (func_800D3550(func_800D3684(D_800FAF5C->f58, D_800F9B00->f58)) > 0x600)
      {
        func_800A6C48(D_800FAF5C, 0x20);
        break;
      }
    }
      if (func_800C7870(D_800FAF5C, D_800F9B00, D_800F9B0C))
    {
      func_800A6C48(D_800FAF5C, 0x27);
      break;
    }
      if (D_800FAF5C->flags & 0x100000000000000ULL)
    {
      a = 0;
    }
    else
    {
      a = 0x93;
    }
      if (D_800F9B0C > 95.0)
    {
      a += 2;
    }
      if (D_800FAF8E[D_800FADB8] != 0)
    {
      a++;
    }
      func_800A7C40(D_800FAF5C, D_800FADB8, a);
      func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 0), 3);
      func_800A7F6C(D_800FAF5C, 0);
      D_800FAF5C->fC++;
      break;

    case 2:
      D_800FABD8 &= ~D_800E3F20[D_800FADB8];
      r = func_800C2CDC(e, 1);
      if (r != (-1))
    {
      D_800FAF5C->fC++;
      func_800C3A78(D_800FAF5C, D_800F9D10 + (r * 0x3B0), 1);
    }

    case 3:
      two = 2.0f;
      func_800D25D0(D_800FAF5C, two);
      o = D_800FAF5C;
      if (o->flags & 0x100ULL) {
        func_800D2B64(o, two, 0, 0xFFFFE);
      } else {
        switch ((s16)(o->fA - 7)) {
        case 15:
          if (o->f6 > o->f371) {
            func_800D2B64(o, 2.0f, 0, 0xE);
          }
          break;
        case 0: case 24: case 25: case 26: case 29: case 30: case 31: case 78: case 79:
          if (o->f6 > o->f371) {
            func_800D2B64(o, 4.0f, 0, 0xFFFFE);
          } else {
            func_800D2B64(o, 2.0f, 0, 0xE);
          }
          break;
        case 1: case 23: case 27: case 28: case 32:
          func_800D2B64(D_800FAF5C, 2.0f, 0, 0xE);
          break;
        }
      }
      func_800A7188(D_800FAF5C);
      break;
  }
}
