#include "common.h"

extern s32 func_800D4148(void);
extern s16 D_80070494[];
extern u16 D_8007E228[];
extern u16 D_8007E280;
extern s32 D_80038AA8;
extern u64 D_800FA490;
extern u64 D_800FA840;
extern s16 D_800FACEA[];
extern s16 D_800FACEE;
extern s16 D_800FACF0;
extern s32 D_8007E240;
extern s32 D_8007E244;
void func_800BFCF0(void)
{
  s16 *st;
  s16 *hist;
  s16 val;
  st = &D_800FACEA[2];
  if (*st == -1) {
    unsigned long prev;
    s16 r;
    s16 j;
    s16 v;
    s16 nx;
    u16 flags;
    s32 gate;
    s32 *pp;
    s16 *tbl;
    u64 *fl;
    u64 t;
    r = ((s16) func_800D4148()) % 5;
    tbl = &D_80070494[0xBD];
    hist = st - 2;
    prev = hist[0];
    flags = D_8007E280;
    gate = D_80038AA8;
    pp = &D_8007E240;
    j = r;
    for (;;) {
      v = tbl[j];
      if (v == prev) {
        nx = j + 1; j = (nx < 5) ? nx : 0;
        if (j == r) break;
        continue;
      }
      if (!(flags & 0x1000)) break;
      if (gate == 0) break;
      if (v != *pp) break;
      nx = j + 1; j = (nx < 5) ? nx : 0;
      if (j == r) break;
    }
    fl = &D_800FA490;
    hist = &D_800FACEE;
    t = *fl;
    val = D_80070494[0xBD + j];
    *hist = val;
    *fl = t | 0x22ULL;
    if (val == 0) *hist = 1;
    D_8007E240 = *hist;
  }
  st = &D_800FACEA[3];
  if (*st == -1) {
    s16 *tbl2;
    s16 *hist2;
    unsigned long prev2;
    s16 r2, j2, nx2;
    u16 flags2;
    s32 gate2;
    s32 *pp2;
    u64 *fl2;
    u64 t2;
    s16 *dst2;
    r2 = ((s16) func_800D4148()) % 5;
    tbl2 = &D_80070494[0x9D];
    hist2 = st - 2;
    prev2 = hist2[0];
    flags2 = D_8007E280;
    gate2 = D_80038AA8;
    pp2 = &D_8007E244;
    j2 = r2;
    for (;;) {
      if (tbl2[j2] == prev2 || tbl2[j2] == hist2[1]) {
        nx2 = j2 + 1; j2 = (nx2 < 5) ? nx2 : 0;
        if (j2 == r2) break;
        continue;
      }
      if (!(flags2 & 0x1000)) break;
      if (gate2 == 0) break;
      if (tbl2[j2] != *pp2) break;
      nx2 = j2 + 1; j2 = (nx2 < 5) ? nx2 : 0;
      if (j2 == r2) break;
    }
    fl2 = &D_800FA840;
    dst2 = &D_800FACF0;
    t2 = *fl2;
    val = D_80070494[0x9D + j2];
    *dst2 = val;
    *fl2 = t2 | 0x22ULL;
    if (val == 0) *dst2 = 1;
    D_8007E244 = *dst2;
  }
}
