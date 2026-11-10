/* @header
 * func_800A2050
 * VRAM 0x800A2050 | ROM 0x954F0 | size 0x65C
 * asm: asm/nonmatchings/code_8009D7A0/func_800A2050.s
 */
#include "common.h"

extern u16 D_800F9D08[];
extern s16 D_800E3262[];
extern u8 D_800FADCF;
extern s8 D_800FAF78,D_800FADB8;
extern u16 D_800FAF8A;
extern u8 D_8007EF30[];
s16 func_800B6DEC(void *,s32,s32);
void func_800D7690(void *,s32,s32);
s8 func_800A93C0(void);
s8 func_800A9348(void *);
s8 func_800B71F8(void *,s32,s32);
void func_800D427C(void *,s16,s32);
s8 func_800D7894(void *,u16);
s8 func_800DA8D0(void *);
void beginEntityActionA8D8C(void *);
void func_800D4AD0(void *);
void func_800A9290(void *);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D2B64 */
s32 func_800D2B64(void *,f32,u16,s32);
#endif
void func_800A2050(void) {
    s32 a3;s32 a1;
    switch(D_800EB408->step) {
    case 0:
        D_800EB408->comboHits=0;D_800EB408->knockdowns=D_800EB408->knockdowns+1;D_800F9D08[(s8)D_800FADB8]=0;
        D_800EB408->escapeTimer=func_800B6DEC(D_800EB408,0,0);func_800D7690(D_800EB408,0,0);
        if(!func_800A93C0()){if(!(D_800EB408->flags&0x10ULL)){if(func_800A9348(D_800EB408)){if(func_800B71F8(D_800EB408,0,8))D_800EB408->stepFlags|=1;}}}
        D_800EB408->step++;
    case 1:
        D_800EB408->flags|=0x1000000000ULL|0x400000ULL;
        if((u32)(D_800EB408->pose-7)>=0x1A){if(D_800EB408->flags&0x200000ULL)D_800EB408->pose=0x1C;else D_800EB408->pose=0x1B;}
        func_800D427C(D_800EB408,D_800E3262[(s8)D_800EB408->pose],1);
        if(D_800EB408->flags&0x8000ULL)D_800EB408->flags|=0x10000ULL;
        D_800EB408->step++;break;
    case 2:
        D_800EB408->flags|=0x400000ULL;
        if(D_800EB408->stepFlags&1){D_800EB408->step=4;break;}
        if((u32)(D_800EB408->pose-0x1B)<2){s8 c=(s8)D_800EB408->pose;if(c==0x1B)a3=0xFC4;if(c==0x1C)a3=0xFC5;func_800D427C(D_800EB408,a3,6);}
        if(*(u16 *)(D_8007EF30+0x170)&0x400){if((D_800EB408->flags&0x100ULL)&&!(D_800EB408->flags&0x8000ULL)){D_800EB408->flags|=0x1000000000ULL|0x800ULL;break;}}
        D_800EB408->step++;break;
    case 3:
        D_800EB408->flags|=0x400000ULL;func_800D2B64(D_800EB408,4.0f,0,0xFFFFE);
        if(D_800FADCF&0x40){
            if(D_800EB408->flags&0x4000ULL)func_800A6C48(D_800EB408,0x43);
            if(D_800EB408->flags&0x8000ULL)break;
            if(!func_800D7894(D_800EB408,D_800FAF8A))break;
            if(D_800FAF78||func_800DA8D0(D_800EB408)){D_800EB408->escapeTimer=0;break;}
            func_800A6C48(D_800EB408,0x43);
        }else{
            if(D_800EB408->flags&0x10ULL)break;
            if(!func_800D7894(D_800EB408,D_800FAF8A))break;
            if(D_800FAF78||func_800DA8D0(D_800EB408)){D_800EB408->escapeTimer=0;break;}
            func_800A6C48(D_800EB408,(D_800EB408->flags&0x8000ULL)&&(D_800EB408->flags&0x40ULL)?0x85:0x43);
        }
        break;
    case 4:func_800A9290(D_800EB408);D_800EB408->step++;break;
    case 5:a3=(D_800EB408->flags&0x200000ULL)?0xF37:0xF36;func_800D427C(D_800EB408,a3,6);D_800EB408->step++;break;
    case 6:
        func_800D2B64(D_800EB408,2.0f,0,0xFFFFE);
        if(D_800EB408->animFramesLeft<=0){func_800D4AD0(D_800EB408);beginEntityActionA8D8C(D_800EB408);}break;
    case 7:
        a3=0x1000;
        if(!(D_800EB408->flags&0x200000ULL))a3=(D_800EB40C->move.flags&0x10)?0xFFE:0xFFF;
        func_800D427C(D_800EB408,a3,6);D_800EB408->step++;
    case 8:
        func_800D2B64(D_800EB408,2.0f,0,0xFFFFE);
        if(D_800EB408->animFramesLeft<=0){func_800D4AD0(D_800EB408);func_800A6C48(D_800EB408,0x2B);}break;
    }
}
