/* @header
 * func_800A3BFC
 * VRAM 0x800A3BFC | ROM 0x9709C | size 0x178
 * asm: asm/nonmatchings/code_8009D7A0/func_800A3BFC.s
 */
#include "common.h"

extern u8 D_800FABE4,D_800FADB8;
void func_800D2BEC(void*,void*,void*,f32,u16,s32);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D5438 */
s16 func_800D5438(void*,s32);
#endif
void func_800D427C(void*,s16,s32);
void func_800A6BE0(void*,s32);
void func_800D4AD0(void*);
void beginEntityActionA8D8C(void*);
void func_800C472C(void*,void*,s32);
void func_800A3BFC(void){
    Wrestler *p = D_800EB408;
    s32 k;
    do { } while (0);
    k = 0xffffe;
    func_800D2BEC(p,D_800EB40C,0,4.0f,0,k);
    if(D_800EB40C->flags&0x800000ULL){
        func_800D427C(D_800EB408,func_800D5438(D_800EB408,0),1);
        func_800A6BE0(D_800EB408,0x51);func_800A6BE0(D_800EB40C,0x52);
        D_800EB408->flags|=WR_FLAG_PAIR_LEADER;
        D_800EB40C->flags&=~WR_FLAG_PAIR_LEADER;
        D_800EB408->attached[0]=D_800FABE4;D_800EB40C->attached[0]=-1;D_800EB40C->heldById=D_800FADB8;
    }
    if(D_800EB408->animFramesLeft<=0){func_800D4AD0(D_800EB408);beginEntityActionA8D8C(D_800EB408);func_800C472C(D_800EB40C,D_800EB408,2);}
}
