/* @header
 * func_800A5A40
 * VRAM 0x800A5A40 | ROM 0x98EE0 | size 0x164
 * asm: asm/nonmatchings/code_8009D7A0/func_800A5A40.s
 */
#include "common.h"

void beginEntityActionA8D8C(void *);
void func_800CE388(void *,void *,void *);
s8 func_800CE6E4(void *,s32);
void func_800D4AD0(void *);
void func_800A7D1C(void *,s32);
void func_800B68A0(void *,void *,void *);
extern s32 D_800F9B24[][4];
extern s8 D_800FADB8;
void func_800A5A40(void) {
    s16 anim;
    s32 value;
    switch(D_800EB408->step) {
    case 0:
        func_800CE388(D_800EB408,D_800EB40C,D_800F9B24[D_800FADB8]);
        D_800EB408->step++;
    case 1:
        if(func_800CE6E4(D_800EB408,D_800F9B24[D_800FADB8][0])) D_800EB408->step++;
        break;
    case 2:
        if(D_800EB408->animFramesLeft<=0) {
            anim=D_800EB408->animId;
            value=0;
            switch(anim) {
            case 0x10AE:value=0x1F;break;
            case 0x10B6:value=0x1E;break;
            case 0x10B4:value=0x20;break;
            }
            if(value) {func_800A7D1C(D_800EB408,value);func_800B68A0(D_800EB408,D_800EB40C,D_800EB408);}
            func_800D4AD0(D_800EB408);
            beginEntityActionA8D8C(D_800EB408);
        }
        break;
    }
}
