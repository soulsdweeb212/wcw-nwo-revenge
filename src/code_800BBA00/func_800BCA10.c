/* @header
 * func_800BCA10
 * VRAM 0x800BCA10 | ROM 0xAFEB0 | size 0xA4C
 * asm: asm/nonmatchings/code_800BBA00/func_800BCA10.s
 */
#include "common.h"

typedef struct {
    u8 pad0[0x38];
    u64 f38;
} SubCA10;

typedef struct {
    u8 pad0[4];
    s16 f4;
    u8 pad6[6];
    s16 fC;
    u8 padE[8];
    s16 f16;
    u8 pad18[8];
    u64 flags;
    u16 f28;
    u8 pad2A[2];
    u32 f2C;
    u8 pad30[0xE];
    s16 f3E;
    u8 pad40[0xC];
    u8 f4C[0xC];
    s32 f58;
    u8 pad5C[0x2E0];
    u8 f33C[0xC];
    s32 f348;
    u8 pad34C[0x14];
    u16 f360;
    s8 f362;
    u8 pad363;
    SubCA10 *f364;
    u8 pad368[4];
    u8 f36C;
} ECA10;

extern ECA10 *D_800FAF5C;
extern ECA10 *D_800F9B00;
extern s8 D_800FADB8;
extern f32 D_800EB480[];
extern s32 D_800E3D00[];
extern u16 D_800FAF8E[];

f32 func_800D3890(void *, void *, s32);
void func_800D427C(void *, s32, s32);
s32 func_800D35B0(s32, s32);
s32 func_800D6610(void *, s32);
s16 func_800D7A68(u16);
s8 func_800BD980(void *, void *, s16);
void func_800A7F6C(void *, s32);
void func_800BE450(void *, void *);
void func_800A837C(void *);
void func_800A7D1C(void *, s32);
void func_800B68A0(void *, void *, void *);
void func_800D3E40(void *, f32 *, s32, void *);
void func_800D2BEC(void *, void *, s32, f32, s32, s32);
void translateEntityXZ(void *, void *);
void func_800D4AD0(void *);

#define O D_800FAF5C
#define P D_800F9B00

#define FINISH() \
    func_800D4AD0(O); \
    func_800A6C48(O, 0x2B); \
    O->flags &= ~0x40000000ULL; \
    O->f362 = -1;

void func_800BCA10(void)
{
    s32 a;
    s16 dir;
    s32 best;
    s16 dirA;
    s16 dirB;
    s32 t;
    s32 r;
    s32 mask;
    s16 d;
    f32 v[3];

    switch (O->fC) {
    case 0:
        O->flags &= ~0x2000000ULL;
        if (O->f364->f38 & 0x400) {
            O->f2C |= 0x800000;
        }
        if (P->f364->f38 & 0x400) {
            O->f2C |= 0x1000000;
        }
        if (O->f2C & 1) {
            if (!(P->flags & 0x80000)) {
                O->f2C &= ~0x800000;
                O->f2C &= ~0x1000000;
            }
        }
        P->f28 = 0x22;
        if (O->f2C & 2) {
            P->f28 = 0x62;
        }
        D_800EB480[D_800FADB8] = func_800D3890(O->f4C, P->f4C, 0);
        if (O->f2C & 0x80) {
            a = 0xEE9;
        } else {
            a = 0xED9;
        }
        func_800D427C(O, a, 2);
        best = 0x800;
        if (O->f2C & 0x80) {
            dir = (((s32)(P->f3E + 2) % 4U) << 1) | 1;
        } else {
            for (dir = 0; dir < 8; dir += 2) {
                t = func_800D3550(func_800D3684(func_800D35B0(O->f58, 0x800), D_800E3D00[dir]));
                if (t < best) {
                    best = t;
                    dirA = dir;
                }
            }
            best = 0x800;
            for (dir = 1; dir < 8; dir += 2) {
                t = func_800D3550(func_800D3684(func_800D35B0(O->f58, 0x800), func_800D6610(O, dir / 2)));
                if (t < best) {
                    best = t;
                    dirB = dir;
                }
            }
            dir = func_800D7A68(D_800FAF8E[D_800FADB8]);
            if (dir != 0) {
                dir--;
            } else {
                dir = dirA;
            }
        }
        if (func_800D3550(func_800D3684(D_800E3D00[dir], O->f58)) < 0x300) {
            if (dir & 1) {
                dir = dirB;
            } else {
                dir = dirA;
            }
        }
        if (func_800BD980(O, P, dir)) {
            break;
        }
        func_800A7F6C(O, 0x4B);
        if (O->f2C & 0x1000000) {
            func_800D427C(O, (O->f2C & 0x80) ? 0xEEB : 0xEE1, 2);
            O->fC = 6;
            break;
        }
        if ((dir & 1) && (O->flags & 0x40)) {
            P->f28 = (P->f28 & ~2) | 8;
        } else {
            a = D_800E3D00[dir];
            O->f348 = func_800D3684(a, func_800D35B0(O->f58, 0x800)) / O->f36C;
        }
        P->f3E = dir / 2;
        O->fC++;
        break;
    case 1:
        if (!(O->f2C & 0x800000)) {
            if (P->f28 & 8) {
                t = func_800D3684(func_800D6610(P, P->f3E), P->f58);
                d = O->f4;
                if (O->f4 == 0) {
                    d = 1;
                }
                O->f348 = t / d;
            }
            O->f58 = func_800D35B0(O->f58, O->f348);
            P->f58 = func_800D35B0(P->f58, O->f348);
            v[0] = 0.0f;
            v[2] = D_800EB480[D_800FADB8];
            func_800D3E40(P->f4C, v, P->f58, O->f4C);
        }
        if (O->f4 <= 0) {
            if (O->f2C & 0x80) {
                func_800BE450(O, P);
            }
            if (P->flags & 0x2000000) {
                func_800D427C(O, 0xEDE, 0);
                break;
            }
            func_800D427C(O, (O->f2C & 0x800000) ? 0xEDF : 0xEDB, 0);
            func_800A837C(O);
            O->fC++;
        }
        if (!(O->f2C & 0x80)) {
            func_800D2BAC(O, P, 1.0f, 2);
        }
        break;
    case 2:
        if (!(O->f2C & 0x80)) {
            func_800D2BAC(O, P, 1.0f, 2);
        }
        if (O->f4 <= 0) {
            FINISH();
        }
        break;
    case 3:
        if (O->f4 <= 0) {
            func_800A7D1C(O, 4);
            func_800B68A0(O, O, P);
            O->f58 = func_800D35B0(O->f58, 0x800);
            P->f58 = func_800D35B0(P->f58, 0x800);
            func_800BE450(O, P);
            if (P->f2C & 0x800000) {
                a = 0xEDF;
                func_800A7D1C(O, 5);
            } else {
                a = 0xEDB;
            }
            func_800D427C(O, a, 0);
            O->fC--;
        }
        if (!(O->f2C & 0x80)) {
            func_800D2BAC(O, P, 1.0f, 2);
        }
        break;
    case 4:
        D_800EB480[D_800FADB8] = func_800D3890(O->f4C, P->f4C, 0);
        O->fC++;
    case 5:
        if (--O->f16 >= 0) {
            translateEntityXZ(O, O->f33C);
            O->f58 = func_800D35B0(O->f58, O->f348);
            P->f58 = func_800D35B0(O->f58, 0x800);
            v[0] = 0.0f;
            v[2] = D_800EB480[D_800FADB8];
            func_800D3E40(O->f4C, v, O->f58, P->f4C);
        }
        if (!(P->f360 & 4)) {
            if (O->f3E & 1) {
                mask = 0xC00;
            } else {
                mask = 0x300;
            }
            func_800D2BEC(O, P, 0, 2.0f, mask, 0xFFFFE);
        }
        if (O->f4 <= 0) {
            FINISH();
        }
        break;
    case 6:
        func_800D2BEC(O, P, 0, 1.0f, 0, 0xFFFFE);
        if (O->f4 <= 0) {
            func_800A7D1C(O, 6);
            func_800B68A0(O, O, O);
            FINISH();
        }
        break;
    }
}
