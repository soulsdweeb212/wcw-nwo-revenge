/* @header
 * func_800A4274
 * VRAM 0x800A4274 | ROM 0x97714 | size 0x1B8
 * asm: asm/nonmatchings/code_8009D7A0/func_800A4274.s
 */
#include "common.h"

/* Three-step reach/hold action on self D_800EB408:
 * 0) copy the opponent's moveId; if the opponent's move has flag 0x1000000 jump
 *    straight to step 2 and request a rerun, else arm the animation and advance;
 * 1) run the hold until the animation ends, then finish and, if the moveIds
 *    still match, have the opponent react;
 * 2) run the alternate 4-frame hold and finish. */
void beginEntityActionA8D8C(void *); void func_800C472C(void *,void *,s32);
s32 func_800D2B64(void *,f32,u16,s32);
s32 func_800D2BEC(void *,void *,void *,f32,u16,s32);
void func_800D427C(void *,s16,s32); void func_800D4AD0(void *);
s16 func_800D5438(void *,s32); void func_800D7E80(void *,void *); void func_800D8D74(void *,s32);
void func_800A4274(void) {
    switch(D_800EB408->step) {
    case 0:
        D_800EB408->moveId=D_800EB40C->moveId;
        if(D_800EB40C->move.flags&0x01000000) {
            D_800EB408->step=2;
            D_800EB408->flags|=WR_FLAG_RERUN;
            return;
        }
        func_800D427C(D_800EB408,func_800D5438(D_800EB40C,1),2);
        func_800D7E80(D_800EB408,D_800EB40C);
        D_800EB408->step++;
    case 1:
        func_800D8D74(D_800EB408,0);
        func_800D2BEC(D_800EB408,D_800EB40C,0,4.0f,0,0xFFFFE);
        if(D_800EB408->animFramesLeft<=0) {
            func_800D4AD0(D_800EB408); beginEntityActionA8D8C(D_800EB408);
            if(D_800EB408->moveId==D_800EB40C->moveId) func_800C472C(D_800EB40C,D_800EB408,2);
        }
        break;
    case 2:
        func_800D2B64(D_800EB408,4.0f,0,0xFFFFE);
        if(D_800EB408->animFramesLeft<=0) {func_800D4AD0(D_800EB408);beginEntityActionA8D8C(D_800EB408);}
        break;
    }
}
