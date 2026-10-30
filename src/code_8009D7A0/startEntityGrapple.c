/* @header
 * startEntityGrapple  (originally func_800B5340)
 * VRAM 0x800B5340 | ROM 0xA87E0 | size 0x3F0
 * asm: asm/nonmatchings/code_8009D7A0/func_800B5340.s
 */
#include "common.h"

/* Resolve a grapple/lockup between 'self' and its nearest other entity.
 * Finds the partner (func_800D26A0), computes the pair's facing flags
 * (getEntityPairFacingFlags) and sets the 0x08000000 facing bit, then based on
 * the two entities' status words and action ids either starts a mutual grapple
 * (both action 5, slot indices swapped) or a one-sided lockup, or runs the
 * grapple check func_800B678C. Returns 1 if a grapple/lockup started. */
extern u8 D_800F9D10[],D_800F9D1A[];
s32 func_800D26A0(void*,s32,s32);s32 getEntityPairFacingFlags(u8*,u8*);
void func_800A6BE0(void*,s32); void func_800A6CDC(void*,s32);void func_800E212C(void*);s16 func_800B678C(void*,void*,u16);
s32 startEntityGrapple(u8 *self,s16 arg1,u16 arg2) {
 s32 id; u8 *other; u32 facing; s16 result;
 id=func_800D26A0(self,0,-1);
 if((s8)id != -1) {
 *(u64*)(self+0x20)&=~0x08000000ULL;
 other=D_800F9D10+(s8)id*0x3B0;
 *(u64*)(other+0x20)&=~0x08000000ULL;
 facing=getEntityPairFacingFlags(self,other);
 if(facing&2) *(u64*)(self+0x20)|=0x08000000ULL;
 if(facing&8) *(u64*)(other+0x20)|=0x08000000ULL;
 if(*(u64*)(other+0x20)&0x100000ULL) {
 if(*(u64*)(self+0x20)&0x80ULL) {
 func_800A6CDC(self,0x28);func_800A6CDC(other,0x28);
 *(u32*)(self+0x30)=0x80800000;*(u32*)(other+0x30)=0x80800000;
 self[0x351]=other[0];other[0x351]=self[0];return 1;
 }
 func_800E212C(self);func_800E212C(other);func_800A6BE0(self,5);func_800A6BE0(other,5);return 1;
 }
 if((u32)(*(u16*)(other+0xA)-0x40)<2 && !(*(u64*)(other+0x20)&0x08000000ULL)) {
 func_800E212C(self);func_800A6BE0(self,5);func_800A6BE0(other,0x41);*(s16*)(other+0xC)=2;return 1;
 }
 if((*(u16*)(self+0x28)&0x20) && *(s16*)(other+0xA)==0x14) {
 func_800A6BE0(self,5);func_800A6CDC(other,0x28);*(u32*)(other+0x30)=0x200000;return 1;
 }
 result=func_800B678C(self,other,(u16)arg2);
 if(result) {if(result==1) {func_800E212C(self);func_800A6C48(self,0x8A);return 1;}return 0;}
 if((*(u16*)(self+0x28)&0x80) && (s8)id==*(s8*)(self+0x351) && *(s16*)(D_800F9D1A+(s8)id*0x3B0)==0x19) return 0;
 if(*(u64*)(self+0x20)&0x80ULL) {
 if(!(*(u64*)(other+0x20)&0x0040001000000000ULL)) {
 func_800A6CDC(self,0x28);*(u32*)(self+0x30)=0x80400000;func_800A6CDC(other,0x28);*(u32*)(other+0x30)=0x80800000;other[0x351]=self[0];return 1;
 }
 if((s16)arg1==0) {*(u32*)(self+0x33C)=0;*(u32*)(self+0x344)=0;*(u64*)(self+0x20)|=0x1000000ULL;return 0;}
 }
 func_800A6C48(self,3);*(s16*)(self+0xC)=3;return 1;
 }
 *(s8*)(self+0x354)=-1;return 0;
}
