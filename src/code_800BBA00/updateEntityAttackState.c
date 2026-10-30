/* @header
 * updateEntityAttackState  (originally func_800C9014)
 * VRAM 0x800C9014 | ROM 0xBC4B4 | size 0x4B8
 * asm: asm/nonmatchings/code_800BBA00/updateEntityAttackState.s
 */
#include "common.h"

/* Entity attack action state machine. Runs the current entity (D_800FAF5C)
 * through attack states 0..6: plays the attack animation (func_800D427C),
 * aligns it to its target (func_800D2BEC/func_800D2B64), checks attack inputs
 * (func_800A93C0, actionFlags), then clears the attack flag and the entity's
 * 0x40000000 status bit when the attack finishes. */
typedef struct {
    u8 pad0[4];
    s16 animTimer;      /* +0x04 countdown; <=0 means the animation is done */
    u8 pad6[6];
    s16 state;          /* +0x0C case selector */
    u8 padE[0x12];
    u64 flags;          /* +0x20 entity status bits */
    u8 pad28[0x338];
    u16 actionFlags;    /* +0x360 */
    s8 f362;            /* +0x362 */
} ObjC9014;
extern ObjC9014 *D_800FAF5C;
extern void *D_800F9B00,*D_800F9B64;
extern s8 D_800FADB8,D_800EB550[];
extern u8 D_800FABE4; extern u16 D_800FABE6,D_800FAF8A;
extern u8 D_800F9D10[];
s8 func_800B71F8(void*,void*,s32);s8 func_800A93C0(void);
void func_800D427C(void*,s32,s32);void func_800D4AD0(void*);
void func_800A7D1C(void*,s32);void beginEntityActionA8D8C(void*);
s16 func_800D5438(void*,s32);
s32 func_800D2BEC(void*,void*,void*,f32,u16,s32);
s32 func_800D2B64(void*,f32,u16,s32);
void applyMovementToEntityPair(void*,void*,u16);void func_800B68A0(void*,void*,void*);
#define ENT D_800FAF5C
void updateEntityAttackState(void){
 switch(ENT->state){
 case 0:{s32 animId;D_800EB550[D_800FADB8]=D_800FABE4;
 if(func_800B71F8(ENT,D_800F9B00,0xB)){ENT->state++;animId=0x10C0;}else{ENT->state=6;ENT->actionFlags|=8;animId=0x10D0;}
 func_800D427C(ENT,animId,3);break;}
 case 1:func_800D2BEC(ENT,D_800F9B00,0,4.0f,0,0xFFFFE);
 if(ENT->animTimer<=0){func_800D427C(ENT,0x10C2,1);ENT->actionFlags&=~0x14;ENT->state++;}break;
 case 2:
 ENT->flags|=0x200000000000ULL;
 if((ENT->actionFlags&1)||(D_800FAF8A&0x10)||func_800A93C0()){
 ENT->actionFlags|=1;func_800D427C(ENT,0x10C4,1);ENT->state++;
 }else if(ENT->actionFlags&0x10){s32 animId;if(ENT->flags&0x8000000)animId=0x10CE;else animId=0x10CA;func_800D427C(ENT,animId,1);ENT->state=4;
 }else if(ENT->actionFlags&4){func_800D427C(ENT,0x10C6,1);ENT->state=5;
 }else if(ENT->actionFlags&2){func_800D427C(ENT,func_800D5438(D_800F9B00,1),1);
 }else applyMovementToEntityPair(ENT,D_800F9D10+D_800EB550[D_800FADB8]*0x3B0,D_800FABE6);
 break;
 case 3:func_800D2BEC(ENT,D_800F9B00,0,4.0f,0,0xFFFFE);if(ENT->animTimer<=0){func_800D4AD0(ENT);func_800A6C48(ENT,0x2B);{ObjC9014 *ent=ENT;ent->f362=-1;ent->flags&=~0x40000000ULL;}}break;
 case 4:func_800D2B64(ENT,2.0f,0,2);if(ENT->animTimer<=0){func_800D4AD0(ENT);func_800A6C48(ENT,0x2B);{ObjC9014 *ent=ENT;ent->f362=-1;ent->flags&=~0x40000000ULL;}}break;
 case 5:func_800D2BEC(ENT,D_800F9D10+D_800EB550[D_800FADB8]*0x3B0,0,4.0f,0,0xFFFFE);if(ENT->animTimer<=0){func_800B68A0(D_800F9B64,D_800F9B64,ENT);func_800D4AD0(ENT);beginEntityActionA8D8C(ENT);{ObjC9014 *ent=ENT;ent->f362=-1;ent->flags&=~0x40000000ULL;}}break;
 case 6:func_800D2BEC(ENT,D_800F9B00,0,4.0f,0,0xFFFFE);if(ENT->animTimer<=0){func_800A7D1C(ENT,0x25);func_800B68A0(ENT,D_800F9B00,ENT);func_800D4AD0(ENT);beginEntityActionA8D8C(ENT);{ObjC9014 *ent=ENT;ent->f362=-1;ent->flags&=~0x40000000ULL;}}break;
 }
}
#undef ENT
