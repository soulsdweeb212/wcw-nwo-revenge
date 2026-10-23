#include "common.h"

extern f32 D_80048270,D_80048274,D_80048278,D_8004827C,D_80048280;
void func_80001930(void *);
/* Stores the per-call lighting parameters (colour bytes and position) into the
 * D_800482xx globals and runs the vertex-light update. */
void func_800018C4(void *arg0, f32 *arg1,s32 arg2,s32 arg3) {
 f32 x,y,z;
 arg2&=255;
 x=arg1[0];y=arg1[1];z=arg1[2];
 D_80048270=arg2; D_80048274=(arg3&255);
 D_80048278=x;D_8004827C=y;D_80048280=z;
 func_80001930(arg0);
}
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
/* Sets entity arg0's part-set byte: arg1==1 clears the flag (resetting the part
 * set when it was active), otherwise sets the flag and part set. Returns the
 * resulting value. */
s16 func_8000DB90(s16 arg0,s16 arg1) {
 s16 r=arg1;
 if(arg1==1) {
 if(D_800566E8[arg0]>=0) r=0;
 else func_8000D238(arg0,D_80065294[arg0*0x13C4]&0x7F);
 } else func_8000D238(arg0,D_80065294[arg0*0x13C4]|0x80);
 return r;
}
/* Sets entity arg0's part-set to arg1 when inactive; returns 1 when inactive. */
u32 func_8000DC50(s16 arg0,s16 arg1) {
 s16 *p;
 if(D_800566E8[arg0]<0) {
 p=(s16 *)(arg0*2+(s32)D_800566E0);
 if(arg1!=*p) {
 *p=arg1;D_800566E8[arg0]=0;
 func_8000D238(arg0,D_80065294[arg0*0x13C4]|0x80);
 }
 }
 return (u32)~D_800566E8[arg0]>>31;
}
