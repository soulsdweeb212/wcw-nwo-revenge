/* @header
 * chooseDodgeAction  (originally func_800DFC8C)
 * VRAM 0x800DFC8C | ROM 0xD312C | size 0x148
 * asm: asm/nonmatchings/code_800DE9C0/chooseDodgeAction.s
 */
#include "common.h"

extern u16 D_800E3CD0[], D_800E3CD8[];
/* Chooses a dodge/counter action for arg0 based on its quadrant (+0x3C) against
 * the incoming direction mask arg2: the two quadrant tables pick actions 0x1C
 * and 0x1B, then the attacker arg1's flags (0x40/0x100) do the same. If arg1
 * carries 0x80, arg0's 0x8000000000 flag is set only when its heading is not
 * behind arg3's angle, and action 0x1D is played. */
void chooseDodgeAction(u8 *arg0,u8 *arg1,s32 arg2,u8 *arg3) {
 s32 index=*(s16*)(arg0+0x3C);
 if (D_800E3CD8[index]&arg2) func_800A6C48(arg0,0x1B);
 else if (D_800E3CD0[index]&arg2) func_800A6C48(arg0,0x1C);
 else if (*(u64*)(arg1+0x20)&0x40) func_800A6C48(arg0,0x1B);
 else if (*(u64*)(arg1+0x20)&0x100) func_800A6C48(arg0,0x1C);
 else if (*(u64*)(arg1+0x20)&0x80) {
 *(u64*)(arg0+0x20)&=~0x8000000000ULL;
 if (func_800D3684(*(s32*)(arg0+0x58),*(s32*)(arg3+0xC))<=0) *(u64*)(arg0+0x20)|=0x8000000000ULL;
 func_800A6C48(arg0,0x1D);
 }
}
