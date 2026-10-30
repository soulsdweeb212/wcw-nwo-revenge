/* @header
 * updateActionStateDC798  (originally func_800DC798)
 * VRAM 0x800DC798 | ROM 0xCFC38 | size 0x3BC
 * asm: asm/nonmatchings/code_800BBA00/updateActionStateDC798.s
 */
#include "common.h"

/* Per-frame step of the global action state machine D_800FAF5C (a Nw2StateObj):
 * switch on state (+0x0C): 0 = pick/enter the action (fixed 0xEF8 when the
 * attachment's flag 0x40000 is set, else a table lookup 0xEF9), 1 = action
 * setup (play select animation and transition), 2 = run the action
 * (collision/timer driven, may advance state), 3 = teardown, 4/5 = idle.
 * Fields: +0x04 timer, +0x06 sub-timer, +0x20 u64 flags, +0x364 attachment
 * pointer, +0x370/+0x371 duration thresholds, +0x3A2 sound id. */
typedef struct 
{
  u8 pad0[4];
  s16 f4;
  s16 f6;
  u8 pad8[4];
  s16 fC;
  u8 padE[0x12];
  u64 flags20;
  u8 pad28[0x33C];
  void *att364;
  u8 pad368[8];
  u8 f370;
  u8 f371;
  u8 pad372[0x30];
  s8 f3A2;
} Nw2StateObj;
extern Nw2StateObj *D_800FAF5C;
extern void *D_800F9B00;
extern s32 D_800F9B0C;
extern s32 D_800FABD8;
extern s8 D_800FADB8;
extern s32 D_800E3F20[];
s32 func_800D4D44(void *, s32, s32);
void func_800D427C(void *, s16, s32);
void func_800D7E80(void *, s32);
s8 func_800D8D74(void *, s32);
void func_800A7C40(void *, s8, s16);
s16 func_800D5438(void *, s32);
void func_800A7F6C(void *, s32);
void func_800A7D1C(void *, s32);
void func_800B68A0(void *, void *, void *);
void func_800D4AD0(void *);
s8 func_800D4CC4(void *);
void addEntityHealthDelta(void *, s32);
void beginEntityActionA8D8C(void *);
void func_800A6C48(void *, s32);
s8 func_800DB4FC(void *, void *);
void func_800C38FC(s8 *, u64, s32);
void func_800D2B64(void *, f32, u32, s32);
void updateActionStateDC798(void)
{
  /* address of the global state pointer, used to reload it after a call */
  u32 *objSlot;
  switch (D_800FAF5C->fC)
  {
    case 0:
      objSlot = &(*((u32 *) (&D_800FAF5C)));
    {
      s32 act;
      if ((*((u64 *) (D_800FAF5C->att364 + 0x38))) & 0x40000ULL)
      {
        act = 0xEF8;
      }
      else
      {
        act = func_800D4D44(D_800FAF5C, 0, D_800F9B0C);
      }
      func_800D427C(D_800FAF5C, act, 2);
      func_800D7E80(D_800FAF5C, 0);
      D_800FAF5C->fC++;
    case 1:
      if (func_800D8D74((Nw2StateObj *) (*objSlot), 0))
      {
        if ((*((u64 *) (D_800FAF5C->att364 + 0x38))) & 0x40000ULL)
        {
          D_800FAF5C->fC++;
        }
        else
        {
          func_800D427C(D_800FAF5C, 0xEF9, 2);
          D_800FAF5C->fC = 5;
        }
      }
      break;
    }

    case 2:
    {
      if (D_800FAF5C->f4 > 0)
      {
        break;
      }
      func_800A7C40(D_800FAF5C, D_800FADB8, 0xDD);
      func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 0), 1);
      func_800A7F6C(D_800FAF5C, 0);
      D_800FAF5C->fC++;
      break;
    }

    case 3:
    {
      D_800FABD8 &= ~D_800E3F20[D_800FADB8];
      if (D_800FAF5C->f6 >= D_800FAF5C->f370)
      {
        D_800FAF5C->flags20 = (D_800FAF5C->flags20 & (~0x40ULL)) | 0x100ULL;
      }
      if (func_800DB4FC(D_800FAF5C, D_800F9B00))
      {
        D_800FAF5C->fC++;
      }
    case 4:
      D_800FAF5C->flags20 |= 0x80000000000ULL;
      func_800C38FC((s8 *) D_800FAF5C, 0x1000000000ULL, 0x800000);
      if (D_800FAF5C->f6 >= D_800FAF5C->f371)
      {
        D_800FAF5C->flags20 &= ~0x80000000000ULL;
        func_800D2B64(D_800FAF5C, 4.0f, 0, 0xFFFFE);
      }
      if (D_800FAF5C->f4 <= 0)
      {
        Nw2StateObj *o;
        func_800D4AD0(D_800FAF5C);
        o = D_800FAF5C;
        if (o->fC == 3)
        {
          func_800A7D1C(o, 0x23);
          func_800B68A0(D_800FAF5C, D_800FAF5C, D_800FAF5C);
          if (func_800D4CC4(o))
          {
            addEntityHealthDelta(o, o->f3A2);
          }
          beginEntityActionA8D8C(o);
          break;
        }
        func_800A6C48(D_800FAF5C, 0x2B);
      }
      break;
    }

    case 5:
    {
      if (D_800FAF5C->f4 > 0)
      {
        break;
      }
      func_800A7D1C(D_800FAF5C, 0xE);
      func_800B68A0(D_800FAF5C, D_800FAF5C, D_800FAF5C);
      func_800D4AD0(D_800FAF5C);
      func_800A6C48(D_800FAF5C, 0x2B);
      break;
    }


  }

}
