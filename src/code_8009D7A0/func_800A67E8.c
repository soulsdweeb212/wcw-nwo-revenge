/* @header
 * func_800A67E8
 * VRAM 0x800A67E8 | ROM 0x99C88 | size 0x2F0
 * asm: asm/nonmatchings/code_8009D7A0/func_800A67E8.s
 */
#include "common.h"

extern u16 D_800FAF8A;
extern s32 D_800E3C98;
extern f64 D_800E46E8;
extern f64 D_800E46F0;

void func_8000DB90(s8, s32);
void func_800A7F6C(void *, s32);
void func_800A837C(void *);
void func_800D427C(void *, s16, s32);
void translateEntityXZ(void *, void *);
s8 func_800B71F8(void *, s32, s32);
s8 func_800E1920(void *, s32);
f32 func_800D63F0(void *, void *, s16);
void func_800D37C0(s32, f32, void *);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D4D44 */
s16 func_800D4D44(void *, s32, s32);
#endif

void func_800A67E8(void) {
    D_800EB408->flags |= 0x1000000000ULL;
    switch (D_800EB408->step) {
    case 0:
        D_800EB408->stateTimer = 0;
        func_8000DB90(D_800EB408->id, 0);
        func_800A7F6C(D_800EB40C, 0x55);
        func_800A837C(D_800EB40C);
        D_800EB408->step++;
    case 1:
        func_800D427C(D_800EB408, 0xE6E, 1);
        translateEntityXZ(D_800EB408, D_800EB408->moveDelta);
        if (!(D_800EB408->stepFlags & 1) && (D_800FAF8A & 0xC030)) {
            if (func_800B71F8(D_800EB408, 0, 3) != 0) {
                D_800EB408->stepFlags |= 2;
            }
            D_800EB408->stepFlags |= 1;
        }
        D_800EB408->stateTimer += 1;
        if (D_800EB408->stateTimer >= 0x1E) {
            if ((D_800EB408->stepFlags & 2) && func_800E1920(D_800EB408, 2) == 0) {
                D_800EB408->stepFlags &= 0xFFFD;
            }
            /* dirIndex, written through a plain pointer: as a member store it is scheduled differently */
            *(s16 *)((u8 *)D_800EB408 + 0x3E) = 2;
            D_800EB408->x = 0;
            D_800EB408->heading = D_800E3C98;
            func_800D37C0(D_800EB408->heading, func_800D63F0(D_800EB408, 0, 2), D_800EB408->moveDelta);
            D_800EB408->step++;
        }
        break;
    case 2:
        func_800D427C(D_800EB408, func_800D4D44(D_800EB408, 0xA, 0), 1);
        translateEntityXZ(D_800EB408, D_800EB408->moveDelta);
        if ((f64)D_800EB408->z < D_800E46E8) {
            func_8000DB90(D_800EB408->id, 1);
        }
        if ((f64)D_800EB408->z < D_800E46F0) {
            if (D_800EB408->stepFlags & 2) {
                D_800EB408->moveMode = (D_800EB408->moveMode & 0xFFDB) | 3;
            }
            func_800A6C48(D_800EB408, 3);
            D_800EB408->step = 2;
            D_800EB408->flags &= 0xFFFFFFFFFEFFFFFFULL;
        }
        break;
    }
}
