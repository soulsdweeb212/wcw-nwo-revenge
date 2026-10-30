/* @header
 * func_8009F8D0
 * VRAM 0x8009F8D0 | ROM 0x92D70 | size 0x33C
 * asm: asm/nonmatchings/code_8009D7A0/func_8009F8D0.s
 */
#include "common.h"

extern void *D_800EB40C;extern u16 D_800FAF8A;extern s32 D_800E3CA0[];
void func_800D427C(void *,s32,s32);void func_800A7F6C(void *,s32);void func_800A837C(void *);void func_800A7D1C(void *,s32);void beginEntityActionA8D8C(void *);void func_800B68A0(void *,void *,void *);u16 func_800B6DEC(void *,s32,s32);s8 func_800B71F8(void *,s32,s32);s32 func_800D35B0(s32,s32);void func_800D7690(void *,s32,s32);void func_800D4AD0(void *);
#define F98(p,t,o) (*(t *)((u8 *)(p)+(o)))

/* Counter/response state machine on D_800EB408's s16 state (+0xC).  Case 0 sends
 * animation 0xF08 and stores a heading increment (turn to D_800E3CA0[quadrant]/5)
 * in +0x348, then falls through to case 1.  Case 1 turns the entity toward the
 * target with func_800D35B0 over the six-frame window +0x16, optionally raises a
 * counter flag in +0xE (func_800B71F8, D_800FAF8A & 0xC030), and when the s16
 * timer +4 expires sends the success animation 0xF06/0xF07 (0xF09/0xF0A when the
 * state fA is 0x11) via func_800A7F6C/func_800A837C and advances (case 3) or moves
 * to case 2 against D_800EB40C.  Cases 2 and 3 run animations 15/16 through
 * func_800A7D1C/func_800B68A0 and finish with func_800A6C48(0x2B). */
void func_8009F8D0(void) {
 s32 animId,turnDelta;
 switch(F98(D_800EB408,s16,0xC)) {
 case 0:
 func_800D427C(D_800EB408,0xF08,3);
 turnDelta=func_800D3684(D_800E3CA0[F98(D_800EB408,u16,0x3E)&3],F98(D_800EB408,s32,0x58));
 F98(D_800EB408,s16,0x16)=0;F98(D_800EB408,s16,0xC)++;
 F98(D_800EB408,s32,0x348)=turnDelta/5;
 case 1:
 F98(D_800EB408,s16,0x16)++;
 if(F98(D_800EB408,s16,0x16)<6) F98(D_800EB408,s32,0x58)=func_800D35B0(F98(D_800EB408,s32,0x58),F98(D_800EB408,s32,0x348));
 if(!(F98(D_800EB408,u16,0x28)&0x80) && ((F98(D_800EB408,u64,0x20)&0x80000) || !(F98(D_800EB40C,u64,0x20)&0x80000))) {
 if(!(F98(D_800EB408,u16,0xE)&1) && (D_800FAF8A&0xC030)) {
 F98(D_800EB408,u16,0xE)|=1;
 if(func_800B71F8(D_800EB408,0,3)) F98(D_800EB408,u16,0xE)|=2;
 }
 }
 if(F98(D_800EB408,s16,4)<=0) {
 if(F98(D_800EB408,u16,0xE)&2) {
 animId=0xF07;if(F98(D_800EB408,s16,0xA)==0x11)animId=0xF0A;
 func_800A7F6C(D_800EB408,0x4D);func_800A837C(D_800EB408);F98(D_800EB408,s16,0xC)=3;
 } else {
 animId=0xF06;if(F98(D_800EB408,s16,0xA)==0x11)animId=0xF09;
 func_800A7F6C(D_800EB40C,0x4E);func_800A837C(D_800EB40C);F98(D_800EB408,s16,0xC)++;
 }
 func_800D427C(D_800EB408,animId,3);
 }
 break;
 case 2:
 if(F98(D_800EB408,s16,4)<=0) {
 func_800A7D1C(D_800EB408,15);func_800B68A0(D_800EB408,D_800EB40C,D_800EB408);
 F98(D_800EB408,u16,0x16)=func_800B6DEC(D_800EB408,0,4);
 func_800D7690(D_800EB408,0,0);func_800D4AD0(D_800EB408);beginEntityActionA8D8C(D_800EB408);
 }
 break;
 case 3:
 if(F98(D_800EB408,s16,4)<=0) {
 func_800A7D1C(D_800EB408,16);func_800B68A0(D_800EB408,D_800EB40C,D_800EB408);func_800D4AD0(D_800EB408);func_800A6C48(D_800EB408,0x2B);
 }
 break;
 }
}
