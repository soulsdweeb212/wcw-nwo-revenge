/* @header
 * updateEntityHealthLevel  (originally func_800E13F8)
 * VRAM 0x800E13F8 | ROM 0xD4898 | size 0x168
 * asm: asm/nonmatchings/code_800DE9C0/func_800E13F8.s
 */
#include "common.h"

extern u16 D_800FAF50[];
extern s16 D_800F98D8[];
s32 func_800BF2FC(void *);
static inline u16 getCount(u8 *p) { if (*(s16 *)(p+10)==0x42) return 0; return D_800FAF50[*(s8 *)p]; }
static inline s16 getValue(u8 *p) { if (*(s16 *)(p+10)==0x42) return 255; return func_800BF2FC(p); }
/* Computes entity p's health/status level code, stores it into D_800F98D8[its
 * id] and returns it. Entities with the 0x80000 flag use the 0xF3D/0xF3E
 * "downed" codes; others derive 1..3 from their item count (or 0..2 from the
 * remaining health), then offset by 0xF2D and +6 when the 0x200000 flag is set. */
s16 updateEntityHealthLevel(u8 *p) {
 s16 result, base;
 s16 value;
 u16 count;
 if (*(u64 *)(p+0x20) & 0x80000ULL) {
  result = 0xF3E;
  if (!(*(u64 *)(p+0x20) & 0x200000ULL)) result=0xF3D;
  if (*(u64 *)(*(u8 **)(p+0x364)+0x38) & 0x800000ULL) result-=2;
 } else {
  count=getCount(p);
  if ((s16)count>=15) {
   result=1;
   if ((s16)count>=22) result=2;
  } else {
   value=getValue(p);
   if (value>=128) result=0;
   else { result=2; if(value>=64) result=1; }
  }
  base=result+0xF2D;
  result=base;
  if (*(u64 *)(p+0x20)&0x200000ULL) result=base+6;
 }
 D_800F98D8[*(s8 *)p]=result;
 return result;
}
