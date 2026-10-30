#include "common.h"

typedef struct {
    u8 pad0[2];
    s16 f2;
    u8 pad4[0x1C];
    u64 flags;
    u8 pad28[0x388];
} Slot4C60;

typedef struct {
    u8 pad0[4];
    s16 f4;
    s16 f6;
    u8 pad8[2];
    s16 fA;
    s16 fC;
    u8 padE[0x12];
    u64 flags;
    u16 f28;
    u16 f2A;
    u8 pad2C[0x2C];
    s32 f58;
    u8 pad5C[0x10];
    f32 f6C[3];
    u8 pad78[0x2F9];
    u8 f371;
    u8 pad372[0x14];
    s16 f386;
    u8 pad388[0x1B];
    u8 f3A3;
} Ent4C60;

extern Ent4C60 *D_800FAF5C;
extern Ent4C60 *D_800F9B00;
extern s8 D_800FADB8;
extern s32 D_800F9B14;
extern s32 D_800FABD8;
extern s32 D_800E3F20[];
extern Slot4C60 D_800F9D10[];

void func_800A7C40(void *, s32, s16);
s16 func_800D5438(void *, s32);
void func_800D427C(void *, s32, s32);
void func_800A7F6C(void *, s32);
s8 func_800D3B24(void *, void *, f32, void *);
s32 func_800D3684(s32, s32);
s32 func_800D3550(s32);
void func_800C5FBC(void *);
s8 func_800C2CDC(void *, s32);
void func_800C3A78(void *, void *, s32);
void func_800D25D0(void *, f32);
void func_800D2B64(void *, f32, s32, s32);
void func_800A7188(void *);

void func_800C4C60(void) {
    Nw2DirectionResult res;
    Ent4C60 *o;
    Ent4C60 *b;
    s16 i;
    s16 v;
    s8 r;
    f32 two;

    switch (D_800FAF5C->fC) {
    case 0:
        if (((D_800F9B00->flags & 0x100000ULL) && (*(u32 *)&D_800F9B00->f28 & 0x280000) == 0x280000) || D_800F9B00->fA == 0x14) {
            v = 0xA5;
        } else {
            v = (D_800FAF5C->f28 & 4) ? 0xA1 : 0xA3;
        }
        func_800A7C40(D_800FAF5C, D_800FADB8, v);
        D_800FAF5C->fC = 2;
        D_800FAF5C->flags |= 0x10000000ULL;
        break;
    case 1:
        func_800A7C40(D_800FAF5C, D_800FADB8, D_800FAF5C->f3A3);
        D_800FAF5C->f58 = D_800F9B14;
        D_800FAF5C->fC++;
    case 2:
        func_800D427C(D_800FAF5C, func_800D5438(D_800FAF5C, 0), 1);
        func_800A7F6C(D_800FAF5C, 0);
        for (i = 0; i < 4; i++) {
            if (D_800F9D10[i].f2 != -1 && (D_800F9D10[i].flags & 0x10000000000ULL)) {
                break;
            }
        }
        if (i == 4) {
            if (((D_800FAF5C->flags & 0x40ULL) && (D_800F9B00->flags & 0xC0ULL)) ||
                ((D_800FAF5C->flags & 0x100ULL) && (D_800F9B00->flags & 0x100ULL))) {
                if ((D_800FAF5C->flags & D_800F9B00->flags) & 0x200ULL) {
                    if (func_800D3B24(D_800FAF5C->f6C, D_800F9B00->f6C, 200.0f, &res)) {
                        if (func_800D3550(func_800D3684(D_800FAF5C->f58, res.angle)) < 0x72) {
                            D_800FAF5C->flags |= 0x10000000000ULL;
                        }
                    }
                }
            }
        }
    case 3:
        D_800FAF5C->fC++;
        D_800FABD8 &= ~D_800E3F20[D_800FADB8];
        func_800C5FBC(D_800FAF5C);
        r = func_800C2CDC(D_800FAF5C, 1);
        if (r != -1) {
            D_800FAF5C->fC++;
            func_800C3A78(D_800FAF5C, (u8 *)D_800F9D10 + r * 0x3B0, D_800FAF5C->f386 == 0xA5 ? 0x10 : 8);
        }
    case 4:
        two = 2.0f;
        func_800D25D0(D_800FAF5C, two);
        o = D_800FAF5C;
        if (o->flags & 0x100ULL) {
            func_800D2B64(o, two, 0, 0xFFFFE);
        } else {
            switch ((s16)(o->fA - 7)) {
            case 15:
                if (o->f6 > o->f371) {
                    func_800D2B64(o, 2.0f, 0, 0xE);
                }
                break;
            case 0: case 24: case 25: case 26: case 29: case 30: case 31: case 78: case 79:
                if (o->f6 > o->f371) {
                    func_800D2B64(o, 4.0f, 0, 0xFFFFE);
                } else {
                    func_800D2B64(o, 2.0f, 0, 0xE);
                }
                break;
            case 1: case 23: case 27: case 28: case 32:
                func_800D2B64(D_800FAF5C, 2.0f, 0, 0xE);
                break;
            }
        }
        func_800A7188(D_800FAF5C);
        break;
    }
}
