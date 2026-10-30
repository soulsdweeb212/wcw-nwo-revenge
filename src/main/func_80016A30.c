/* @header
 * func_80016A30
 * VRAM 0x80016A30 | ROM 0x17630 | size 0x4AC
 * asm: asm/nonmatchings/main/func_80016A30.s
 */
#include "common.h"

typedef struct 
{
  s32 f0;
  s32 f4;
  s32 f8;
  s32 fC;
  void *callback;
  void *heap;
  s32 value;
  s32 f1C;
} Nw2Cfg;
typedef struct Nw2Pool
{
  struct Nw2Pool *f0;
  struct Nw2Pool *f4;
  s32 f8;
  s32 fC;
  void *f10;
} Nw2Pool;
typedef struct 
{
  void *f0;
  s32 f4;
  s32 f8;
  s32 fC;
  s32 f10;
  s32 f14;
  s32 f18;
  s32 f1C;
  void *f20;
  s32 f24;
  void *f28;
  s32 f2C;
  void *f30;
  s32 f34;
  s32 f38;
  s32 f3C;
  s32 f40;
  s32 f44;
  s32 f48;
  s32 f4C;
  s32 f50;
  s32 f54;
  s32 f58;
  s32 f5C;
  s32 f60;
  s32 f64;
  s32 f68;
  s32 f6C;
  s16 f70;
  s16 f72;
  void *f74;
} Nw2Dma;
extern s32 D_80036F40;
extern u8 D_8003A5C0[];
extern f64 D_8003B400;
extern f64 D_8003B408;
extern volatile u8 D_80062520;
extern s32 D_8006252C;
extern u32 D_80062530;
extern s32 D_80062534;
extern s32 D_80062538;
extern u8 D_80062540[];
extern volatile s32 D_80062558;
extern Nw2Pool *D_8006255C;
extern void *D_80062560;
extern void *D_80062564;
extern volatile s32 D_80062568;
extern volatile s32 D_8006256C;
extern void *D_80062570;
extern void * volatile D_80062574;
extern void *D_8006E1A8[];
extern Nw2Dma *D_8006E1B0[];
extern u8 D_8006E3A8[];
extern u8 D_8006E3E0[];
extern u8 func_8002BC40[];
extern u8 func_8002BD10[];
extern u8 D_8002BD10[];
void func_80017510(void *, void *, s32);
void func_8001C890(void *, void *, s32);
void func_8001C8C0(void *, s32, void *, s32, void *, s32);
s32 startThread(void *);
void func_8002021C(void *, void *);
void *func_800202B0(s32, s32, void *, s32, s32);
void *initControllerPakDescriptor(void);
void *func_80021B80(void);
s32 func_80022000(s32);
void *func_80016EDC(void);
void *func_800173C0(void);
void func_80016A30(s32 arg0, Nw2Cfg *arg1, s32 arg2, s32 *arg3, s32 arg4, s32 arg5, s32 arg6)
{
  Nw2Dma *r2;
  Nw2Dma *rec;
  u32 i;
  s32 v;
  f32 fv;
  f64 dv;
  void *p;
  s32 sz;
  u8 *q;
  D_80062570 = initControllerPakDescriptor();
  p = func_80021B80();
  D_80062520 = 0;
  D_80062574 = p;
  D_80062558 = arg0;
  D_80062568 = arg5;
  do
  {
    D_8006256C = 0x50;
  }
  while (0);
  *((void **) (((u8 *) arg1) + 0x10)) = func_800173C0;
  arg1->value = func_80022000(arg3[0]);
  D_8006255C = func_800202B0(0, 0, arg1->heap, 1, arg4 * 0x14);
  D_80062560 = func_800202B0(0, 0, arg1->heap, 1, arg4 * 0x30);
  D_80062564 = func_800202B0(0, 0, arg1->heap, 1, arg4 * 8);
  v = arg3[1];
  dv = (f64) v;
  if (v < 0)
  {
    dv += D_8003B400;
  }
  fv = (((f32) dv) * ((f32) arg1->value)) / ((f32) arg6);
  v = (s32) fv;
  D_80062530 = v;
  dv = (f64) v;
  if (v < 0)
  {
    dv += D_8003B408;
  }
  if (((f32) dv) < fv)
  {
    D_80062530 = v + 1;
 do { } while (0);
  }
  q = D_8006E3E0;
  D_80062530 = ((D_80062530 / 184) + 1) * 0xB8;
  D_8006252C = D_80062530 - 0xB8;
  D_80062534 = (D_80062530 + (sz = D_8006256C)) + 0x10;
  func_80017510(q, arg1, sz);
  {
    u32 tq = (u32)q & 1;
    if (tq >> 1) {
      D_80062538 = 0;
    }
  }
  D_8006255C->f4 = 0;
  D_8006255C->f0 = 0;
  for (i = 0; i < (arg4 - 1); i++)
  {
    func_8002021C(&D_8006255C[i + 1], &D_8006255C[i]);
    D_8006255C[i].f10 = func_800202B0(0, 0, arg1->heap, 1, arg5);
  }

  D_8006255C[i].f10 = func_800202B0(0, 0, arg1->heap, 1, arg5);
  for (i = 0; i < 2; i++)
  {
    D_8006E1A8[i] = func_800202B0(0, 0, arg1->heap, 1, arg3[2] * 8);
  }

  D_80062538 = arg3[2];
  for (i = 0; i < 4; i++)
  {
    rec = func_800202B0(0, 0, arg1->heap, 1, 0x90);
    D_8006E1B0[i] = rec;
    rec->f70 = 2;
    D_8006E1B0[i]->f74 = D_8006E1B0[i];
    D_8006E1B0[i]->f0 = func_800202B0(0, 0, arg1->heap, 1, D_80062534 * 4);
    r2 = D_8006E1B0[i];
    r2->f18 = 2;
    r2->f20 = func_8002BC40;
    r2->f24 = func_8002BD10 - func_8002BC40;
    r2->f28 = D_8002BD10;
    r2->f30 = D_8003A5C0;
    r2->f2C = 0x1000;
    r2->f34 = 0x800;
    r2->f1C = 0;
    r2->f38 = 0;
    r2->f3C = 0;
    r2->f40 = 0;
    r2->f44 = 0;
    r2->f50 = 0;
    r2->f54 = 0;
  }

  func_8001C890(D_8006E3A8, D_8006E3A8 + 0x18, 8);
  func_8001C890(D_8006E3A8 - 0x38, D_8006E3A8 - 0x20, 8);
  func_8001C890(D_80062540, D_80062564, arg4 * 2);
  if (D_80036F40 == 0)
  {
    func_8001C8C0(D_8006E3A8 - 0x1E8, 3, func_80016EDC, 0, (void *) (&D_80062520), arg2);
    startThread(D_8006E3A8 - 0x1E8);
  }
  D_80036F40 = 1;
}
