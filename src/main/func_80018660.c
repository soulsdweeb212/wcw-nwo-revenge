/* @header
 * func_80018660
 * VRAM 0x80018660 | ROM 0x19260 | size 0x5C4
 * asm: asm/nonmatchings/main/func_80018660.s
 */
#include "common.h"

typedef struct Nw2EnvStep Nw2EnvStep;
struct Nw2EnvStep
{
  Nw2EnvStep *next;
  s32 f4;
  s16 type;
  s16 flag;
  s32 value;
  s16 f10;
  u8 f12;
  u8 f13;
  s32 f14;
  s32 f18;
};
typedef struct 
{
  u8 pad0[0x44];
  f32 f44;
  s32 f48;
  u8 pad4C[0xC];
  s16 f58;
  s16 f5A;
  s16 f5C;
  s16 f5E;
  u16 f60;
  u16 f62;
  u16 f64;
  s16 f66;
  s16 f68;
  u16 f6A;
  s16 f6C;
  s16 f6E;
  s32 f70;
  s32 f74;
  s32 f78;
  Nw2EnvStep *f7C;
  s32 f80;
  s32 f84;
} Nw2EnvObj;
extern u16 D_800370F0[];
extern char D_8003B460[];
extern char D_8003B464[];
void func_8001CEE0(char *, char *, s32);
s32 func_800194B8(Nw2EnvObj *, s32, s32);
void func_80017FBC(void *);
void func_80017F44(void *);
void func_80018C24(Nw2EnvObj *, s32, s32);
u8 *func_80018CC4(Nw2EnvObj *, s16 *, s16 *, s32, u8 *);
s16 func_80019024(s16, s32, s16, u16);
u8 *func_80018660(Nw2EnvObj *o, s32 time, u8 *out)
{
  s16 counter;
  s16 accum;
  Nw2EnvStep *rec;
  Nw2EnvObj *new_var;
  s32 total;
  s32 prev;
  s32 delta;
  s32 cur;
  new_var = o;
  cur = time;
  total = 0xB8;
  accum = 0;
  counter = 0;
  while (new_var->f7C)
  {
    prev = cur;
    cur = ((new_var->f7C->f4 + 0x5C) / 184) * 184;
    delta = cur - prev;
    if (total < delta)
    {
      break;
    }
    if (delta < 0)
    {
      func_8001CEE0(D_8003B460, D_8003B464, 0x82);
    }
    if (delta >= 0xB9)
    {
      func_8001CEE0(D_8003B460, D_8003B464, 0x86);
    }
    switch (new_var->f7C->type)
    {
      case 13:
      {
        Nw2EnvStep *r = new_var->f7C;
        if (r->flag != 0)
        {
          new_var->f48 = 1;
        }
        func_800194B8(new_var, 5, r->f18);
        new_var->f84 = 1;
        new_var->f78 = 1;
        new_var->f70 = 0;
        new_var->f74 = ((r->f14 + 0x5C) / 184) * 184;
        new_var->f5A = (r->f10 * r->f10) >> 15;
        new_var->f58 = r->f12;
        new_var->f60 = D_800370F0[r->f13];
        new_var->f62 = D_800370F0[0x7F - r->f13];
        if (r->f14 != 0)
        {
          new_var->f5C = 1;
          new_var->f5E = 1;
        }
        else
        {
          new_var->f5C = (new_var->f5A * ((s16) D_800370F0[new_var->f58])) >> 15;
          new_var->f5E = (new_var->f5A * ((s16) D_800370F0[0x7F - new_var->f58])) >> 15;
        }
        new_var->f44 = *((f32 *) (&r->value));
        break;
      }

      case 11:

      case 12:

      case 16:
        out = func_80018CC4(new_var, &counter, &accum, delta, out);
        if ((new_var->f70 >= new_var->f74) || (((u32) delta) < 1))
      {
        new_var->f68 = (new_var->f5A * ((s16) D_800370F0[new_var->f58])) >> 15;
        new_var->f6E = (new_var->f5A * ((s16) D_800370F0[0x7F - new_var->f58])) >> 15;
        new_var->f70 = new_var->f74;
        new_var->f5C = new_var->f68;
        new_var->f5E = new_var->f6E;
      }
      else
      {
        new_var->f5C = func_80019024(new_var->f5C, new_var->f70, new_var->f66, new_var->f64);
        new_var->f5E = func_80019024(new_var->f5E, new_var->f70, new_var->f6C, new_var->f6A);
      }
        if (new_var->f5C == 0)
      {
        new_var->f5C = 1;
      }
        if (new_var->f5E == 0)
      {
        new_var->f5E = 1;
      }
        if (new_var->f7C->type == 0xC)
      {
        new_var->f58 = new_var->f7C->value;
      }
        if (new_var->f7C->type == 0xB)
      {
        new_var->f70 = 0;
        new_var->f5A = (new_var->f7C->value * new_var->f7C->value) >> 15;
        new_var->f74 = (((*((s32 *) (&new_var->f7C->f10))) + 0x5C) / 184) * 184;
      }
        if (new_var->f7C->type == 0x10)
      {
        new_var->f60 = D_800370F0[new_var->f7C->value];
        *(volatile u16 *)&new_var->f62 = D_800370F0[0x7F - new_var->f7C->value];
      }
        new_var->f78 = 1;
        break;

      case 14:
      {
        Nw2EnvStep *r = new_var->f7C;
        if (r->flag != 0)
        {
          new_var->f48 = 1;
        }
        func_800194B8(new_var, 5, r->value);
        new_var->f84 = 1;
        break;
      }

      case 15:
        out = func_80018CC4(new_var, &counter, &accum, delta, out);
        func_80018C24(new_var, 4, 0);
        break;

      case 0:
      {
        Nw2EnvStep *r = new_var->f7C;
        *((s32 *) (((u8 *) r->value) + 0x88)) = 0;
        func_80017FBC((void *) r->value);
        break;
      }

      case 7:
        out = func_80018CC4(new_var, &counter, &accum, delta, out);
        new_var->f44 = *((f32 *) (&new_var->f7C->value));
        break;

      case 8:
        out = func_80018CC4(new_var, &counter, &accum, delta, out);
        new_var->f48 = 1;
        break;

      case 5:
        out = func_80018CC4(new_var, &counter, &accum, delta, out);
        func_800194B8(new_var, 5, new_var->f7C->value);
        break;

      default:
        out = func_80018CC4(new_var, &counter, &accum, delta, out);
        func_80018C24(new_var, new_var->f7C->type, new_var->f7C->value);
        break;

    }

    rec = new_var->f7C;
    total -= delta;
    accum += delta * 2;
    new_var->f7C = rec->next;
    if (new_var->f7C == 0)
    {
      new_var->f80 = 0;
    }
    func_80017F44(rec);
  }

  out = func_80018CC4(new_var, &counter, &accum, total, out);
  {
    s32 t70 = new_var->f70;
    if (new_var->f74 < t70)
    {
      new_var->f70 = new_var->f74;
    }
  }
  return out;
}
