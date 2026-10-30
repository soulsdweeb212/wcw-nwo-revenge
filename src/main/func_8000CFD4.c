/* @header
 * func_8000CFD4
 * VRAM 0x8000CFD4 | ROM 0xDBD4 | size 0x23C
 * asm: asm/nonmatchings/main/func_8000CFD4.s
 */
#include "common.h"

s32 releaseHeapBlock(void *);
void func_80007AFC(void *);
void func_80008B5C(s16);
void func_80008C94(s16);
void func_8000BDD0(s16);
extern u16 *D_80031998[];
extern void ***D_80032B44[];
extern s16 D_8003673C[];
extern u16 D_8006A2A4[];
extern s16 D_8007DFB0[];
extern s16 D_8007DFBC[];
extern u16 D_800566E0[];
extern s16 D_80075440[];
extern s16 D_80075442[];
extern s16 D_80075444[];
extern s16 D_8007C318[][23];
extern void *D_8007C438[][23];
extern u8 D_8007C3D0[][16];
inline static void **getList(u32 id)
{
  s32 bank = (id >> 8) & 0x1F;
  s32 idx = (id & 0x1F) - 1;
  return D_80032B44[bank][idx];
}

inline static s32 countList(void **list)
{
  s32 n = 0;
  while (list[n] != NULL)
    n++;
  return n;
}

void func_8000CFD4(s16 arg0, u32 arg1, s16 arg2, s16 arg3, s32 arg4, s8 arg5, s8 arg6)
{
  void **list;
  s32 count;
  u32 i;
  u8 *e;
  s16 *new_var;
  s32 bank;
  u16 new_var2;
  s32 idx;
  u32 val;
  u16 *row;
  bank = (arg1 >> 8) & 0x1F;
  idx = (arg1 & 0x1F) - 1;
  row = D_80031998[bank];
  if (arg2 >= D_8003673C[row[idx] & 0x7F])
  {
    arg2 = 0;
  }
  list = D_80032B44[bank][idx];
  val = arg1;
  count = countList(list);

  if ((s16)count <= arg3)
  {
    arg3 = 0;
  }
  new_var = D_8007DFB0;
  D_8006A2A4[arg0] = val;
  D_8007DFBC[arg0] = arg2;
  D_8007DFB0[arg0] = arg3;
  D_800566E0[arg0] = D_8006A2A4[arg0];
  e = getList(D_8006A2A4[arg0])[new_var[arg0]];
  new_var2 = *((u16 *) (e + 0x16));
  D_80075442[arg0 * 3] = arg5;
  D_80075444[arg0 * 3] = arg6;
  D_80075440[arg0 * 3] = new_var2;
  for (i = 0; i < 23; i++)
  {
    if (D_8007C438[arg0][i] != NULL)
    {
      releaseHeapBlock(D_8007C438[arg0][i]);
      D_8007C438[arg0][i] = NULL;
      D_8007C318[arg0][i] = 0;
    }
  }

  func_80007AFC(D_8007C3D0[arg0]);
  func_8000BDD0(arg0);
  func_80008B5C(arg0);
  func_80008C94(arg0);
}
