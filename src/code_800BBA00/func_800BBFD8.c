#include "common.h"

typedef struct {
    u8 pad0[2];
    s16 f2;
    u8 pad4[2];
    s16 f6;
    s16 f8;
    u8 padA[0x16];
    u64 flags;
    u8 pad28[0x34E];
    u8 f376;
    u8 f377;
    u8 pad378[4];
    u8 f37C;
    u8 pad37D[0x33];
} RecBFD8;

typedef struct {
    s16 f0;
    s16 f2;
    u8 pad4[2];
    u16 f6;
    u16 f8;
    u8 padA[2];
    u8 fC;
    u8 padD[0x53];
} SlotBFD8;

typedef struct {
    u8 pad0[4];
    u16 f4;
    u16 f6;
    u8 pad8[2];
    s8 fA;
    s8 fB;
} PadBFD8;

typedef struct {
    u8 a;
    u8 b;
    u8 pad[22];
} PairBFD8;

extern RecBFD8 D_800F9D10[];
extern SlotBFD8 D_800F9B88[];
extern PadBFD8 D_8006E178[];
extern PairBFD8 D_8007E850[];
extern s16 D_800FAF96[];
extern s16 D_800FABD4;
extern u16 D_800FABE6;
extern s8 D_800FADB8;
extern u8 D_800FAF78;
extern u16 D_800FAF8A;
extern s16 D_800FAF9E;

void remapControllerButtons(s16, u16 *);
void startEntityAction(void);
void func_8009D8D0(void);
void updateEntityModeFlags(void *);

void func_800BBFD8(void) {
    s16 i;
    s16 a3;
    s16 a2;
    s16 cnt;
    u16 v1;
    u16 v2;
    s32 t;
    s32 idx;
    u64 fl;

    if (D_800F9D10[D_800FADB8].f2 == -1) {
        return;
    }
    i = D_800FAF96[D_800FADB8];
    v1 = D_8006E178[i].f4;
    v2 = D_8006E178[i].f6;
    D_800FABE6 = v1;
    D_800FAF8A = v2;
    remapControllerButtons(i, &D_800FABE6);
    remapControllerButtons(i, &D_800FAF8A);
    D_800FABD4 = D_8006E178[i].fA;
    D_800FAF9E = D_8006E178[i].fB;
    if (func_800D3550(D_800FABD4) >= 0x29 || func_800D3550(D_800FAF9E) >= 0x29) {
        D_800FAF78 = 1;
    } else {
        D_800FAF78 = 0;
    }
    t = D_8006E178[i].f6 & 0x2000;
    a2 = a3 = (t != 0);
    if (a3) {
        if (D_8007E280 & 0x100) {
            if (!(D_800F9D10[D_800FADB8].flags & 3)) {
                a2 = 0;
            }
        }
        if (D_8007E280 & 0x200) {
            a2 = 0;
        }
        if (D_8007E280 & 0x400) {
            a2++;
        }
        if (a2) {
            idx = D_800FADB8;
            if (D_800F9D10[idx].flags & 4) {
                D_800F9D10[idx].flags &= ~4ULL;
            } else {
                D_800F9D10[idx].flags |= 4;
                D_800F9B88[idx].f0 = 0;
                D_800F9B88[idx].f2 = 0;
            }
            if (D_8007E280 & 0x400) {
                if (D_800F9D10[D_800FADB8].flags & 4) {
                    D_8007E850[D_800FADB8].b = 1;
                } else {
                    D_8007E850[D_800FADB8].a = 1;
                }
            }
        }
    }
    if (D_800F9D10[D_800FADB8].flags & 4) {
        u16 w1;
        u16 w2;
        u8 w3;
        do {
            startEntityAction();
        } while (D_800F9D10[D_800FADB8].flags & 0x10000000);
        idx = D_800FADB8;
        w1 = D_800F9B88[idx].f6;
        w2 = D_800F9B88[idx].f8;
        D_800FABE6 = w1;
        D_800FAF8A = w2;
        w3 = D_800F9B88[idx].fC;
        D_800FABD4 = 0;
        D_800FAF9E = 0;
        D_800FAF78 = w3;
    }
    do {
        func_8009D8D0();
    } while (D_800F9D10[D_800FADB8].flags & 0x10000000);
    idx = D_800FADB8;
    cnt = D_800F9D10[idx].f6;
    if (D_800F9D10[idx].f6 == 0) {
        cnt = 1;
    }
    fl = D_800F9D10[idx].flags;
    if (fl & 0x1000000000ULL) {
        if (cnt >= D_800F9D10[idx].f37C && D_800F9D10[idx].f8 != 0x10FF) {
            D_800F9D10[idx].flags = fl | 0x400000;
        }
    } else {
        if (cnt >= D_800F9D10[D_800FADB8].f37C && D_800F9D10[D_800FADB8].f8 != 0x10FF) {
            D_800F9D10[D_800FADB8].flags |= 0x400000;
            updateEntityModeFlags(&D_800F9D10[D_800FADB8]);
        }
        if (!(D_800F9D10[D_800FADB8].flags & 0x400000) && cnt >= D_800F9D10[D_800FADB8].f376 &&
            cnt <= D_800F9D10[D_800FADB8].f377) {
            D_800F9D10[D_800FADB8].flags |= 0x1000000000ULL;
        }
    }
    D_800F9D10[D_800FADB8].flags |= 0x20000000;
}
