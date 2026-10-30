/* @header
 * func_800CBC4C
 * VRAM 0x800CBC4C | ROM 0xBF0EC | size 0x110
 * asm: asm/nonmatchings/code_800BBA00/func_800CBC4C.s
 */
#include "common.h"

void func_800A7C40(void *, s8, s16);
void func_800A7F6C(void *, s32);
s32 func_800CBC4C(u8 *arg0, u8 *arg1) {
 s16 anim;
 s8 id;
 u8 flags = arg0[0x36];
 if (flags & 1) anim = (-((flags & 2) != 0) & 0xC6) | 0xC4;
 else anim = (-((flags & 2) != 0) & 0xCA) | 0xC8;
 if ((arg0[0x36] & 0x10) && !(*(u64 *)(arg1+0x20) & 9)) id = arg1[0];
 else id = arg0[0];
 func_800A7C40(arg0,id,anim);
 func_800A7F6C(arg0,0);
 if ((arg0[0x36] & 8) || (*(u16 *)(arg1+0x360) & 0x10)) {
 func_800A7C40(arg1,id,(s16)(*(u16 *)(arg0+0x386)+1));
 return 1;
 }
 return 0;
}
