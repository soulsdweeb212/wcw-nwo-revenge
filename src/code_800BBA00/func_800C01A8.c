#include "common.h"

extern s16 D_800F9D12[][472],D_800F9D1A[][472],D_800F9D1C[][472];
extern u16 D_800E3AB0[],D_800FACEA[],D_800FADD0;
extern u8 D_800F9D10[],D_800F9D30[];
void func_800A6C48(void *,s32);
s32 func_800C01A8(s8 arg0) {
 s32 offset;
 s32 side;
 s16 state;
 { s32 t=arg0*0x3B0; offset=t; }
 if(*(s16 *)((u8 *)D_800F9D12+offset)==-1 && (((u64 (*)[118])D_800F9D30)[arg0][0]&2)) {
  side=arg0&1;
  if(D_800FADD0&D_800E3AB0[side]) {
   state=D_800F9D1A[side][0];
   if((state==1)|(state==44)) {
    D_800FADD0 &= 0xFFCF;
    *(s16 *)((u8 *)D_800F9D12+offset)=D_800FACEA[arg0];
    func_800A6C48(D_800F9D10+offset,143);
    *(s16 *)((u8 *)D_800F9D1C+offset)=5;
    return 1;
   }
  }
  return 0;
 }
 return 0;
}
