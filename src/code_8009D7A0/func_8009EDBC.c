#include "common.h"

typedef struct {
    s32 f0;
    s16 f4;
    s16 f6;
    s32 f8;
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
    u8 pad34C[8];
    s8 f354;
} Nw2F408Action;

#define O ((Nw2F408Action *)D_800EB408)
#define EB40C ((Nw2F408Action *)D_800EB40C)

extern void *D_800EB40C;
extern s8 D_800FADB8;
extern s16 D_800FADC6[];
extern u16 D_800FAF8A;
extern s32 D_800E3C90[];
extern s32 D_800E3CA0[];
extern u16 D_800E3CD0[];

void func_800E212C(void *);
void translateEntityByActionQuadrant(void *);
void translateEntityXZ(void *, void *);
void func_800C38FC(void *, u64, s32);
void func_800D427C(void *, s16, s32);
s32 func_800D2B64(void *, s32, u16, s32);
s32 func_800D35B0(s32, s32);
s32 func_800D3684(s32, s32);
f32 func_800D63F0(void *, void *, s32);
void func_800D37C0(s32, f32, f32 *);
void func_800A7D1C(void *, s32);
void func_800A7F6C(void *, s32);
void func_800A837C(void *);
s8 func_800B71F8(void *, s32, s32);
void func_800B68A0();

void func_8009EDBC(void) {
    Nw2F408Action *o = O;
    o->f354 = -1;
    o->flags |= 0x100000ULL;

    switch (O->fC) {
    case 0:
        func_800E212C(D_800EB408);
        func_800D427C(D_800EB408, 0xEF5, 1);
        O->f58 = D_800E3C90[O->f3E];
        D_800FADC6[D_800FADB8]++;
        O->fC++;
        /* fall through */
    case 1:
        func_800C38FC(D_800EB408, 0x40001000000000ULL, 0x1000000);
        translateEntityByActionQuadrant(D_800EB408);
        if ((O->flags & 9) == 0) {
            u16 f28 = O->f28;
            if (f28 & 0x20) {
                if (!(f28 & 0x480)) {
                    if ((s16)D_800FADC6[D_800FADB8] == 1) {
                        if ((O->flags & 0x80000) != 0 ||
                            (EB40C->flags & 0x80000) == 0) {
                            if ((s16)O->f6 < 3 && (D_800FAF8A & 0xC030) &&
                                func_800B71F8(D_800EB408, 0, 3)) {
                                func_800A7F6C(D_800EB408, 0x4D);
                                func_800A837C(D_800EB408);
                                if (D_800FAF8A & 0x8000) {
                                    O->f28 |= 0x400;
                                } else {
                                    func_800D427C(D_800EB408, 0xEF7, 1);
                                    O->fC = 3;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (O->f4 > 0) {
            break;
        }
        O->f58 = D_800E3CA0[O->f3E];
        func_800D427C(D_800EB408, 0xEF6, 1);
        O->fC++;
        break;
    case 2: {
        u16 v;
        f32 d;
        translateEntityByActionQuadrant(D_800EB408);
        if (O->f4 <= 0) {
            O->f3E ^= 2;
            d = func_800D63F0(D_800EB408, 0, 2);
            func_800D37C0(O->f58, d, (f32 *)((u8 *)D_800EB408 + 0x33C));
            v = O->f28;
            O->f28 = v & 0xFF7F;
            if ((*(u32 *)&O->f28 & 0x04200000) == 0x00200000) {
                if ((s16)D_800FADC6[D_800FADB8] >= 2) {
                    func_800A6C48(D_800EB408, 1);
                    break;
                }
            } else {
                O->f28 = (v & 0xFF5B) | 3;
            }
            func_800A6C48(D_800EB408, 3);
            O->fC = 2;
            O->flags &= 0xFFFFFFFFFEFFFFFFULL;
        }
        break;
    }
    case 3:
        translateEntityByActionQuadrant(D_800EB408);
        if (O->f4 <= 0) {
            func_800D427C(D_800EB408, 0xEFA, 1);
            O->f58 = D_800E3CA0[O->f3E];
            O->fC++;
        }
        break;
    case 4:
        translateEntityByActionQuadrant(D_800EB408);
        if (O->f4 <= 0) {
            func_800A7D1C(D_800EB408, 0xB);
            func_800B68A0(D_800EB408, D_800EB408, D_800EB408);
            func_800A6C48(D_800EB408, 0x2B);
        }
        break;
    case 5: {
        f32 d;
        func_800D427C(D_800EB408, 0xE7F, 3);
        d = func_800D63F0(D_800EB408, 0, 2);
        func_800D37C0(D_800E3C90[O->f3E], d,
                      (f32 *)((u8 *)D_800EB408 + 0x33C));
        O->f348 = func_800D3684(D_800E3CA0[O->f3E], O->f58) / 6;
        O->f16 = 0;
        O->fC++;
    }
    case 6: {
        s32 mask;
        O->f16++;
        if ((s16)O->f16 < 7) {
            O->f58 = func_800D35B0(O->f58, O->f348);
        }
        translateEntityXZ(D_800EB408, (u8 *)D_800EB408 + 0x33C);
        mask = func_800D2B64(D_800EB408, 0x3F800000, 0, 2);
        if (mask & 0xFFFF) {
            if (D_800E3CD0[O->f3E] & mask) {
                func_800D427C(D_800EB408, 0xE74, 3);
                O->f58 = D_800E3CA0[O->f3E];
                D_800FADC6[D_800FADB8]++;
                O->fC++;
            }
        }
        break;
    }
    case 7: {
        f32 d;
        func_800C38FC(D_800EB408, 0x40001000000000ULL, 0x1000000);
        if (O->f4 <= 0) {
            O->f3E ^= 2;
            d = func_800D63F0(D_800EB408, 0, 2);
            func_800D37C0(O->f58, d, (f32 *)((u8 *)D_800EB408 + 0x33C));
            O->flags &= 0xFFFFFFFFFEFFFFFFULL;
            O->f28 = (O->f28 & 0xFF7F) | 3;
            func_800A6C48(D_800EB408, 3);
            O->fC = 2;
        }
        break;
    }
    }
}
