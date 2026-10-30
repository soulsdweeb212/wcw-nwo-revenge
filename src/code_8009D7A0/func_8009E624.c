/* @header
 * func_8009E624
 * VRAM 0x8009E624 | ROM 0x91AC4 | size 0x798
 * asm: asm/nonmatchings/code_8009D7A0/func_8009E624.s
 */
#include "common.h"

typedef struct {
    s32 f0;
    s16 f4;
    s16 f6;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 fE;
    u8 pad10[6];
    s16 f16;
    u8 pad18[8];
    u64 flags;
    u16 f28;
    u8 pad2A[0x12];
    s16 f3C;
    s16 f3E;
    u8 pad40[0x18];
    s32 f58;
    u8 pad5C[0x2E0];
    f32 vec[3];
    s32 f348;
} Nw2E624;

#define O ((Nw2E624 *)D_800EB408)

extern void *D_800EB40C;
extern s8 D_800FADB8;
extern u16 D_800FABE6;
extern u16 D_800FAF8A;
extern s8 D_800FAF78;
extern f32 D_800F9B0C;
extern s32 D_800EB3E0[];

void func_800E212C(void *);
void translateEntityXZ(void *, void *);
void func_800D427C(void *, s16, s32);
s32 func_800D4D44(void *, s32, s32);
s32 func_800D3684(s32, s32);
s32 func_800D35B0(s32, s32);
f32 func_800D63F0(void *, void *, s32);
void func_800D37C0(s32, f32, f32 *);
s32 func_800D6610(void *, s16);
s32 func_800D2B64(void *, f32, u16, s32);
void func_800D25D0(void *, f32);
void func_800D4AD0(void *);
void func_800A7188(void *);
void func_800A6BE0(void *, s32);
void func_800A6C48(void *, s32);
s8 resolveEntityMoveHeading(void *, u16, s32 *);
s8 func_800B4C60(void *, void *, s32, s32);
s8 func_800B61EC(void *, void *, s32, s32);
s8 func_800B5730(void *, void *, u16, u16, s8, f32);
s8 func_800B5CA0(void *, void *, s32, f32);
s8 updateSpecialMoveRequest(void *);
void func_800D93DC(void *);

void func_8009E624(void) {
    O->flags |= 0x100000ULL;
    func_800D93DC(O);

    switch (O->fC) {
    case 0:
        if (!resolveEntityMoveHeading(O, D_800FABE6, &D_800EB3E0[D_800FADB8])) {
            if (O->flags & 0x80) {
                if (O->f8 != 0x108D) {
                    if (O->f8 != 0x1081) {
                        func_800D427C(O, 0x1081, 2);
                    }
                }
            }
            func_800A6BE0(O, 1);
            break;
        }
        if (O->f28 & 0x4000) {
            func_800A6C48(O, 4);
            O->fC = 5;
            break;
        }
        {
            s32 s0 = (O->flags & 0x80) ? 2 : 3;
            func_800D427C(O, func_800D4D44(O, 9, 0), s0);
        }
        O->f348 = func_800D3684(D_800EB3E0[D_800FADB8], O->f58) / O->f4;
        O->fC++;
        /* fall through */
    case 1:
        if (O->f4 <= 0) {
            O->f58 = D_800EB3E0[D_800FADB8];
            if (O->flags & 0x80) {
                func_800D427C(O, func_800D4D44(O, 0xA, 0), 0);
                translateEntityXZ(O, (u8 *)O + 0x33C);
                func_800D2B64(O, 1.0f, 0, 2);
            } else {
                O->flags |= 0x10000000ULL;
            }
            O->fC++;
            break;
        }
        if (O->flags & 0x140) {
            O->f58 = func_800D35B0(O->f58, O->f348);
        }
        if (func_800B4C60(O, D_800EB40C, D_800FABE6, 0)) {
            break;
        }
        if (func_800B61EC(O, D_800EB40C, D_800FABE6, D_800EB3E0[D_800FADB8])) {
            O->f348 = D_800EB3E0[D_800FADB8];
            func_800A6C48(O, 0x86);
        }
        break;
    case 2:
        if (updateSpecialMoveRequest(O)) {
            O->fC++;
            break;
        }
        if (O->flags & 0x80) {
            func_800D427C(O, func_800D4D44(O, 0xA, 0), 0);
        } else {
            func_800D427C(O, func_800D4D44(O, 0xA, 0), 1);
        }
        if (O->f28 & 8) {
            f32 d;
            O->f58 = func_800D6610(O, O->f3E);
            d = func_800D63F0(O, 0, 2);
            func_800D37C0(O->f58, d, (f32 *)((u8 *)O + 0x33C));
        }
        if (func_800B4C60(O, D_800EB40C, D_800FABE6, 1)) {
            break;
        }
        if (func_800B61EC(O, D_800EB40C, D_800FABE6, O->f58)) {
            O->f348 = O->f58;
            func_800A6C48(O, 0x86);
            break;
        }
        if (func_800B5730(O, D_800EB40C, D_800FABE6, D_800FAF8A, D_800FAF78,
                          D_800F9B0C)) {
            if (O->fA != 8) {
                func_800E212C(O);
            }
        }
        if (O->flags & 0x1000000) {
            O->fC++;
        }
        break;
    case 3:
        func_800D25D0(O, 4.0f);
        func_800D2B64(O, 1.0f, 0, 2);
        {
            s32 s0;
            if (O->flags & 0x80) s0 = 0; else s0 = 1;
            func_800D427C(O, func_800D4D44(O, 0xB, 0), s0);
        }
        if (func_800B5CA0(O, D_800EB40C, D_800FABE6, D_800F9B0C)) {
            break;
        }
        if (O->f4 > 0) {
            break;
        }
        func_800D4AD0(O);
        func_800A6C48(O, 0x2B);
        break;
    case 4:
        func_800D427C(O, 0xE79, 3);
        O->fC++;
        /* fall through */
    case 5:
        translateEntityXZ(O, (u8 *)O + 0x33C);
        func_800D25D0(O, 4.0f);
        func_800D2B64(O, 1.0f, 0, 0x22);
        if (O->f6 == 0xB && !(D_800FABE6 & 0x20)) {
            func_800D427C(O, 0xE80, 1);
            O->fC++;
        }
        if (O->f4 <= 0) {
            O->fC = 2;
        }
        break;
    case 6:
        func_800D25D0(O, 4.0f);
        func_800D2B64(O, 1.0f, 0, 0x22);
        func_800A7188(O);
        break;
    }
}
