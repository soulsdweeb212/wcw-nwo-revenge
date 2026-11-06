/* @header
 * func_800CE388
 * VRAM 0x800CE388 | ROM 0xC1828 | size 0x35C
 * asm: asm/nonmatchings/code_800BBA00/func_800CE388.s
 */
#include "common.h"

void func_800A72FC(void *,void *,s32); void func_800A7328(void *); void func_800A7C40(void *,s8,s16);s32 func_800D35B0(s32,s32);void func_800D3E40(void *,void *,s32,void *);void func_800D427C(void *,s32,s32);s32 func_800D5438(void *,s32);extern s32 D_800E3CA0[];

/* Sets up a grapple/clinch positioning move between self and opp: a target
 * position posVec, the facing *headingOut (from D_800E3CA0, indexed by a ringSide:
 * the heading that faces the ring centre from that side) and an animation id.
 * - self in state 0x79 or 0x87, self->grappleCtx bit 0x10000: posVec = (0, -77)
 *   rotated by D_800E3CA0[opp->ringSide] around opp's pelvis (jointA[1]); anim
 *   0x10B5, or (grappleCtx bit 0x2000000 clear) move 0x85 of self's own table
 *   loaded by func_800A7C40 and anim func_800D5438(self, 0).
 * - same states without 0x10000: posVec = opp's pelvis x/z with one axis set to
 *   +/-345 by self->ringSide; heading D_800E3CA0[self->ringSide]; anim 0x10AD
 *   (0x10B3 with grappleCtx bit 0x40).
 * - otherwise, opp->grappleCtx bit 0x10000: self->moveDelta x/z = 0, heading
 *   D_800E3CA0[self->ringSide], anim 0x10B6 or func_800D5438(opp, 1); self's root
 *   is moved under its pelvis (func_800A7328) and the anim starts with mode 2.
 * - otherwise: posVec = self's pelvis x/z with one axis set to +/-190 by
 *   opp->ringSide; heading D_800E3CA0[opp->ringSide] with opp->grappleCtx bit 0x40
 *   (anim 0x10B4), else that plus 0x800 (anim 0x10AE).
 * The posVec branches set moveDelta toward posVec over 6 ticks (func_800A72FC) and
 * start the anim with mode 3. Finally self->turnPerTick = heading error / 6 and
 * stateTimer = 0. */
void func_800CE388(Wrestler *self,Wrestler *opp,s32 *headingOut) {
    f32 offsetVec[4]; f32 posVec[4]; s32 animId; s32 headingStep;
    if((self->state==0x79)|(self->state==0x87)) {
        if(self->grappleCtx&0x10000) {
            offsetVec[0]=0;offsetVec[2]=-77.0f;
            *headingOut=D_800E3CA0[opp->ringSide];func_800D3E40(&opp->jointA[1],offsetVec,*headingOut,posVec);
            animId=0x10B5;
            if(!(self->grappleCtx&0x2000000)) {func_800A7C40(self,self->id,0x85);animId=func_800D5438(self,0);}
        } else {
            posVec[0]=opp->jointA[1].x;posVec[2]=opp->jointA[1].z;
            switch(self->ringSide) {case 0:posVec[2]=345.0f;break;case 1:posVec[0]=345.0f;break;case 2:posVec[2]=-345.0f;break;case 3:posVec[0]=-345.0f;break;}
            *headingOut=D_800E3CA0[self->ringSide];animId=0x10AD;if(self->grappleCtx&0x40) animId=0x10B3;
        }
        goto position;
    } else if(opp->grappleCtx&0x10000) {
        self->moveDelta[0]=0;self->moveDelta[2]=0;*headingOut=D_800E3CA0[self->ringSide];animId=0x10B6;
        if(!(opp->grappleCtx&0x2000000)) animId=func_800D5438(opp,1);
        func_800A7328(self);func_800D427C(self,(s16)animId,2);
    } else {
        posVec[0]=self->jointA[1].x;posVec[2]=self->jointA[1].z;
        switch(opp->ringSide) {case 0:posVec[2]=190.0f;break;case 1:posVec[0]=190.0f;break;case 2:posVec[2]=-190.0f;break;case 3:posVec[0]=-190.0f;break;}
        animId=0x10B4;
        if(opp->grappleCtx&0x40) *headingOut=D_800E3CA0[opp->ringSide];
        else {*headingOut=func_800D35B0(D_800E3CA0[opp->ringSide],0x800);animId=0x10AE;}
        position:func_800A72FC(self,posVec,6);func_800D427C(self,(s16)animId,3);
    }
    headingStep=func_800D3684(*headingOut,self->heading)/6;self->stateTimer=0;self->turnPerTick=headingStep;
}
