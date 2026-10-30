/* @header
 * func_800A9D5C
 * VRAM 0x800A9D5C | ROM 0x9D1FC | size 0x534
 * asm: asm/nonmatchings/code_8009D7A0/func_800A9D5C.s
 */
#include "common.h"

typedef struct 
{
  u8 b0;
  u8 pad1[9];
  u16 state;
  u8 padC[0x14];
  u64 flags;
  u8 pad28[0x44];
  f32 vec[3];
  u8 pad78[0x2DB];
  s8 b353;
  s8 b354;
  s8 b355;
} Nw2E9D5C;
typedef struct 
{
  u8 pad0[2];
  s16 f2;
  s16 f4;
  u8 pad6[0xE];
  s16 f14;
  u8 pad16[8];
  s16 s1E;
  s16 f20;
  u8 pad22[0xC];
  s16 s2E;
  u8 pad30[2];
  u16 f32;
  u8 pad34[8];
  f32 f3C;
  u8 pad40[0x1C];
  u32 f5C;
} Nw2B9D5C;
typedef struct 
{
  u8 pad0[0x20];
  u64 flags;
  u8 pad28[0x44];
  f32 vec[3];
} Nw2G9D5C;
extern Nw2E9D5C *D_800FAF58;
extern Nw2B9D5C *D_800FABD0;
extern Nw2G9D5C *D_800F9B60;
extern s16 D_800F9D12[][0x1D8];
extern u8 D_800F9D30[];
extern u8 D_800F9D7C[];
extern s8 D_800FA063[];
s8 func_800D3B24(void *, void *, f32, s32);
s32 func_800D4148(void);
void func_800ADFB8(void);
void func_800AA290(void);
void func_800AA9A0(void);
void func_800AABA0(void);
void func_800AABF8(void);
void selectActionVariant(void);
void func_800A9D5C(void)
{
  if (D_800FAF58->flags & 1)
  {
    switch ((s16) D_800FAF58->state)
    {
      case 0x11:
      case 0x12:
      case 0x13:
      case 0x28:
      case 0x3B:
      case 0x3D:
      case 0x3F:
      case 0x4A:
      case 0x4C:
      case 0x4E:
      case 0x50:
      case 0x52:
      case 0x54:
      case 0x57:
        if ((!(D_800FABD0->f5C & 8)) && (D_800FABD0->f20 != ((s16) D_800FAF58->state)))
      {
        D_800FABD0->f20 = (s16) D_800FAF58->state;
        {
          u16 t = D_800FABD0->f32 - 1;
          D_800FABD0->f32 = t;
          if (((s16) t) < 0)
          {
            D_800FABD0->f5C |= 8;
            D_800FABD0->f32 = ((s16) func_800D4148()) % 8;
          }
        }
      }
        break;
      default:
        D_800FABD0->f20 = D_800FAF58->state;
        break;
    }

    if (D_800FABD0->f5C & 0x10)
    {
      if (!func_800D3B24(&D_800FAF58->vec[0], &D_800F9B60->vec[0], 300.0f, 0))
      {
        u64 gm = D_800F9B60->flags & 0x1C0ULL;
        if (!(D_800FAF58->flags & gm))
        {
          D_800FABD0->f5C &= ~0x18;
          return;
        }
      }
    }
    else
    {
      if (D_800FABD0->f5C & 8)
      {
        s16 k;
        s8 c = D_800FAF58->b0;
        k = (c & 1) ^ 1;
        if ((D_800FA063[k * 0x3B0] == c) && func_800D3B24(&D_800FAF58->vec[0], (void *) (D_800F9D7C + (k * 0x3B0)), 120.0f, 0))
        {
          D_800FAF58->b353 = k;
          D_800FABD0->f5C |= 0x10;
          return;
        }
        k |= 2;
        if ((D_800FA063[k * 0x3B0] == ((s8) D_800FAF58->b0)) && func_800D3B24(&D_800FAF58->vec[0], (void *) (D_800F9D7C + (k * 0x3B0)), 120.0f, 0))
        {
          D_800FAF58->b353 = k;
          D_800FABD0->f5C |= 0x10;
          return;
        }
      }
      func_800ADFB8();
      return;
    }
  }
  if (D_800FAF58->flags & 2)
  {
    if (!(D_800FAF58->flags & 0x20))
    {
      s16 i;
      for (i = 0; i < 4; i++)
      {
        u64 f;
        s32 off;
        if (i == ((s8) D_800FAF58->b0))
        {
          continue;
        }
        if (D_800F9D12[i][0] == (-1))
        {
          continue;
        }
        off = i * 0x3B0;
        f = *(u64 *)(D_800F9D30 + off);
        if (!(f & 2))
        {
          continue;
        }
        if (f & 0x20)
        {
          break;
        }
      }

      if (i == 4)
      {
        func_800ADFB8();
        return;
      }
    }
    if (D_800FAF58->b353 == D_800FAF58->b355)
    {
      if (D_800FAF58->flags & 0x20)
      {
        D_800FAF58->b353 = D_800FAF58->b355 ^ 1;
      }
      else
      {
        D_800FAF58->b353 = D_800FAF58->b0 ^ 1;
      }
    }
  }
  if (D_800FABD0->f14 == 1)
  {
    if (D_800FABD0->f5C & 0x1110000)
    {
      func_800AA290();
    }
    if (D_800FABD0->f5C & 0x20000)
    {
      func_800AA290();
    }
    if (D_800FABD0->f5C & 0x40000)
    {
      func_800AA9A0();
    }
    if (D_800FABD0->f5C & 0x200000)
    {
      func_800AABA0();
    }
    if (D_800FABD0->f5C & 0x80000)
    {
      func_800AABF8();
    }
    if (D_800FABD0->f5C & 0x400000)
    {
      selectActionVariant();
    }
    if (D_800FABD0->f5C & 0x800000)
    {
      selectActionVariant();
    }
  }
}
