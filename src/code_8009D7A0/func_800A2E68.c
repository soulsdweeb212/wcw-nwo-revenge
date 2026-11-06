/* @header
 * func_800A2E68
 * VRAM 0x800A2E68 | ROM 0x96308 | size 0x294
 * asm: asm/nonmatchings/code_8009D7A0/func_800A2E68.s
 */
#include "common.h"

extern s32 D_800F9B14;
extern s32 D_800F9B0C;
extern u16 D_800FABE6;
s32 func_800D4D44(void *, s32, s32);
void func_800D427C(void *, s32, s32);
void func_800A7240(void *, s32, s32, u64);
s8 func_800A93C0(void);
void func_800A7D1C(void *, s32);
void func_800B68A0(void *, void *, void *);
void func_800D4AD0(void *);
void func_800D25D0(void *, f32);
s32 func_800D2B64(void *, f32, u16, s32);

void func_800A2E68(void) {
    func_800D25D0(D_800EB408, 4.0f);
    func_800D2B64(D_800EB408, 1.0f, 0, 2);
    switch (D_800EB408->step) {
    case 0:
        func_800D427C(D_800EB408, (s16)func_800D4D44(D_800EB408, 2, 0), 3);
        D_800EB408->stateTimer = 0;
        D_800EB408->step = D_800EB408->step + 1;
        return;
    case 1:
        *(u64 *)(u8 *)&D_800EB408->flags |= 0x100000000000ULL;
        func_800A7240(D_800EB408, D_800F9B14, 0x155, 0x100000000ULL);
        D_800EB408->stateTimer = D_800EB408->stateTimer + 1;
        if ((s16)D_800EB408->stateTimer < 5) return;
        if ((s16)D_800EB408->stateTimer >= 100) D_800EB408->stateTimer = 100;
        if (D_800FABE6 & 0x10) {
            if (func_800A93C0() == 0) return;
        }
        func_800D427C(D_800EB408, (s16)func_800D4D44(D_800EB408, 1, D_800F9B0C), 3);
        D_800EB408->stateTimer = 100;
        D_800EB408->step = D_800EB408->step + 1;
        return;
    case 2:
        *(u64 *)(u8 *)&D_800EB408->flags |= 0x100000000000ULL;
        func_800A7240(D_800EB408, D_800F9B14, 0x155, 0x100000000ULL);
        D_800EB408->stateTimer = D_800EB408->stateTimer + 1;
        if ((s16)D_800EB408->stateTimer < 0x6A) return;
        func_800A6C48(D_800EB408, 1);
        return;
    case 3:
        func_800D427C(D_800EB408, 0xEC0, 3);
        D_800EB408->step = D_800EB408->step + 1;
        return;
    case 4:
        if (D_800EB408->animFramesLeft > 0) return;
        func_800A7D1C(D_800EB408, 2);
        func_800B68A0(D_800EB408, D_800EB408, D_800EB408);
        func_800D4AD0(D_800EB408);
        func_800A6C48(D_800EB408, 0x2B);
        return;
    }
}
