/* @header
 * func_800E0590
 * VRAM 0x800E0590 | ROM 0xD3A30 | size 0x130
 * asm: asm/nonmatchings/code_800DE9C0/func_800E0590.s
 */
#include "common.h"

extern f64 D_800E76D8;
f32 func_800D3EEC(void *,void *,s32);
void func_800E212C(void *);
void beginPairedEntityActions(void *,s32,void *,s32);
s32 func_800E0590(u8 *arg0,u8 *arg1,s32 arg2,f32 *arg3) {
 if(arg2 & 2) {
 if((*(u64 *)(arg1+0x20)&0x400000) && !(*(u64 *)(arg1+0x20)&0x1000000000ULL)) {
 if((*(u64 *)(arg0+0x20)&*(u64 *)(arg1+0x20)&0x40) || (*(u64 *)(arg0+0x20)&*(u64 *)(arg1+0x20)&0x100)) {
 if(arg3[1] < func_800D3EEC(arg1+0x4C,arg0+0x6C,*(s32 *)(arg1+0x58))+D_800E76D8) {
 func_800E212C(arg0); beginPairedEntityActions(arg0,0x30,arg1,0x31); return 1;
 }
 }
 }
 }
 return 0;
}
