/* @header
 * updateActionObjectHandoff  (originally func_800A3610)
 * VRAM 0x800A3610 | ROM 0x96AB0 | size 0x198
 * asm: asm/nonmatchings/code_8009D7A0/updateActionObjectHandoff.s
 */
#include "common.h"

/* Action-object handler for the 0x800A34xx family.
 * A = D_800EB408 (action object), B = D_800EB40C (entity).
 * If B's flags bit 0x800000 is set, the action is handed off to A: B clears
 * its 0x40000000 flag, A gains it, animation ids are swapped and A restarts
 * with animation 0x49. Otherwise the action runs its normal teardown/begin
 * sequence unless A is still busy (A->f4 > 0). */
extern void *D_800EB40C;
extern u8 D_800FABE4;
s32 func_800D2BEC(void *,void *,void *,f32,u16,s32);
s16 func_800D5438(void *,s32);
void func_800D427C(void *,s16,s32);
void func_800D4AD0(void *);
void func_800A6BE0(void *,s32);
void func_800A7F6C(void *,s32);
void beginEntityActionA8D8C(void *);
s8 func_800C472C(void *,void *,s32);
#define AOBJ ((Nw2ActionEB408 *)D_800EB408)
#define BOBJ ((Nw2ActionEB408 *)D_800EB40C)
void updateActionObjectHandoff(void){
 Nw2ActionEB408 *action=AOBJ;
 do {}while(0);
 if(!(BOBJ->f2C&0x380))func_800D2BEC(action,D_800EB40C,0,4.0f,0,0xFFFFE);
 if(BOBJ->flags&0x800000ULL){
 BOBJ->flags&=~0x40000000ULL;
 AOBJ->flags|=0x40000000ULL;
 BOBJ->f362=-1;
 AOBJ->f362=D_800FABE4;
 AOBJ->f2C=BOBJ->f2C;
 func_800D427C(D_800EB408,func_800D5438(D_800EB408,0),1);
 func_800A6BE0(D_800EB408,0x49);
 func_800A7F6C(D_800EB408,0);
 return;
 }
 if(AOBJ->f4>0)return;
 func_800D4AD0(D_800EB408);
 beginEntityActionA8D8C(D_800EB408);
 if(AOBJ->f8!=0x16B7&&AOBJ->f8!=0x16B9)func_800C472C(D_800EB40C,D_800EB408,2);
}
