#include "common.h"

extern u8 *D_800FABD0,*D_800FAF58,*D_800F9B60;
extern s16 D_800FABEC[][32],D_800FABF4[][32];
s8 func_800D4198(s16);
#define A(o,t) (*(t *)(D_800FABD0+(o)))
void func_800AE7C8(void) {
 switch(A(4,s16)) {
 case 0: A(6,u16)=0x4000; A(4,s16)++; break;
 case 1:
 switch(*(s16 *)(D_800FAF58+0xA)) {
 case 30:
 A(6,u16)=0x4000;
 if(A(0x5C,u32)&2) {
 s32 id=*(s8 *)D_800FAF58;
 s32 a=D_800FABEC[id][0], b=D_800FABF4[id][0];
 if(b<a) { A(6,u16)=0x4F00; break; }
 if(a!=b) break;
 }
 if(func_800D4198(500)) A(6,u16)|=0xF00;
 break;
 case 31: break;
 default: {u8 *g=D_800F9B60;
 A(2,s16)=0; A(4,s16)=0; A(0x2E,u16)=*(u16 *)(g+0xA); A(0x5C,u32)&=~7;
 } break;
 }
 break;
 }
}
#undef A
