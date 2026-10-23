#include "common.h"

s32 func_800D4148(void);
extern u8 *D_800FABD0,*D_800F9B60,*D_800FAF58;
void func_800B2A78(void) {
 u8 *p=D_800FABD0,*g; s32 mask; s32 random; u32 state; s16 timer;
 switch(*(s16 *)(p+4)) {
 case 0:
 switch(*(s16 *)(p+0x1e)) {
 case 0: case 2: mask=0x200; if(*D_800FAF58&2) mask=0x100; break;
 case 1: case 3: mask=0x400; if(*D_800FAF58&2) mask=0x800; break;
 }
 *(s16 *)(D_800FABD0+0xa)=mask;
 random=(s16)func_800D4148();
 p=D_800FABD0;
 (*(s16 *)(p+4))++;
 *(s16 *)(p+0xe)=random%18+8;
 break;
 case 1:
 timer=--(*(s16 *)(p+0xe));
 *(s16 *)(p+6)=*(s16 *)(p+0xa);
 if(timer<0 || *(s16 *)(p+0x14)!=1) {
 g=D_800F9B60;
 *(s16 *)(p+2)=0; *(s16 *)(p+4)=0;
 state=*(u16 *)(g+0xa);
 *(u32 *)(p+0x5c)&=~7;
 *(u16 *)(p+0x2e)=state;
 }
 break;
 }
}
