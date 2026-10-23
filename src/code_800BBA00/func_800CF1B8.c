#include "common.h"

/* Defensive reaction selector: if self is "hurt" (flag 0x80), start the hurt
 * animation; otherwise, if both fighters' stance bits overlap, pick a block/
 * reversal animation based on self's action bits; else fall back to the
 * checkFacingProximity test and a generic reaction. */
void func_800A7364(void *);
void func_800A7C40(void *,s8,s16);
void func_800A7F6C(void *,s32);
s8 checkFacingProximity(void *,void *,s32);
void func_800D427C(void *,s16,s32);
s16 func_800D5438(void *,s32);
void func_800CF1B8(u8 *self,u8 *opponent,s32 arg2,s32 arg3) {
 s32 animId;
 s16 reactionId;
 if (*(u64*)(self+0x20)&0x80ULL) {
 *(u32*)(self+0x2C)|=0x10;
 func_800A7364(self);
 func_800D427C(self,(*(u32*)(self+0x2C)&2)?0x108E:0x109E,2);
 } else if ((*(u64*)(opponent+0x20)&0x100000ULL) && (*(u16*)(opponent+0x28)&0x420) && (*(u64*)(self+0x20)&*(u64*)(opponent+0x20)&0x140ULL)) {
 *(u32*)(self+0x2C)|=4;
 if (*(u32*)(self+0x2C)&0x200000) func_800A7C40(self,*(s8*)self,0x56);
 else {
 if (*(u32*)(self+0x2C)&2) {
 animId=0x4A;
 if (*(u16*)(opponent+0x28)&0x40) animId=0x52;
 } else animId=(*(u16*)(opponent+0x28)&0x40)?0x4E:0x46;
 func_800A7C40(self,*(s8*)self,animId);
 }
 func_800D427C(self,func_800D5438(self,0),3);
 func_800A7F6C(self,0);
 } else {
 if (checkFacingProximity(self,opponent,arg3)) func_800D427C(self,0xEA2,3);
 else {
 if (*(u32*)(self+0x2C)&1) reactionId=(*(u32*)(self+0x2C)&2)?0xE9F:0xE9E;
 else reactionId=(*(u32*)(self+0x2C)&2)?0xE85:0xE84;
 func_800D427C(self,reactionId,3);
 }
 }
}
