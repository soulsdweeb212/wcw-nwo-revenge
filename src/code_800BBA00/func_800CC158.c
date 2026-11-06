/* @header
 * func_800CC158
 * VRAM 0x800CC158 | ROM 0xBF5F8 | size 0xB0C
 * asm: asm/nonmatchings/code_800BBA00/func_800CC158.s
 */
#include "common.h"

extern u16 D_800EB5B8[];extern u8 D_8007EF30[];extern s8 D_800FADB8,D_800FAF78;extern u16 D_800FABE6,D_800FAF8A;
s16 func_800D5438(void*,s32);void func_800D427C(void*,s16,s32);s16 func_800B6DEC(void*,void*,s32);void func_800D7690(void*,s32,s32);s16 func_8000B710(s8);s8 func_800B71F8(void*,s32,s32);void func_800B68A0(void*,void*,void*);void func_800A7F6C(void*,s32);void func_800A837C(void*);void func_800D2BEC(void*,void*,void*,f32,u16,s32);void beginEntityActionA8D8C(void*);void func_800C472C(void*,void*,s32);void func_800D4AD0(void*);void func_800D7894(void*,u16,u64);void *func_800087DC(s16);void func_8000B728(s8,void*);void func_8000C784(s8);void func_800CCC64(void*,void*,u32);void func_8009786C(s32);void func_8009791C(void);void func_80097BB4(void);
#define CONFIG (*(u16*)&D_8007EF30[0x170])
void func_800CC158(void){switch(D_800FAF5C->step){case 0:
        D_800FAF5C->flags|=0x400000000000ULL;func_800D427C(D_800FAF5C,func_800D5438(D_800F9B00,1),1);D_800EB5B8[D_800FADB8]=0;D_800FAF5C->escapeTimer=func_800B6DEC(D_800FAF5C,D_800F9B00,3);func_800D7690(D_800FAF5C,0,0);
        if(D_800F9B00->move.flags&0x80){if((CONFIG&0x100)||(D_800FAF5C->flags&0x40)){if(D_800FAF5C->flags&D_800F9B00->flags&0x200)func_8009786C(4);}}D_800FAF5C->step++;break;
    case 1:D_800FAF5C->flags|=0x400000000000ULL;func_800D7894(D_800FAF5C,D_800FAF8A,0x400000000000ULL);
        if(D_800FAF78){if(D_800FAF5C->escapeTimer<=0){if((CONFIG&0x100)||(D_800FAF5C->flags&0x40))D_800FAF5C->flags|=0x800000000000ULL;}D_800FAF5C->escapeTimer=1;}
        if(D_800FAF5C->escapeTimer<0){if(!(D_800F9B00->pairSignals&0x21F))D_800F9B00->pairSignals|=2;}
        if(D_800FAF5C->escapeTimer<5){if(!(D_800F9B00->pairSignals&0x100)){if(!(D_800F9B00->pairSignals&0x21F)){
                    if((CONFIG&0x10)&&(D_800F9B00->move.flags&0x80)){if(D_800FAF5C->flags&D_800F9B00->flags&0x200){if((CONFIG&0x100)||(D_800FAF5C->flags&0x40)){if(D_800FAF5C->spirit<0x5B){if(D_800FAF5C->bodyPart[D_800F9B00->move.targetPart]<=0){if(D_800FAF5C->flags&0x800000000000ULL)D_800F9B00->pairSignals|=8;}}}}}
                    if(D_800F9B00->move.flags&0x4000){if(func_8000B710(D_800FAF5C->id)){if(!(D_800FAF5C->flags&0x4000000000000ULL)){if(!(D_800FAF5C->pairSignals&0x400)){if(D_800FAF5C->bodyPart[D_800F9B00->move.targetPart]<=0){D_800FAF5C->pairSignals|=0x400;if(func_800B71F8(D_800FAF5C,0,0xD)){D_800FAF5C->flags|=0x4000000000000ULL;D_800F9B00->pairSignals|=0x200;}}}}}}
                }}}
        {u16 *p=&D_800EB5B8[D_800FADB8];*p=*p+1;if((s16)*p>=0x1F){func_800B68A0(D_800F9B00,D_800F9B00,D_800FAF5C);D_800EB5B8[D_800FADB8]=0;
                if(!(D_800F9B00->pairSignals&0x100)){if(!(D_800F9B00->pairSignals&0x21F)){if(!(D_800FAF5C->pairSignals&0x80)){D_800FAF5C->pairSignals|=0x80;if((CONFIG&8)&&(D_800F9B00->move.flags&0x80)){if((CONFIG&0x100)||(D_800FAF5C->flags&0x40)){if(D_800FAF5C->flags&D_800F9B00->flags&0x200){if(D_800FAF5C->spirit<0x5B){if(func_800B71F8(D_800FAF5C,0,7))D_800F9B00->pairSignals|=8;}}}}}}}}}
        if(D_800FAF5C->flags&0x40){if(D_800FAF8A&0xC030){if(!(D_800F9B00->move.flags&0x200000)){func_800CCC64(D_800FAF5C,D_800F9B00,D_800FABE6);}}}
        if(!(D_800F9B00->move.flags&0x400000)){if(func_800D2BAC(D_800FAF5C,D_800F9B00,4.0f,0xFFFFC)){if(!(D_800F9B00->pairSignals&0x21F)){if(CONFIG&2){if(!(D_800FAF5C->flags&0x100)){if(D_800F9B00->move.flags&0x100){D_800F9B00->pairSignals|=4;func_800A7F6C(D_800FAF5C,0x56);func_800A837C(D_800FAF5C);D_800F9B00->pairSignals|=4;if(D_800FAF5C->flags&D_800F9B00->flags&0x200)func_8009791C();}}}}}}
        if(D_800F9B00->pairSignals&0x20){if(D_800F9B00->move.flags&0x80){if(!(D_800F9B00->pairSignals&0xC)){if(D_800FAF5C->flags&D_800F9B00->flags&0x200)func_80097BB4();}}
            if(D_800F9B00->pairSignals&2){if((CONFIG&0x100)||(D_800FAF5C->flags&0x40))D_800FAF5C->flags|=0x800000000000ULL;}
            {s16 a1;if(D_800F9B00->pairSignals&0x10)a1=7;else if(D_800F9B00->pairSignals&0x208)a1=5;else a1=3;func_800D427C(D_800FAF5C,func_800D5438(D_800F9B00,a1),0);}D_800FAF5C->step++;}break;
    case 2:func_800D2BEC(D_800FAF5C,D_800F9B00,0,2.0f,0,0xFFFFE);
        if(D_800F9B00->pairSignals&8){u8 *ptr=func_800087DC(D_800F9B00->animId);s16 i;for(i=0;i<8;i++){u8 a=ptr[0];if(a){if(a==D_800FAF5C->animFrame){if(ptr[1]==2)D_800FAF5C->flags|=0x1000;}}ptr+=2;}}
        if(D_800F9B00->pairSignals&0x200){if(D_800FAF5C->animFrame==0x28){D_800FAF5C->spirit=0x64;func_8000B728(D_800FADB8,D_800FAF5C);if(D_800FAF5C->flags&0x400000000ULL)func_8000C784(D_800FADB8);}}
        if(D_800FAF5C->animFramesLeft<=0){func_800D4AD0(D_800FAF5C);if((D_800FAF5C->flags&0x100)||(D_800F9B00->move.flags&4)||(D_800FAF5C->flags&0x8000))beginEntityActionA8D8C(D_800FAF5C);else{D_800FAF5C->flags|=0x80000000000000ULL;func_800A6C48(D_800FAF5C,0x2B);}if(!(D_800FAF5C->flags&0x8000)||(D_800FAF5C->flags&0x10000))func_800C472C(D_800F9B00,D_800FAF5C,2);}break;}}
