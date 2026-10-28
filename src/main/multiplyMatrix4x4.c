#include "common.h"

extern f32 D_80048270,D_80048274,D_80048278,D_8004827C,D_80048280;
void func_80001930(void *);
/* Multiplies two 4x4 matrices (arg0 * arg1) into arg2. */
void multiplyMatrix4x4(f32 arg0[4][4],f32 arg1[4][4],f32 arg2[4][4]) {
 u32 i,j,k;
 for(i=0;i<4;i++) for(j=0;j<4;j++) {
 f32 sum=0;
 for(k=0;k<4;k++) sum+=arg0[i][k]*arg1[k][j];
 arg2[i][j]=sum;
 }
}
extern s8 D_800566E8[];extern s16 D_800566E0[]; extern u8 D_80065294[];
void func_8000D238(s32,s32);
