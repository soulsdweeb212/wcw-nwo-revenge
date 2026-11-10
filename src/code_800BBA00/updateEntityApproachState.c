/* @header
 * updateEntityApproachState  (originally func_800D0804)
 * VRAM 0x800D0804 | ROM 0xC3CA4 | size 0x464
 * asm: asm/nonmatchings/code_800BBA00/updateEntityApproachState.s
 */
#include "common.h"

/* Entity approach state machine. Self (D_800FAF5C) moves toward its
 * opponent (D_800F9B00): stepTowardTarget walks it along the heading until the
 * per-id tick threshold (D_800EB620) is reached, then it plays the approach and
 * end animations and, based on the pair's animation state (func_800D7690),
 * decides which entity leads the follow-up action. */
extern s16 D_800EB620[];extern s32 D_800EB600[];extern u16 D_800FAF8A;extern u8 D_800FABE4,D_800FADB8;
#ifdef TARGET_PC
/* PC: port_decls.h declares func_800D5438, so the PC copy of this line leaves it out. */
void setupEntityMoveCD990(void*,void*);
void func_800A7F6C(void*,s32);
s16 func_800CDEE4(void*,void*);
void func_800A837C(void*);
void func_800A7C40(void*,s8,s16);
s32 func_800D35B0(s32,s32);
void func_800D427C(void*,s16,s32);
s16 func_800D7690(void*,u16,s16);
void func_800D43B4(void*,s16,s32);
void translateEntityXZ(void*,void*);
#else
void setupEntityMoveCD990(void*,void*);void func_800A7F6C(void*,s32);s16 func_800CDEE4(void*,void*);void func_800A837C(void*);void func_800A7C40(void*,s8,s16);s32 func_800D35B0(s32,s32);void func_800D427C(void*,s16,s32);s16 func_800D7690(void*,u16,s16);void func_800D43B4(void*,s16,s32);s16 func_800D5438(void*,s32);void translateEntityXZ(void*,void*);
#endif
/* Advance one step of the approach: either finish (heading from D_800EB600,
 * advance to step 7 on grappleCtx 0x100000 else reset stateTimer via
 * func_800CDEE4) or walk toward the target and tick stateTimer. Returns 1 when the approach is done. */
static inline s8 stepTowardTarget(Wrestler *o,Wrestler *b){s32 result;if(o->stateTimer>=D_800EB620[o->id]){o->heading=D_800EB600[o->id];if(o->grappleCtx&0x100000)o->step=7;else o->stateTimer=func_800CDEE4(o,b);result=1;}else{translateEntityXZ(o,o->moveDelta);o->heading=func_800D35B0(o->heading,o->turnPerTick);if(o->grappleCtx&0x400)func_800D2BAC(o,b,4.0f,0xFFFFE);o->stateTimer++;result=0;}return (s8)result;}
void updateEntityApproachState(void){D_800FAF5C->flags|=0x1000000000ULL;func_800D2BAC(D_800FAF5C,D_800F9B00,4.0f,0xFFFFE);switch(D_800FAF5C->step){case 0:setupEntityMoveCD990(D_800FAF5C,D_800F9B00);func_800A7F6C(D_800FAF5C,0x3D);D_800FAF5C->step++;
    case 1:if(stepTowardTarget(D_800FAF5C,D_800F9B00))D_800FAF5C->step++;break;
    case 2:if(D_800FAF5C->animFramesLeft<=0){func_800D427C(D_800FAF5C,0xEB6,1);func_800D7690(D_800FAF5C,0,0);D_800FAF5C->stateTimer=0x1E;D_800FAF5C->step++;}break;
    case 3:func_800D7690(D_800FAF5C,D_800FAF8A,2);D_800FAF5C->stateTimer--;if(D_800FAF5C->stateTimer<0)D_800FAF5C->pairSignals|=1;if(D_800FAF5C->animFramesLeft<=0){u16 inFlags=D_800FAF5C->pairSignals;if(inFlags&1){D_800FAF5C->pairSignals=inFlags|2;{Wrestler *lead=(D_800FAF5C->spirit<D_800F9B00->spirit)?D_800FAF5C:D_800F9B00;if(!(*(u64*)(lead->profile+0x38)&1)){D_800FAF5C->pairSignals=inFlags|6;if(lead==D_800FAF5C)D_800FAF5C->pairSignals=inFlags|0xE;}}if(D_800FAF5C->pairSignals&4){func_800D427C(D_800FAF5C,(D_800FAF5C->pairSignals&8)?0xEB9:0xEB8,1);D_800FAF5C->step++;}else D_800FAF5C->step=5;}else func_800D43B4(D_800FAF5C,D_800FAF5C->animId,1);}break;
    case 4:func_800D7690(D_800FAF5C,D_800FAF8A,2);if(D_800FAF5C->animFramesLeft<=0)D_800FAF5C->step++;break;
    case 5:{s16 a=func_800D7690(D_800FAF5C,0,3);s16 b=func_800D7690(D_800F9B00,0,3);if(a>=b){func_800A837C(D_800FAF5C);func_800A7C40(D_800FAF5C,D_800FADB8,0x84);func_800D427C(D_800FAF5C,func_800D5438(D_800FAF5C,0),1);func_800A6C48(D_800FAF5C,0x53);}else{D_800FAF5C->pairSignals|=0x10;func_800A837C(D_800F9B00);func_800A7C40(D_800F9B00,D_800FABE4,0x84);func_800D427C(D_800FAF5C,func_800D5438(D_800F9B00,1),1);}}break;}}
