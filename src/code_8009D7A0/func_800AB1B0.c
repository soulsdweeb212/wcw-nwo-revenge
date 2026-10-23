#include "common.h"

s8 func_800D4198(s16);
extern u8 D_8007E228[];
extern f64 D_800E4DE0;
extern void *D_800F9B60, *D_800FABD0, *D_800FAF58;
s32 func_800AB1B0(void) {
 if (!func_800D4198(200)) return 0;
 if (*(u16 *)(D_8007E228+0x58) & 0x100) {
  if (*(u64 *)((u8 *)D_800F9B60+0x20) & 0x200) return 0;
 } else {
  if (!(*(u64 *)((u8 *)D_800FAF58+0x20) & 0x8000) &&
      !(*(u64 *)((u8 *)D_800F9B60+0x20) & 0x8000) &&
      !(D_800E4DE0 < (f64)*(f32 *)((u8 *)D_800FABD0+0x34))) return 0;
 }
 *(s16 *)((u8 *)D_800FABD0+8)=1;
 return 1;
}
