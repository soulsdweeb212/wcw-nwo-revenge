/* @header
 * func_800D0700
 * VRAM 0x800D0700 | ROM 0xC3BA0 | size 0x104
 * asm: asm/nonmatchings/code_800BBA00/func_800D0700.s
 */
#include "common.h"

s8 func_800B71F8(void *, void *, s32);
void func_800D0700(void *arg0, void *arg1, s32 arg2) {
 if ((*(u64 *)((u8 *)arg0+0x20) & 0x80000) || !(*(u64 *)((u8 *)arg1+0x20) & 0x80000)) {
  if (!(*(u64 *)((u8 *)arg0+0x20) & 9) && !(*(u64 *)((u8 *)arg0+0x20) & 0x4000000) && (arg2 & 0xC030)) {
   if (func_800B71F8(arg0,arg1,1)) *(u64 *)((u8 *)arg0+0x20) |= 0x2000000;
   *(u64 *)((u8 *)arg0+0x20) |= 0x4000000;
  }
 }
}
