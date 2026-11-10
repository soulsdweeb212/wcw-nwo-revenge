/* @header
 * updateActionObjectHandoff  (originally func_800A3610)
 * VRAM 0x800A3610 | ROM 0x96AB0 | size 0x198
 * asm: asm/nonmatchings/code_8009D7A0/updateActionObjectHandoff.s
 */
#include "common.h"

/* Action-object handler for the 0x800A34xx family.
 * A = D_800EB408 (action object), B = D_800EB40C (entity).
 * If B's flags bit 0x800000 is set, the action is handed off to A: B clears
 * its 0x40000000 (pair leader) flag, A gains it, attached[0] and grappleCtx
 * move over and A restarts with animation 0x49. Otherwise the action runs its
 * normal teardown/begin sequence unless A is still busy (animFramesLeft > 0). */
extern u8 D_800FABE4;
s32 func_800D2BEC(void *,void *,void *,f32,u16,s32);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D5438 */
s16 func_800D5438(void *,s32);
#endif
void func_800D427C(void *,s16,s32);
void func_800D4AD0(void *);
void func_800A6BE0(void *,s32);
void func_800A7F6C(void *,s32);
void beginEntityActionA8D8C(void *);
s8 func_800C472C(void *,void *,s32);
void updateActionObjectHandoff(void){
    Wrestler *action=D_800EB408;
    do {}while(0);
    if(!(D_800EB40C->grappleCtx&0x380))func_800D2BEC(action,D_800EB40C,0,4.0f,0,0xFFFFE);
    if(D_800EB40C->flags&0x800000ULL){
        D_800EB40C->flags&=~0x40000000ULL;
        D_800EB408->flags|=0x40000000ULL;
        D_800EB40C->attached[0]=-1;
        D_800EB408->attached[0]=D_800FABE4;
        D_800EB408->grappleCtx=D_800EB40C->grappleCtx;
        func_800D427C(D_800EB408,func_800D5438(D_800EB408,0),1);
        func_800A6BE0(D_800EB408,0x49);
        func_800A7F6C(D_800EB408,0);
        return;
    }
    if(D_800EB408->animFramesLeft>0)return;
    func_800D4AD0(D_800EB408);
    beginEntityActionA8D8C(D_800EB408);
    if(D_800EB408->animId!=0x16B7&&D_800EB408->animId!=0x16B9)func_800C472C(D_800EB40C,D_800EB408,2);
}
