/* @header
 * func_800A63D8
 * VRAM 0x800A63D8 | ROM 0x99878 | size 0xF4
 * asm: asm/nonmatchings/code_8009D7A0/func_800A63D8.s
 */
#include "common.h"

void beginEntityActionA8D8C(void *);
void func_800CE388(void *, void *, void *);
s8 func_800CE6E4(void *, s32);
void func_800D4AD0(void *);
extern s32 D_800F9B24[][4];
extern s8 D_800FADB8;
void func_800A63D8(void) {
    switch (D_800EB408->step) {
    case 0:
        func_800CE388(D_800EB408,D_800EB40C,D_800F9B24[D_800FADB8]);
        D_800EB408->step++;
    case 1:
        if(func_800CE6E4(D_800EB408,D_800F9B24[D_800FADB8][0])) D_800EB408->step++;
        break;
    case 2:
        if(D_800EB408->animFramesLeft<=0) {
            func_800D4AD0(D_800EB408); beginEntityActionA8D8C(D_800EB408);
        }
        break;
    }
}
