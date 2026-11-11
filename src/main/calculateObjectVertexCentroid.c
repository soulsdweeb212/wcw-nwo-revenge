/* @header
 * calculateObjectVertexCentroid  (originally func_800016F4)
 * VRAM 0x800016F4 | ROM 0x22F4 | size 0x194
 * asm: asm/nonmatchings/main/calculateObjectVertexCentroid.s
 */
#include "common.h"

typedef struct { u16 x,y,z; u8 pad[10]; } CenterVertex;
#ifdef TARGET_PC
/* PC: CenterMesh is the 0xDC-byte object and CenterObject its work block, which keep their N64 layout (Nw2SceneObj and
 * Nw2SceneWork in common.h). Their address fields, the vertices and the owner, hold 4-byte handles (port.h's
 * PTR_TO_SLOT), which the code below turns back with SLOT_TO_PTR. The asserts check the views against the two. */
typedef struct { u8 pad[12]; u32 vertices; u8 pad10[11]; s8 count; } CenterMesh;
typedef struct { s32 f0; u32 mesh; s32 f8; f32 x,y,z; } CenterObject;
_Static_assert(offsetof(CenterMesh, vertices) == offsetof(Nw2SceneObj, vtx) &&
                   offsetof(CenterMesh, count) == offsetof(Nw2SceneObj, vtxCount),
               "CenterMesh must follow Nw2SceneObj");
_Static_assert(offsetof(CenterObject, mesh) == offsetof(Nw2SceneWork, owner) &&
                   offsetof(CenterObject, x) == offsetof(Nw2SceneWork, center),
               "CenterObject must follow Nw2SceneWork");
#else
typedef struct { u8 pad[12]; CenterVertex *vertices; u8 pad10[11]; s8 count; } CenterMesh;
typedef struct { s32 f0; CenterMesh *mesh; s32 f8; f32 x,y,z; } CenterObject;
#endif
f32 __floatdisf(s64);
/* Computes the average of mesh->vertices (signed 16-bit x/y/z) and stores the
 * result in the object's x/y/z. Sums accumulate in 64-bit, are divided by the
 * vertex count, then converted to float. No mesh or no vertices -> no write. */
void calculateObjectVertexCentroid(CenterObject *obj) {
#ifdef TARGET_PC
    /* PC: the owner and its vertices are handles (see the views above). */
    CenterMesh *mesh=SLOT_TO_PTR(obj->mesh);
    s64 sumX=0,sumY=0,sumZ=0;
    CenterVertex *vertices=SLOT_TO_PTR(mesh->vertices);
#else
    CenterMesh *mesh=obj->mesh;
    s64 sumX=0,sumY=0,sumZ=0;
    CenterVertex *vertices=mesh->vertices;
#endif
    u32 i;
    if(vertices) {
        u32 count=mesh->count;
        for(i=0;i<count;i++) {
            u16 vx=vertices[i].x,vy=vertices[i].y,vz=vertices[i].z;
            sumX+=(s16)vx; sumY+=(s16)vy; sumZ+=(s16)vz;
        }
        if(count) {sumX/=count;sumY/=count;sumZ/=count;}
        obj->x=__floatdisf(sumX);obj->y=__floatdisf(sumY);obj->z=__floatdisf(sumZ);
    }
}
