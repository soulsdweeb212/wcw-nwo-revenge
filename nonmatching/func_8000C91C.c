#include "common.h"

extern u16 D_80036746;
extern u16 *D_80031998[];
extern void ***D_80032B44[];
extern s16 D_8003673C[];
extern u16 D_8006A2A4[];
extern s16 D_8007DFB0[];
extern s16 D_8007DFBC[];
extern u16 D_800566E0[];
extern s8 D_800566E8[];
extern u8 D_800706A4[];
extern u8 D_80075468[];
extern s16 D_80075440[][3];
extern s16 D_8007C318[][23];
extern s32 D_8007C438[][23];
extern s32 D_8007C3D0[][4];
extern s32 D_8007C3D8[][4];
extern u8 D_800651A0[];
extern u8 D_80073EB0[];
extern u8 D_800517D0[];
extern u8 D_80050800[];
typedef struct 
{
  u8 d[0xDC];
} ObjC91C;
typedef struct 
{
  u8 d[0x2C];
} SlotC91C;
void func_80004B34(void *, void *, s32, f32, f32, f32);
void func_80007A74(void *, s32, s32);
void func_80008B5C(s16);
void func_80008C94(s16);
void func_8000BDD0(s16);
void func_8000C1B8(s16, s16);
void buildObjectChain(void *, void *);
inline static void **getListC91C(u32 id)
{
  s32 bank = (id >> 8) & 0x1F;
  s32 idx = (id & 0x1F) - 1;
  return D_80032B44[bank][idx];
}

void func_8000C91C(s16 arg0, u32 arg1, s16 arg2, s16 arg3, s32 arg4, s8 arg5, s8 arg6)
{
  u32 i;
  void **list;
  s32 count;
  s32 bank;
  s32 idx;
  u8 *e;
  ObjC91C *a;
  SlotC91C *s;
  s32 lim;
  s32 *new_var;
  u32 tq;
  u32 tr;
  u32 tu;
  u32 tv;
  if (D_80036746 != 0)
  {
    u32 k;
    u32 j;
    D_80036746 = 0;
    for (k = 0; k < 4; k++)
    {
      ((s16 *) D_8006A2A4)[k] = -1;
      D_8007DFBC[k] = -1;
      D_8007DFB0[k] = -1;
      D_800706A4[k] = 0;
      D_80075468[k] = 0x32;
      ((s16 *) D_800566E0)[k] = -1;
      D_800566E8[k] = -1;
      for (j = 0; j < 23; j++)
      {
        D_8007C438[k][j] = 0;
        D_8007C318[k][j] = 0;
      }

      for (j = 0; j < 3; j++)
      {
        D_80075440[k][j] = 0;
      }

      D_8007C3D0[k][0] = 0;
      D_8007C3D8[k][0] = 0;
    }

  }
  tq = arg5 & 1;
  tr = arg5 & 2;
  tu = arg5 & 4;
  tv = arg5 & 8;
  i = tu >> 3;
  if ((((tq >> 1) | (tr >> 2)) | i) | (tv >> 4))
  {
    D_80036746 = 0;
  }
  bank = (arg1 >> 8) & 0x1F;
  idx = (arg1 & 0x1F) - 1;
  lim = D_8003673C[D_80031998[bank][idx] & 0x7F];
  if (arg2 >= lim)
  {
    arg2 = 0;
  }
  list = D_80032B44[bank][idx];
  for (count = 0; list[count] != NULL; count++)
  {
  }

  if (((s16) count) <= arg3)
  {
    arg3 = 0;
  }
  D_8006A2A4[arg0] = arg1;
  D_8007DFBC[arg0] = arg2;
  D_8007DFB0[arg0] = arg3;
  D_800566E0[arg0] = D_8006A2A4[arg0];
  e = getListC91C(D_8006A2A4[arg0])[D_8007DFB0[arg0]];
  s = (SlotC91C *) (D_80073EB0 + (arg0 * 0x3F4));
  a = (ObjC91C *) (D_800651A0 + (arg0 * 0x13C4));
  D_80075440[arg0][0] = *((u16 *) (e + 0x16));
  D_80075440[arg0][1] = arg5;
  D_80075440[arg0][2] = arg6;
  for (i = 0; i < 23; i++)
  {
    func_80004B34(&a[i], &s[i], 4, 0.0f, 0.0f, 0.0f);
  }

  new_var = D_8007C3D0[arg0];
  func_80007A74(new_var, 0x2BC, 0x4B0);
  func_8000BDD0(arg0);
  func_8000C1B8(arg0, 0);
  func_8000C1B8(arg0, 1);
  func_80008B5C(arg0);
  func_80008C94(arg0);
  buildObjectChain(D_800517D0 + (arg0 * 0x13C4), D_80050800 + (arg0 * 0x3F4));
}
