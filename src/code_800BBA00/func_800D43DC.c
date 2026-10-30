/* @header
 * func_800D43DC
 * VRAM 0x800D43DC | ROM 0xC787C | size 0x228
 * asm: asm/nonmatchings/code_800BBA00/func_800D43DC.s
 */
#include "common.h"

typedef struct 
{
  s8 f0;
  s8 f1;
  s16 f2;
  s16 f4;
  s16 f6;
  s16 f8;
  u8 padA[0x42];
  u8 f4C[0x321];
  u8 f36D;
  u8 pad36E[0x42];
} Ent43DC;
typedef struct 
{
  u8 b[12];
} Look43DC;
typedef struct 
{
  s8 b0;
  s8 b1;
  s8 b2;
  s8 b3;
} Col43DC;
extern Look43DC D_800EB688[];
extern Col43DC D_800EB6B8[];
extern Ent43DC D_800F9D10[];
s32 updateEntityTargetLookAngles(s8, void *);
void func_800D427C(void *, s16, s32);
void func_80008CE8(s8, s16, s16, void *, s32, s32);
void func_800D43DC(void)
{
  s16 i;
  s32 base;
  s32 mask;
  s32 r;
  Ent43DC *ent;
  u16 old;
  for (i = 0; i < 4; i++)
  {
    if (D_800F9D10[i].f2 != (-1))
    {
      base = (s32) (&D_800EB688[i]);
      r = updateEntityTargetLookAngles(i, (void *) base);
 do { } while (0);
      mask = base & (-((r << 24) != 0));
      if (D_800F9D10[i].f4 <= 0)
      {
        if (D_800F9D10[i].f36D == 0)
        {
          func_80008CE8(D_800F9D10[i].f0, D_800F9D10[i].f8, D_800F9D10[i].f6, D_800F9D10[i].f4C, mask, (&D_800EB6B8[i])->b3);
          continue;
        }
        ent = &D_800F9D10[i];
        old = D_800F9D10[i].f8;
        ent->f8 = -1;
        func_800D427C(ent, old, 0);
      }
      func_80008CE8(D_800F9D10[i].f0, D_800F9D10[i].f8, D_800F9D10[i].f6, D_800F9D10[i].f4C, mask, (&D_800EB6B8[i])->b3);
      if (D_800F9D10[i].f4 > 0)
      {
        D_800F9D10[i].f6++;
        D_800F9D10[i].f4--;
      }
    }
  }

}
