/* @header
 * func_800DA3D8
 * VRAM 0x800DA3D8 | ROM 0xCD878 | size 0x210
 * asm: asm/nonmatchings/code_800BBA00/func_800DA3D8.s
 */
#include "common.h"

extern u16 D_800F9848[]; extern u16 D_800F9850[]; 
/* Tag in: arg0 becomes legal (0x200) and its partner stops being legal, the
 * partner is marked with 0x20000000000000, arg0's health is cached in
 * D_800F9848 (D_800F9850 reset), the CPU bit (4) moves to the partner when the
 * two differ, and arg0 picks an opponent on the other team (id^2, else id^3 when
 * that slot is empty or not legal), which in turn faces arg0. */
void func_800DA3D8(Wrestler *arg0){Wrestler *p=arg0;Wrestler *partner;u8 id;s32 t;s8 slot;s8 other;
    p=(Wrestler*)((u32)p|((u32)p&~(u32)p));
    p->flags|=WR_FLAG_LEGAL; partner=&D_800F9D10[p->partnerId];
    partner->flags=(partner->flags&~WR_FLAG_LEGAL)|0x20000000000000ULL;
    D_800F9848[p->id]=p->health; D_800F9850[p->id]=0;
    if((p->flags&WR_FLAG_CPU)!=(partner->flags&WR_FLAG_CPU)){p->flags&=~WR_FLAG_CPU; partner->flags|=WR_FLAG_CPU;}
    id=p->id; t=id^2; t|=t&~t; p->opponentId=t; t<<=24; t>>=24;
    if(D_800F9D10[t].characterId==-1||(D_800F9D10[t].flags&WR_FLAG_LEGAL)==0) p->opponentId=id^3;
    slot=p->opponentId; if(D_800F9D10[slot].characterId!=-1) D_800F9D10[slot].opponentId=p->id;
    other=p->opponentId^1; if(D_800F9D10[other].characterId!=-1) D_800F9D10[other].opponentId=p->id; }
