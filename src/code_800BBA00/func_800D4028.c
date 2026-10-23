#include "common.h"

extern f64 D_800E6C00, D_800E6C08, D_800E6BD0, D_800E6BB0;
f32 cosf(f32);
f32 sinf(f32);
f32 func_80003A3C(f32,f32);
f32 nw2Sqrtf(f32);
s32 func_8001C580(void);
s16 func_800D4204(void);
extern s32 gRandSeed, D_800EB634;
extern s16 D_800EB638[];
typedef union { f32 f; s32 i; } NwFI;
typedef struct { NwFI e[4]; } NwV4;

/* Evaluate the three quadratic spline basis weights at t. */
void func_800D4028(f32 t, f32 *out) {
 f32 a,b,c;
 f64 u = D_800E6C00 - (f64)t;
 a = u*u*D_800E6C08;
 b = u*(f64)t+D_800E6C08;
 c = (f64)(t*t)*D_800E6C08;
 *out++ = a; *out++ = b; *out = c;
}

/* Seed the shared random generator from func_8001C580, discard `arg0 & 15` draws,
 * then choose an odd multiplier and fill the 32 rolling slots in D_800EB638. */
void func_800D4088(s32 arg0) {
 u8 n;
 s16 i;
 gRandSeed=func_8001C580();
 n=arg0&15;
 for(i=0;i<n;i++) func_8001C580();
 D_800EB634=func_8001C580()|1;
 for(i=0;i<32;i++) D_800EB638[i]=func_800D4204();
}

/* Rotate point arg1 by arg2 angle steps about the origin and add it to arg0,
 * writing the resulting X/Z into arg3. */
void func_800D3E40(f32 *arg0, f32 *arg1, s32 arg2, f32 *arg3) {
 f32 angle, c,s,x,z;
 angle=(f32)((f64)arg2*D_800E6BD0);
 c=cosf(angle);
 s=sinf(angle);
 x=arg1[0]; z=arg1[2];
 arg3[0]=arg0[0]+(x*c+z*s);
 arg3[2]=arg0[2]+(z*c-x*s);
}

/* YZ-plane distance and heading between two positions; optionally copy the
 * {distance,dy,dz,angle} result to arg2 and return the distance. */
f32 func_800D3A74(void *arg0, void *arg1, void *arg2) {
 f32 *p0=arg0,*p1=arg1;
 NwFI v[4];
 f32 dz,dy,dist;
 dz=p1[2]-p0[2]; v[2].f=dz;
 dy=p1[1]-p0[1]; v[1].f=dy;
 dist=nw2Sqrtf(dy*dy+dz*dz); v[0].f=dist;
 v[3].i=(s32)((f64)func_80003A3C(dy,dz)*D_800E6BB0);
 if(arg2!=NULL) *(NwV4*)arg2=*(NwV4*)v;
 return v[0].f;
}
