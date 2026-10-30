/* @header
 * calculateObjectVertexCentroid  (originally func_800016F4)
 * VRAM 0x800016F4 | ROM 0x22F4 | size 0x194
 * asm: asm/nonmatchings/main/func_800016F4.s
 */
#include "common.h"

typedef struct { u16 x,y,z; u8 pad[10]; } CenterVertex;
typedef struct { u8 pad[12]; CenterVertex *vertices; u8 pad10[11]; s8 count; } CenterMesh;
typedef struct { s32 f0; CenterMesh *mesh; s32 f8; f32 x,y,z; } CenterObject;
f32 signed64ToFloatTrunc(s64);
/* Computes the average of mesh->vertices (signed 16-bit x/y/z) and stores the
 * result in the object's x/y/z. Sums accumulate in 64-bit, are divided by the
 * vertex count, then converted to float. No mesh or no vertices -> no write. */
void calculateObjectVertexCentroid(CenterObject *obj) {
 CenterMesh *mesh=obj->mesh;
 s64 sumX=0,sumY=0,sumZ=0;
 CenterVertex *vertices=mesh->vertices;
 u32 i;
 if(vertices) {
  u32 count=mesh->count;
  for(i=0;i<count;i++) {
   u16 vx=vertices[i].x,vy=vertices[i].y,vz=vertices[i].z;
   sumX+=(s16)vx; sumY+=(s16)vy; sumZ+=(s16)vz;
  }
  if(count) {sumX/=count;sumY/=count;sumZ/=count;}
  obj->x=signed64ToFloatTrunc(sumX);obj->y=signed64ToFloatTrunc(sumY);obj->z=signed64ToFloatTrunc(sumZ);
 }
}
