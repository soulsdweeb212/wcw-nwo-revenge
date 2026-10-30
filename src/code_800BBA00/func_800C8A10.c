#include "common.h"

typedef struct {
    u8 pad0[4];
    s16 f4;
    u8 pad6[6];
    s16 fC;
    u8 padE[0xA];
    s16 f18;
    u8 pad1A[6];
    u64 f20;
} Nw2ActionObj800C8A10;
typedef struct {
    u8 pad0[0xA];
    s16 fA;
    u8 padC[0x20];
    u32 f2C;
    u8 pad30[0x330];
    u16 f360;
} Nw2Entity800C8A10;
typedef struct {
    Nw2ActionObj800C8A10 *p;
} Nw2Holder800C8A10;
extern Nw2ActionObj800C8A10 *D_800FAF5C;
extern Nw2Entity800C8A10 *D_800F9B00;
extern u16 D_800FAF8A;
extern s8 D_800FAF78;
#define SOBJ (((Nw2Holder800C8A10 *)&D_800FAF5C)->p)
void func_800D7E80(void *, void *);
void func_800D427C(void *, s16, s32);
s8 func_800D8D74(void *, s32);
s16 func_800B6DEC(void *, void *, s32);
void func_800D7690(void *, s32, s32);
s8 func_800D7894(void *, u16);
s32 func_800D2BAC(void *, void *, f32, s32);
s32 func_800D2B64(void *, f32, u16, s32);
void func_800A7188(void *);

void func_800C8A10(void) {
    switch (D_800FAF5C->fC) {
    case 0:
        if (!(D_800F9B00->f2C & 0x10)) {
            func_800D427C(D_800FAF5C, 0x10B8, 0);
            D_800FAF5C->fC = 2;
            return;
        }
        func_800D7E80(D_800FAF5C, D_800F9B00);
        func_800D427C(D_800FAF5C, 0x10A6, 2);
        {
            u16 *pc = (u16 *)((u8 *)SOBJ + 0xC);
            s32 v = *pc + 1;
            u32 tq;
            *pc = v;
            tq = v & 1;
            if (tq >> 1) {
                func_800A7188(0);
            }
        }
    case 1:
        if (func_800D8D74(D_800FAF5C, 0)) {
            D_800FAF5C->fC++;
        }
        return;
    case 2:
        if (D_800FAF5C->f4 > 0) {
            return;
        }
        func_800D427C(D_800FAF5C, (D_800F9B00->f2C & 0x10) ? 0x10A8 : 0x10BA, 0);
        {
            s16 r = func_800B6DEC(D_800FAF5C, D_800F9B00, 5);
            D_800FAF5C->f18 = r;
            if (D_800F9B00->f2C & 2) {
                D_800FAF5C->f18 = r + r / 2;
            }
        }
        func_800D7690(D_800FAF5C, 0, 0);
        D_800FAF5C->fC++;
        return;
    case 3:
        if (!(D_800F9B00->f2C & 0x10)) {
            D_800FAF5C->f20 |= 0x0400400000000000ULL;
        }
        if (D_800F9B00->fA != 0x72) {
            D_800FAF5C->fC++;
            return;
        }
        if (D_800F9B00->f360 & 4) {
            D_800FAF5C->f20 |= 0x10000000ULL;
            D_800FAF5C->fC++;
        } else {
            if (func_800D7894(D_800FAF5C, D_800FAF8A)) {
                if (D_800FAF78 != 0) {
                    D_800FAF5C->f18 = 0;
                } else {
                    D_800F9B00->f360 |= 2;
                }
            }
        }
        if (!(D_800F9B00->f2C & 0x10)) {
            func_800D2BAC(D_800FAF5C, D_800F9B00, 2.0f, 2);
        }
        return;
    case 4:
        {
            s16 anim = (D_800F9B00->f2C & 0x10) ? 0x10AA
                      : (D_800F9B00->fA == 0x72) ? ((D_800F9B00->f360 & 1) ? 0x10BC : 0x10BE)
                      : 0x10BE;
            func_800D427C(D_800FAF5C, anim, 0);
        }
        (*(s16 *)((u8 *)SOBJ + 0xC))++;
    case 5:
        D_800FAF5C->f20 |= 0x1000000000ULL;
        func_800D2B64(D_800FAF5C, 2.0f, 0, 2);
        func_800A7188(D_800FAF5C);
        return;
    }
}
