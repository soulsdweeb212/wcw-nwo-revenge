/* @header
 * func_800A3A74
 * VRAM 0x800A3A74 | ROM 0x96F14 | size 0x188
 * asm: asm/nonmatchings/code_8009D7A0/func_800A3A74.s
 */
#include "common.h"

s32 func_800D2BEC(void *,void *,void *,f32,u16,s32);
s16 func_800D5438(void *,s32);
void func_800D427C(void *,s16,s32);
void func_800B68A0(void *,void *,void *);
void func_800A837C(void *);
s8 func_800A83DC(void *,void *);
void func_800D4AD0(void *);
void func_800A3A74(void) {
    Wrestler *p; Wrestler *q;
    func_800D2BEC(D_800EB408,D_800EB40C,0,4.0f,0,0xFFFFE);
    if (!(D_800EB40C->flags&0x800000ULL) && D_800EB408->animFrame == D_800EB408->anim.reversalFrame && (D_800EB40C->flags&0x1000000ULL)) {
        D_800EB408->flags|=0x800000ULL;
        func_800D427C(D_800EB408,func_800D5438(D_800EB40C,1),1);
    }
    if (D_800EB408->animFramesLeft==1) func_800B68A0(D_800EB408,D_800EB408,D_800EB40C);
    if (D_800EB408->animFramesLeft<=0) {
        func_800A837C(D_800EB408);
        if (!func_800A83DC(D_800EB408,D_800EB40C)) {
            p=D_800EB408;
            p->attached[0]=-1;
            p->flags&=(q=D_800EB408,~WR_FLAG_PAIR_LEADER);
            func_800D4AD0(q);
            func_800A6C48(D_800EB408,0x2B);
        }
    }
}
