#include "common.h"

s8 checkFacingProximity(void *,void *,s32);
void func_800D427C(void *,s32,s32);
extern f64 D_800E6AF8,D_800E6B00;
/* When arg0 carries the 0x100 flag, tests the direction result arg2: if the
 * facing check passes and arg2->y is below D_800E6AF8 it starts action 0xEA2
 * and clears arg0's +0x2C, returning 1. If instead arg1 carries the 0x80 flag
 * and arg2->y is below D_800E6B00 it starts action 0xE84. */
s32 func_800D23B4(u8 *arg0,u8 *arg1,Nw2DirectionResult *arg2) {
 if(*(u64 *)(arg0+0x20)&0x100) {
 if(checkFacingProximity(arg0,arg1,arg2->angle) && (f64)arg2->y < D_800E6AF8) {
 func_800D427C(arg0,0xEA2,3); *(s32 *)(arg0+0x2C)=0; return 1;
 }
 if(*(u64 *)(arg1+0x20)&0x80) {
 if((f64)arg2->y < D_800E6B00) {func_800D427C(arg0,0xE84,3); return 1;}
 }
 }
 return 0;
}
