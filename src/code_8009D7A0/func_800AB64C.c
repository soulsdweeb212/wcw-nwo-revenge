/* @header
 * func_800AB64C
 * VRAM 0x800AB64C | ROM 0x9EAEC | size 0x134
 * asm: asm/nonmatchings/code_8009D7A0/func_800AB64C.s
 */
#include "common.h"

void func_800AD958(s32);
void func_800ADA38(void *);
s8 func_800D4198(s16);
extern u8 D_800E3548[];
extern f64 D_800E4E00,D_800E4E08,D_800E4E10,D_800E4E18;
extern u8 *D_800F9B60,*D_800FABD0;
#define F(p,o,t) (*(t *)((p)+(o)))
void func_800AB64C(void) {
 s32 action;
 s16 base,state,chance;
 s8 result;
 if(D_800E4E00 < (f64)F(D_800FABD0,0x34,f32)) {
  func_800ADA38(D_800E3548); return;
 }
 base=(s32)((f64)F(D_800FABD0,0x12,s16)*D_800E4E08)+F(D_800FABD0,0x18,s16)*3;
 state=F(D_800F9B60,0xA,s16);
 chance=base;
 if(state==0x1F) chance=(s32)((f64)base*D_800E4E10);
 if(state==7) chance=(s32)((f64)chance*D_800E4E18);
 result=func_800D4198(chance);
 action=0x1F;
 if(result && F(D_800FABD0,0x16,s16)<0xD2) action=0x20;
 func_800AD958(action);
}
