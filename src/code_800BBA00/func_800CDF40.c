#include "common.h"

/* Attack-eligibility tick for an entity: count down a re-arm timer, choose the
 * falling action id from the entity's state bits, latch the "new action" bit
 * when eligible, and otherwise return a mask describing which attack inputs
 * are accepted (writes the animation id to *animOut). */
s8 func_800A93C0(void*);s8 isEntityActionEligible(void*,s32,s32);void func_800D427C(void*,s16,s32);
s32 func_800CDF40(u8*self,u16 animBits,u16 inputBits,s16 flag,s16*animOut){
 s16 action;
 s32 bits,mask;
 if(func_800A93C0(self))*(s16*)(self+0x16)=0;
 if(inputBits&0x10)*(s16*)(self+0x16)=0;
 if(--*(s16*)(self+0x16)<0){
  s32 state=*(s32*)(self+0x2C);
  if(state&0x400)action=0xE8C;
  if(state&0x40)action=0xE90;
  if(state&0x80)action=0xE94;
  if(state&0x100)action=0xE98;
  if(state&0x200)action=0xE9C;
  func_800D427C(self,action,1);
  return 2;
 }
 bits=*(s32*)(self+0x2C);
 if(((bits&0x401)==0x401)&((s8)flag!=0)){
  *(s32*)(self+0x2C)|=0x200000;
  return 1;
 }
 if(isEntityActionEligible(self,0,0x7E)&&(s8)flag){
  *(s32*)(self+0x2C)|=0x200000;
  return 1;
 }
 if(isEntityActionEligible(self,0,0x6E)&&(s8)flag){
  *(s32*)(self+0x2C)|=0x200000;
  return 1;
 }
 bits=*(s32*)(self+0x2C);
 if(bits&0x40){
  mask=inputBits&0xC028;
  if(mask){
   *animOut=mask|(animBits&0xF00);
   return 1;
  }
 }else{
  mask=inputBits&0xC004;
  if(mask){
   *animOut=mask|(animBits&0xF00);
   return 1;
  }
  if((bits&0x400)&&(inputBits&0x20))return 3;
 }
 return 0;
}
