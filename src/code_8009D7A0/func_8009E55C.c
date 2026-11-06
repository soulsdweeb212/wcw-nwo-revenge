/* @header
 * func_8009E55C
 * VRAM 0x8009E55C | ROM 0x919FC | size 0xC8
 * asm: asm/nonmatchings/code_8009D7A0/func_8009E55C.s
 */
#include "common.h"

extern void func_800D427C(void *, s32, s32);
extern void func_800D4AD0(void *);

void func_8009E55C(void) {
    s16 step = D_800EB408->step;
    s32 id;

    switch (step) {
    case 0:
        if (D_800EB408->flags & 0x8000000000ULL)
            id = 0x109B;
        else
            id = 0x109C;
        func_800D427C(D_800EB408, id, 0);
        D_800EB408->step++;
    case 1:
        if (D_800EB408->animFramesLeft <= 0) {
            func_800DECAC(D_800EB408, 0, 0, 0);
            func_800D4AD0(D_800EB408);
            func_800A6C48(D_800EB408, 0x2B);
        }
        break;
    }
}
