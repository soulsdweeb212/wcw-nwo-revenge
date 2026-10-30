/* @header
 * updateEntitySetupAction  (originally func_8009DC18)
 * VRAM 0x8009DC18 | ROM 0x910B8 | size 0x148
 * asm: asm/nonmatchings/code_8009D7A0/func_8009DC18.s
 */
#include "common.h"

void func_800D4270(void *);
void func_800D427C(void *,s16,s32);
s16 func_800D4D44(void *,s32,f32);
void func_8000B728(s8);
void func_8000C784(s8);
void func_800C2B8C(void);
void func_800A6BE0(void *,s32);
extern u8 D_800FADCE;
/* Two-state entity setup action (state at +0xC). State 0: reset the animation
 * system, pick the idle (0x1081) or the boundary-derived animation, run the
 * 0x4000000000000/0x400000000 setup hooks, then advance. State 1: when the
 * match is configured (D_800FADCE bit0), finish setup and switch to action 1. */
void updateEntitySetupAction(void) {
 switch (*(s16*)((u8*)D_800EB408+0xC)) {
 case 0:
 func_800D4270(D_800EB408);
 if (*(u64*)((u8*)D_800EB408+0x20)&0x80) func_800D427C(D_800EB408,0x1081,0);
 else func_800D427C(D_800EB408,func_800D4D44(D_800EB408,1,400.0f),0);
 if (*(u64*)((u8*)D_800EB408+0x20)&0x4000000000000ULL) func_8000B728(*(s8*)D_800EB408);
 if (*(u64*)((u8*)D_800EB408+0x20)&0x400000000ULL) func_8000C784(*(s8*)D_800EB408);
 (*(s16*)((u8*)D_800EB408+0xC))++;
 break;
 case 1:
 if (D_800FADCE&1) {func_800C2B8C();func_800A6BE0(D_800EB408,1);}
 break;
 }
}
