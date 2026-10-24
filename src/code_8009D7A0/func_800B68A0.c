#include "common.h"

typedef struct {u8 pad0[3];u8 f3,pad4;s8 f5[5],fA[5];} AttrB68;
typedef struct {s8 id;u8 pad1[9];s16 state;u8 padC[4];s16 f10,f12,f14;u8 pad16[0xA];u64 flags;u8 pad28[0x324];u8 f34C[8];u8 pad354[0x10];AttrB68 *f364;u8 pad368[0x28];u8 f390,f391;s8 f392;u8 pad393[2];s8 f395;u8 f396;u8 pad397[5];u8 f39C[5];u8 pad3A1[7];u8 f3A8,f3A9;} ObjB68;
extern u8 D_8007E228[];extern f32 D_800E37CC[];extern f64 D_800E55C0;extern s16 D_800F9B78[];extern s8 D_800FADB9[];
s16 func_800BF1E0(void*,s8);void func_800BF338(void*,s16,s32);void func_800BF228(void*,s32,s8);void addEntityHealthDelta(void*,s16);s16 updateEntityStunTimer(void*,s32,s32);
s16 func_800B68A0(ObjB68 *source,ObjB68 *attacker,ObjB68 *target){
 s16 pieces[3];s16 base,part,i,total,min,bonus; s8 key;s32 mode;
 base=(s8)source->f390;key=source->f395;part=(s8)source->f396;
 pieces[0]=((func_800BF1E0(attacker,key)+50)*base)/100;
 pieces[1]=((attacker->f364->f5[key]-target->f364->fA[part])*base)/10;
 if(base)pieces[2]=(attacker->f14-target->f14)/20;else pieces[2]=0;
 total=0;
 for(i=0;i<3;i++){if(pieces[i]<0)pieces[i]=0;total+=(u16)pieces[i];}
 if(attacker->flags&0x80000)total=(f32)total*D_800E55C0;
 if(target->flags&8)total=(f32)total*2.0;
 total=(f32)total*D_800E37CC[((s32*)(D_8007E228+0x610))[attacker->id]];
 switch(target->state){case 0x39:case 0x3D:case 0x3F:mode=1;break;default:mode=0;break;}
 func_800BF338(target,-total,mode);
 target->f12-=total/4;if(target->f12<129)target->f12=128;
 for(i=0;i<5;i++)func_800BF228(target,i,-source->f39C[i]);
 if(part!=4){min=50;for(i=0;i<4;i++){if((s8)target->f34C[i]<=min)min=(s8)target->f34C[i];}if(min>=(s8)target->f34C[part])D_800FADB9[target->id]=part;}
 bonus=(s8)source->f391;if(attacker->state!=0x3D && attacker->f10<49)bonus+=3;
 if(attacker->flags&0x400000000ULL)bonus+=(s8)attacker->f364->f3;
 addEntityHealthDelta(attacker,bonus);addEntityHealthDelta(target,source->f392);updateEntityStunTimer(target,0,3);
 attacker->flags|=0x40000000000ULL;target->flags|=0x40000000000ULL;
 D_800F9B78[attacker->id]+=(s8)source->f3A8;
 if(D_800F9B78[attacker->id]<30)D_800F9B78[attacker->id]=30;
 if(D_800F9B78[attacker->id]>200)D_800F9B78[attacker->id]=200;
 D_800F9B78[target->id]+=(s8)source->f3A9;
 if(D_800F9B78[target->id]<30)D_800F9B78[target->id]=30;
 if(D_800F9B78[target->id]>200)D_800F9B78[target->id]=200;
 return total;
}
