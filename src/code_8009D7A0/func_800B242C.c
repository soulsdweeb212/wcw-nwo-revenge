#include "common.h"

extern u8 *D_800FABD0, *D_800F9B60, *D_800FAF58;
extern u16 D_800E3CF0[];
extern f64 D_800E5290;
s32 func_800D3650(void *,void *);
void func_800B242C(void) {
 u8 *p=D_800FABD0; u8 *g; s16 state=*(s16*)(p+4); u32 v;
 switch(state) {
 case 0:
 *(s16*)(D_800FABD0+6)=D_800E3CF0[(s16)func_800D3650(D_800F9B60+0x6C,D_800FAF58+0x6C)]|4;
 (*(s16*)(D_800FABD0+4))++;
 break;
 case 1:
 if (*(s16*)p==4) {
 if (*(s16*)(D_800FAF58+0xA)!=3) { *(s16*)(p+4)=state+1; }
 else if (D_800E5290 < (f64)*(f32*)(p+0x48+*(s16*)(D_800F9B60+0x3E)*4) || *(s16*)(p+0x22)!=0x11) {
 *(s16*)(p+8)=0xF00; (*(s16*)(p+4))++;
 }
 }
 break;
 case 2:
 if (*(s16*)(D_800FAF58+0xA)==3) *(s16*)(p+8)=0xF00;
 else if (*(s16*)(D_800FAF58+0xA)!=4) {
 g=D_800F9B60;
 *(s16*)(p+2)=0; *(s16*)(p+4)=0;
 v=*(u16*)(g+0xA);
 *(u32*)(p+0x5C)&=~7;
 *(u16*)(p+0x2E)=v;
 }
 break;
 }
}
