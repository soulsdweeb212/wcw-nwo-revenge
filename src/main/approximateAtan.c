#include "common.h"

extern f64 D_8003B0B0,D_8003B0B8;
f32 approximateAtan(f32 x) {
 s32 sign;
 s32 i,j;
 f32 value;
 if(x>1.0f) {sign=1;x=1.0f/x;}
 else if(x< -1.0f) {sign=-1;x=1.0f/x;}
 else sign=0;
 value=0.0f;
 for(i=8,j=17;i>0;j-=2,i--) value=(i*i*x*x)/(j+value);
 if(sign>0) return D_8003B0B0-x/(value+1.0f);
 else if(sign<0) return D_8003B0B8-x/(value+1.0f);
 else return x/(value+1.0f);
}
