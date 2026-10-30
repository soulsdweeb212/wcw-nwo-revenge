/* @header
 * updateFlaggedAnimationAction  (originally func_800A4660)
 * VRAM 0x800A4660 | ROM 0x97B00 | size 0x164
 * asm: asm/nonmatchings/code_8009D7A0/func_800A4660.s
 */
#include "common.h"

extern void *D_800EB40C;
s32 func_800D2BEC(void *,void *,void *,f32,u16,s32);
void func_800A7328(void *);
void beginEntityActionA8D8C(void *);
void func_800D427C(void *,s16,s32);
void func_800D4AD0(void *);
/* Three-state action (state +0xC) that plays one of four animations chosen from
 * the entity's 0x3A flag bits (0x2200/0x400/0x4800/0x1000): state 0 starts the
 * entry animation (last matching flag wins) and advances; state 1 waits for the
 * timer then plays the exit animation; state 2 tears the action down and
 * restarts the entity action. */
void updateFlaggedAnimationAction(void) {
 s16 anim;
 u16 flags;
 func_800D2BEC(D_800EB408,D_800EB40C,0,4.0f,0,0xFFFFE);
 flags=*(u16*)((u8*)D_800EB40C+0x3A);
 switch(((Nw2F408*)D_800EB408)->fC) {
 case 0:
 if(flags&0x2200)anim=0x101A;
 if(flags&0x400)anim=0x1007;
 if(flags&0x4800)anim=0x101E;
 if(flags&0x1000)anim=0x100F;
 func_800A7328(D_800EB408);
 func_800D427C(D_800EB408,anim,2);
 ((Nw2F408*)D_800EB408)->fC++;
 break;
 case 1:
 if(((Nw2F408*)D_800EB408)->f4<=0) {
 if(flags&0x2200)anim=0x101C;
 if(flags&0x400)anim=0x1016;
 if(flags&0x4800)anim=0x1020;
 if(flags&0x1000)anim=0x1018;
 func_800D427C(D_800EB408,anim,0);
 ((Nw2F408*)D_800EB408)->fC++;
 }
 break;
 case 2:
 if(((Nw2F408*)D_800EB408)->f4<=0) {
 func_800D4AD0(D_800EB408);
 beginEntityActionA8D8C(D_800EB408);
 }
 break;
 }
}
