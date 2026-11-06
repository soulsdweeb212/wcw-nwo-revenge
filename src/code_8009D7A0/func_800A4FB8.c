/* @header
 * func_800A4FB8
 * VRAM 0x800A4FB8 | ROM 0x98458 | size 0x2A4
 * asm: asm/nonmatchings/code_8009D7A0/func_800A4FB8.s
 */
#include "common.h"

extern f32 D_800E3248[]; extern f32 D_800E324C[]; extern s32 D_800E3238[]; extern s32 D_800F9B0C; extern s32 D_800F9B24[]; extern s8 D_800FADB8;
s32 func_800D4D44(void*,s32,s32); void func_800D427C(void*,s32,s32); void func_800A7240(void*,s32,s32,u64); void func_800A6BE0(void*,s32); void translateEntityXZ(void*,void*); s32 func_800D2B64(void*,f32,u16,s32);
void func_800A4FB8(void){
    D_800EB408->flags|=0x1000000000ULL;
    switch(D_800EB408->step){
    case 0: if (D_800EB408->flags&0x200000ULL) func_800D427C(D_800EB408,0xFC5,1); else func_800D427C(D_800EB408,0xFC4,1); D_800EB408->stateTimer=0x3C; D_800EB408->step++;
    case 1: { Wrestler *q = D_800EB408; q->stateTimer--; if(q->stateTimer<0){ if (q->flags&0x200000ULL) func_800D427C(q,0xF33,1); else func_800D427C(q,0xF2D,1); D_800EB408->flags&=0xFFFFFFFFFFDFFFFFULL; D_800EB408->step++; } } break;
    case 2: if(D_800EB408->animFramesLeft>0) break; func_800D427C(D_800EB408,(s16)func_800D4D44(D_800EB408,0,D_800F9B0C),1); D_800EB408->dirIndex=getXZDirectionQuadrant(&D_800EB408->x); D_800EB408->moveDelta[0]=D_800E3248[D_800EB408->dirIndex*2]; D_800EB408->moveDelta[2]=D_800E324C[D_800EB408->dirIndex*2]; D_800F9B24[D_800FADB8*4]=D_800E3238[D_800EB408->dirIndex]; D_800EB408->flags|=WR_FLAG_RERUN; D_800EB408->step++; break;
    case 3: { s32 a = D_800F9B24[D_800FADB8*4]; func_800A7240(D_800EB408,a,0x155,0); } translateEntityXZ(D_800EB408,D_800EB408->moveDelta); if((u16)func_800D2B64(D_800EB408,1.0f,0,2)) func_800A6BE0(D_800EB408,0x60); break;
    }
}
