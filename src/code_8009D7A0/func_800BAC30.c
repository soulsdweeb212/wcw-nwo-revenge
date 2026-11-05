/* @header
 * func_800BAC30
 * VRAM 0x800BAC30 | ROM 0xAE0D0 | size 0xDD0
 * asm: asm/nonmatchings/code_8009D7A0/func_800BAC30.s
 */
#include "common.h"

/* Entity record, 0x3B0 bytes (D_800F9D10[4]): +2 s16 state, +0x20 u64 flags,
 * +0x4C/+0x50/+0x54 f32 x/y/z position, +0x58 s32 heading, +0x353 s8 facing target id. */
typedef struct {
  u8 pad0[2];
  s16 f2;
  u8 pad4[0x1C];
  u64 flags;
  u8 pad28[0x24];
  f32 x;
  f32 y;
  f32 z;
  s32 heading;
  u8 pad5C[0x2F7];
  s8 f353;
  u8 pad354;
  u8 f355;
  u8 pad356[0x5A];
} EntBAC30;

extern EntBAC30 D_800F9D10[];
extern u16 D_8007E280;
extern u16 D_8007F0A0;
extern s16 D_800FACEA[];
extern s16 D_800FAF96[];
/* D_8007E228 bss block: per-player 8-byte setup records at +0x60, 0x18-byte records at +0x628.
 * Indexed through struct members so the sym+K addresses are not forced into pseudos and
 * LICM-hoisted (the ROM keeps every access as lui/addu/%lo). */
typedef struct {
  u8 pad0[0x60];
  u8 f60[4][8];
  u8 pad80[0x5A8];
  u8 f628[4][0x18];
} G7E228;

extern G7E228 D_8007E228;
extern u16 D_800E39A8[];
extern u16 D_800E397C[];
extern f32 D_800E39B0[][2];
extern f32 D_800E39D0[][2];
extern f32 D_800E39F0[][2];
extern f32 D_800E3A10[][2];
extern f32 D_800E3A30[][2];
extern f32 D_800E3A50[][2];
extern s32 D_800E3CA0[];
extern s32 D_80038AA8;
extern s16 D_800EB476;

void func_800BA770(s8, s16, s32);
void func_800E1920(void *, s32);
void func_8000DB90(s32, s32);
void func_800D3890(void *, void *, void *);

void func_800BAC30(void)
{
  Nw2DirectionResult res;
  s16 i;

  for (i = 0; i < 4; i++)
  {
    func_800BA770(i, D_800FACEA[i], 0);
    if (D_8007E280 & D_800E39A8[i])
    {
      D_800F9D10[i].flags |= 4ULL;
    }
    if (D_8007E280 & D_800E397C[i])
    {
      D_800F9D10[i].flags |= 0x200000000ULL;
    }
    if (D_8007E228.f60[i][6] & 2)
    {
      D_800F9D10[i].flags |= 0x4000000000000ULL;
    }
    if (D_8007E228.f60[i][6] & 1)
    {
      D_800F9D10[i].flags |= 0x400000000ULL;
    }
    if (D_8007E280 & 0x100)
    {
      if (D_800F9D10[i].flags & 2ULL)
      {
        D_800F9D10[i].flags |= 0x100ULL;
        D_800F9D10[i].x = 0.0f;
        D_800F9D10[i].y = 0.0f;
        D_800F9D10[i].f353 = (i & 1) ^ 1;
        D_800F9D10[i].f355 = i & 1;
        D_800F9D10[i].z = 1500.0f;
      }
      else if (D_800F9D10[i].flags & 1ULL)
      {
        D_800F9D10[i].flags |= 0x100ULL;
        D_800F9D10[i].x = D_800E3A50[i][0];
        D_800F9D10[i].z = D_800E3A50[i][1];
        D_800F9D10[i].y = 0.0f;
        D_800F9D10[i].f353 = i & 1;
        D_800F9D10[i].f355 = i & 1;
      }
      else
      {
        D_800F9D10[i].flags |= 0x240ULL;
        D_800F9D10[i].x = D_800E39B0[i][0];
        D_800F9D10[i].z = D_800E39B0[i][1];
        D_800F9D10[i].f353 = i ^ 1;
        D_800F9D10[i].f355 = i | 2;
      }
    }
    if (D_8007E280 & 0x400)
    {
      D_800F9D10[i].flags |= 0x240ULL;
      D_800F9D10[i].x = D_800E39D0[i][0];
      D_800F9D10[i].z = D_800E39D0[i][1];
      D_800F9D10[i].f353 = i ^ 3;
      D_800F9D10[i].f355 = i;
    }
    if (D_8007E280 & 0x200)
    {
      D_800F9D10[i].f355 = i ^ 1;
      if ((i == 2) && (D_800FACEA[3] == (-1)))
      {
        D_800F9D10[2].f355 = 2;
      }
      if ((i == 2) && (D_800FACEA[3] == (-1)))
      {
        D_800F9D10[2].x = D_800E39B0[1][0];
        D_800F9D10[2].z = D_800E39B0[1][1];
      }
      else if (D_8007F0A0 & 0x40)
      {
        D_800F9D10[i].x = D_800E39F0[i][0];
        D_800F9D10[i].z = D_800E39F0[i][1];
      }
      else if (i & 1)
      {
        D_800F9D10[i].flags |= 0x80ULL;
        D_800F9D10[i].x = D_800E3A30[i][0];
        D_800F9D10[i].z = D_800E3A30[i][1];
      }
      else
      {
        D_800F9D10[i].x = D_800E3A10[i][0];
        D_800F9D10[i].z = D_800E3A10[i][1];
      }
      if (D_8007F0A0 & 0x40)
      {
        D_800F9D10[i].f353 = i ^ 2;
        D_800F9D10[i].flags |= 0x240ULL;
        if ((i == 1) && (D_800FACEA[3] == (-1)))
        {
          D_800F9D10[1].f353 = 2;
        }
      }
      else
      {
        if (!(i & 1))
        {
          D_800F9D10[i].flags |= 0x240ULL;
        }
        D_800F9D10[i].f353 = (i & 2) ^ 2;
      }
      if (D_8007F0A0 & 0x40)
      {
        if ((i & 1) && (D_800FAF96[i] == D_800FAF96[i ^ 1]))
        {
          D_800F9D10[i].flags |= 4ULL;
        }
      }
      else if ((!(D_800F9D10[i].flags & 0x200ULL)) && (D_800FAF96[i] == D_800FAF96[i ^ 1]))
      {
        D_800F9D10[i].flags |= 4ULL;
      }
    }
    if (D_800F9D10[i].flags & 0x200ULL)
    {
      func_800E1920(&D_800F9D10[i], 6);
    }
  }

  for (i = 0; i < 4; i++)
  {
    if (D_800F9D10[i].flags & 0x80ULL)
    {
      D_800F9D10[i].heading = D_800E3CA0[(s16) getXZDirectionQuadrant(&D_800F9D10[i].x)];
    }
    else
    {
      func_800D3890(&D_800F9D10[i].x, &D_800F9D10[D_800F9D10[i].f353].x, &res);
      D_800F9D10[i].heading = res.angle;
    }
  }

  if (D_8007E280 & 0x100)
  {
    for (i = 2; i < 4; i++)
    {
      if (D_800F9D10[i].flags & 2ULL)
      {
        D_800F9D10[i].f2 = -1;
        D_800F9D10[i & 1].f355 = i & 1;
        func_8000DB90(i, 0);
      }
    }
  }
  if (D_8007E280 & 0x400)
  {
    D_800EB478 = 4;
    D_800EB474 = D_80038AA8;
    D_800EB476 = D_80038AA8 - 4;
  }
  if (D_8007E280 & 0x500)
  {
    for (i = 0; i < 4; i++)
    {
      D_800FAF96[i] = i;
    }
  }
  if (D_8007E280 & 0x200)
  {
    for (i = 0; i < 4; i++)
    {
      if (--D_800FAF96[i] < 0)
      {
        D_800FAF96[i] = 0;
      }
    }
  }
  if (D_8007E280 & 0x400)
  {
    for (i = 0; i < 4; i++)
    {
      if (D_800F9D10[i].flags & 4ULL)
      {
        D_8007E228.f628[i][0] = 0;
        D_8007E228.f628[i][1] = 1;
      }
      else
      {
        D_8007E228.f628[i][0] = 1;
        D_8007E228.f628[i][1] = 0;
      }
      D_8007E228.f628[i][2] = 0;
      D_8007E228.f628[i][3] = 0;
      D_8007E228.f628[i][4] = 0;
      D_8007E228.f628[i][5] = 0;
      D_8007E228.f628[i][6] = 0;
      D_8007E228.f628[i][7] = 0;
      D_8007E228.f628[i][8] = 0;
      D_8007E228.f628[i][9] = 0;
      D_8007E228.f628[i][10] = 0;
      D_8007E228.f628[i][11] = 0;
      D_8007E228.f628[i][12] = 0;
      D_8007E228.f628[i][13] = 0;
      D_8007E228.f628[i][14] = 0;
      D_8007E228.f628[i][15] = 0;
      D_8007E228.f628[i][16] = 0;
      D_8007E228.f628[i][17] = 0;
      D_8007E228.f628[i][18] = 0;
      D_8007E228.f628[i][19] = 0;
      D_8007E228.f628[i][20] = 0;
      D_8007E228.f628[i][21] = 0;
      D_8007E228.f628[i][22] = 0;
      D_8007E228.f628[i][23] = 0;
    }
  }
}
