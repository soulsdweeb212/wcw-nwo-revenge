/* @header
 * updatePairedEntityActionState  (originally func_800BD45C)
 * VRAM 0x800BD45C | ROM 0xB08FC | size 0x524
 * asm: asm/nonmatchings/code_800BBA00/updatePairedEntityActionState.s
 */
#include "common.h"

/* Paired-entity (grapple) action state machine. Drives the primary entity
 * D_800FAF5C through steps 0..5, animating it (func_800D427C), aligning it to
 * and separating it from its linked partner D_800F9B00 (func_800D2BEC /
 * func_800D2BAC), and dispatching partner actions (beginPairedEntityActions). */
extern s8 D_800FADB8;extern s16 D_800FADC6[];
void func_800D427C(void*,s32,s32);void func_800D4AD0(void*);void func_800A7D1C(void*,s32);void beginEntityActionA8D8C(void*);
void beginPairedEntityActions(void*,s32,void*,s32);void func_800B68A0(void*,void*,void*);void func_800C472C(void*,void*,s32);
s32 func_800D2BEC(void*,void*,void*,f32,u16,s32);f32 func_800D63F0(void*,void*,s32);void func_800D37C0(s32,f32,void*);
#define A D_800FAF5C
#define B D_800F9B00
void updatePairedEntityActionState(void){s32 animId;s16 actionId;
    switch(A->step){
    case 0:
        if(A->pairSignals&0xF){
            if(A->pairSignals&1)animId=0xEE4;
            else if(A->pairSignals&2){A->flags&=~0x100ULL;A->flags|=0x40;animId=0xEE6;}else animId=0xEE8;
            A->step=4;
        }else if(B->grappleCtx&0x1000000){if(B->grappleCtx&0x80)animId=0xEEC;else animId=0xEE2;func_800D427C(A,animId,2);A->step=5;break;
        }else{if(B->grappleCtx&0x80)animId=0xEEA;else animId=0xEDA;A->step++;}
        func_800D427C(A,animId,2);break;
    case 1:
#ifdef TARGET_PC
        /* The N64 code passes B, the partner's address, cast to s32, which would cut a 64-bit pointer; the PC passes
         * the pointer, which func_800D2BAC takes (common.h declares it with Wrestler *). */
        if(!(B->grappleCtx&0x80))func_800D2BAC(A,B,1.0f,2);
#else
        if(!(B->grappleCtx&0x80))func_800D2BAC(A,(s32)B,1.0f,2);
#endif
        if(A->animFramesLeft<=0){
            if(A->flags&0x2000000){func_800D427C(A,0xEDD,0);beginPairedEntityActions(A,0xB,B,0xC);A->step=3;B->step=3;A->grappleCtx=B->grappleCtx&0x80;B->moveMode=A->moveMode;B->dirIndex=A->dirIndex;
            }else{if(B->grappleCtx&0x800000)animId=0xEE0;else animId=0xEDC;func_800D427C(A,animId,0);A->step++;}
        }break;
    case 2:
#ifdef TARGET_PC
        /* as above: the partner's pointer, not an s32 */
        if(!(B->grappleCtx&0x80))func_800D2BAC(A,B,1.0f,2);
#else
        if(!(B->grappleCtx&0x80))func_800D2BAC(A,(s32)B,1.0f,2);
#endif
        if(A->animFramesLeft<=0){A->flags&=~0x1000000ULL;
            if(A->animId==0xEE0){func_800A7D1C(A,5);func_800B68A0(A,B,B);func_800D4AD0(A);beginEntityActionA8D8C(A);
            }else{D_800FADC6[D_800FADB8]=0;func_800D37C0(A->heading,func_800D63F0(A,0,2),A->moveDelta);func_800A6C48(A,3);A->step=2;}
        }break;
    case 3:
#ifdef TARGET_PC
        /* as above: the partner's pointer, not an s32 */
        if(!(A->grappleCtx&0x80))func_800D2BAC(A,B,1.0f,2);
#else
        if(!(A->grappleCtx&0x80))func_800D2BAC(A,(s32)B,1.0f,2);
#endif
        if(A->animFramesLeft<=0){if(A->grappleCtx&0x800000)animId=0xEE0;else animId=0xEDC;func_800D427C(A,animId,0);A->step--;}
        break;
    case 4:
        if(!(A->pairSignals&4)){u16 mask;if(A->dirIndex&1)mask=0xC00;else mask=0x300;func_800D2BEC(A,B,0,2.0f,mask,0xFFFFE);}
        if(A->animFramesLeft<=0){
            if(A->pairSignals&1)actionId=7;
            if(A->pairSignals&2)actionId=8;
            if(A->pairSignals&4)actionId=9;
            if(A->pairSignals&8)actionId=9;
            func_800A7D1C(A,actionId);func_800B68A0(A,B,A);func_800D4AD0(A);beginEntityActionA8D8C(A);func_800C472C(A,A,2);
        }break;
    case 5:func_800D2BEC(A,B,0,1.0f,0,0xFFFFE);if(A->animFramesLeft<=0){func_800D4AD0(A);func_800A6C48(A,0x2B);}break;
    }
}
#undef A
#undef B
