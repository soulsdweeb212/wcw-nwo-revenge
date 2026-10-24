#include "common.h"

typedef struct {
    s8 id;              /* 0x00 */
    u8 pad1[3];
    s16 f4;             /* 0x04 */
    s16 f6;             /* 0x06 */
    u8 pad8[2];
    s16 fA;             /* 0x0A */
    s16 state;          /* 0x0C */
    u16 flagsE;         /* 0x0E */
    u8 pad10[6];
    s16 f16;            /* 0x16 */
    u8 pad18[8];
    u64 flags;          /* 0x20 */
    u8 pad28[0x353 - 0x28];
    s8 f353;            /* 0x353 */
    u8 pad354;
    s8 f355;            /* 0x355 */
    u8 pad356[0x36C - 0x356];
    u8 f36C;            /* 0x36C */
    u8 pad36D[0x386 - 0x36D];
    s16 f386;           /* 0x386 */
} Wrestler;

#define P ((Wrestler *)D_800EB408)
extern Wrestler *D_800EB40C;
extern Wrestler *D_800EB410;
extern s32 D_800EB3F0[];
extern s32 D_800F9B0C[];
extern s16 D_800FABD4;
extern u32 D_800FABD8;
extern s8 D_800FABDC;
extern u16 D_800FABE6;
extern s8 D_800FADB8;
extern u8 D_800FADCF;
extern s8 D_800FAF78;
extern u16 D_800FAF8A;
extern s16 D_800FAF9E;

void func_800A6BE0(void *, s32);
void func_800A7828(void *, void *);
void func_800A7C40(void *, s32, s32);
void func_800A7F6C(void *, s32);
void func_800A837C(void *);
s8 func_800A9128(void *);
void func_800A9488(void *, void *);
void func_800B68A0(void *, void *, void *);
void func_800D25D0(void *, f32);
void func_800D2B64(void *, f32, s32, s32);
s32 func_800D36E8(f32, f32);
void func_800D427C(void *, s16, s32);
void func_800D4AD0(void *);
s32 func_800D4D44(void *, s32, s32);
s32 func_800D5438(void *, s32);
s8 func_800DF214(void *, u16);
s8 func_800DF3E4(void *, void *, u16, s32);
s8 func_800DF99C(void *, void *, u16, s32 *);
s8 func_800DFDD4(void *, void *, u16, s32 *);
s8 func_800E022C(void *, void *, u16, s32 *);
void func_800E212C(void *);

void func_800A01B0(void) {
    s32 s0;
    s32 s1;
    Wrestler *o2;
    s32 v;
    s32 anim;

    func_800D93DC(D_800EB408);
    switch (P->state) {
    case 0:
        if (D_800FADCF & 0x40) {
            func_800E212C(D_800EB408);
            D_800FADCF |= 0x20;
            P->state = 4;
            break;
        }
        if (!(P->flags & 0x80)) {
            if (func_800D3550(func_800D3684(0x800, func_800D36E8(D_800FABD4, D_800FAF9E))) < 0xAA) {
                P->state = 7;
                break;
            }
        }
        if (P->flags & 0x40000) {
            P->flags = (P->flags & ~0x40000) | 0x80000;
            P->flagsE |= 1;
            if (P->flags & 0x80) {
                func_800A7C40(P, D_800FADB8, 0xC2);
                s0 = func_800D5438(P, 0);
            } else {
                func_800A7C40(P, D_800FADB8, 0xBE);
                s0 = func_800D5438(P, 0);
                func_800A7828(P, D_800EB40C);
            }
            func_800D427C(P, s0, 3);
            func_800A7F6C(P, 0x3F);
            func_800A9488(P, D_800EB40C);
            P->state++;
            break;
        }
        if (P->flags & 0x80000) {
            if (P->flags & 0x80) {
                s1 = 0xC2;
            } else {
                s1 = 0xBE;
            }
            func_800A7C40(P, D_800FADB8, s1);
            s0 = func_800D5438(P, 0);
        } else if (P->flags & 1) {
            if (P->flags & 0x80) {
                s1 = 0xC2;
            } else {
                s1 = 0xBD;
                if (D_800EB410->flags & 0x1000000000000000ULL) {
                    s1 = 0xBE;
                }
                if (*(u64 *)&D_800F9D30[D_800EB410->f353 * 0x3B0] & 0x1000000000000000ULL) {
                    s1 = 0xBD;
                }
            }
            func_800A7C40(P, D_800FADB8, s1);
            s0 = func_800D5438(P, 0);
        } else {
            if (P->flags & 0x80) {
                s1 = 0xC2;
            } else {
                s1 = 0xBD;
            }
            func_800A7C40(P, D_800FADB8, s1);
            s0 = func_800D5438(P, 0);
        }
        if (!(P->flags & 0x80)) {
            o2 = D_800EB410;
            if (P->id != o2->id && !(o2->flags & 1) && o2->fA == 0x17 && o2->f6 < 10) {
                if (P->flags & 1) {
                    func_800A7C40(P, P->id, 0xC1);
                    s0 = func_800D5438(P, 0);
                } else {
                    anim = o2->f386;
                    if (anim == s1) {
                        func_800A7C40(P, P->f355, anim);
                        s0 = func_800D5438(P, 0);
                    }
                }
            }
        }
        func_800D427C(P, s0, 3);
        D_800EB3F0[D_800FADB8] = func_800D36E8(D_800FABD4, D_800FAF9E);
        func_800A7F6C(P, 0);
        P->state++;
        break;
    case 1:
        if (P->flags & 0x80) {
            P->flags |= 0x0800000000000000ULL;
        }
        if (!(D_800EB40C->flags & 1) && !(P->flagsE & 1) && !(P->flags & 0x80) && P->f6 < 7 && D_800FAF78 != 0
            && func_800D3550(func_800D3684(D_800EB3F0[D_800FADB8], func_800D36E8(D_800FABD4, D_800FAF9E))) > 0x600) {
            if (D_800EB40C->flags & 0x80000) {
                s1 = 0xBE;
            } else {
                s1 = 0xBD;
            }
            func_800A7C40(P, D_800EB40C->id, s1);
            func_800D427C(P, func_800D5438(P, 0), 3);
            P->flagsE |= 1;
        }
        if (func_800DF214(P, D_800FABE6) || func_800DF3E4(P, D_800EB40C, D_800FABE6, D_800F9B0C[0])) {
            goto block;
        }
        s0 = (s32)(D_800F9B0C - 1);
        if (func_800DFDD4(P, D_800EB40C, D_800FABE6, (s32 *)s0)) {
            break;
        }
        if (func_800DF99C(P, D_800EB40C, D_800FABE6, (s32 *)s0) || func_800E022C(P, D_800EB40C, D_800FABE6, (s32 *)s0)) {
        block:
            func_800A9128(P);
            break;
        }
        func_800D25D0(P, 4.0f);
        func_800D2B64(P, 4.0f, 0, 0xFFFFE);
        if (P->f4 > 0) {
            break;
        }
        if (!(P->flags & 0x100) || (D_800EB40C->flags & 0x100)) {
            func_800B68A0(P, P, D_800EB40C);
        }
        func_800A7828(P, D_800EB40C);
        func_800D4AD0(P);
        if (func_800A9128(P)) {
            func_800A6BE0(P, 1);
            func_800D427C(P, 0x108D, 2);
        } else {
            func_800A6C48(P, 1);
        }
        func_800A837C(P);
        break;
    case 2:
        anim = 0xBF;
        func_800A7C40(P, D_800FADB8, anim);
        func_800D427C(P, func_800D5438(P, 0), 1);
        func_800A7F6C(P, 0);
        if (P->flags & 0x40000) {
            P->flags = (P->flags & ~0x40000) | 0x80000;
            func_800A9488(P, D_800EB40C);
        }
        P->state++;
        break;
    case 3:
        if (func_800DF214(P, D_800FABE6)) {
            break;
        }
        if (func_800DF3E4(P, D_800EB40C, D_800FAF8A, D_800F9B0C[0])) {
            break;
        }
        s0 = (s32)(D_800F9B0C - 1);
        if (func_800DFDD4(P, D_800EB40C, D_800FABE6, (s32 *)s0)) {
            break;
        }
        if (func_800DF99C(P, D_800EB40C, D_800FABE6, (s32 *)s0)) {
            break;
        }
        if (func_800E022C(P, D_800EB40C, D_800FABE6, (s32 *)s0)) {
            break;
        }
        func_800D25D0(P, 4.0f);
        func_800D2B64(P, 4.0f, 0, 0xFFFFE);
        if (P->f4 > 0) {
            break;
        }
        if (!(P->flags & 0x100) || (D_800EB40C->flags & 0x100)) {
            func_800B68A0(P, P, D_800EB40C);
        }
        func_800D4AD0(P);
        func_800A6C48(P, 0x2B);
        func_800A7828(P, D_800EB40C);
        func_800A837C(P);
        break;
    case 4:
        func_800A7C40(P, P->id, 0xC3);
        func_800D427C(P, func_800D5438(P, 0), 3);
        P->f16 = 0;
        P->state++;
        break;
    case 5:
        if (++P->f16 == 30 && P->id == D_800FABDC) {
            D_800FABD8 |= 4;
        }
        func_800D25D0(P, 4.0f);
        func_800D2B64(P, 4.0f, 0, 0xFFFFE);
        if (P->f4 > 0) {
            break;
        }
        v = P->f36C;
        if (v > 0xB4) {
            v = 0xF;
        } else {
            v = 0xC3 - v;
        }
        P->f16 = v;
        if (P->id == D_800FABDC) {
            D_800FABD8 |= 4;
        }
        func_800D4AD0(P);
        func_800D427C(P, func_800D4D44(P, 0xC, 0), 3);
        P->state++;
        break;
    case 6:
        if (--P->f16 == 0 && P->id == D_800FABDC && (D_800FABD8 & 0x100)) {
            D_800FABD8 |= 1;
            D_800FADCF &= ~0x20;
        }
        if (P->f16 < -29) {
            P->f16 = -30;
        }
        break;
    case 7:
        P->flags |= 0x1000000000ULL;
        func_800D427C(P, 0xFB9, 3);
        P->state++;
        break;
    case 8:
        P->flags |= 0x1000000000ULL;
        func_800D25D0(P, 4.0f);
        func_800D2B64(P, 4.0f, 0, 0xFFFFE);
        if (P->f4 > 0) {
            break;
        }
        func_800D4AD0(P);
        P->state = 2;
        break;
    }
}
