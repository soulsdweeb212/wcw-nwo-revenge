#include "common.h"

extern s16 D_80059D82;
extern void *D_80036CB4[];
extern void *D_80036CCC[];
extern void *D_80036CE4[];
extern s8 D_80036CAC[];
extern s32 D_80058A0C;
extern u8 D_80058A10[];
extern s32 D_80058F90;
extern u8 D_80058FA0[];
extern s32 D_80059520;
extern u8 D_80059528[];
extern s32 D_80059898;
extern u8 D_800598A0[];
extern s32 D_80059C10;
extern u8 D_80059C18[];
extern s32 D_80059CC8;
extern u8 D_80059CD0[];
extern u8 D_80056950[];
extern u8 *D_80056954;
extern u8 D_80036750[];
extern u8 D_80036758[];
extern u8 D_80036760[];
extern u8 D_80036768[];
extern u8 D_80036790[];
extern u8 D_800367B8[];
extern const f64 D_8003B230;
extern const f64 D_8003B238;
extern const f64 D_8003B240;
s32 func_80007020(void *, void *, void *, s8);
void initializeTransformNode(void *, s32, f32, f32, f32);
void func_80007818(void *, void *, s32, s32);
void func_80001544(void *);
void func_80007E14(void *, f32);
void func_80001DC4(void *);
void func_8000EF90(void)
{
  u8 *base;
  u8 *node;
  u32 s1;
  unsigned int s2;
  u32 s3;
  u32 t;
  s16 idx;
  s32 q;
  f64 a;
  f64 b;
  f64 c;
  f64 d;
  f32 ft;
  f32 zero;
  u8 *new_var3;
  u8 *p;
  int new_var2;
  s32 r;
  idx = D_80059D82;
  s1 = 1;
  D_80058A0C = func_80007020(D_80058A10, D_80036CB4[idx], D_80036CCC[idx], D_80036CAC[idx]);
  idx = D_80059D82;
  s2 = 1;
  ft = 0.0f;
  s3 = 0x1B8;
  zero = ft;
  D_80058F90 = func_80007020(D_80058FA0, D_80036CB4[idx], D_80036CE4[idx], D_80036CAC[idx]);
  D_80059520 = func_80007020(D_80059528, D_80036768, D_80036790, 0x13);
  D_80059898 = func_80007020(D_800598A0, D_80036768, D_800367B8, 0x13);
  D_80059C10 = func_80007020(D_80059C18, D_80036750, D_80036758, 3);
  r = func_80007020(D_80059CD0, D_80036750, D_80036760, 3);
  {
    base = D_80056950;
  }
  D_80059CC8 = r;
  initializeTransformNode(base, 0, zero, zero, zero);
  node = (D_80056954 = base + 0xDC);
  loop1:
  initializeTransformNode(node, 0, zero, zero, zero);

  new_var2 = 4;
  if (s2 == new_var2)
  {
    func_80007818(node, D_80058A10, D_80058A0C, 0);
  }
  else
  {
    func_80007818(node, D_80059528, D_80059520, 0);
  }
  func_80001544(node);
  *((f32 *) ((*((u8 **) (node + 0x14))) + 0x24)) = 3000.0f;
  p = node + 0x1C;
  *((u8 **) node) = base;
  *((u8 **) (node + 8)) = base + s3;
  q = s1 & 3;
  a = (f64) q;
  if (q < 0)
  {
    a += D_8003B230;
  }
  ft = a * D_8003B238;
  func_80007E14(p, ft);
  s3 += 0xDC;
  node += 0xDC;
  s1++;
  s2++;
  if (s2 < 5)
  {
    goto loop1;
  }
  ;
  t = 5;
  c = D_8003B240;
  d = D_8003B238;
  for (s3 = s1 * 0xDC + 0xDC; t < 8; t++)
  {
    node = base + (s1 * 0xDC);
    initializeTransformNode(node, 5, 0.0f, 0.0f, 0.0f);
    func_80007818(node, D_80059C18, D_80059C10, 0);
    func_80001544(node);
    ;
    *((u8 **) node) = base;
    *((u8 **) (node + 8)) = base + s3;
    q = s1 & 3;
    b = (f64) q;
    new_var3 = 0x1C + node;
    if (q < 0)
    {
      b += c;
    }
    func_80007E14(new_var3, (f32) (b * d));
    s3 += 0xDC;
    s1++;
  }

  *((s32 *) ((base + (s1 * 0xDC)) - (0xD4 ^ 0))) = 0;
  func_80001DC4(D_80056950);
}
