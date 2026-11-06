/* @header
 * tryStartFacingGroupAtGate  (originally func_800CD6C4)
 * VRAM 0x800CD6C4 | ROM 0xC0B64 | size 0x148
 * asm: asm/nonmatchings/code_800BBA00/tryStartFacingGroupAtGate.s
 */
#include "common.h"

void setupEntityFacingGroup(void*,void*,void*,s32);
/* Checks whether wrestler p (arg0) can start a facing group with q (arg1) at
 * q's opponent (q->opponentId): requires shared 0x40/0x100 zone flags, q in
 * state 0x46 with grappleCtx bit 0x400 and stateTimer below 0xB, and p not on
 * the apron (0x80). Chooses a group flag value from the grappleCtx 0x40 bits of
 * that opponent and p and starts the group, returning 1; otherwise returns 0. */
s32 tryStartFacingGroupAtGate(Wrestler *arg0,Wrestler *arg1){Wrestler *p,*q;u64 m;Wrestler *t2;s32 a3;t2=&D_800F9D10[arg1->opponentId];p=arg0;q=arg1;m=t2->flags&p->flags&q->flags;if((m&0x40)||(m&0x100)){if(q->state==0x46){if(q->grappleCtx&0x400){if(!(p->flags&0x80)){if(q->stateTimer<0xB){if(t2->grappleCtx&0x40)a3=(p->grappleCtx&0x40)?0x1000:0x2000;else a3=(p->grappleCtx&0x40)?0x2000:0x800;setupEntityFacingGroup(t2,p,q,a3);return 1;}}}}}return 0;}
