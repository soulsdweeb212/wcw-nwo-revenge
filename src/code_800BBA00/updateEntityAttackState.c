/* @header
 * updateEntityAttackState  (originally func_800C9014)
 * VRAM 0x800C9014 | ROM 0xBC4B4 | size 0x4B8
 * asm: asm/nonmatchings/code_800BBA00/updateEntityAttackState.s
 */
#include "common.h"

/* Wrestler attack action state machine. Runs self (D_800FAF5C) through
 * attack steps 0..6: plays the attack animation (func_800D427C), aligns it
 * to its target (func_800D2BEC/func_800D2B64), checks attack inputs
 * (func_800A93C0, pairSignals), then clears attached[0] and the 0x40000000
 * pair-leader flag when the attack finishes. */
extern s8 D_800FADB8,D_800EB550[];
extern u8 D_800FABE4; extern u16 D_800FABE6,D_800FAF8A;
s8 func_800B71F8(void*,void*,s32);s8 func_800A93C0(void);
void func_800D427C(void*,s32,s32);void func_800D4AD0(void*);
void func_800A7D1C(void*,s32);void beginEntityActionA8D8C(void*);
s16 func_800D5438(void*,s32);
s32 func_800D2BEC(void*,void*,void*,f32,u16,s32);
s32 func_800D2B64(void*,f32,u16,s32);
void applyMovementToEntityPair(void*,void*,u16);void func_800B68A0(void*,void*,void*);
void updateEntityAttackState(void){
    switch(D_800FAF5C->step){
    case 0:{s32 animId;D_800EB550[D_800FADB8]=D_800FABE4;
        if(func_800B71F8(D_800FAF5C,D_800F9B00,0xB)){D_800FAF5C->step++;animId=0x10C0;}else{D_800FAF5C->step=6;D_800FAF5C->pairSignals|=8;animId=0x10D0;}
        func_800D427C(D_800FAF5C,animId,3);break;}
    case 1:func_800D2BEC(D_800FAF5C,D_800F9B00,0,4.0f,0,0xFFFFE);
        if(D_800FAF5C->animFramesLeft<=0){func_800D427C(D_800FAF5C,0x10C2,1);D_800FAF5C->pairSignals&=~0x14;D_800FAF5C->step++;}break;
    case 2:
        D_800FAF5C->flags|=0x200000000000ULL;
        if((D_800FAF5C->pairSignals&1)||(D_800FAF8A&0x10)||func_800A93C0()){
            D_800FAF5C->pairSignals|=1;func_800D427C(D_800FAF5C,0x10C4,1);D_800FAF5C->step++;
        }else if(D_800FAF5C->pairSignals&0x10){s32 animId;if(D_800FAF5C->flags&0x8000000)animId=0x10CE;else animId=0x10CA;func_800D427C(D_800FAF5C,animId,1);D_800FAF5C->step=4;
        }else if(D_800FAF5C->pairSignals&4){func_800D427C(D_800FAF5C,0x10C6,1);D_800FAF5C->step=5;
        }else if(D_800FAF5C->pairSignals&2){func_800D427C(D_800FAF5C,func_800D5438(D_800F9B00,1),1);
        }else applyMovementToEntityPair(D_800FAF5C,&D_800F9D10[D_800EB550[D_800FADB8]],D_800FABE6);
        break;
    case 3:func_800D2BEC(D_800FAF5C,D_800F9B00,0,4.0f,0,0xFFFFE);if(D_800FAF5C->animFramesLeft<=0){func_800D4AD0(D_800FAF5C);func_800A6C48(D_800FAF5C,0x2B);{Wrestler *ent=D_800FAF5C;ent->attached[0]=-1;ent->flags&=~WR_FLAG_PAIR_LEADER;}}break;
    case 4:func_800D2B64(D_800FAF5C,2.0f,0,2);if(D_800FAF5C->animFramesLeft<=0){func_800D4AD0(D_800FAF5C);func_800A6C48(D_800FAF5C,0x2B);{Wrestler *ent=D_800FAF5C;ent->attached[0]=-1;ent->flags&=~WR_FLAG_PAIR_LEADER;}}break;
    case 5:func_800D2BEC(D_800FAF5C,&D_800F9D10[D_800EB550[D_800FADB8]],0,4.0f,0,0xFFFFE);if(D_800FAF5C->animFramesLeft<=0){func_800B68A0(D_800F9B64,D_800F9B64,D_800FAF5C);func_800D4AD0(D_800FAF5C);beginEntityActionA8D8C(D_800FAF5C);{Wrestler *ent=D_800FAF5C;ent->attached[0]=-1;ent->flags&=~WR_FLAG_PAIR_LEADER;}}break;
    case 6:func_800D2BEC(D_800FAF5C,D_800F9B00,0,4.0f,0,0xFFFFE);if(D_800FAF5C->animFramesLeft<=0){func_800A7D1C(D_800FAF5C,0x25);func_800B68A0(D_800FAF5C,D_800F9B00,D_800FAF5C);func_800D4AD0(D_800FAF5C);beginEntityActionA8D8C(D_800FAF5C);{Wrestler *ent=D_800FAF5C;ent->attached[0]=-1;ent->flags&=~WR_FLAG_PAIR_LEADER;}}break;
    }
}
