/* @header
 * tryStartFacingGroupAtGate  (originally func_800CD6C4)
 * VRAM 0x800CD6C4 | ROM 0xC0B64 | size 0x148
 * asm: asm/nonmatchings/code_800BBA00/func_800CD6C4.s
 */
#include "common.h"

extern u8 D_800F9D10[];void setupEntityFacingGroup(void*,void*,void*,s32);
typedef struct{u8 pad0[0xA];s16 state;u8 padC[0xA];s16 f16;u8 pad18[8];u64 flags;u8 pad28[4];u32 f2C;u8 pad30[0x323];s8 link;u8 pad354[0x5C];}Nw2GateEntity;
/* Checks whether the entity p (arg0) can start a facing group with q (arg1) at
 * the entity referenced by q->link: requires shared 0x40/0x100 flags, q in
 * state 0x46 with its 0x400 flag and a short timer, and p not carrying 0x80.
 * Chooses a group flag value from the two entities' 0x40 flags and starts the
 * group, returning 1; otherwise returns 0. */
s32 tryStartFacingGroupAtGate(void *arg0,void *arg1){Nw2GateEntity *p,*q;u64 m;Nw2GateEntity *t2;s32 a3;t2=(Nw2GateEntity*)(D_800F9D10+*(s8*)((u8*)arg1+0x353)*0x3B0);p=arg0;q=arg1;m=t2->flags&p->flags&q->flags;if((m&0x40)||(m&0x100)){if(q->state==0x46){if(q->f2C&0x400){if(!(p->flags&0x80)){if(q->f16<0xB){if(t2->f2C&0x40)a3=(p->f2C&0x40)?0x1000:0x2000;else a3=(p->f2C&0x40)?0x2000:0x800;setupEntityFacingGroup(t2,p,q,a3);return 1;}}}}}return 0;}
