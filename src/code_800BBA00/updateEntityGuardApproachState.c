/* @header
 * updateEntityGuardApproachState  (originally func_800D0C68)
 * VRAM 0x800D0C68 | ROM 0xC4108 | size 0x3AC
 * asm: asm/nonmatchings/code_800BBA00/updateEntityGuardApproachState.s
 */
#include "common.h"

/* Defender-side approach state machine (steps 0..5). Self (D_800FAF5C)
 * braces against the attacker (D_800F9B00): it steps toward the
 * attacker until the per-id tick threshold is reached (stepD0C), plays the
 * brace/impact animations, and resolves the grapple/counter from the attacker's
 * pairSignals (0x10 -> mutual grapple with flag/slot swap, else the counter). */
extern s16 D_800EB628[]; extern s32 D_800EB610[]; extern u16 D_800FAF8A; extern u8 D_800FABE4, D_800FADB8;
void selectTurnAnimationCDC04(void *,void *); void func_800A7F6C(void *,s32); void translateEntityXZ(void *,void *); s32 func_800D35B0(s32,s32); void func_800D427C(void *,s16,s32); void func_800D7690(void *,u16,s32); void func_800D43B4(void *,s16,s32); s32 func_800D5438(void *,s32); void func_800A6BE0(void *,s32);
/* One step of the brace approach: tick until the per-id threshold, then finish
 * (heading from D_800EB610, step 7 if the attacker's grappleCtx has 0x100000)
 * else walk the entity forward when the attacker allows (0x200). Returns 1 when done. */
static __inline__ s32 stepD0C(Wrestler *o,Wrestler *b) { s32 result; o->stateTimer++; if(o->stateTimer>D_800EB628[o->id]) { o->heading=D_800EB610[o->id]; if(b->grappleCtx&0x100000) o->step=7; result=1; } else { if(b->grappleCtx&0x200) translateEntityXZ(o,o->moveDelta); o->heading=func_800D35B0(o->heading,o->turnPerTick); result=0; } return (s8)result; }
void updateEntityGuardApproachState(void) { D_800FAF5C->flags|=0x1000000000ULL; func_800D2BAC(D_800FAF5C,D_800F9B00,4.0f,0xFFFFE); switch(D_800FAF5C->step) { case 0: selectTurnAnimationCDC04(D_800FAF5C,D_800F9B00); func_800A7F6C(D_800FAF5C,0x3D); D_800FAF5C->stateTimer=0; D_800FAF5C->step++; case 1: if(stepD0C(D_800FAF5C,D_800F9B00)) D_800FAF5C->step++; break; case 2: if(D_800FAF5C->animFramesLeft<=0) { func_800D427C(D_800FAF5C,0xEB7,1); func_800D7690(D_800FAF5C,0,0); D_800FAF5C->step++; } break; case 3: func_800D7690(D_800FAF5C,D_800FAF8A,2); if(D_800F9B00->pairSignals&2) { if(D_800F9B00->pairSignals&4) { func_800D427C(D_800FAF5C,(D_800F9B00->pairSignals&8)?0xEB8:0xEB9,1); D_800FAF5C->step++; } else D_800FAF5C->step=5; } else if(D_800FAF5C->animFramesLeft<=0) func_800D43B4(D_800FAF5C,D_800FAF5C->animId,1); break; case 4: func_800D7690(D_800FAF5C,D_800FAF8A,2); if(D_800FAF5C->animFramesLeft<=0) D_800FAF5C->step++; break; case 5: if(D_800F9B00->pairSignals&0x10) { func_800D427C(D_800FAF5C,(s16)func_800D5438(D_800FAF5C,0),1); func_800A6BE0(D_800FAF5C,0x53); func_800A6BE0(D_800F9B00,0x54); D_800FAF5C->flags|=WR_FLAG_PAIR_LEADER; D_800F9B00->flags&=~WR_FLAG_PAIR_LEADER; D_800FAF5C->attached[0]=D_800FABE4; D_800F9B00->attached[0]=-1; D_800F9B00->heldById=D_800FADB8; } else { func_800D427C(D_800FAF5C,(s16)func_800D5438(D_800F9B00,1),1); func_800A6C48(D_800FAF5C,0x54); } break; } }
