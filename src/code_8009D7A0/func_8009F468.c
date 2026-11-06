/* @header
 * func_8009F468
 * VRAM 0x8009F468 | ROM 0x92908 | size 0x1EC
 * asm: asm/nonmatchings/code_8009D7A0/func_8009F468.s
 */
#include "common.h"

extern s32 D_800E3CA0[];
void func_800D25D0(void *,f32);
s32 func_800D2B64(void *,f32,u16,s32);
s8 func_800D4198(s16);
s16 func_800C778C(void *);
void func_800D427C(void *,s16,s32);
void func_800D4AD0(void *);
void beginEntityActionA8D8C(void *);
/* 'Taunt/celebration' action for the wrestler being updated (D_800EB408): apply its
 * physics modifiers, then pick an animation from its flags (on the apron -> face
 * D_800E3CA0[ringSide] and play 0x10AB; 0x8000000 -> 0x1047; else a random gate
 * that can switch to step 2 and set hitInfo variant 0x1; else 0x1047/0x1046
 * depending on the profile's flags at +0x38), then count down and finish. */
void func_8009F468(void) {
    s16 anim;
    func_800D25D0(D_800EB408,4.0f);
    func_800D2B64(D_800EB408,2.0f,0,0xFFFFE);
    switch (D_800EB408->step) {
    case 0:
        if (D_800EB408->flags&WR_FLAG_ON_APRON) {
            D_800EB408->heading=D_800E3CA0[D_800EB408->ringSide];
            anim=0x10AB;
        } else if (D_800EB408->flags&0x8000000ULL) anim=0x1047;
        else if (func_800D4198(300)) {
            D_800EB408->hitInfo=(D_800EB408->hitInfo&0x8FFFEFFF)|0x10000000;
            func_800D427C(D_800EB408,func_800C778C(D_800EB408),1);
            D_800EB408->step=2;
            break;
        } else if (*(u64*)(D_800EB408->profile+0x38)&0x200ULL) anim=0x1047;
        else anim=0x1046;
        func_800D427C(D_800EB408,anim,1);
        D_800EB408->step++;
        break;
    case 1:
        if (D_800EB408->animFramesLeft<=0) func_800A6C48(D_800EB408,1);
        break;
    case 2:
        if (D_800EB408->animFramesLeft<=0) {func_800D4AD0(D_800FAF5C);beginEntityActionA8D8C(D_800FAF5C);}
        break;
    }
}
