#include "common.h"

/* Entity approach state machine. The entity O (D_800FAF5C) moves toward its
 * target T (D_800F9B00): stepTowardTarget walks it along the heading until the
 * per-id tick threshold (D_800EB620) is reached, then it plays the approach and
 * end animations and, based on the pair's animation state (func_800D7690),
 * decides which entity leads the follow-up action. */
typedef struct {s8 id;u8 p1[3];s16 timer;u8 p6[2];s16 anim,state,phase;u8 pE[6];s16 f14,ticks;u8 p18[8];u64 flags;u16 f28;u8 p2A[2];u32 f2C;u8 p30[0x28];s32 heading;u8 p5C[0x2E0];f32 vec[3];s32 delta;u8 p34C[5];u8 f351;u8 p352[14];u16 input;s8 f362;u8 p363;void *f364;} Obj;
extern Obj *D_800FAF5C,*D_800F9B00;extern s16 D_800EB620[];extern s32 D_800EB600[];extern u16 D_800FAF8A;extern u8 D_800FABE4,D_800FADB8;
void setupEntityMoveCD990(void*,void*);void func_800A7F6C(void*,s32);s16 func_800CDEE4(void*,void*);void func_800A837C(void*);void func_800A7C40(void*,s8,s16);s32 func_800D35B0(s32,s32);void func_800D427C(void*,s16,s32);s16 func_800D7690(void*,u16,s16);void func_800D43B4(void*,s16,s32);s16 func_800D5438(void*,s32);void translateEntityXZ(void*,void*);
/* Advance one step of the approach: either finish (heading from D_800EB600,
 * advance to phase 7 on 0x100000 else reset ticks via func_800CDEE4) or walk
 * toward the target and tick the counter. Returns 1 when the approach is done. */
static inline s8 stepTowardTarget(Obj *o,Obj *b){s32 result;if(o->ticks>=D_800EB620[o->id]){o->heading=D_800EB600[o->id];if(o->f2C&0x100000)o->phase=7;else o->ticks=func_800CDEE4(o,b);result=1;}else{translateEntityXZ(o,o->vec);o->heading=func_800D35B0(o->heading,o->delta);if(o->f2C&0x400)func_800D2BAC(o,b,4.0f,0xFFFFE);o->ticks++;result=0;}return (s8)result;}
#define O D_800FAF5C
#define T D_800F9B00
void updateEntityApproachState(void){O->flags|=0x1000000000ULL;func_800D2BAC(O,T,4.0f,0xFFFFE);switch(O->phase){case 0:setupEntityMoveCD990(O,T);func_800A7F6C(O,0x3D);O->phase++;
case 1:if(stepTowardTarget(O,T))O->phase++;break;
case 2:if(O->timer<=0){func_800D427C(O,0xEB6,1);func_800D7690(O,0,0);O->ticks=0x1E;O->phase++;}break;
case 3:func_800D7690(O,D_800FAF8A,2);O->ticks--;if(O->ticks<0)O->input|=1;if(O->timer<=0){u16 inFlags=O->input;if(inFlags&1){O->input=inFlags|2;{Obj *lead=(O->f14<T->f14)?O:T;if(!(*(u64*)((char*)lead->f364+0x38)&1)){O->input=inFlags|6;if(lead==O)O->input=inFlags|0xE;}}if(O->input&4){func_800D427C(O,(O->input&8)?0xEB9:0xEB8,1);O->phase++;}else O->phase=5;}else func_800D43B4(O,O->anim,1);}break;
case 4:func_800D7690(O,D_800FAF8A,2);if(O->timer<=0)O->phase++;break;
case 5:{s16 a=func_800D7690(O,0,3);s16 b=func_800D7690(T,0,3);if(a>=b){func_800A837C(O);func_800A7C40(O,D_800FADB8,0x84);func_800D427C(O,func_800D5438(O,0),1);func_800A6C48(O,0x53);}else{O->input|=0x10;func_800A837C(T);func_800A7C40(T,D_800FABE4,0x84);func_800D427C(O,func_800D5438(T,1),1);}}break;}}
