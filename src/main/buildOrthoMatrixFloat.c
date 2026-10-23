#include "common.h"

void initIdentityMatrix4x4(void *);
/* Builds a float orthographic projection matrix from left/right/bottom/top/
 * near/far, then scales every element by `scale`. */
void buildOrthoMatrixFloat(f32 m[4][4], f32 l, f32 r, f32 b, f32 t, f32 n, f32 f, f32 scale) {
 f32 x,y,z,tx,ty,tz;
 s32 i,j;
 initIdentityMatrix4x4(m);
 x=2.0f/(r-l);
 y=2.0f/(t-b);
 z=-2.0f/(f-n);
 tx=-(r+l)/(r-l);
 ty=-(t+b)/(t-b);
 tz=-(f+n)/(f-n);
 m[3][3]=1.0f;
 m[0][0]=x; m[3][0]=tx;
 m[1][1]=y; m[2][2]=z;
 m[3][1]=ty; m[3][2]=tz;
 for(i=0;i<4;i++) for(j=0;j<4;j++) m[i][j]*=scale;
}
