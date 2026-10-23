#include "common.h"

/* Spawn one particle/effect instance for an entity: take a free slot from
 * func_800E2A18, set the entity's "active" flag, and fill the slot's type
 * (from the source flags or a random 3..10), owner id and (optionally) mirror
 * the type. Returns 1 on success, 0 if no slot was available. */
s8 func_800E2A18(void); s32 func_800D4148(void);
extern s8 D_800F99A0[]; extern s8 D_800F98E0[][48],D_800F98E1[][48],D_800F98E2[][48];
#define F(p,t,o) (*(t *)((u8 *)(p)+(o)))
s32 func_800E1920(void *entity,s32 flags) {
 s8 slot,variant; u16 flagsIn=flags;
 if(!(flags&4) || (F(F(entity,void *,0x364),u64,0x38)&0xC000000000ULL)) {
 slot=func_800E2A18();
 if(slot==-1) return 0;
 F(entity,u64,0x20)|=0x1000000000000ULL;
 D_800F99A0[F(entity,s8,0)]=slot;
 if(flagsIn&4) {
 variant=(F(F(entity,void *,0x364),u64,0x38)&0x4000000000ULL)?4:6;
 } else {
 variant=0;
 if(F(entity,s16,2)!=0x703) variant=(s16)func_800D4148()%8+3;
 }
 D_800F98E0[slot][0]=variant;
 if(variant<6) F(entity,u64,0x20)|=0x2000000000000ULL;
 D_800F98E2[slot][0]=F(entity,s8,0);
 if(flagsIn&2) D_800F98E1[slot][0]=D_800F98E0[slot][0];
 return 1;
 }
 return 0;
}
