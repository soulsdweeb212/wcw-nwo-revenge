#include "common.h"

typedef struct 
{
  u8 pad[0x160];
  s16 active;
  s16 velocity;
  u16 amount;
  u16 step;
  s16 limit;
  s16 radius;
  s16 x;
  s16 z;
  s16 height;
  s16 angle;
  f32 scale;
} Nw2Effect;
extern u8 stepRecordedFramePlayback[];
extern u8 func_800D6658[];
void buildScaledRotationTranslationMatrix(void *, f32, f32, f32, f32, f32, f32, f32);
void func_8001B3EC(void *, f32, f32, f32, f32 *, f32 *, f32 *);
void func_80090384(s32 arg0, s32 arg1, s32 arg2)
{
  f32 m[4][4];
  f32 x;
  f32 y;
  f32 z;
  f32 r;
  f32 zero = 0.0f;
  f64 c3 = *((f64 *) (stepRecordedFramePlayback + 0x244));
  f64 c2 = *((f64 *) (stepRecordedFramePlayback + 0x24C));
  f64 c4 = *((f64 *) (stepRecordedFramePlayback + 0x254));
  s32 col;
  s32 i = 0;
  Nw2Effect *p = (Nw2Effect *) (func_800D6658 + 0x6F8);
  s32 off = (arg0 << 6) + 0xE0;
  Nw2Effect *q;
  u8 *base;
  s32 alpha;
  f64 a;
  s32 angle;
  s16 t;
  long new_var2;
  new_var2 = (((arg1 & 255) << 24) | ((arg1 & 255) << 16)) | ((arg1 & 255) << 8);
  col = new_var2;
  do
  {
    q = p;
    t = q->active;
    if (t >= 0)
    {
      q->active = t + q->step;
      base = (u8 *) p;
      if (q->active >= q->limit)
      {
        q->active = -1;
        q->scale = 0.0f;
      }
      else
      {
        q->scale = ((((f64) q->active) * c3) / q->limit) + c2;
        alpha = q->radius;
        q->velocity--;
        q->height += q->velocity;
        r = alpha * q->scale;
        if ((!(q->angle & 1)) && (q->height < r))
        {
          q->height = (s32) r;
        }
        if (arg2 == 0)
        {
          a = q->scale;
          if (a < (*((f64 *) (stepRecordedFramePlayback + 0x25C))))
          {
            alpha = (s32) (((a - c2) * c4) * 2.0);
          }
          else if (c3 < a)
          {
            alpha = (s32) (((c2 - (a - c3)) * c4) * 2.0);
          }
          else
          {
            alpha = 196;
          }
          *((s32 *) ((((u8 *) p) + off) + 8)) = 0xFA000000;
          *((s32 *) ((((u8 *) p) + off) + 12)) = col | (alpha & 255);
          *((void **) (base + 0x10)) = ((u8 *) p) + off;
          r = (f32) ((q->radius * q->active) / q->limit);
          angle = (q->angle * 360) / 4096;
          buildScaledRotationTranslationMatrix(m, zero, angle, zero, 1.0f, (f32) q->x, (f32) ((s16) (q->height / 12)), (f32) q->z);
          func_8001B3EC(m, zero, zero, r * 4.0f, &x, &y, &z);
          do {
          buildScaledRotationTranslationMatrix(base + 0x1C, zero, zero, zero, 1.0f, x, y, z);
          } while (0);
        }
      }
    }
    i++;
    p++;
  }
  while (i < 48);
}
