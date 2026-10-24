#include "common.h"

extern u16 D_800F9848[]; extern u16 D_800F9850[]; extern u8 D_800F9D10[]; extern u8 D_800F9D12[]; extern u8 D_800FA063[];
/* Per-entity action state (0x3B0 bytes per action record).
 * id +0x00, action +0x10, u64 flags +0x20, actionSlot +0x353, partnerSlot +0x355. */
typedef struct {s8 id;u8 pad1[0xF];u16 action;u8 pad12[0xE];u64 flags;u8 pad28[0x32B];s8 actionSlot;u8 pad354;s8 partnerSlot;} Ent;
typedef struct {u8 pad0[0x20];u64 flags;} Rec;
/* Release an entity's action binding: mark the shared action record as used by
 * this entity, reset the entity's per-slot timers, and hand the action slot to
 * the other player slot when the two sides' bit-4 state differs. */
void func_800DA3D8(void *arg0){Ent *p=arg0;Rec *rec;s32 off;s32 off2;u8 id;s32 t;s8 slot;s8 other;
  p=(Ent*)((u32)p|((u32)p&~(u32)p));
  p->flags|=0x200; rec=(Rec*)(D_800F9D10+p->partnerSlot*0x3B0);
  rec->flags=(rec->flags&~0x200ULL)|0x20000000000000ULL;
  D_800F9848[p->id]=p->action; D_800F9850[p->id]=0;
  if((p->flags&4ULL)!=(rec->flags&4ULL)){p->flags&=~4ULL; rec->flags|=4ULL;}
  id=p->id; t=id^2; t|=t&~t; p->actionSlot=t; t<<=24; t>>=24; off=t*0x3B0;
  if(*(s16*)(D_800F9D12+off)==-1||(*(u64*)(D_800F9D30+off)&0x200)==0) p->actionSlot=id^3;
  slot=p->actionSlot; off2=slot*0x3B0; if(*(s16*)(D_800F9D12+off2)!=-1) D_800FA063[off2]=p->id;
  other=p->actionSlot^1; off2=other*0x3B0; if(*(s16*)(D_800F9D12+off2)!=-1) D_800FA063[off2]=p->id; }
