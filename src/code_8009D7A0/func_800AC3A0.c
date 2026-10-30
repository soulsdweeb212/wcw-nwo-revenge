/* @header
 * func_800AC3A0
 * VRAM 0x800AC3A0 | ROM 0x9F840 | size 0x8A8
 * asm: asm/nonmatchings/code_8009D7A0/func_800AC3A0.s
 */
#include "common.h"

typedef struct {
    s8 f0;
    u8 pad1[3];
    s16 f4;
    s16 f6;
    u16 f8;
    s16 fA;
    s16 fC;
    s16 fE;
    u8 pad10[6];
    s16 f16;
    u8 pad18[8];
    u64 flags;
    u8 pad28[4];
    u32 f2C;
    u8 pad30[0x28];
    s32 f58;
    u8 pad5C[0x2E0];
    f32 vec[3];
    s32 f348;
    u8 pad34C[0x14];
    u16 f360;
    s8 f362;
    u8 pad363[9];
    u8 f36C;
    u8 pad36D[4];
    u8 f371;
    u8 pad372[0x31];
    u8 f3A3;
} Nw2ActAC3A0;

extern Nw2ActAC3A0 *D_800FAF5C;
extern Nw2ActAC3A0 *D_800F9B00;
extern s8 D_800FADB8;
extern u16 D_800FABE6;
extern u16 D_800FAF8A;
extern s8 D_800FAF78;
extern s16 D_800FAF8E[];
extern s16 D_800EB420[];
extern s16 D_800EB428[];
extern s16 D_800EB438[];
extern s16 D_800EB448[];
extern u16 D_800F9B78[];

s32 func_800D2BAC(void *, void *, f32, s32);
void func_800A7C40(void *, s8, s16);
s16 func_800D5438(void *, s32);
void func_800D427C(void *, s16, s32);
s32 func_800AD218(void *, u16, u16, s8, s16 *);
void func_800AD6D0(void *);
void func_800D4AD0(void *);
void func_800A6C48(void *, s32);
void func_800AD2C4(void *, void *, u16, s16);
void func_800D7E80(void *, void *);
void func_800A7328(void *);
void func_800D43B4(void *, s16, s32);
s32 func_800D3E40(void *, f32 *, s32, f32 *);
void func_800D3838(void *, f32 *, s16, f32 *);
void translateEntityXZ(void *, void *);
s32 func_800D35B0(s32, s32);
s32 func_800D3684(s32, s32);
void func_800D8D74(void *, s32);
void func_800A6BE0(void *, s32);

#define O D_800FAF5C
#define P D_800F9B00

void func_800AC3A0(void) {
    func_800D2BAC(O, P, 2.0f, 0xFFFFE);

    switch (O->fC) {
    case 0:
        func_800A7C40(O, D_800FADB8, 0xEC);
        D_800EB428[D_800FADB8] = func_800D5438(O, 0);
        D_800EB428[D_800FADB8 + 4] = func_800D5438(O, 1);
        func_800A7C40(O, D_800FADB8, 0xED);
        D_800EB428[D_800FADB8 + 8] = func_800D5438(O, 0);
        D_800EB428[D_800FADB8 + 12] = func_800D5438(O, 1);
        func_800A7C40(O, D_800FADB8, 0xEE);
        D_800EB428[D_800FADB8 + 16] = func_800D5438(O, 0);
        D_800EB428[D_800FADB8 + 20] = func_800D5438(O, 1);
        func_800D427C(O, D_800EB428[D_800FADB8], 3);
        D_800EB420[D_800FADB8] = (s16)D_800F9B78[D_800FADB8] / 10;
        if (O->f2C & 1) {
            D_800EB420[D_800FADB8] = 0xA;
        } else {
            D_800EB420[D_800FADB8] = 6;
        }
        D_800FAF8E[D_800FADB8] = 0;
        O->fC++;
        break;
    case 1:
        if (O->f4 == 1) {
            O->fC++;
        }
        break;
    case 2:
        func_800D427C(O, D_800EB438[D_800FADB8], 3);
        O->fC++;
    case 3:
        if (O->f360 & 1) {
            O->f360 &= ~1;
            O->fC++;
            break;
        }
        if ((s8)func_800AD218(O, D_800FABE6, D_800FAF8A, D_800FAF78, &D_800FAF8E[D_800FADB8])) {
            O->fC++;
        }
        if (O->f4 > 0) {
            break;
        }
        O->flags &= 0xFFFFFFFFBFFFFFFFULL;
        O->f362 = -1;
        P->fC = 3;
        func_800AD6D0(O);
        func_800D4AD0(O);
        func_800A6C48(O, 0x2B);
        break;
    case 4:
        func_800AD2C4(O, P, D_800FAF8E[D_800FADB8], D_800EB420[D_800FADB8]);
        if (O->f2C & 0x80000) {
            func_800D7E80(O, P);
            func_800D427C(O, D_800EB448[D_800FADB8], 2);
            D_800EB420[D_800FADB8]--;
            O->fC = 6;
            P->fC = 7;
        } else {
            func_800A7328(O);
            func_800D43B4(O, (s16)func_800D5438(O, 0), 2);
            D_800EB420[D_800FADB8]--;
            D_800FAF8E[D_800FADB8] = 0;
            O->fC++;
            P->fC = 4;
            P->f360 &= ~2;
        }
        break;
    case 5: {
        s16 cnt;
        f32 dir[3];
        f32 out[4];
        s32 ang;
        s32 dd;

        if (O->f371 >= O->f6) {
            cnt = O->f371 - O->f6 + 1;
            dir[0] = 0.0f;
            dir[2] = 130.0f;
            func_800D3E40((u8 *)P + 0x6C, dir, P->f58, out);
            func_800D3838((u8 *)O + 0x4C, out, cnt, O->vec);
            translateEntityXZ(O, O->vec);
            ang = func_800D35B0(P->f58, 0x800);
            dd = func_800D3684(ang, O->f58) / cnt;
            O->f58 = func_800D35B0(O->f58, dd);
        }
        if (O->f6 != O->f371) {
            goto tail;
        }
        P->f360 |= 4;
        if (P->f360 & 2) {
            if (D_800EB420[D_800FADB8] == 0 && !(O->f2C & 0x400000)) {
                if (P->f3A3) {
                    func_800A7328(O);
                    func_800D427C(O, (s16)func_800D5438(P, 1), 2);
                } else {
                    func_800D427C(O, (s16)func_800D5438(P, 1), 1);
                }
            }
        } else {
            func_800A837C(O);
        }
tail:
        if (O->f6 >= O->f36C - 4) {
            if ((s8)func_800AD218(O, D_800FABE6, D_800FAF8A, D_800FAF78, &D_800FAF8E[D_800FADB8])) {
                O->f360 |= 1;
            }
        }
        if (O->f4 > 0) {
            break;
        }
        if (D_800EB420[D_800FADB8] == 0 || P->fA != 0x4C || (O->f2C & 0x400000)) {
            func_800AD6D0(O);
            func_800D4AD0(O);
            func_800A6C48(O, 0x2B);
            O->flags &= 0xFFFFFFFFBFFFFFFFULL;
            O->f362 = -1;
        } else {
            O->fC = 2;
            O->flags |= 0x10000000ULL;
        }
        break;
    }
    case 6:
        func_800D8D74(O, 0);
        if (O->f4 > 0) {
            break;
        }
        func_800AD6D0(O);
        func_800D427C(O, (s16)func_800D5438(O, 0), 1);
        func_800A6BE0(O, 0x51);
        break;
    }
}
