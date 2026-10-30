/* @header
 * func_800A3818
 * VRAM 0x800A3818 | ROM 0x96CB8 | size 0x158
 * asm: asm/nonmatchings/code_8009D7A0/func_800A3818.s
 */
#include "common.h"

extern void *D_800EB40C;
void func_800A7C40(void *, s8, s16);
void func_800A837C(void *);
s8 func_800A83DC(void *, void *);
void func_800B68A0(void *, void *, void *);
s32 func_800D2BEC(void *, void *, void *, f32, u16, s32);
void func_800D427C(void *, s16, s32);
void func_800D4AD0(void *);
s16 func_800D5438(void *, s32);
extern s8 D_800FADB8;

void func_800A3818(void) {
    switch (((Nw2F408 *)D_800EB408)->fC) {
    case 0:
        func_800A7C40(D_800EB408, D_800FADB8, (s16)(*(u16 *)((u8 *)D_800EB408 + 0x386) + 1));
        func_800D427C(D_800EB408, func_800D5438(D_800EB408, 0), 3);
        ((Nw2F408 *)D_800EB408)->fC++;
        break;
    case 1:
        func_800D2BEC(D_800EB408, D_800EB40C, 0, 2.0f, 0, 0xFFFFE);
        if (((Nw2F408 *)D_800EB408)->f4 <= 0) {
            func_800B68A0(D_800EB408, D_800EB408, D_800EB40C);
            func_800A837C(D_800EB408);
            if (func_800A83DC(D_800EB408, D_800EB40C) == 0) {
                *(s8 *)((u8 *)D_800EB408 + 0x362) = -1;
                func_800A6C48(D_800EB408, 0x2B);
                func_800D4AD0(D_800EB408);
                *(u64 *)((u8 *)D_800EB408 + 0x20) &= ~0x40000000ULL;
            }
        }
        break;
    }
}
