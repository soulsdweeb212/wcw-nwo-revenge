#include "common.h"

extern u16 D_800F9848[]; extern u16 D_800F9850[]; extern u8 D_800F9D10[]; extern u8 D_800F9D12[]; extern u8 D_800FA063[];
typedef struct {s8 f0;u8 pad1[0xF];u16 f10;u8 pad12[0xE];u64 flags;u8 pad28[0x32B];s8 f353;u8 pad354;s8 f355;} Ent;
typedef struct {u8 pad0[0x20];u64 flags;} Rec;
void func_800DA3D8(void *arg0){Ent *p=arg0;Rec *rec;s32 off;s32 off2;u8 id;s32 t;s8 j;s8 v;
  p=(Ent*)((u32)p|((u32)p&~(u32)p));
  p->flags|=0x200; rec=(Rec*)(D_800F9D10+p->f355*0x3B0);
  rec->flags=(rec->flags&~0x200ULL)|0x20000000000000ULL;
  D_800F9848[p->f0]=p->f10; D_800F9850[p->f0]=0;
  if((p->flags&4ULL)!=(rec->flags&4ULL)){p->flags&=~4ULL; rec->flags|=4ULL;}
  id=p->f0; t=id^2; t|=t&~t; p->f353=t; t<<=24; t>>=24; off=t*0x3B0;
  if(*(s16*)(D_800F9D12+off)==-1||(*(u64*)(D_800F9D30+off)&0x200)==0) p->f353=id^3;
  j=p->f353; off2=j*0x3B0; if(*(s16*)(D_800F9D12+off2)!=-1) D_800FA063[off2]=p->f0;
  v=p->f353^1; off2=v*0x3B0; if(*(s16*)(D_800F9D12+off2)!=-1) D_800FA063[off2]=p->f0; }
