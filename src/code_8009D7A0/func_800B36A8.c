#include "common.h"

extern u8 *D_800FABD0, *D_800FAF58, *D_800F9B60;
extern f64 D_800E5398;
#define A(o,t) (*(t *)(D_800FABD0+(o)))
void func_800B36A8(void) {
 switch(A(4,s16)) {
 case 0: A(6,s16)=4; A(4,s16)++; break;
 case 1:
 switch(*(s16 *)(D_800FAF58+0xA)) {
 case 3: if (*(s16 *)(D_800FAF58+0xC)==2 && (f64)A(0x34,f32)<D_800E5398) { A(6,s16)=0x4000; A(4,s16)++; } break;
 case 4: A(4,s16)++; break;
 default: goto reset;
 } break;
 case 2:
 switch ((s16)*(u16 *)(D_800FAF58+0xA)) {
 case 3: A(8,s16)=0xF00; break;
 case 4: case 6: case 7: case 0x26: break;
 default: { u8 *g;
 reset: g=D_800F9B60;
 A(2,s16)=0; A(4,s16)=0; A(0x2E,u16)=*(u16 *)(g+0xA); A(0x5C,u32)&=~7;
 } break; } break;
 }
}
#undef A
