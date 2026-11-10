/* @header
 * func_8009E624
 * VRAM 0x8009E624 | ROM 0x91AC4 | size 0x798
 * asm: asm/nonmatchings/code_8009D7A0/func_8009E624.s
 */
#include "common.h"

extern s8 D_800FADB8;
extern u16 D_800FABE6;
extern u16 D_800FAF8A;
extern s8 D_800FAF78;
extern f32 D_800F9B0C;
extern s32 D_800EB3E0[];

void func_800E212C(void *);
void translateEntityXZ(void *, void *);
void func_800D427C(void *, s16, s32);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D4D44 */
s32 func_800D4D44(void *, s32, s32);
#endif
s32 func_800D3684(s32, s32);
s32 func_800D35B0(s32, s32);
f32 func_800D63F0(void *, void *, s32);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800D2B64, func_800D37C0 and func_800D6610 */
void func_800D37C0(s32, f32, f32 *);
s32 func_800D6610(void *, s16);
s32 func_800D2B64(void *, f32, u16, s32);
#endif
void func_800D25D0(void *, f32);
void func_800D4AD0(void *);
void func_800A7188(void *);
void func_800A6BE0(void *, s32);
s8 resolveEntityMoveHeading(void *, u16, s32 *);
s8 func_800B4C60(void *, void *, s32, s32);
s8 func_800B61EC(void *, void *, s32, s32);
s8 func_800B5730(void *, void *, u16, u16, s8, f32);
s8 func_800B5CA0(void *, void *, s32, f32);
s8 updateSpecialMoveRequest(void *);

void func_8009E624(void) {
    D_800EB408->flags |= 0x100000ULL;
    func_800D93DC(D_800EB408);

    switch (D_800EB408->step) {
    case 0:
        if (!resolveEntityMoveHeading(D_800EB408, D_800FABE6, &D_800EB3E0[D_800FADB8])) {
            if (D_800EB408->flags & 0x80) {
                if (D_800EB408->animId != 0x108D) {
                    if (D_800EB408->animId != 0x1081) {
                        func_800D427C(D_800EB408, 0x1081, 2);
                    }
                }
            }
            func_800A6BE0(D_800EB408, 1);
            break;
        }
        if (D_800EB408->moveMode & 0x4000) {
            func_800A6C48(D_800EB408, 4);
            D_800EB408->step = 5;
            break;
        }
        {
            s32 s0 = (D_800EB408->flags & 0x80) ? 2 : 3;
            func_800D427C(D_800EB408, func_800D4D44(D_800EB408, 9, 0), s0);
        }
        D_800EB408->turnPerTick = func_800D3684(D_800EB3E0[D_800FADB8], D_800EB408->heading) / D_800EB408->animFramesLeft;
        D_800EB408->step++;
        /* fall through */
    case 1:
        if (D_800EB408->animFramesLeft <= 0) {
            D_800EB408->heading = D_800EB3E0[D_800FADB8];
            if (D_800EB408->flags & 0x80) {
                func_800D427C(D_800EB408, func_800D4D44(D_800EB408, 0xA, 0), 0);
                translateEntityXZ(D_800EB408, D_800EB408->moveDelta);
                func_800D2B64(D_800EB408, 1.0f, 0, 2);
            } else {
                D_800EB408->flags |= 0x10000000ULL;
            }
            D_800EB408->step++;
            break;
        }
        if (D_800EB408->flags & 0x140) {
            D_800EB408->heading = func_800D35B0(D_800EB408->heading, D_800EB408->turnPerTick);
        }
        if (func_800B4C60(D_800EB408, D_800EB40C, D_800FABE6, 0)) {
            break;
        }
        if (func_800B61EC(D_800EB408, D_800EB40C, D_800FABE6, D_800EB3E0[D_800FADB8])) {
            D_800EB408->turnPerTick = D_800EB3E0[D_800FADB8];
            func_800A6C48(D_800EB408, 0x86);
        }
        break;
    case 2:
        if (updateSpecialMoveRequest(D_800EB408)) {
            D_800EB408->step++;
            break;
        }
        if (D_800EB408->flags & 0x80) {
            func_800D427C(D_800EB408, func_800D4D44(D_800EB408, 0xA, 0), 0);
        } else {
            func_800D427C(D_800EB408, func_800D4D44(D_800EB408, 0xA, 0), 1);
        }
        if (D_800EB408->moveMode & 8) {
            f32 d;
            D_800EB408->heading = func_800D6610(D_800EB408, D_800EB408->dirIndex);
            d = func_800D63F0(D_800EB408, 0, 2);
            func_800D37C0(D_800EB408->heading, d, (f32 *)(D_800EB408->moveDelta));
        }
        if (func_800B4C60(D_800EB408, D_800EB40C, D_800FABE6, 1)) {
            break;
        }
        if (func_800B61EC(D_800EB408, D_800EB40C, D_800FABE6, D_800EB408->heading)) {
            D_800EB408->turnPerTick = D_800EB408->heading;
            func_800A6C48(D_800EB408, 0x86);
            break;
        }
        if (func_800B5730(D_800EB408, D_800EB40C, D_800FABE6, D_800FAF8A, D_800FAF78,
                          D_800F9B0C)) {
            if (D_800EB408->state != 8) {
                func_800E212C(D_800EB408);
            }
        }
        if (D_800EB408->flags & 0x1000000) {
            D_800EB408->step++;
        }
        break;
    case 3:
        func_800D25D0(D_800EB408, 4.0f);
        func_800D2B64(D_800EB408, 1.0f, 0, 2);
        {
            s32 s0;
            if (D_800EB408->flags & 0x80) s0 = 0; else s0 = 1;
            func_800D427C(D_800EB408, func_800D4D44(D_800EB408, 0xB, 0), s0);
        }
        if (func_800B5CA0(D_800EB408, D_800EB40C, D_800FABE6, D_800F9B0C)) {
            break;
        }
        if (D_800EB408->animFramesLeft > 0) {
            break;
        }
        func_800D4AD0(D_800EB408);
        func_800A6C48(D_800EB408, 0x2B);
        break;
    case 4:
        func_800D427C(D_800EB408, 0xE79, 3);
        D_800EB408->step++;
        /* fall through */
    case 5:
        translateEntityXZ(D_800EB408, D_800EB408->moveDelta);
        func_800D25D0(D_800EB408, 4.0f);
        func_800D2B64(D_800EB408, 1.0f, 0, 0x22);
        if (D_800EB408->animFrame == 0xB && !(D_800FABE6 & 0x20)) {
            func_800D427C(D_800EB408, 0xE80, 1);
            D_800EB408->step++;
        }
        if (D_800EB408->animFramesLeft <= 0) {
            D_800EB408->step = 2;
        }
        break;
    case 6:
        func_800D25D0(D_800EB408, 4.0f);
        func_800D2B64(D_800EB408, 1.0f, 0, 0x22);
        func_800A7188(D_800EB408);
        break;
    }
}
