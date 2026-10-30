/* @header
 * updatePairedEntityActionState  (originally func_800BD45C)
 * VRAM 0x800BD45C | ROM 0xB08FC | size 0x524
 * asm: asm/nonmatchings/code_800BBA00/updatePairedEntityActionState.s
 */
#include "common.h"

/* Paired-entity (grapple) action state machine. Drives the primary entity
 * D_800FAF5C through states 0..5, animating it (func_800D427C), aligning it to
 * and separating it from its linked partner D_800F9B00 (func_800D2BEC /
 * func_800D2BAC), and dispatching partner actions (beginPairedEntityActions). */
typedef struct {
    u8 pad0[4];
    s16 animTimer;      /* +0x04 countdown; <=0 means the animation is done */
    u16 pad6;
    s16 curAnim;        /* +0x08 */
    u16 padA;
    s16 state;          /* +0x0C case selector */
    u8 padE[0x12];
    u64 flags;          /* +0x20 entity status bits */
    u16 f28;
    u16 pad2A;
    u32 status;         /* +0x2C */
    u8 pad30[0xE];
    s16 f3E;
    u8 pad40[0x18];
    s32 objHandle;      /* +0x58 display-object handle */
    u8 pad5C[0x2E0];
    f32 vec[4];         /* +0x33C */
    u8 pad34C[0x14];
    u16 actionFlags;    /* +0x360 */
} ObjBD45;
extern ObjBD45 *D_800FAF5C,*D_800F9B00;extern s8 D_800FADB8;extern s16 D_800FADC6[];
void func_800D427C(void*,s32,s32);void func_800D4AD0(void*);void func_800A7D1C(void*,s32);void beginEntityActionA8D8C(void*);
void beginPairedEntityActions(void*,s32,void*,s32);void func_800B68A0(void*,void*,void*);void func_800C472C(void*,void*,s32);
s32 func_800D2BEC(void*,void*,void*,f32,u16,s32);f32 func_800D63F0(void*,void*,s32);void func_800D37C0(s32,f32,void*);
#define A D_800FAF5C
#define B D_800F9B00
void updatePairedEntityActionState(void){s32 animId;s16 actionId;
 switch(A->state){
 case 0:
 if(A->actionFlags&0xF){
 if(A->actionFlags&1)animId=0xEE4;
 else if(A->actionFlags&2){A->flags&=~0x100ULL;A->flags|=0x40;animId=0xEE6;}else animId=0xEE8;
 A->state=4;
 }else if(B->status&0x1000000){if(B->status&0x80)animId=0xEEC;else animId=0xEE2;func_800D427C(A,animId,2);A->state=5;break;
 }else{if(B->status&0x80)animId=0xEEA;else animId=0xEDA;A->state++;}
 func_800D427C(A,animId,2);break;
 case 1:
 if(!(B->status&0x80))func_800D2BAC(A,(s32)B,1.0f,2);
 if(A->animTimer<=0){
 if(A->flags&0x2000000){func_800D427C(A,0xEDD,0);beginPairedEntityActions(A,0xB,B,0xC);A->state=3;B->state=3;A->status=B->status&0x80;B->f28=A->f28;B->f3E=A->f3E;
 }else{if(B->status&0x800000)animId=0xEE0;else animId=0xEDC;func_800D427C(A,animId,0);A->state++;}
 }break;
 case 2:
 if(!(B->status&0x80))func_800D2BAC(A,(s32)B,1.0f,2);
 if(A->animTimer<=0){A->flags&=~0x1000000ULL;
 if(A->curAnim==0xEE0){func_800A7D1C(A,5);func_800B68A0(A,B,B);func_800D4AD0(A);beginEntityActionA8D8C(A);
 }else{D_800FADC6[D_800FADB8]=0;func_800D37C0(A->objHandle,func_800D63F0(A,0,2),A->vec);func_800A6C48(A,3);A->state=2;}
 }break;
 case 3:
 if(!(A->status&0x80))func_800D2BAC(A,(s32)B,1.0f,2);
 if(A->animTimer<=0){if(A->status&0x800000)animId=0xEE0;else animId=0xEDC;func_800D427C(A,animId,0);A->state--;}
 break;
 case 4:
 if(!(A->actionFlags&4)){u16 mask;if(A->f3E&1)mask=0xC00;else mask=0x300;func_800D2BEC(A,B,0,2.0f,mask,0xFFFFE);}
 if(A->animTimer<=0){
 if(A->actionFlags&1)actionId=7;
 if(A->actionFlags&2)actionId=8;
 if(A->actionFlags&4)actionId=9;
 if(A->actionFlags&8)actionId=9;
 func_800A7D1C(A,actionId);func_800B68A0(A,B,A);func_800D4AD0(A);beginEntityActionA8D8C(A);func_800C472C(A,A,2);
 }break;
 case 5:func_800D2BEC(A,B,0,1.0f,0,0xFFFFE);if(A->animTimer<=0){func_800D4AD0(A);func_800A6C48(A,0x2B);}break;
 }
}
#undef A
#undef B
