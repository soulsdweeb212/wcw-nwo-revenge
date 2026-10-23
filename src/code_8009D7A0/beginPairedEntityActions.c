#include "common.h"

/* Start a matched pair of actions: reset both entities' action/anim/timer
 * fields, set the "paired" flag bits, run their action setup, then cross-link
 * each entity to the other (facing, source id and partner pointers). */
void func_800DECAC(void *,s32,s32,s32);
void func_800A700C(void *);
#define P6(p,t,o) (*(t*)((u8*)(p)+(o)))
void beginPairedEntityActions(void *self,s16 selfAction,void *other,s16 otherAction) {
 P6(self,s16,0xA)=selfAction;
 P6(self,s16,0xC)=0; P6(self,s16,0xE)=0; P6(self,s16,0x360)=0;
 P6(self,u64,0x20)=(P6(self,u64,0x20)&~0x10810000000ULL)|0x1000000000ULL;
 func_800DECAC(self,0,0,0);
 P6(self,s8,0x362)=-1; P6(self,s8,0x363)=-1;
 P6(self,u64,0x20)&=~0x40000000ULL;
 P6(other,s16,0xA)=otherAction;
 P6(other,s16,0xC)=0; P6(other,s16,0xE)=0; P6(other,s16,0x360)=0;
 P6(other,u64,0x20)=(P6(other,u64,0x20)&~0x10810000000ULL)|0x1000000000ULL;
 func_800DECAC(other,0,0,0);
 P6(other,s8,0x362)=-1; P6(other,s8,0x363)=-1;
 P6(other,u64,0x20)&=~0x40000000ULL;
 func_800A700C(self);func_800A700C(other);
 P6(self,u64,0x20)|=0x1060000000ULL;
 P6(other,u64,0x20)|=0x1020000000ULL;
 P6(self,u8,0x362)=P6(other,u8,0);
 P6(self,s8,0x351)=-1;
 P6(self,u8,0x353)=P6(other,u8,0);
 P6(other,u8,0x353)=P6(self,u8,0);
 P6(other,u8,0x351)=P6(self,u8,0);
}
