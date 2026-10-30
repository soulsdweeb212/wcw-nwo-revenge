/* @header
 * func_800B9194
 * VRAM 0x800B9194 | ROM 0xAC634 | size 0x21C
 * asm: asm/nonmatchings/code_8009D7A0/func_800B9194.s
 */
#include "common.h"

extern s8 D_8007E8C0[];
extern u8 D_8007EF30[];
extern u8 D_800E3978[];
extern u8 D_800EB468[];
extern u8 D_800EB46F;
extern s16 D_800EB46A;
extern s16 D_800F9D12[];
extern u8 D_800F9D30[];
extern u8 D_800F9D34[];
extern s8 D_800FACE8;
extern s32 func_8009678C(void);
extern s32 func_800DA8B4(void *, s32, s32);
extern s8 func_800A93C0(void);
extern s32 func_800DA850(void *, s32);
extern s8 func_80096854(s8);
extern s8 func_800B8484(s32);
/* Gate for a multi-stage "finish" sequence: only runs while the enable byte is
 * set, the inhibit flag is clear and no attachment is active. It scans the four
 * entity slots for one carrying flags 0x100|0x200; if none, it resets the run.
 * Otherwise it steps a countdown D_800FACE8 (mapped from a table to a required
 * tag at D_800EB46A) and advances the stage until the countdown clears, at
 * which point it fires func_800B8484(0x10000). Returns a nonzero object/status
 * for the parent state machine, 0 to signal "not now". */
s8 func_800B9194(void)
{
  s16 idx;
  s32 entityOff;
  u64 entFlags;
  s8 required;
  s16 *counter;
  if (D_8007E8C0[0x66C] == 0)
  {
    return 0;
  }
  if ((*((u16 *) (D_8007EF30 + 0x170))) & 4)
  {
    return 0;
  }
  if (((s8) D_800EB46F) != (-1))
  {
    return 0;
  }
  for (idx = 0; idx < 4; idx++)
  {
    entityOff = idx * 0x3B0;
    if ((*((s16 *) (((u8 *) D_800F9D12) + entityOff))) == (-1))
    {
      continue;
    }
    entFlags = *((u64 *) (D_800F9D30 + entityOff));
    if (entFlags & 0x100)
    {
      if (entFlags & 0x200)
      {
        break;
      }
    }
  }

  if (idx == 4)
  {
    func_8009678C();
 do { func_800DA8B4(D_800EB468, 0, 0); D_800FACE8 = D_800E3978[(s8) D_8007E8C0[0x66C]]; } while (0);
    return 0;
  }
  if (func_800A93C0())
  {
    return 0;
  }
  func_800DA850(D_800EB468, 0x1E);
  if (((s8) D_800FACE8) < 3)
  {
    required = 4;
  }
  else
    if (((s8) D_800FACE8) < 6)
  {
    required = 3;
  }
  else
  {
    required = 2;
  }
  counter = &D_800EB46A;
  if ((*counter) != required)
  {
    return 0;
  }
  D_800FACE8 = (s8) (((u8) D_800FACE8) - 1);
  func_800DA8B4(((u8 *) counter) - 2, 0, 0);
  func_80096854((s8) (D_800E3978[(s8) D_8007E8C0[0x66C]] - ((u8) D_800FACE8)));
  if (D_800FACE8 != 0)
  {
    return 0;
  }
  return func_800B8484(0x10000);
}
