#include "common.h"

extern f64 D_800E54E0,D_800E54E8,D_800E54F0;
void translateEntityXZ(void *,void *);
s8 func_800B5DC4(u8 *arg0,s16 arg1) {
 f32 vec[3];
 f32 pos;
 switch(*(s16 *)(arg0+0x3E)) {
 case 0:pos=*(f32 *)(arg0+0x74);break;
 case 1:pos=*(f32 *)(arg0+0x6C);break;
 case 2:pos=-*(f32 *)(arg0+0x74);break;
 case 3:pos=-*(f32 *)(arg0+0x6C);break;
 }
 if(arg1==0) {
 if(D_800E54E0<=pos && pos<D_800E54E8)return 1;
 } else if(D_800E54F0<=pos) {
 vec[0]=0;vec[2]=0;
 switch(*(s16 *)(arg0+0x3E)) {
 case 0:vec[2]=D_800E54F0-pos;break;
 case 1:vec[0]=D_800E54F0-pos;break;
 case 2:vec[2]=pos-D_800E54F0;break;
 case 3:vec[0]=pos-D_800E54F0;break;
 }
 translateEntityXZ(arg0,vec);
 return 1;
 }
 return 0;
}
