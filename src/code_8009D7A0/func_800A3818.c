/* @header
 * func_800A3818
 * VRAM 0x800A3818 | ROM 0x96CB8 | size 0x158
 * asm: asm/nonmatchings/code_8009D7A0/func_800A3818.s
 */
#include "common.h"

void func_800A7C40(void *, s8, s16);
void func_800A837C(void *);
s8 func_800A83DC(void *, void *);
void func_800B68A0(void *, void *, void *);
s32 func_800D2BEC(void *, void *, void *, f32, u16, s32);
void func_800D427C(void *, s16, s32);
void func_800D4AD0(void *);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D5438 */
s16 func_800D5438(void *, s32);
#endif
extern s8 D_800FADB8;

void func_800A3818(void) {
    switch (D_800EB408->step) {
    case 0:
        func_800A7C40(D_800EB408, D_800FADB8, (s16)(D_800EB408->moveId + 1));
        func_800D427C(D_800EB408, func_800D5438(D_800EB408, 0), 3);
        D_800EB408->step++;
        break;
    case 1:
        func_800D2BEC(D_800EB408, D_800EB40C, 0, 2.0f, 0, 0xFFFFE);
        if (D_800EB408->animFramesLeft <= 0) {
            func_800B68A0(D_800EB408, D_800EB408, D_800EB40C);
            func_800A837C(D_800EB408);
            if (func_800A83DC(D_800EB408, D_800EB40C) == 0) {
                D_800EB408->attached[0] = -1;
                func_800A6C48(D_800EB408, 0x2B);
                func_800D4AD0(D_800EB408);
                D_800EB408->flags &= ~0x40000000ULL;
            }
        }
        break;
    }
}
