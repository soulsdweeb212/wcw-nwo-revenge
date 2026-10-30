/* @header
 * buildEntityPartTransforms  (originally func_8000D770)
 * VRAM 0x8000D770 | ROM 0xE370 | size 0x420
 * asm: asm/nonmatchings/main/func_8000D770.s
 */
#include "common.h"

/* Build the transform matrices for up to 19 entity parts.
 * For each part i (kind D_80030894[i]) it derives the part's local offset
 * (x/z) from the kind-specific table, computes its angle and scale from the
 * measured distance (nw2Sqrtf) and per-part tables (D_800308BC/D_800308A8),
 * clamps the height against the upper/lower bounds, and composes the scale,
 * rotation and placement offset into dst->mat. */
extern u8 D_80030894[];
extern u8 D_800308A8[];
extern f32 D_800308BC[];
extern u8 D_8006527C[];
extern f32 D_80070C70[],D_80070C78[],D_80070C88[],D_80070C8C[],D_80070C90[],D_80070C94[],D_80070C98[],D_80070C9C[],D_80070CAC[],D_80070CB4[],D_80070E20[],D_80070E28[];
extern f64 D_8003B1E0,D_8003B1E8,D_8003B1F0;

void func_8000801C(void*,f32,f32,f32,f32*,f32*);
f32 func_80003A3C(f32,f32);
f32 func_80003CF0(f32);
f32 nw2Sqrtf(f32);
void func_8001BE70(void*,f32,f32,f32);
void func_80007E14(void*,f32);
void multiplyMatrix4x4(void*,void*,void*);
void func_80007E04(void*,f32,f32,s32);

typedef struct {
  u8 pad0[0x18];
  u8 f18;
  u8 pad19[3];
  f32 mat[4][4];
  f32 mat2[4][4];
  u8 pad9C[0x40];
} Nw2Part770;
typedef struct { Nw2Part770 part[0x17]; } Nw2Entity770;

#define FLD(base,off) (*(f32*)((u8*)(base) + (off)))

void buildEntityPartTransforms(Nw2Part770 *arg0, s16 id, f32 upper, f32 lower) {
  u32 size;
  s32 off;
  u32 i;
  Nw2Part770 *src;
  Nw2Part770 *dst;
  f32 m[4][4];
  f32 r[4][4];
  f32 x, z;
  f32 angle;
  f32 height;
  f32 zoff;
  u32 conv;
  f32 ta,tb;
  f32 sx,sz;
  u8 v18;
  f64 scale;
  s32 inside;
  f64 threshold;
  s32 group;
  u8 kind;
  f32 tz, tx;
  f32 fs;

  i = 1;
  group = id * 0xB24;
  off = group + 0x7C;
  src = (Nw2Part770 *)((Nw2Entity770 *)D_8006527C + id);
  dst = arg0 + 1;
loop:
  kind = D_80030894[i];
  if (kind) {
  switch (kind) {
  case 2:
    ta = FLD(D_80070CAC,off);
    tb = FLD(D_80070CB4,off);
    x = ta;
    z = tb;
    break;
  case 4:
    ta = FLD(D_80070E20,group);
    tb = FLD(D_80070E28,group);
    x = ta;
    z = tb;
    break;
  case 3:
    func_8000801C(src->mat2, FLD(D_80070C88,off), FLD(D_80070C8C,off), FLD(D_80070C78,off), &x, &z);
    x = -x;
    break;
  case 1:
    func_8000801C(src->mat2, FLD(D_80070C70,off), FLD(D_80070C8C,off), FLD(D_80070C90,off), &x, &z);
    x = -x;
    break;
  }
    tz = z - FLD(D_80070C9C,off);
    tx = x - FLD(D_80070C94,off);
    z = tz;
    x = tx;
    angle = func_80003A3C(z, x) * D_8003B1E0;
    conv = (u32)(nw2Sqrtf(x*x + z*z) * D_800308BC[i]);
    size = conv;
    if ((u8)size < D_800308A8[i]) size = D_800308A8[i];
    zoff = *(f32*)((u8*)D_80070C9C + off);
    threshold = D_8003B1E8;
    if (func_80003CF0(FLD(D_80070C94,off)) < threshold && func_80003CF0(zoff) < threshold) inside = 1; else inside = 0;
    height = lower;
    if (inside && (upper - 20.0f) <= FLD(D_80070C98,off)) height = upper;
    v18 = src->f18;
    fs = (f32)(u8)size;
    scale = D_8003B1F0;
    sx = fs * scale;
    dst->f18 = v18;
    sz = (f32)D_800308A8[i] * scale;
    func_8001BE70(m, sx, 1.0f, sz);
    func_80007E14(r, angle);
    multiplyMatrix4x4(m, r, dst->mat);
    func_80007E04(dst->mat, -FLD(D_80070C94,off), height, *(volatile s32*)((u8*)D_80070C9C + off));
  }
  off += 0x7C;
  src++;
  dst++;
  i++;
  if (i < 20) goto loop;
}
