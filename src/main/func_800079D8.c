/* @header
 * func_800079D8
 * VRAM 0x800079D8 | ROM 0x85D8 | size 0x9C
 * asm: asm/nonmatchings/main/func_800079D8.s
 */
#include "common.h"

void func_800079D8(u16 *arg0, s32 arg1)
{
  u16 *p = arg0;
  u32 i = 0;
  s32 mode = arg1 & 0xFF;
  s32 hi;
  s32 c;
  do
  {
    switch (mode)
    {
      case 0:
        c = (((u16) (*p)) >> 8) & 0xF8;
        break;
      case 1:
        c = (((u16) (*p)) >> 3) & 0xF8;
        break;
      case 2:
      default:
        c = ((*p) * 4) & 0xF8;
        break;
    }
    hi = c;
    if (c & 0xFFFF)
    {
      hi = c + 7;
      c = (0xFF - c) * (0xFF - c);
      c = 0xFF - ((u32)(c & 0xFFFF) >> 8);
    }
    c |= hi << 8;
    *p = c;
    i++;
    p++;
  }
  while (i < 0x10);
}
