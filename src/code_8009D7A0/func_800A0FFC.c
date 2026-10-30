/* @header
 * func_800A0FFC
 * VRAM 0x800A0FFC | ROM 0x9449C | size 0x110
 * asm: asm/nonmatchings/code_8009D7A0/func_800A0FFC.s
 */
#include "common.h"

void func_800A7188(void *);
void func_800A7C40(void *, s8, s16);
void func_800A7F6C(void *, s32);
void func_800A837C(void *);
void func_800D427C(void *, s16, s32);
s16 func_800D5438(void *, s32);
void func_800D7E80(void *, s32);
void func_800D8D74(void *, s32);
void func_800A0FFC(void) {
 *(u64 *)((u8 *)D_800EB408+0x20) |= 0x1000000000ULL;
 switch(*(s16 *)((u8 *)D_800EB408+0xC)) {
 case 0:
 func_800A7C40(D_800EB408, *(s8 *)D_800EB408,0xC0);
 *(u64 *)((u8 *)D_800EB408+0x20) &= ~0x200000ULL;
 func_800D427C(D_800EB408,func_800D5438(D_800EB408,0),2);
 func_800D7E80(D_800EB408,0);
 func_800A7F6C(D_800EB408,0);
 func_800A837C(D_800EB408);
 ++*(s16 *)((u8 *)D_800EB408+0xC);
 case 1:
 func_800D8D74(D_800EB408,0);
 func_800A7188(D_800EB408);
 }
}
