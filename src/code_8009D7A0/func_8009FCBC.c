/* @header
 * func_8009FCBC
 * VRAM 0x8009FCBC | ROM 0x9315C | size 0x388
 * asm: asm/nonmatchings/code_8009D7A0/func_8009FCBC.s
 */
#include "common.h"

extern f32 D_800E3C70[];
extern f32 D_800E3C74[];
extern s32 D_800E3CC0[];
extern u8 D_800FADCF;
extern u16 D_800FAF8A;
extern s8 D_800FAF78;
extern s8 func_800A7240(void *, s32, s32, u64);
extern void func_800A7D1C(void *, s32);
extern void beginEntityActionA8D8C(void *);
extern void func_800B68A0(void *, void *, void *);
extern s16 func_800B6DEC(void *, s32, s32);
extern void func_800D25D0(void *, f32);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D2B64 */
extern void func_800D2B64(void *, f32, s32, s32);
#endif
extern void func_800D427C(void *, s32, s32);
extern void func_800D4AD0(void *);
extern s16 func_800D7690(void *, s32, s32);
extern s8 func_800D7894(void *, u16);

/* Six-step action state machine on the step of the wrestler being updated
 * (D_800EB408).  Steps 0/2 aim it at side dirIndex (position tables
 * D_800E3C70/D_800E3C74 plus heading D_800E3CC0) and start the action via
 * func_800A7240; step 1 marks frameStatus bit0 and hands the entity to
 * func_800B68A0; step 3 waits for the proximity/range checks
 * (func_800D7894, D_800FADCF bit0x40, flag 0x4000, D_800FAF78); steps 4/5
 * run the recovery via func_800D2B64/func_800D4AD0 and end with
 * func_800A6C48(0x2B) or beginEntityActionA8D8C.  animFramesLeft is the timer. */
void func_8009FCBC(void)
{
    switch (D_800EB408->step) {
    case 0:
        D_800EB408->x = D_800E3C70[D_800EB408->dirIndex * 2];
        D_800EB408->z = D_800E3C74[D_800EB408->dirIndex * 2];
        func_800D427C(D_800EB408, 0xEFB, 2);
        if (!func_800A7240(D_800EB408, D_800E3CC0[D_800EB408->dirIndex], 0x155, 0)) {
            return;
        }
        if (D_800EB408->moveMode & 0x40) {
            func_800D427C(D_800EB408, 0xF00, 2);
            D_800EB408->step = 5;
            return;
        }
        func_800D427C(D_800EB408, 0xEFC, 2);
        D_800EB408->step++;
        return;
    case 1:
        D_800EB408->frameStatus |= 1;
        if (D_800EB408->animFramesLeft > 0) {
            return;
        }
        func_800A7D1C(D_800EB408, 0xD);
        func_800B68A0(D_800EB408, D_800EB40C, D_800EB408);
        D_800EB408->flags |= 0x10000000ULL;
        D_800EB408->step++;
        return;
    case 2:
        D_800EB408->frameStatus |= 1;
        D_800EB408->x = D_800E3C70[D_800EB408->dirIndex * 2];
        D_800EB408->z = D_800E3C74[D_800EB408->dirIndex * 2];
        D_800EB408->heading = D_800E3CC0[D_800EB408->dirIndex];
        func_800D427C(D_800EB408, 0xEFD, 0);
        D_800EB408->escapeTimer = func_800B6DEC(D_800EB408, 0, 2);
        func_800D7690(D_800EB408, 0, 0);
        D_800EB408->step++;
        return;
    case 3:
        D_800EB408->frameStatus |= 1;
        if ((D_800FADCF & 0x40) && (D_800EB408->flags & 0x4000ULL)) {
            func_800D427C(D_800EB408, 0xEFF, 0);
            D_800EB408->step++;
            return;
        }
        if (!func_800D7894(D_800EB408, D_800FAF8A)) {
            return;
        }
        if (D_800FAF78) {
            D_800EB408->escapeTimer = 0;
            return;
        }
        func_800D427C(D_800EB408, 0xEFF, 0);
        D_800EB408->step++;
        return;
    case 4:
        D_800EB408->frameStatus |= 1;
        func_800D2B64(D_800EB408, 2.0f, 0, 2);
        if (D_800EB408->animFramesLeft > 0) {
            return;
        }
        func_800D4AD0(D_800EB408);
        func_800A6C48(D_800EB408, 0x2B);
        return;
    case 5:
        func_800D25D0(D_800FAF5C, 4.0f);
        if (D_800EB408->animFramesLeft > 0) {
            return;
        }
        func_800D4AD0(D_800EB408);
        beginEntityActionA8D8C(D_800EB408);
        return;
    default:
        return;
    }
}
