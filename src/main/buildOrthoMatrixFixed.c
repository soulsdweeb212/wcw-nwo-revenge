#include "common.h"

void func_8001B090(void *,void *);
void initIdentityMatrix4x4(void *);
/* Builds an orthographic projection matrix (left/right/bottom/top/near/far) in
 * float, scales every element by `scale`, and converts it into the fixed-point
 * matrix at dst. */
void buildOrthoMatrixFixed(void *dst,f32 l,f32 r,f32 b,f32 t,f32 n,f32 f,f32 scale) {
 f32 m[4][4];
 f32 (*p)[4]=m;
 f32 x,y,z,tx,ty,tz;
 s32 i,j;
 initIdentityMatrix4x4(p);
 x=2.0f/(r-l); y=2.0f/(t-b); z=-2.0f/(f-n);
 tx=-(r+l)/(r-l); ty=-(t+b)/(t-b); tz=-(f+n)/(f-n);
 m[3][3]=1.0f;
 m[0][0]=x;m[3][0]=tx;
 m[1][1]=y;m[2][2]=z;
 m[3][1]=ty;m[3][2]=tz;
 for(i=0;i<4;i++,p++) for(j=0;j<4;j++)p[0][j]*=scale;
 func_8001B090(m,dst);
}
