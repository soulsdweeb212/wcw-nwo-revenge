#include "common.h"

typedef struct 
{
  s16 f0;
  s16 f2;
  s16 f4;
  u16 f6;
  u16 f8;
  u16 fA;
  u8 pC[2];
  s16 fE;
  u8 p10[30];
  s16 f2E;
  u8 p30[4];
  f32 f34;
  u8 p38[36];
  u32 f5C;
} ActB0C;
typedef struct 
{
  u8 p0[10];
  s16 fA;
  u8 pC[0x60];
  f32 position[3];
} EntB0C;
extern ActB0C *D_800FABD0;
extern EntB0C *D_800FAF58;
extern EntB0C *D_800F9B60;
extern u16 D_800E3CF0[];
extern s32 D_800E3D00[];
extern f64 D_800E5250;
extern f64 D_800E5258;
s32 func_800D3650(void *, void *);
f32 func_800D3890(void *, void *, void *);
s8 func_800D4198(s16);
s32 func_800D4148(void);

/* Chooses and holds a directional idle/taunt action for the D_800FABD0 actor.
 * Phase 0 picks an 8-way facing (fA) from D_800E3CF0 pointing relative to the
 * D_800FAF58 entity's position when the target D_800F9B60 is close and in range
 * (else a small random adjustment), and sets a random 5..36 frame timer (fE).
 * Phase 1 counts fE down; when it expires it either transitions to substate 7
 * (grab, when the target's fA matches stored f2E, a coin flip succeeds and the
 * actor's f34 exceeds the f64 D_800E5258), backs off a frame, or resets to
 * substate 0; it also resets when the target's or D_800FAF58's state changes.
 * f2 is the substate, f6 the held animation, f2E the last-seen target state. */
void func_800B0C90(void)
{
  f32 origin[3];
  s32 direction;
  s32 phase;
  s16 delta;
  s16 adjust;
  s16 prior;
  s16 random;
  s16 timer;
  u16 counter;
  EntB0C *target;
  phase = D_800FABD0->f4;
  switch (phase)
  {
    case 0:
      origin[0] = 0;
      origin[2] = 0;
      direction = func_800D3650(D_800FAF58->position, D_800F9B60->position);
      if ((D_800E5250 < ((f64) func_800D3890(origin, D_800FAF58->position, 0))) && (func_800D3550(func_800D3684(D_800E3D00[(s16) func_800D3650(origin, D_800FAF58->position)], D_800E3D00[(s16) direction])) < 0x300))
    {
      delta = (func_800D4198(500)) ? (2) : (-2);
      D_800FABD0->fA = D_800E3CF0[(((s16) direction) + delta) & 7];
    }
    else
    {
      random = func_800D4148();
      adjust = 0;
      if (random >= 400)
      {
        adjust = (((s16) func_800D4148()) % 5) + 2;
      }
      D_800FABD0->fA = D_800E3CF0[(((s16) direction) + adjust) & 7];
    }
      D_800FABD0->fE = (func_800D4148() & 31) + 5;
      D_800FABD0->f4++;
      break;

    case 1:
      timer = D_800FABD0->fE - 1;
      D_800FABD0->fE = timer;
      D_800FABD0->f6 = D_800FABD0->fA;
      if (timer < 0)
    {
      prior = D_800FABD0->f2E;
      if ((prior == D_800F9B60->fA) && (prior != phase))
      {
        if (func_800D4198(400) && (D_800E5258 < ((f64) D_800FABD0->f34)))
        {
          target = D_800F9B60;
          D_800FABD0->f2 = 7;
          D_800FABD0->f4 = 0;
          counter = target->fA;
          D_800FABD0->f5C &= ~7;
          D_800FABD0->f2E = counter;
          break;
        }
        if (func_800D4198(150))
        {
          D_800FABD0->f4--;
          break;
        }
      }
      D_800FABD0->f2 = 0;
      D_800FABD0->f4 = 0;
      D_800FABD0->f2E = D_800F9B60->fA;
      D_800FABD0->f5C = D_800FABD0->f5C & (~7);
      break;
    }
      if ((D_800FAF58->fA != phase) || (D_800FABD0->f2E != D_800F9B60->fA))
    {
      target = D_800F9B60;
      D_800FABD0->f2 = 0;
      D_800FABD0->f4 = 0;
      counter = (D_800FABD0->f2E = target->fA);
      D_800FABD0->f5C &= ~7;
    }
      break;

  }

}
