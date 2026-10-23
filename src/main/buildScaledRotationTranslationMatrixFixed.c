#include "common.h"

/* Build a 4x4 row-major fixed-point-friendly transform: rotate by the Euler
 * angles x/y/z (degrees scaled by D_80037220), scale, then translate; the
 * result is converted through func_8001B090 (float -> fixed) into out. */
f32 cosf(f32); f32 sinf(f32); extern f32 D_80037220; void func_8001B090(void *,void *);
void buildScaledRotationTranslationMatrixFixed(void *out, f32 x, f32 y, f32 z, f32 scale, f32 tx, f32 ty, f32 tz) {
 f32 sx,cx,sy,cy,sz,cz;
 f32 mat[4][4];
 f32 rx=x*D_80037220, ry=y*D_80037220, rz=z*D_80037220;
 sx=sinf(rx); cx=cosf(rx); sy=sinf(ry); cy=cosf(ry); sz=sinf(rz); cz=cosf(rz);
 mat[0][0]=cy*cz*scale; mat[0][1]=cy*sz*scale; mat[0][2]=-sy*scale; mat[0][3]=0.0f;
 mat[1][0]=(sx*sy*cz-cx*sz)*scale; mat[1][1]=(sx*sy*sz+cx*cz)*scale; mat[1][2]=sx*cy*scale; mat[1][3]=0.0f;
 mat[2][0]=(cx*sy*cz+sx*sz)*scale; mat[2][1]=(cx*sy*sz-sx*cz)*scale; mat[2][2]=cx*cy*scale; mat[2][3]=0.0f;
 mat[3][0]=tx; mat[3][1]=ty; mat[3][2]=tz; mat[3][3]=1.0f; func_8001B090(mat,out);
}
