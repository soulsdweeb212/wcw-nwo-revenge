/* @header
 * updateEntityTargetLookAngles  (originally func_800D4604)
 * VRAM 0x800D4604 | ROM 0xC7AA4 | size 0x39C
 * asm: asm/nonmatchings/code_800BBA00/updateEntityTargetLookAngles.s
 */
#include "common.h"

typedef struct { f32 f0,f4; s32 f8; } Heading;
f32 func_800D3564(f32);
f32 func_800D3890(void *,void *,void *);
f32 func_800D3A74(void *,void *,void *);
extern f64 D_800E6C10,D_800E6C18,D_800E6C20,D_800E6C28,D_800E6C30,D_800E6C38,D_800E6C40,D_800E6C48,D_800E6C50,D_800E6C58;
extern Nw2DirectionResult D_800F9D6C[][59];
extern s16 D_800F9D18[][472];
extern u8 D_800F9D68[],D_800F9DBC[],D_800F9DC0[],D_800F9DC4[],D_800FA063[];
static __inline__ Nw2DirectionResult *getGeo(s8 id) {return D_800F9D6C[id];}

/* Smoothly turns an entity's look/tilt angles (Heading: f0 yaw, f4 pitch) toward
 * a target, but only while the entity carries u64 flag 0x100000000000.  It reads
 * the target direction vector (func_800D3890) and applies a clamped per-frame
 * pitch step and yaw step derived from the heading error against the entity's
 * stored heading (D_800F9D68), the f64 rate constants D_800E6C10..C58 and the
 * limits (+/-67.5 deg pitch, +/-30 deg yaw); a second geo vector drives the yaw
 * error through func_800D3A74.  Without the flag the angles are zeroed and 0 is
 * returned. */
s32 updateEntityTargetLookAngles(s8 entityIndex, Heading *look) {
 Nw2DirectionResult targetVec; s32 recordOffset; f32 delta,lookDistance;
 recordOffset=(s8)entityIndex*0x3B0;
 if (*(u64 *)(D_800F9D30+recordOffset)&(0x1000ULL<<32)) {
 f32 pitchStep;
 lookDistance=func_800D3890(getGeo(entityIndex)+5,getGeo(*(s8 *)(D_800FA063+recordOffset))+5,&targetVec);
 delta=(f32)((f64)func_800D3684(targetVec.angle,*(s32 *)(D_800F9D68+recordOffset))*D_800E6C10);
 pitchStep=delta;
 if(D_800E6C18<(f64)delta) pitchStep=8.0f;
 if((f64)delta<D_800E6C20) pitchStep=-8.0f;
 look->f4+=pitchStep;
 {f32 currentPitch=func_800D3564(look->f4); if(currentPitch>func_800D3564(delta)) look->f4=delta;}
 if(D_800E6C28<(f64)look->f4) look->f4=67.5f;
 if((f64)look->f4<D_800E6C30) look->f4=-67.5f;
 if(*(u64 *)(D_800F9D30+recordOffset)&0x140ULL) {if(D_800F9D18[(s8)entityIndex][0]!=0xF13) look->f4=0.0f;}
 {s32 selfOffset=(s8)entityIndex*0x3B0;
 targetVec.x=0.0f;
 targetVec.y=*(f32 *)(D_800F9DC0+*(s8 *)(D_800FA063+selfOffset)*0x3B0);
 targetVec.z=*(f32 *)(D_800F9DC4+selfOffset)+lookDistance;
 func_800D3A74(D_800F9DBC+selfOffset,&targetVec,&targetVec);}
 delta=(f32)((f64)targetVec.angle*D_800E6C38-(f64)look->f0);
 if(D_800E6C40<(f64)delta) delta=4.0f;
 if((f64)delta<D_800E6C48) delta=-4.0f;
 look->f0+=delta;
 if(D_800E6C50<(f64)look->f0) look->f0=30.0f;
 if((f64)look->f0<D_800E6C58) look->f0=-30.0f;
 return 1;
 }
 look->f0=0.0f;look->f4=0.0f;look->f8=0;return 0;
}
