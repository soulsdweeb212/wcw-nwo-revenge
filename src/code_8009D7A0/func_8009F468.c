#include "common.h"

extern s32 D_800E3CA0[];
extern void *D_800FAF5C;
void func_800D25D0(void *,f32);
s32 func_800D2B64(void *,f32,u16,s32);
s8 func_800D4198(s16);
s16 func_800C778C(void *);
void func_800D427C(void *,s16,s32);
void func_800D4AD0(void *);
void beginEntityActionA8D8C(void *);
/* 'Taunt/celebration' action for attacker entity D_800EB408: apply its physics
 * modifiers, then pick an animation from the entity's flags (0x80 -> substitute
 * the action-table entry at 0x58 and play 0x10AB; 0x8000000 -> 0x1047; else a
 * random gate that can switch to state 2 and force action variant 0x1; else
 * 0x1047/0x1046 depending on the owner's flags), then count down and finish. */
void func_8009F468(void) {
 s16 anim;
 func_800D25D0(D_800EB408,4.0f);
 func_800D2B64(D_800EB408,2.0f,0,0xFFFFE);
 switch (((Nw2F408*)D_800EB408)->fC) {
 case 0:
 if (*(u64*)((u8*)D_800EB408+0x20)&0x80ULL) {
 *(s32*)((u8*)D_800EB408+0x58)=D_800E3CA0[*(s16*)((u8*)D_800EB408+0x3C)];
 anim=0x10AB;
 } else if (*(u64*)((u8*)D_800EB408+0x20)&0x8000000ULL) anim=0x1047;
 else if (func_800D4198(300)) {
 *(u32*)((u8*)D_800EB408+0x30)=(*(u32*)((u8*)D_800EB408+0x30)&0x8FFFEFFF)|0x10000000;
 func_800D427C(D_800EB408,func_800C778C(D_800EB408),1);
 ((Nw2F408*)D_800EB408)->fC=2;
 break;
 } else if (*(u64*)(*(u8**)((u8*)D_800EB408+0x364)+0x38)&0x200ULL) anim=0x1047;
 else anim=0x1046;
 func_800D427C(D_800EB408,anim,1);
 ((Nw2F408*)D_800EB408)->fC++;
 break;
 case 1:
 if (((Nw2F408*)D_800EB408)->f4<=0) func_800A6C48(D_800EB408,1);
 break;
 case 2:
 if (((Nw2F408*)D_800EB408)->f4<=0) {func_800D4AD0(D_800FAF5C);beginEntityActionA8D8C(D_800FAF5C);}
 break;
 }
}
