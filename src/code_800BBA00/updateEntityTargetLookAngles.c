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
static __inline__ WrJointPos *getJoints(s8 id) {return D_800F9D10[id].jointA;}

/* Smoothly turns an entity's look/tilt angles (Heading: f0 yaw, f4 pitch) toward
 * its opponent, but only while the entity carries u64 flag 0x100000000000.  It
 * reads the direction from its joint 5 to the opponent's (func_800D3890) and
 * applies a clamped per-frame pitch step and yaw step derived from the error
 * against the entity's heading, the f64 rate constants D_800E6C10..C58 and the
 * limits (+/-67.5 deg pitch, +/-30 deg yaw); the opponent's joint 5 height,
 * relative to the entity's joint 5, drives the yaw error through func_800D3A74.
 * Without the flag the angles are zeroed and 0 is returned. */
s32 updateEntityTargetLookAngles(s8 entityIndex, Heading *look) {
    Nw2DirectionResult targetVec; f32 delta,lookDistance;
    if (D_800F9D10[(s8)entityIndex].flags&(0x1000ULL<<32)) {
        f32 pitchStep;
        lookDistance=func_800D3890(getJoints(entityIndex)+5,getJoints(D_800F9D10[(s8)entityIndex].opponentId)+5,&targetVec);
        delta=(f32)((f64)func_800D3684(targetVec.angle,D_800F9D10[(s8)entityIndex].heading)*D_800E6C10);
        pitchStep=delta;
        if(D_800E6C18<(f64)delta) pitchStep=8.0f;
        if((f64)delta<D_800E6C20) pitchStep=-8.0f;
        look->f4+=pitchStep;
        {f32 currentPitch=func_800D3564(look->f4); if(currentPitch>func_800D3564(delta)) look->f4=delta;}
        if(D_800E6C28<(f64)look->f4) look->f4=67.5f;
        if((f64)look->f4<D_800E6C30) look->f4=-67.5f;
        if(D_800F9D10[(s8)entityIndex].flags&0x140ULL) {if(D_800F9D10[(s8)entityIndex].animId!=0xF13) look->f4=0.0f;}
#ifdef TARGET_PC
        /* PC: a wrestler record is sizeof(Wrestler) bytes (0x3B8), not the N64's 0x3B0, so the byte offset of slot n is n * sizeof(Wrestler). */
        {s32 selfOffset=(s8)entityIndex*(s32)sizeof(Wrestler);
#else
        {s32 selfOffset=(s8)entityIndex*0x3B0;
#endif
            targetVec.x=0.0f;
            targetVec.y=D_800F9D10[*(s8 *)((u8 *)&D_800F9D10[0].opponentId+selfOffset)].jointA[5].y;
            targetVec.z=*(f32 *)((u8 *)&D_800F9D10[0].jointA[5].z+selfOffset)+lookDistance;
            func_800D3A74((u8 *)&D_800F9D10[0].jointA[5]+selfOffset,&targetVec,&targetVec);}
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
