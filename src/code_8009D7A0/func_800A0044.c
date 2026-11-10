/* @header
 * func_800A0044
 * VRAM 0x800A0044 | ROM 0x934E4 | size 0x150
 * asm: asm/nonmatchings/code_8009D7A0/func_800A0044.s
 */
#include "common.h"

/* func_800A0044: two-phase action state machine for the entity in D_800EB408.
 * Phase 0 copies the x/z position for the current side
 * (dirIndex) out of D_800E3C70/D_800E3C74, requests action 0xF02 and, if the
 * animation 0x155 can start, selects sub-action 0x4D and advances. Phase 1,
 * once the phase timer expires, plays animation 0xC, runs the paired action,
 * writes the quadrant heading (D_800E3CC0) and switches to action 0x2B. */
extern f32 D_800E3C70[];
extern f32 D_800E3C74[];
extern s32 D_800E3CB0[];
extern s32 D_800E3CC0[];

#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D2B64 */
void func_800D2B64(void *, f32, u16, s32);
#endif
void func_800D427C(void *, s32, s32);
s8 func_800A7240(void *, s32, s32, u64);
void func_800A7F6C(void *, s32);
void func_800A837C(void *);
void func_800A7D1C(void *, s32);
void func_800B68A0(void *, void *, void *);

void func_800A0044(void) {
    func_800D2B64(D_800EB408, 2.0f, 0, 2);

    switch (D_800EB408->step) {
    case 0:
        D_800EB408->x = D_800E3C70[D_800EB408->dirIndex * 2];
        D_800EB408->z = D_800E3C74[D_800EB408->dirIndex * 2];
        func_800D427C(D_800EB408, 0xF02, 0);
        if (func_800A7240(D_800EB408, D_800E3CB0[D_800EB408->dirIndex], 0x155, 0) != 0) {
            func_800A7F6C(D_800EB408, 0x4D);
            func_800A837C(D_800EB408);
            D_800EB408->step++;
        }
        break;
    case 1:
        if (D_800EB408->animFramesLeft <= 0) {
            func_800A7D1C(D_800EB408, 0xC);
            func_800B68A0(D_800EB408, D_800EB408, D_800EB408);
            D_800EB408->heading = D_800E3CC0[D_800EB408->dirIndex];
            func_800A6C48(D_800EB408, 0x2B);
        }
        break;
    }
}
