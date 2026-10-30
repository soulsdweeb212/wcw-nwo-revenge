/* @header
 * getRingBoundaryPointAlongHeading  (originally func_800D746C)
 * VRAM 0x800D746C | ROM 0xCA90C | size 0x218
 * asm: asm/nonmatchings/code_800BBA00/getRingBoundaryPointAlongHeading.s
 */
#include "common.h"

f32 cosf(f32);f32 sinf(f32);
f32 func_800D3564(f32);f32 func_800D35D4(s32);
extern const f64 D_800E6DA0,D_800E6DA8;
typedef struct {f32 x,y,z;} Vec746C;
/* Returns the point where the ray from `from` at `angle` (4096 units per turn)
 * meets the +/-230 ring boundary, writing it to `out`, and returns the resulting
 * XZ direction quadrant.  Axis-aligned angles short-circuit straight to the
 * edge; other angles project onto the Z or X edge, whichever the ray hits
 * first (falling back to the X edge when the Z-edge hit is out of range). */
s16 getRingBoundaryPointAlongHeading(Vec746C *from,s32 angle,Vec746C *out) {
 f32 coord,boundary,z;
 switch(angle) {
 case 0: out->x=from->x;out->z=230.0f;break;
 case 1024:out->x=230.0f;out->z=from->z;break;
 case -1024:out->x=-230.0f;out->z=from->z;break;
 case 2048:case -2048:out->x=from->x;out->z=-230.0f;break;
 default:
 boundary=-230.0f;
 if((u32)(angle+0x3FF)<0x7FF)boundary=230.0f;
 coord=func_800D3564(boundary-from->z);
 coord=func_800D3564(coord/cosf(func_800D35D4(angle)));
 coord=coord*sinf(func_800D35D4(angle))+from->x;
 if(D_800E6DA0<=(f64)coord && (f64)coord<=D_800E6DA8) {
 out->x=coord;out->z=boundary;
 }else {
 boundary=-230.0f;if(angle>=0)boundary=230.0f;
 coord=func_800D3564(boundary-from->x);
 coord=func_800D3564(coord/sinf(func_800D35D4(angle)));
 z=coord*cosf(func_800D35D4(angle))+from->z;
 out->x=boundary;out->z=z;
 }
 break;
 }
 return (s16)getXZDirectionQuadrant((f32*)out);
}
