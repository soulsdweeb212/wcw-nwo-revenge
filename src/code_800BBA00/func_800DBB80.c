#include "common.h"

typedef struct {
    u8 pad0[4];
    s16 f4;
    s16 f6;
    u8 pad8[2];
    s16 fA;
    s16 fC;
    u16 fE;
    u8 pad10[6];
    s16 f16;
    s16 f18;
    u8 pad1A[6];
    u64 flags;
    u8 pad28[0x16];
    s16 f3E;
    u8 pad40[0x18];
    s32 f58;
    u8 pad5C[0x10];
    u8 f6C[0x2D0];
    u8 f33C[0x28];
    u8 *f364;
    u8 pad368[4];
    u8 f36C;
    u8 pad36D[9];
    u8 f376;
} EntDBB;

typedef struct { f32 a; f32 b; f32 c; s32 d; } ResDBB;

extern EntDBB *D_800FAF5C;
extern EntDBB *D_800F9B00;
extern s8 D_800FADB8;
extern s16 D_800F9860[];
extern s16 D_800F9868[];
extern u16 D_800FAF8A;
extern s8 D_800FAF78;
extern u16 D_800FABE6;
extern u16 D_8007F0A0;
extern f32 D_800E3C50[];
extern f32 D_800E3C54[];
extern s32 D_800E3CB0[];
extern s32 D_800E3CC0[];

void func_800E212C(EntDBB *);
s8 func_800DF924(EntDBB *, EntDBB *);
s16 func_800DA9C0(EntDBB *, EntDBB *);
void func_800D427C(void *, s16, s32);
void func_800D7E80(EntDBB *, s32);
s8 func_800D8D74(EntDBB *, s32);
s8 func_800A93C0(void);
void func_800A7C40(EntDBB *, s8, s16);
s16 func_800D5438(EntDBB *, s32);
void func_800A7F6C(void *, s32);
void func_800A9488(EntDBB *, EntDBB *);
s8 checkEntityAttackHit(EntDBB *, u16);
s8 func_800D9568(EntDBB *);
s8 func_800D8DF0(EntDBB *);
void func_800A7188(EntDBB *);
void func_800A7D1C(EntDBB *, s32);
void func_800B68A0(EntDBB *, EntDBB *, EntDBB *);
void func_800D4AD0(EntDBB *);
void func_800E2500(EntDBB *, s32, s32);
void func_800A837C(void *);
void func_800D3890(f32 *, void *, ResDBB *);
void func_800D37C0(s32, f32, void *);
void translateEntityXZ(EntDBB *, void *);

void func_800DBB80(void)
{
    s16 anim;
    s16 cur;
    s16 sfx;
    s16 v;
    f32 pos[4];
    ResDBB res;
    s16 old;

    func_800D93DC(D_800FAF5C);
    switch (D_800FAF5C->fC) {
    case 0:
        if (D_800FAF5C->flags & 0x80) {
            D_800FAF5C->flags |= 0x100000;
        } else {
            pos[0] = D_800E3C50[D_800FAF5C->f3E * 2];
            pos[2] = D_800E3C54[D_800FAF5C->f3E * 2];
            func_800D3890(pos, D_800FAF5C->f6C, &res);
            func_800D37C0(res.d, 73.53910526280188 - res.b, D_800FAF5C->f33C);
            translateEntityXZ(D_800FAF5C, D_800FAF5C->f33C);
        }
        D_800FAF5C->fC++;
    case 1:
        func_800E212C(D_800FAF5C);
        if (D_800FAF5C->flags & 0x80) {
            D_800FAF5C->fE |= 1;
            if (D_800FAF5C->flags & 0x8000000000LL) {
                D_800F9860[D_800FADB8] = 4;
                if (D_800FAF5C->flags & 0x100000) {
                    anim = 0x1097;
                } else {
                    anim = 0x1095;
                }
            } else {
                D_800F9860[D_800FADB8] = 5;
                if (D_800FAF5C->flags & 0x100000) {
                    anim = 0x1098;
                } else {
                    anim = 0x1096;
                }
            }
            func_800D427C(D_800FAF5C, anim, 3);
            D_800FAF5C->fC = 3;
            break;
        }
        if (func_800DF924(D_800FAF5C, D_800F9B00)) {
            D_800FAF5C->fE |= 1;
            v = func_800DA9C0(D_800FAF5C, D_800F9B00);
            D_800F9868[D_800FADB8] = v;
            switch (v) {
            case 209:
                D_800F9860[D_800FADB8] = (s8)D_800FAF5C->f364[0x11];
                break;
            case 213:
                D_800F9860[D_800FADB8] = (s8)D_800FAF5C->f364[0x12];
                break;
            case 216:
                D_800F9860[D_800FADB8] = (s8)D_800FAF5C->f364[0x15];
                break;
            case 217:
                D_800F9860[D_800FADB8] = (s8)D_800FAF5C->f364[0x16];
                break;
            case 214:
                D_800F9860[D_800FADB8] = (s8)D_800FAF5C->f364[0x13];
                break;
            case 215:
                D_800F9860[D_800FADB8] = (s8)D_800FAF5C->f364[0x14];
                break;
            case 232: case 233:
                D_800F9860[D_800FADB8] = 2;
                break;
            case 210:
                D_800F9860[D_800FADB8] = (s8)D_800FAF5C->f364[0x17];
                break;
            }
            func_800D427C(D_800FAF5C, D_800F9860[D_800FADB8] + 0xF0B, 2);
            if (D_800F9B00->fA == 0x2C) {
                D_800F9B00->f18 += D_800FAF5C->f36C;
            }
        } else {
            func_800D427C(D_800FAF5C, 0xF0F, 2);
        }
        func_800D7E80(D_800FAF5C, 0);
        D_800FAF5C->fC++;
    case 2:
        if (D_800FAF8A & 0x10) {
            D_800FAF5C->fE |= 2;
        }
        if (D_800FAF78) {
            D_800FAF5C->fE |= 4;
        }
        if (func_800D8D74(D_800FAF5C, 0)) {
            D_800FAF5C->fC = (D_800FAF5C->fE & 1) ? D_800FAF5C->fC + 1 : 6;
        }
        break;
    case 3:
        if (D_800FAF8A & 0x10) {
            D_800FAF5C->fE |= 2;
        }
        if (D_800FAF78) {
            D_800FAF5C->fE |= 4;
        }
        if (D_800FAF5C->f4 > 0) {
            break;
        }
        cur = D_800F9860[D_800FADB8];
        if (cur >= 0) {
            if (cur < 2) {
                D_800FAF5C->f58 = D_800E3CB0[D_800FAF5C->f3E];
            } else if (cur < 6) {
                D_800FAF5C->f58 = D_800E3CC0[D_800FAF5C->f3E];
            }
        }
        func_800D427C(D_800FAF5C, 0xF13, 1);
        D_800FAF5C->f16 = 0;
        D_800FAF5C->flags |= 0x1000000000LL;
        D_800FAF5C->fC++;
        break;
    case 4:
        D_800FAF5C->flags |= 0x40104000000000LL;
        if (func_800A93C0()) {
            D_800FAF5C->fE |= 2;
        }
        if (D_800FAF8A & 0x10) {
            D_800FAF5C->fE |= 2;
        }
        if (D_800FAF78) {
            D_800FAF5C->fE |= 4;
        }
        if (!(D_800FAF5C->fE & 2)) {
            if ((D_800FAF5C->fE & 4) && D_800FAF5C->f16 < 150) {
                D_800FAF5C->fE &= ~4;
                func_800A7C40(D_800FAF5C, D_800FADB8, 0xC1);
                func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 0), 1);
                func_800A7F6C(D_800FAF5C, 0);
                if (D_800FAF5C->flags & 0x40000) {
                    D_800FAF5C->flags = (D_800FAF5C->flags & ~0x40000LL) | 0x80000;
                    func_800A9488(D_800FAF5C, D_800F9B00);
                }
                D_800FAF5C->fC = 7;
                break;
            }
            if ((D_800FAF8A & 0x28) && !(D_800FAF5C->flags & 0x200)) {
                if (checkEntityAttackHit(D_800FAF5C, D_800FABE6)) {
                    break;
                }
                if (func_800D9568(D_800FAF5C)) {
                    break;
                }
            }
            if (D_800FABE6 & 0xC004) {
                if (++D_800FAF5C->f16 < 150) {
                    break;
                }
            }
        }
        if (!func_800D8DF0(D_800FAF5C) && (D_800F9B00->flags & 0x40)) {
            D_800FAF5C->fE |= 2;
        }
        if ((D_8007F0A0 & 0x404) && (D_800F9B00->flags & 0x180) && (D_800FAF5C->flags & 0x200)) {
            D_800FAF5C->fE |= 2;
        }
        if (D_800FAF5C->fE & 2) {
            switch (D_800F9860[D_800FADB8]) {
            case 0: case 1:
                anim = 0xF11;
                break;
            case 2: case 3:
                anim = 0xF10;
                break;
            case 4:
                anim = 0x109A;
                break;
            case 5:
                anim = 0x1099;
                break;
            }
            func_800D427C(D_800FAF5C, anim, 1);
            D_800FAF5C->fC++;
            break;
        }
        old = D_800F9868[D_800FADB8];
        cur = func_800DA9C0(D_800FAF5C, D_800F9B00);
        if (cur != old) {
            if (cur == 0xD6 && old == 0xD7) {
                cur = 0xD7;
            }
        }
        func_800A7C40(D_800FAF5C, D_800FADB8, cur);
        switch (cur) {
        case 209: case 210: case 213:
            sfx = 0x6B;
            break;
        case 216: case 217:
            sfx = 0x6C;
            break;
        case 214: case 215:
            sfx = 0x6D;
            break;
        case 232:
            sfx = 0x6E;
            break;
        case 233:
            sfx = 0x6F;
            break;
        }
        func_800A6C48(D_800FAF5C, sfx);
        break;
    case 5:
        if (D_800FAF5C->f6 < D_800FAF5C->f376) {
            D_800FAF5C->flags |= 0x4000000000LL;
        }
        func_800A7188(D_800FAF5C);
        break;
    case 6:
        if (D_800FAF5C->f4 > 0) {
            break;
        }
        func_800A7D1C(D_800FAF5C, 0x26);
        func_800B68A0(D_800FAF5C, D_800FAF5C, D_800FAF5C);
        func_800D4AD0(D_800FAF5C);
        func_800A6C48(D_800FAF5C, 0x2B);
        break;
    case 7:
        D_800FAF5C->flags |= 0x40004000000000LL;
        D_800FAF5C->f16++;
        func_800E2500(D_800FAF5C, 0, 1);
        if (D_800FAF8A & 0x10) {
            D_800FAF5C->fE |= 2;
        }
        if (D_800FAF5C->f4 > 0) {
            break;
        }
        func_800B68A0(D_800FAF5C, D_800FAF5C, D_800F9B00);
        func_800D427C(D_800FAF5C, 0xF13, 1);
        func_800A837C(D_800FAF5C);
        D_800FAF5C->fC = 4;
        break;
    }
}
