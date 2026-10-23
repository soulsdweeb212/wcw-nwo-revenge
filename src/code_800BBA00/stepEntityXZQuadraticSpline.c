#include "common.h"

extern f64 D_800E6D98;
extern f32 D_800F97F0[],D_800F9800[];
extern s8 D_800FADB8;
void func_800D4028(f32,f32 *);
typedef struct {u8 pad[0x4C]; f32 x,y,z;} Entity732C;
s32 stepEntityXZQuadraticSpline(Entity732C *arg0,f32 arg1[][4]) {
 f32 w[3];
 f64 threshold=D_800E6D98;
 if(D_800F97F0[D_800FADB8]>=threshold) D_800F97F0[D_800FADB8]=1.0f;
 func_800D4028(D_800F97F0[D_800FADB8],w);
 arg0->x=w[0]*arg1[0][0]+w[1]*arg1[1][0]+w[2]*arg1[2][0];
 arg0->z=w[0]*arg1[0][2]+w[1]*arg1[1][2]+w[2]*arg1[2][2];
 if(D_800F97F0[D_800FADB8]>=threshold) return 1;
 D_800F97F0[D_800FADB8]+=D_800F9800[D_800FADB8];
 return 0;
}
