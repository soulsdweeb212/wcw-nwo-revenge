/* @header
 * tryBeginPairedActionOnContact  (originally func_800E0420)
 * VRAM 0x800E0420 | ROM 0xD38C0 | size 0x170
 * asm: asm/nonmatchings/code_800DE9C0/tryBeginPairedActionOnContact.s
 */
#include "common.h"

extern u8 D_8007EF30[];
extern f64 D_800E76D0;
f32 func_800D3EEC(void *,void *,s32);
void beginPairedEntityActions(void *,s32,void *,s32);
/* When the global 0x100 flag or arg0's 0x40 flag is set, and arg0/arg1 share
 * the grapple flags (0x140) with arg1 flagged 0x400000 and not 0x1000000000,
 * and arg0 is not already acting (low 2 flag bits clear): if arg2 is within
 * arg1's boundary distance plus D_800E76D0, clear arg0's high flag and start
 * the paired actions 0x36/0x37. Returns 1 when started, 0 otherwise. */
s32 tryBeginPairedActionOnContact(u8 *arg0,u8 *arg1,f32 arg2) {
 if ((*(u16 *)(D_8007EF30+0x170)&0x100) || (*(u64 *)(arg0+0x20)&0x40)) {
 if (!(*(u64 *)(arg0+0x20)&3) && (*(u64 *)(arg0+0x20)&*(u64 *)(arg1+0x20)&0x140) && (*(u64 *)(arg1+0x20)&0x400000) && !(*(u64 *)(arg1+0x20)&0x1000000000ULL)) {
 if (arg2 < func_800D3EEC(arg1+0x4C,arg0+0x6C,*(s32 *)(arg1+0x58))+D_800E76D0) {
 *(u64 *)(arg0+0x20) &= ~0x200000000000000ULL;
 beginPairedEntityActions(arg0,0x36,arg1,0x37);
 return 1;
 }
 return 0;
 }
 }
 return 0;
}
