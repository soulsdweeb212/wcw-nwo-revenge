/* @header
 * func_80015F64
 * VRAM 0x80015F64 | ROM 0x16B64 | size 0x184
 * asm: asm/nonmatchings/main/func_80015F64.s
 */
#include "common.h"

extern s32 *D_800604D4;
extern s32 D_800604DC;
extern s32 D_800604E8;
extern s32 D_800604F0;
typedef struct 
{
  s32 f0;
  s32 f4;
  u8 p8[16];
  s32 f18;
  u8 p1C[32];
  f32 f3C;
  u8 p40[32];
  s32 f60;
  s32 f64;
  u8 p68[16];
  f32 f78;
  f32 f7C;
  f32 f80;
  u8 p84[8];
  f32 f8C;
  u8 p90[8];
  s32 f98;
  s32 f9C;
  u8 pA0[24];
  s16 fB8;
  s16 fBA;
  s16 fBC;
  s16 fBE;
  u16 fC0;
  s16 fC2;
  s16 fC4;
  s16 fC6;
  s16 fC8;
  u8 pCA[6];
  s16 fD0;
  u8 pD2[10];
  u8 fDC;
  u8 fDD;
  u8 fDE;
  u8 fDF;
  u8 fE0;
  u8 fE1;
  u8 fE2;
  u8 fE3;
  u8 fE4;
  u8 fE5;
  u8 fE6;
  u8 fE7;
  u8 fE8;
  u8 fE9;
  u8 fEA;
  u8 fEB;
  u8 fEC;
  u8 pED[5];
  u8 fF2;
  u8 fF3;
  u8 rest[100];
} InitVoice15;
s32 func_80015F64(InitVoice15 *v, s32 kind, s16 pitch, s16 level, s32 priority)
{
  u8 saved;
  s16 rate;
  s32 sample;
  u8 *p;
  u32 i;
  saved = v->fE9;
  v->f4 = 0;
  p = (u8 *)v;
  for (i = 0; i < 0x158; i++)
  {
    *p++ = 0;
  }
  v->fEC = 255;
  v->fDE = 255;
  rate = 0x6000 / D_800604DC;
  v->fF2 = 0;
  v->fF3 = 127;
  v->fDC = 127;
  v->fDD = 64;
  v->fDF = 1;
  v->fE1 = 127;
  v->fE6 = 1;
  v->fE8 = 15;
  v->fE7 = 255;
  v->fE2 = 127;
  v->fC6 = kind;
  v->fC0 = 65535;
  v->fBA = 1;
  v->fC2 = 1;
  v->fC4 = 1;
  v->f18 = -1;
  v->fBE = 128;
  v->fD0 = 128;
  v->fB8 = 128;
  v->f98 = D_800604F0;
  v->fE9 = saved;
  v->fBE = pitch;
  v->f3C = 99.9f;
  v->f8C = 0.03125f;
  v->f78 = 1.0f;
  v->f7C = 1.0f / 255;
  v->f80 = 1.0f / 15;
  v->fC8 = rate;
  v->fBC = rate;
  v->fD0 = level;
  v->f64 = priority;
  v->f60 = D_800604E8;
  sample = D_800604D4[kind];
  D_800604E8++;
  v->f9C = sample;
  v->f4 = sample;
  return v->f60;
}
