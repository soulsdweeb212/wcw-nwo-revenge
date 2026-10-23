#include "common.h"

/* Emit a 3-digit decimal number as Gfx: set up the font tile block, then for
 * each digit slot load the glyph tile and write the cube/quad command; a zero
 * digit additionally tints the counter. arg1 is the packed counter value. */
s32 loadResourceTexture4b(void *, void *, s32);
void accumulateColorChannels(s32, s32, s32);
extern u8 func_800C5D48[];
extern u8 func_800DBB80[];
typedef struct 
{
  s32 f0;
  u32 f4;
  u16 f8;
} Desc929;
void func_80092960(Nw2GfxCommand **arg0, s32 arg1, Desc929 *arg2)
{
  Nw2GfxCommand *cmd;
  s32 digitIdx;
  s32 i;
  cmd = *arg0;
  {
    Nw2GfxCommand *g = cmd++;
    g->w0 = 0xDE000000;
    g->w1 = (u32) (func_800C5D48 + 0x48);
  }
  {
    Nw2GfxCommand *g = cmd++;
    g->w0 = (0x01000000 | ((arg2->f8 & 255) << 12)) | ((arg2->f8 & 127) * 2);
    g->w1 = arg2->f4;
  }
  i = 0;
  do
  {
    if (arg1 >= 0)
    {
      if (arg2)
      {
        digitIdx = arg1 % 22;
      }
      else
      {
        digitIdx = arg1 % 22;
      }
      if (digitIdx >= 8)
      {
        digitIdx += 14;
      }
      if (loadResourceTexture4b(&cmd, arg2, digitIdx))
      {
        Nw2GfxCommand *g = cmd++;
        g->w0 = (((((i * 8) & 255) << 16) | ((((i * 8) + 2) & 255) << 8)) | (((i * 8) + 6) & 255)) | 0x07000000;
        g->w1 = ((((i * 8) & 255) << 16) | ((((i * 8) + 6) & 255) << 8)) | (((i * 8) + 4) & 255);
      }
      if (digitIdx == 0)
      {
        accumulateColorChannels(0x1F, 0x1F, 0x1F);
        if (i == 0)
        {
          *((s32 *) (func_800DBB80 + 0x1D4)) = 0x421;
        }
      }
    }
    i++;
    arg1 -= 7;
  }
  while (i < 3);
  *arg0 = cmd;
}
