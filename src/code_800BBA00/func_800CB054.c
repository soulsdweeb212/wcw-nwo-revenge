/* @header
 * func_800CB054
 * VRAM 0x800CB054 | ROM 0xBE4F4 | size 0x824
 * asm: asm/nonmatchings/code_800BBA00/func_800CB054.s
 */
#include "common.h"

typedef struct {
    s32 f0;
    s16 f4;
    s16 f6;
    u16 f8;
    s16 fA;
    s16 fC;
    s16 fE;
    u8 pad10[0x10];
    u64 flags;
    u8 pad28[0xE];
    u8 f36;
    u8 pad37[0x15];
    f32 f4C;
    f32 f50;
    f32 f54;
    s32 f58;
    u8 pad5C[0x304];
    u16 f360;
    s8 f362;
} Nw2F5C;

#define A ((Nw2F5C *)D_800FAF5C)
#define B ((Nw2F5C *)D_800F9B00)

extern void *D_800FAF5C;
extern void *D_800F9B00;
extern s8 D_800FADB8;
extern u32 D_800F9B14;
extern u16 D_800FABE6;
extern s32 D_800E3CFC[];
extern u8 D_800FACF8[];
extern u8 D_800EB578[];
extern u8 D_800EB57C[];
extern u8 D_800EB584[];

void func_800A6C48(void *, s32);
s8 func_800A7240(void *, s32, s32, u64);
void func_800A837C(void *);
s8 func_800A83DC(void *, void *);
void func_800B68A0(void *, void *, void *);
s8 func_800CBC4C(void *, void *);
s32 func_800D2BAC(void *, void *, f32, s32);
s32 func_800D2BEC(void *, void *, void *, f32, u16, s32);
s32 func_800D2C68(void *, void *, f32, void *, s32);
s32 func_800D3550(s32);
s32 func_800D35B0(s32, s32);
s32 func_800D3684(s32, s32);
void func_800D3890(void *, void *, void *);
s32 func_800D3E40(void *, void *, s32, void *);
void func_800D427C(void *, s16, s32);
void func_800D43B4(void *, s16, s32);
void func_800D4AD0(void *);
s16 func_800D5438(void *, s32);
void func_800D7128(void *, void *, void *, void *);
s8 func_800D732C(void *, void *);
s32 func_800D7A68(s32);

void func_800CB054(void) {
    f32 arr[6];
#define vec arr
#define out (arr+4)
    s32 anim;
    s32 r;
    s32 d;
    s16 sum;
    u8 *rec;
    Nw2F5C *o;

    switch (A->fC) {
    case 0:
        anim = (A->flags & 0x200000000000000ULL) ? 0xF3A : 0xFB9;
        func_800D427C(A, anim, 3);
        A->fC++;
        break;
    case 1:
        if (B->flags & 0x200000ULL) {
            A->f36 |= 2;
        }
        d = func_800D3550(func_800D3684(B->f58, D_800F9B14));
        if (B->flags & 0x200000ULL) {
            if (d < 0x401) {
                goto l198;
            }
        } else {
            if (d >= 0x400) {
                goto l198;
            }
        }
        A->f36 |= 1;
    l198:
        vec[0] = 0.0f;
        if (A->f36 & 1) {
            vec[2] = -130.0f;
        } else {
            vec[2] = 150.0f;
        }
        if (B->flags & 0x200000ULL) {
            vec[2] = -vec[2];
        }
        func_800D3E40((u8 *)B + 0x4C, vec, B->f58, out);
        rec = D_800FACF8 + (s8)D_800FADB8 * 0x30;
        func_800D7128(B, A, out, rec);
        A->fC++;
        /* fall through */
    case 2:
        func_800D2C68(A, B, 4.0f, D_800FACF8 + (s8)D_800FADB8 * 0x30,
                      0xFFFFE);
        sum = func_800D732C(A, D_800FACF8 + (s8)D_800FADB8 * 0x30);
        { s32 t = D_800F9B14; sum += func_800A7240(A, t, 0x155, 0x100000000ULL); }
        if (sum != 2) {
            break;
        }
        if (A->f4 > 0) {
            break;
        }
        A->flags |= 0x10000000ULL;
        if (!(A->flags & 9ULL)) {
            if (!(D_800FABE6 & 0x8000)) {
                goto inc;
            }
            if (!(D_800FABE6 & 0xF00)) {
                goto inc;
            }
        }
        func_800D3890((u8 *)B + 0x4C, (u8 *)A + 0x4C,
                      D_800EB578 + (s8)D_800FADB8 * 16);
        A->fC = 5;
        break;
    case 3:
        func_800D2BEC(A, B, 0, 4.0f, 0, 0xFFFFE);
        if (func_800CBC4C(A, B)) {
            A->f360 |= 2;
            r = func_800D5438(B, 1);
            func_800D427C(A, r, 2);
            break;
        }
        A->f360 |= 1;
        r = func_800D5438(A, 0);
        func_800D427C(A, r, 2);
        func_800A837C(A);
        A->fC++;
        break;
    case 4:
        func_800D2BEC(A, B, 0, 4.0f, 0, 0xFFFFE);
        if (A->f4 == 1) {
            func_800B68A0(A, A, B);
        }
        if (A->f4 > 0) {
            break;
        }
        if (func_800A83DC(A, B)) {
            break;
        }
        o = A;
        o->f362 = -1;
        o->flags &= ~0x40000000ULL;
        func_800D4AD0(A);
        func_800A6C48(A, 0x2B);
        break;
    case 5:
        A->f360 |= 4;
        anim = 0xFC8;
        if (!(A->f36 & 1)) {
            anim = 0xFD0;
        }
        if (A->f36 & 2) {
            anim += 0x10;
        }
        func_800D427C(A, anim, 0);
        func_800D2BAC(A, B, 4.0f, 0xFFFFE);
        if (A->f4 > 0) {
            break;
        }
        func_800D427C(A, (s16)(A->f8 + 2), 0);
    inc:
        A->fC++;
        break;
    case 6:
        if (B->f360 & 0x18) {
            goto l758;
        }
        if (D_800FABE6 & 0x8000) {
            r = (s16)func_800D7A68(D_800FABE6);
            if (r != 0) {
                d = func_800D3684(A->f58, D_800E3CFC[r]);
                if (func_800D3550(d) >= 0xE3 &&
                    func_800D3550(d) < 0x71D) {
                    if (d >= 0) {
                        d = 0xB;
                    } else {
                        d = -0xB;
                    }
                    A->f58 = func_800D35B0(A->f58, d);
                    B->f58 = func_800D35B0(B->f58, d);
                    *(s32 *)(D_800EB584 + (s8)D_800FADB8 * 16) =
                        func_800D35B0(
                            *(s32 *)(D_800EB584 + (s8)D_800FADB8 * 16), d);
                }
            }
            vec[0] = 0.0f;
            vec[2] = *(f32 *)(D_800EB57C + (s8)D_800FADB8 * 16);
            func_800D3E40((u8 *)B + 0x4C, vec,
                          *(s32 *)(D_800EB584 + (s8)D_800FADB8 * 16),
                          (u8 *)A + 0x4C);
        } else {
            B->f360 |= 8;
        }
    l758:
        if (A->f4 <= 0) {
            if (B->f360 & 0x18) {
                A->f360 |= 0x20;
                func_800D427C(A, (s16)(A->f8 + 4), 1);
                A->fC++;
            } else {
                func_800D43B4(A, (s16)A->f8, 1);
            }
        }
        func_800D2BAC(A, B, 1.0f, 0xFFFFE);
        break;
    case 7:
        func_800D2BAC(A, B, 1.0f, 0xFFFFE);
        o = A;
        if (o->f4 <= 0) {
            o->f362 = -1;
            o->flags &= ~0x40000000ULL;
            func_800D4AD0(A);
            func_800A6C48(A, 0x2B);
        }
        break;
    }
}
