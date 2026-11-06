/* @header
 * updateEntityActionState  (originally func_800A164C)
 * VRAM 0x800A164C | ROM 0x94AEC | size 0x548
 * asm: asm/nonmatchings/code_8009D7A0/updateEntityActionState.s
 */
#include "common.h"

/* Action/animation step machine for the current entity (D_800EB408).
 * Steps 0..7 pick animations via func_800D427C, set koFlags/flags bits, and
 * advance when animFramesLeft runs out or stateTimer exceeds 60. */
extern s16 D_800E3262[],D_800F9B68[];extern s8 D_800FADB8;extern u16 D_800FAF8A;extern u8 D_8007EF30[];
s32 func_800D2B64(void*,f32,u16,s32);void func_800D427C(void*,s32,s32);void func_800D4AD0(void*);void func_800D4CC4(void*);s8 func_800D4198(s16);s8 func_800B71F8(void*,s32,s32);s8 func_800A93C0(void);void beginEntityActionA8D8C(void*);void playEntitySound(s8,s32);
void updateEntityActionState(void){s32 animId;
    func_800D2B64(D_800EB408,2.0f,0,0xFFFFE);
    switch(D_800EB408->step){
    case 0:
        D_800EB408->spirit=0;
        if(D_800EB408->koFlags&8){D_800EB408->step=2;D_800EB408->flags|=0x10000000;break;}
        if(D_800EB408->koFlags&4)animId=0x105E;else if(D_800EB408->flags&0x8000000)animId=0x105B;else animId=0x105A;
        func_800D427C(D_800EB408,animId,3);D_800EB408->step++;break;
    case 1:if(D_800EB408->animFramesLeft<=0){func_800D4AD0(D_800EB408);func_800D4CC4(D_800EB408);D_800EB408->step++;D_800EB408->flags|=0x10000000;}break;
    case 2:D_800EB408->flags|=0x1000000000ULL;func_800D427C(D_800EB408,D_800E3262[(s8)D_800EB408->pose],1);D_800EB408->step++;break;
    case 3:if(D_800EB408->flags&0x200000)animId=0x1060;else animId=0x105F;func_800D427C(D_800EB408,animId,6);D_800EB408->step++;break;
    case 4:if(D_800EB408->animFramesLeft<=0){
            if(D_800EB408->flags&0x200000)animId=0x1066;else animId=0x1065;func_800D427C(D_800EB408,animId,6);
            D_800F9B68[D_800FADB8]++;D_800EB408->stateTimer=0;
            if(D_800EB408->koFlags&0x40){if(func_800D4198(500))D_800EB408->stepFlags|=1;}else D_800EB408->stepFlags|=1;
            D_800EB408->step++;
        }break;
    case 5:
        if((D_800EB408->stepFlags&1)&&(D_800FAF8A&0xC030)&&func_800B71F8(D_800EB408,0,6))D_800EB408->koFlags|=0x10;
        if(++D_800EB408->stateTimer>60){
            if((D_800EB408->flags&0x100)&&!(*(u16*)(D_8007EF30+0x170)&0x100))D_800EB408->koFlags|=0x10;
            if(!(D_800EB408->flags&0x200))D_800EB408->koFlags|=0x10;
            if(func_800A93C0())D_800EB408->koFlags|=0x10;
            if(D_800EB408->koFlags&0xB0){if(D_800EB408->flags&0x200000)animId=0x106C;else animId=0x106B;D_800EB408->step=7;}
            else{if(D_800EB408->flags&0x200000)animId=0x106A;else animId=0x1069;D_800EB408->step++;}
            func_800D427C(D_800EB408,animId,6);
        }break;
    case 6:
        if(D_800EB408->animFrame==0x29)playEntitySound(D_800EB408->id,2);
        if(D_800EB408->animFramesLeft==1)D_800EB408->flags|=0x2000;
        if(D_800EB408->animFramesLeft<=0){func_800D4AD0(D_800EB408);beginEntityActionA8D8C(D_800EB408);}break;
    case 7:if(D_800EB408->animFramesLeft<=0){func_800D4AD0(D_800EB408);func_800A6C48(D_800EB408,0x2B);}break;
    }
}
