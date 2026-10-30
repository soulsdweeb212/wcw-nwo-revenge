#include "common.h"

typedef struct {
    s32 f0;
    s16 f4, f6, f8, fA, fC;
    u8 pE[0x12];
    u64 flags;
    u8 p28[4];
    u32 f2C;
    u8 p30[0x321];
    u8 f351;
    u8 p352[0xE];
    u16 f360;
    s8 f362;
    u8 p363;
    void *f364;
    u8 p368[0x3B];
    u8 f3A3;
} ObjACC48;

extern ObjACC48 *D_800FAF5C;
extern ObjACC48 *D_800F9B00;
extern u8 D_800FABE4;
extern u8 D_800FADB8;
extern u16 D_800FABE6;
extern u16 D_800FAF8A;
extern s16 D_800EB420[];
extern s16 D_800EB430[];
extern s16 D_800EB440[];
extern s16 D_800EB450[];
typedef struct { ObjACC48 *p; } PtrBoxACC48;
extern struct { s32 pad; ObjACC48 *p; } D_800FAF58;

void func_800D427C(void *, s16, s32);
s16 func_800D5438(void *, s32);
void func_800D43B4(void *, s16, s32);
void tryApplyHitReaction(void *, void *, u16, u16);
void func_800AD574(void *, void *, u16);
void func_800A7F6C(void *, s32);
void func_800A837C(void *);
void func_800A6BE0(void *, s32);
void func_800D4AD0(void *);
void beginEntityActionA8D8C(void *);
void func_800D7E80(void *, void *);
s8 func_800D8D74(void *, s32);
s32 func_800C472C(void *, void *, s32);
void func_800B68A0();

void func_800ACC48(void) {
    register s16 r;
    ObjACC48 *o;

    func_800D2BAC(D_800FAF5C, D_800F9B00, 2.0f, 0xFFFFE);
    switch (D_800FAF5C->fC) {
    case 0:
        func_800D427C(D_800FAF5C, D_800EB430[(s8)D_800FABE4], 3);
        D_800FAF5C->fC++;
        break;
    case 1:
        if (D_800FAF5C->f4 <= 0) {
            func_800D427C(D_800FAF5C, D_800EB440[(s8)D_800FABE4], 3);
            D_800FAF5C->fC += 1;
        }
        break;
    case 2:
        if (D_800FAF5C->f4 <= 0) {
            func_800D43B4(D_800FAF5C, D_800EB440[(s8)D_800FABE4], 3);
        }
        break;
    case 4:
        if (D_800FAF5C->f4 <= 0) {
            func_800D43B4(D_800FAF5C, D_800EB440[(s8)D_800FABE4], 3);
        }
        tryApplyHitReaction(D_800F9B00, D_800FAF5C, D_800FABE6, D_800FAF8A);
        o = D_800FAF5C;
        if (o->f360 & 4) {
            o->f360 &= ~4;
            if (o->f360 & 2) {
                if (D_800EB420[(s8)D_800FABE4] == 0 && !(D_800F9B00->f2C & 0x400000)) {
                    if (o->f3A3) {
                        r = func_800D5438(o, 0);
                        func_800D43B4(D_800FAF5C, r, 2);
                        func_800D7E80(D_800FAF5C, D_800F9B00);
                    } else {
                        r = func_800D5438(o, 0);
                        func_800D43B4(D_800FAF5C, r, 1);
                    }
                    D_800FAF5C->fC = 6;
                } else {
                    r = func_800D5438(D_800FAF5C, 0);
                    func_800D43B4(D_800FAF5C, r, 1);
                    func_800B68A0(D_800FAF5C, D_800FAF5C, D_800F9B00);
                    D_800FAF5C->fC++;
                }
                func_800A7F6C(D_800FAF5C, 0x2B);
                func_800A837C(D_800FAF5C);
                goto finish;
            }
        } else {
            break;
        }
        func_800B68A0(D_800F9B00, D_800F9B00);
        if ((func_800C472C(D_800F9B00, D_800FAF5C, 0) << 24) != 0) {
            D_800FAF5C->flags &= ~0x08000000ULL;
            break;
        }
        r = func_800D5438(D_800F9B00, 1);
        func_800D43B4(D_800FAF5C, r, 1);
        D_800FAF5C->fC++;
finish:
        o = D_800FAF5C;
        o->f360 &= ~2;
        o->flags |= 0x10000000ULL;
        break;
    case 5:
        if (D_800FAF5C->f4 > 0) {
            break;
        }
        if (D_800EB420[(s8)D_800FABE4] == 0 || D_800F9B00->fA != 0x4B) {
            func_800D4AD0(D_800FAF5C);
            beginEntityActionA8D8C(D_800FAF5C);
            break;
        }
        if (D_800F9B00->f2C & 0x400000) {
    case 3:
            func_800D4AD0(D_800FAF58.p);
            beginEntityActionA8D8C(D_800FAF5C);
            break;
        }
        func_800D427C(D_800FAF5C, D_800EB440[(s8)D_800FABE4], 3);
        D_800FAF5C->fC = 2;
        D_800FAF5C->flags |= 0x10000000ULL;
        break;
    case 6:
        if (D_800FAF5C->f3A3 && (func_800D8D74(D_800FAF5C, 0) << 24) == 0) {
            break;
        }
        func_800A6BE0(D_800FAF5C, 0x53);
        func_800A6BE0(D_800F9B00, 0x54);
        D_800FAF5C->flags |= 0x40000000ULL;
        D_800F9B00->flags &= ~0x40000000ULL;
        D_800FAF5C->f362 = D_800FABE4;
        D_800F9B00->f362 = -1;
        D_800F9B00->f351 = D_800FADB8;
        break;
    case 7:
        D_800FAF5C->flags &= ~0x07800000ULL;
        func_800D427C(D_800FAF5C, D_800EB450[(s8)D_800FABE4], 3);
        *(volatile s16 *)&D_800FAF5C->fC += 1;
    case 8:
        func_800AD574(D_800F9B00, ((PtrBoxACC48 *)&D_800FAF5C)->p, D_800FAF8A);
        if (D_800FAF5C->f4 <= 0) {
            r = func_800D5438(D_800F9B00, 1);
            func_800D427C(D_800FAF5C, r, 1);
            func_800A6BE0(D_800FAF5C, 0x52);
        }
        break;
    }
}
