/* @header
 * func_800DFDD4
 * VRAM 0x800DFDD4 | ROM 0xD3274 | size 0x2B4
 * asm: asm/nonmatchings/code_800DE9C0/func_800DFDD4.s
 */
#include "common.h"

extern u16 D_800E3CD0[];
extern u16 D_800E3CD8[];
s32 tryStartPairedEntityActions(u8 *, u8 *, u16, s32);
void func_800E212C(u8 *);
s32 func_800D23B4(u8 *, u8 *, u8 *);
s32 func_800DFDD4(u8 *arg0, u8 *arg1, s32 arg2, u8 *arg3)
{
  u16 m = arg2;
  s32 ret;
  *((u64 *) (arg0 + 0x20)) &= ~0x0000020000000000ULL;
  if (arg2 & 0x8000)
  {
    u64 f;
    *((u64 *) (arg0 + 0x20)) &= ~0x0100000000000000ULL;
    if ((s8) tryStartPairedEntityActions(arg0, arg1, m, *((s32 *) (arg3 + 4))))
    {
      func_800E212C(arg0);
      return 1;
    }
    goto body;
    ret1:
    return 1;

    body:
    if ((*((s16 *) (arg0 + 0xA))) == 0x17)
    {
      *((u64 *) (arg0 + 0x20)) |= 0x0000020000000000ULL;
    }

    if ((*((u64 *) (arg0 + 0x20))) & 9)
    {
      func_800E212C(arg0);
      if ((s8) func_800D23B4(arg0, arg1, arg3))
      {
        func_800A6C48(arg0, 0x44);
        *((s16 *) (arg0 + 0xC)) = 4;
        goto ret1;
      }
      f = (*((u64 *) (arg0 + 0x20))) | 0x0100000000000000ULL;
      *((u64 *) (arg0 + 0x20)) = f;
      if (f & 0x80)
      {
        s32 index = *((s16 *) (arg0 + 0x3C));
        if (D_800E3CD8[index] & arg2)
        {
          func_800A6C48(arg0, 0x1B);
          return 1;
        }
        if (D_800E3CD0[index] & arg2)
        {
          func_800A6C48(arg0, 0x1C);
          return 1;
        }
        if ((*((u64 *) (arg1 + 0x20))) & 0x40)
        {
          func_800A6C48(arg0, 0x1B);
          return 1;
        }
        if ((*((u64 *) (arg1 + 0x20))) & 0x100)
        {
          func_800A6C48(arg0, 0x1C);
          return 1;
        }
        if (!((*((u64 *) (arg1 + 0x20))) & 0x80))
        {
          return 1;
        }
        *((u64 *) (arg0 + 0x20)) = f & (~0x0000008000000000ULL);
        if (func_800D3684(*((s32 *) (arg0 + 0x58)), *((s32 *) (arg3 + 0xC))) <= 0)
        {
          *((u64 *) (arg0 + 0x20)) |= 0x0000008000000000ULL;
        }
        func_800A6C48(arg0, 0x1D);
        return 1;
      }
      else
      {
        func_800A6C48(arg0, 0x1E);
      }
    }
    else
    {
      func_800A6C48(arg0, 0x44);
    }
    ret = 1;
  }
  else
  {
    ret = 0;
  }
  return ret;
}
