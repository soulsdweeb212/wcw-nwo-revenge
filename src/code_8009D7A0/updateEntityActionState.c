/* @header
 * updateEntityActionState  (originally func_800A164C)
 * VRAM 0x800A164C | ROM 0x94AEC | size 0x548
 * asm: asm/nonmatchings/code_8009D7A0/updateEntityActionState.s
 */
#include "common.h"

/* Action/animation state machine for the current entity (D_800EB408).
 * States 0..7 pick animations via func_800D427C, set status/flags bits, and
 * advance when the animation timer (animTimer) runs out or the state timer
 * (timer16) exceeds 60. */
typedef struct {
    s8 id;                  /* +0x00 */
    u8 pad1[3];
    s16 animTimer;          /* +0x04 animation countdown; <=0 means finished */
    s16 curAnim;            /* +0x06 */
    u8 pad8[4];
    s16 state;              /* +0x0C current state (switch selector) */
    u16 statusFlags;        /* +0x0E */
    u8 pad10[4];
    s16 timer14;            /* +0x14 */
    s16 timer16;            /* +0x16 state timer, compared against 60 */
    u8 pad18[8];
    u64 flags;              /* +0x20 entity status bits */
    u8 pad28[0xD];
    u8 actionFlags;         /* +0x35 */
    u8 pad36[0xC];
    s8 animIndex;           /* +0x42 */
} ObjA164;
#define ENT ((ObjA164*)D_800EB408)
extern s16 D_800E3262[],D_800F9B68[];extern s8 D_800FADB8;extern u16 D_800FAF8A;extern u8 D_8007EF30[];
s32 func_800D2B64(void*,f32,u16,s32);void func_800D427C(void*,s32,s32);void func_800D4AD0(void*);void func_800D4CC4(void*);s8 func_800D4198(s16);s8 func_800B71F8(void*,s32,s32);s8 func_800A93C0(void);void beginEntityActionA8D8C(void*);void playEntitySound(s8,s32);
void updateEntityActionState(void){s32 animId;
 func_800D2B64(ENT,2.0f,0,0xFFFFE);
 switch(ENT->state){
 case 0:
 ENT->timer14=0;
 if(ENT->actionFlags&8){ENT->state=2;ENT->flags|=0x10000000;break;}
 if(ENT->actionFlags&4)animId=0x105E;else if(ENT->flags&0x8000000)animId=0x105B;else animId=0x105A;
 func_800D427C(ENT,animId,3);ENT->state++;break;
 case 1:if(ENT->animTimer<=0){func_800D4AD0(ENT);func_800D4CC4(ENT);ENT->state++;ENT->flags|=0x10000000;}break;
 case 2:ENT->flags|=0x1000000000ULL;func_800D427C(ENT,D_800E3262[ENT->animIndex],1);ENT->state++;break;
 case 3:if(ENT->flags&0x200000)animId=0x1060;else animId=0x105F;func_800D427C(ENT,animId,6);ENT->state++;break;
 case 4:if(ENT->animTimer<=0){
 if(ENT->flags&0x200000)animId=0x1066;else animId=0x1065;func_800D427C(ENT,animId,6);
 D_800F9B68[D_800FADB8]++;ENT->timer16=0;
 if(ENT->actionFlags&0x40){if(func_800D4198(500))ENT->statusFlags|=1;}else ENT->statusFlags|=1;
 ENT->state++;
 }break;
 case 5:
 if((ENT->statusFlags&1)&&(D_800FAF8A&0xC030)&&func_800B71F8(ENT,0,6))ENT->actionFlags|=0x10;
 if(++ENT->timer16>60){
 if((ENT->flags&0x100)&&!(*(u16*)(D_8007EF30+0x170)&0x100))ENT->actionFlags|=0x10;
 if(!(ENT->flags&0x200))ENT->actionFlags|=0x10;
 if(func_800A93C0())ENT->actionFlags|=0x10;
 if(ENT->actionFlags&0xB0){if(ENT->flags&0x200000)animId=0x106C;else animId=0x106B;ENT->state=7;}
 else{if(ENT->flags&0x200000)animId=0x106A;else animId=0x1069;ENT->state++;}
 func_800D427C(ENT,animId,6);
 }break;
 case 6:
 if(ENT->curAnim==0x29)playEntitySound(ENT->id,2);
 if(ENT->animTimer==1)ENT->flags|=0x2000;
 if(ENT->animTimer<=0){func_800D4AD0(ENT);beginEntityActionA8D8C(ENT);}break;
 case 7:if(ENT->animTimer<=0){func_800D4AD0(ENT);func_800A6C48(ENT,0x2B);}break;
 }
}
