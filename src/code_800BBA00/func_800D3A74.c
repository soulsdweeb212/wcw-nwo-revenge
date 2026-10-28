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
/* YZ-plane distance/heading between arg0 and arg1: stores the distance, dy, dz
 * and the heading into a 4-word result, copies to arg2 when given, returns the
 * distance. */
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
