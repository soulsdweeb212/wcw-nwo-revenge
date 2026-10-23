#include "common.h"

/* Defender-side approach state machine (phases 0..5). The entity O
 * (D_800FAF5C) braces against the attacker T (D_800F9B00): it steps toward the
 * attacker until the per-id tick threshold is reached (stepD0C), plays the
 * brace/impact animations, and resolves the grapple/counter from the attacker's
 * input flags (0x10 -> mutual grapple with flag/slot swap, else the counter). */
typedef struct { s8 id; u8 p1[3]; s16 timer; u8 p6[2]; s16 anim; s16 state; s16 phase; u8 pE[8]; s16 ticks; u8 p18[8]; u64 flags; u16 f28; u8 p2A[2]; u32 f2C; u8 p30[0x28]; s32 heading; u8 p5C[0x2E0]; f32 vec[3]; s32 delta; u8 p34C[5]; u8 f351; u8 p352[14]; u16 input; s8 f362; } ObjD0C;
extern ObjD0C *D_800FAF5C, *D_800F9B00;
extern s16 D_800EB628[]; extern s32 D_800EB610[]; extern u16 D_800FAF8A; extern u8 D_800FABE4, D_800FADB8;
void selectTurnAnimationCDC04(void *,void *); void func_800A7F6C(void *,s32); void translateEntityXZ(void *,void *); s32 func_800D35B0(s32,s32); void func_800D427C(void *,s16,s32); void func_800D7690(void *,u16,s32); void func_800D43B4(void *,s16,s32); s32 func_800D5438(void *,s32); void func_800A6BE0(void *,s32);
/* One step of the brace approach: tick until the per-id threshold, then finish
 * (heading from D_800EB610, phase 7 if the attacker is 0x100000) else walk the
 * entity forward when the attacker allows (0x200). Returns 1 when done. */
static __inline__ s32 stepD0C(ObjD0C *o,ObjD0C *b) { s32 result; o->ticks++; if(o->ticks>D_800EB628[o->id]) { o->heading=D_800EB610[o->id]; if(b->f2C&0x100000) o->phase=7; result=1; } else { if(b->f2C&0x200) translateEntityXZ(o,o->vec); o->heading=func_800D35B0(o->heading,o->delta); result=0; } return (s8)result; }
void updateEntityGuardApproachState(void) { D_800FAF5C->flags|=0x1000000000ULL; func_800D2BAC(D_800FAF5C,D_800F9B00,4.0f,0xFFFFE); switch(D_800FAF5C->phase) { case 0: selectTurnAnimationCDC04(D_800FAF5C,D_800F9B00); func_800A7F6C(D_800FAF5C,0x3D); D_800FAF5C->ticks=0; D_800FAF5C->phase++; case 1: if(stepD0C(D_800FAF5C,D_800F9B00)) D_800FAF5C->phase++; break; case 2: if(D_800FAF5C->timer<=0) { func_800D427C(D_800FAF5C,0xEB7,1); func_800D7690(D_800FAF5C,0,0); D_800FAF5C->phase++; } break; case 3: func_800D7690(D_800FAF5C,D_800FAF8A,2); if(D_800F9B00->input&2) { if(D_800F9B00->input&4) { func_800D427C(D_800FAF5C,(D_800F9B00->input&8)?0xEB8:0xEB9,1); D_800FAF5C->phase++; } else D_800FAF5C->phase=5; } else if(D_800FAF5C->timer<=0) func_800D43B4(D_800FAF5C,D_800FAF5C->anim,1); break; case 4: func_800D7690(D_800FAF5C,D_800FAF8A,2); if(D_800FAF5C->timer<=0) D_800FAF5C->phase++; break; case 5: if(D_800F9B00->input&0x10) { func_800D427C(D_800FAF5C,(s16)func_800D5438(D_800FAF5C,0),1); func_800A6BE0(D_800FAF5C,0x53); func_800A6BE0(D_800F9B00,0x54); D_800FAF5C->flags|=0x40000000ULL; D_800F9B00->flags&=~0x40000000ULL; D_800FAF5C->f362=D_800FABE4; D_800F9B00->f362=-1; D_800F9B00->f351=D_800FADB8; } else { func_800D427C(D_800FAF5C,(s16)func_800D5438(D_800F9B00,1),1); func_800A6C48(D_800FAF5C,0x54); } break; } }
