/* @header
 * func_80007960
 * VRAM 0x80007960 | ROM 0x8560 | size 0x78
 * asm: asm/nonmatchings/main/func_80007960.s
 */
#include "common.h"

void func_80007960(u16 *arg0, s32 arg1)
{
  u16 *p = arg0;
  u32 i = 0;
  s32 mode = arg1 & 0xFF;
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
    if (c & 0xFFFF)
      c += 7;
    c |= 0xFF00;
    *p = c;
    i++;
    p++;
  }
  while (i < 0x10);
}
