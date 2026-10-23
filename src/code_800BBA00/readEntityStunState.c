#include "common.h"

extern u8 D_800F9D10[], D_800F9D24[];
s16 updateEntityStunTimer(void *, s32, s32);
/* Reads entity arg0's stun/health state. If the entity's 0x80000 flag is set,
 * the health is forced to 100 and the stun timer comes from
 * updateEntityStunTimer; otherwise the stored health (s16 at +0x14, clamped to
 * 1..99 unless the 0x20000 flag is set) is returned with a zero timer. Returns
 * 1 when the entity carries the 0x40000000000 flag. */
s32 readEntityStunState(s8 arg0, s16 *arg1, s16 *arg2) {
 s32 off = arg0 * 0x3B0;
 if (*(u64 *)(D_800F9D30 + off) & 0x80000ULL) {
  *arg1 = 100;
  *arg2 = updateEntityStunTimer(D_800F9D10 + off, 0, 4);
 } else {
  *arg1 = *(s16 *)(D_800F9D24 + off);
  if (*arg1 >= 100) *arg1 = 99;
  else if (*arg1 <= 0 && !(*(u64 *)(D_800F9D30 + off) & 0x20000ULL)) *arg1 = 1;
  *arg2 = 0;
 }
 if (*(u64 *)(D_800F9D30 + arg0 * 0x3B0) & 0x40000000000ULL) return 1;
 return 0;
}
