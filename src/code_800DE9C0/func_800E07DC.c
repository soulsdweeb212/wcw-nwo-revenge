#include "common.h"

extern s16 D_800F9D12[][0x1D8];
extern s16 D_800F9D1A[][0x1D8];
extern s16 D_800F9D1C[][0x1D8];
extern s16 D_800F9D4E[][0x1D8];
s32 func_800E07DC(void *arg0) {
 s16 i;
 for(i=0;i<4;i++) {
  if(D_800F9D12[i][0]!=-1 && D_800F9D4E[i][0]==*(s16 *)((u8 *)arg0+0x3E)) {
   if(D_800F9D1A[i][0]==20 && D_800F9D1C[i][0]<4) return 0;
   if(D_800F9D1A[i][0]==10) return 0;
   if(D_800F9D1A[i][0]==24) return 0;
  }
 }
 return 1;
}
