/* @header
 * func_800A67E8
 * VRAM 0x800A67E8 | ROM 0x99C88 | size 0x2F0
 * asm: asm/nonmatchings/code_8009D7A0/func_800A67E8.s
 */
#include "common.h"

typedef struct {
    s8 f0;
    u8 pad1[3];
    s16 f4, f6;
    s32 f8;
    s16 fC;
    u16 fE;
    u8 pad10[6];
    u16 f16;
    u8 pad18[6];
    u64 flags;
    u16 f28;
    u8 pad2A[0x14];
    s16 f3E;
    u8 pad40[0xC];
    f32 f4C;
    f32 f50;
    f32 f54;
    unsigned f58;
    u8 pad5C[0x2E0];
    f32 vec[3];
} Nw2F408a;

extern void *D_800EB408;
extern void *D_800EB40C;
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
s16 func_800D4D44(void *, s32, s32);
void func_800A6C48(void *, s32);

#define P ((Nw2F408a *)D_800EB408)
#define RAW(T, off) (*(T *)((u8 *)D_800EB408 + (off)))

void func_800A67E8(void) {
    P->flags |= 0x1000000000ULL;
    switch (P->fC) {
    case 0:
        P->f16 = 0;
        func_8000DB90(P->f0, 0);
        func_800A7F6C(D_800EB40C, 0x55);
        func_800A837C(D_800EB40C);
        P->fC++;
    case 1:
        func_800D427C(D_800EB408, 0xE6E, 1);
        translateEntityXZ(D_800EB408, P->vec);
        if (!(P->fE & 1) && (D_800FAF8A & 0xC030)) {
            if (func_800B71F8(D_800EB408, 0, 3) != 0) {
                P->fE |= 2;
            }
            P->fE |= 1;
        }
        P->f16 += 1;
        if ((s16)P->f16 >= 0x1E) {
            if ((P->fE & 2) && func_800E1920(D_800EB408, 2) == 0) {
                P->fE &= 0xFFFD;
            }
            RAW(s16, 0x3E) = 2;
            P->f4C = 0;
            RAW(s32, 0x58) = D_800E3C98;
            func_800D37C0(P->f58, func_800D63F0(D_800EB408, 0, 2), P->vec);
            P->fC++;
        }
        break;
    case 2:
        func_800D427C(D_800EB408, func_800D4D44(D_800EB408, 0xA, 0), 1);
        translateEntityXZ(D_800EB408, P->vec);
        if ((f64)P->f54 < D_800E46E8) {
            func_8000DB90(P->f0, 1);
        }
        if ((f64)P->f54 < D_800E46F0) {
            if (P->fE & 2) {
                P->f28 = (P->f28 & 0xFFDB) | 3;
            }
            func_800A6C48(D_800EB408, 3);
            P->fC = 2;
            P->flags &= 0xFFFFFFFFFEFFFFFFULL;
        }
        break;
    }
}
