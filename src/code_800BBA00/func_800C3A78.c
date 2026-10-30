#include "common.h"

typedef struct {
    u8 f0;
    u8 p1[7];
    s16 f8;
    u8 pA[0x39];
    u8 f43;
    u8 p44[0x311];
    s8 f355;
    u8 p356[0x45];
    s8 f39B;
} Src3A78;

typedef struct {
    s8 f0;
    u8 p1[9];
    s16 fA;
    u8 pC[0xA];
    s16 f16;
    u8 p18[8];
    u64 flags;
    u8 p28[8];
    u32 f30;
    u8 p34[3];
    u8 f37;
    u8 p38[0xB];
    s8 f43;
    u8 p44[0x30D];
    u8 f351;
    u8 p352;
    u8 f353;
} Tgt3A78;

extern s16 D_800E3B14[][8];
extern s16 D_800E3B1C[];
extern s16 D_800E3B64[];
extern s16 D_800E3B74[];
extern s16 D_800E3B78[];
extern s16 D_800E3B7C[];
extern s16 D_800E3B8C[];
extern s16 D_800E3B9C[];
extern s16 D_800E3BA0[];
extern s16 D_800E3BA4[];
extern s16 D_800E3BB4[];
extern s16 D_800E3BC4[];
extern s16 D_800E3BC8[];
extern s16 D_800E3BCC[];
extern s16 D_800E3BE4[];
extern s16 D_800E3BF4[];
extern s16 D_800E3BF8[];
extern s16 D_800E3BFC[];

void func_800A6D80(void *, s32);
void func_800A837C(void *);
s16 func_800BF2FC(void *);
void addEntityHealthDelta(void *, s32);
s8 func_800C41F0(void *, void *);
void func_800C4610(void *, void *);
s8 func_800C472C(void *, void *, s32);
void updateEntityStatus43Timer(void *, s32);
s16 func_800D4148(void);
s8 func_800D4198(s16);
s8 func_800D7B54(void *, s32, s32, s32);
void func_800E212C(void *);

void func_800C3A78(Src3A78 *src, Tgt3A78 *tgt, u32 arg2) {
    u32 bits;
    s16 v;
    s16 i;
    s16 j;
    s16 r;
    s16 *tbl;

    if ((tgt->flags & 0x600000000000ULL) && !(tgt->flags & 0x0400000000000000ULL)) {
        return;
    }
    src->f43 = 0;
    tgt->f351 = src->f0;
    if (src->f355 != tgt->f0) {
        tgt->f353 = src->f0;
    }
    tgt->f30 = arg2;
    func_800E212C(tgt);
    func_800C4610(src, tgt);
    switch (src->f39B) {
    case 0: case 1:
        tgt->f30 |= 0x10000000;
        break;
    case 2: case 5:
        tgt->f30 |= 0x20000000;
        break;
    case 3: case 4:
        tgt->f30 |= 0x40000000;
        break;
    }
    switch (tgt->fA) {
    case 23:
        addEntityHealthDelta(tgt, -10);
        break;
    case 64:
        if (!(tgt->flags & 9)) {
            if (tgt->f16 < 3 && func_800C41F0(tgt, src)) {
                return;
            }
            if (!(tgt->f30 & 0x600) && !(tgt->flags & 0x8000000)) {
                func_800A6C48(tgt, 0x41);
                return;
            }
        }
        break;
    case 65:
        if (!(tgt->flags & 9) && !(tgt->f30 & 0x600) && !(tgt->flags & 0x8000000)) {
            return;
        }
        break;
    case 20:
        if (tgt->f37 & 1) {
            tgt->f30 |= 0x2000;
        }
        break;
    case 45: case 46: case 47:
        if (func_800D7B54(tgt, 0, 0, 2) && func_800C41F0(tgt, src)) {
            return;
        }
        break;
    }
    func_800A837C(src);
    if (tgt->flags & 0x80) {
        u32 f;
        bits = 0;
        if (tgt->f30 & 1) {
            bits = func_800D4198(700) ? 0x400000 : 0x800000;
        }
        if (tgt->f30 & 0xE0) {
            bits = func_800D4198(800) ? 0x400000 : 0x800000;
        }
        f = tgt->f30;
        if (f & 0x606) {
            bits = 0x800000;
        }
        if (f & 0x18) {
            bits = 0x1000000;
        }
        if (f & 0x100) {
            bits = 0x800000;
        }
        if (bits == 0) {
            bits = 0x800000;
        }
        tgt->f30 = f | bits;
        func_800A6D80(tgt, 0x28);
        return;
    }
    if (func_800C472C(src, tgt, 0)) {
        return;
    }
    tgt->f43++;
    if (tgt->f43 >= 5) {
        tgt->f43 = 4;
    }
    updateEntityStatus43Timer(tgt, 0);
    if ((tgt->f30 & 0x2010) == 0x2010) {
        tgt->f30 |= 0x100000;
    }
    if ((tgt->f30 & 0x1008) == 8) {
        tgt->f30 |= 0x40000;
    }
    if (tgt->f30 & 0x4000) {
        if (tgt->f37 & 1) {
            tgt->f30 |= 0x4000000;
        } else {
            tgt->f30 = (tgt->f30 & ~0x4000) | 1;
        }
    }
    if ((tgt->f30 & 0x3400) == 0x400) {
        tgt->f30 |= 0x8000000;
    }
    {
        u32 f = tgt->f30;
        if (f & 0x4100000) {
            func_800A6D80(tgt, 0x28);
            return;
        }
        if (f & 0x2000) {
            tgt->f30 = f | 0x200000;
            func_800A6D80(tgt, 0x28);
            return;
        }
        if (f & 0x8040000) {
            func_800A6D80(tgt, 0x28);
            return;
        }
        if (f & 0x518) {
            if ((f & 0x100) && src->f8 == 0x1985) {
                tgt->f30 = f | 0x8000;
            } else {
                tgt->f30 |= 0x20000;
            }
            func_800A6D80(tgt, 0x28);
            return;
        }
    }
    v = func_800BF2FC(tgt);
    for (i = 0; i < 4; i++) {
        if (v >= D_800E3B1C[i]) {
            break;
        }
    }
    {
        u32 f = tgt->f30;
        if (f & 0x40) {
            tbl = &D_800E3BFC[i * 2];
        } else if (tgt->flags & 0x100000) {
            if (f & 0x202) {
                tbl = &D_800E3B8C[i * 2];
            } else if (f & 4) {
                tbl = D_800E3B9C;
            } else if (f & 1) {
                tbl = &D_800E3B7C[i * 2];
            } else {
                tbl = D_800E3BA0;
            }
        } else if (tgt->fA == 0x2E) {
            if (f & 0x202) {
                tbl = &D_800E3BB4[i * 2];
            } else if (f & 4) {
                tbl = D_800E3BC4;
            } else if (f & 1) {
                tbl = &D_800E3BA4[i * 2];
            } else {
                tbl = D_800E3BC8;
            }
        } else if (tgt->fA == 0x2D) {
            if (f & 0x202) {
                tbl = &D_800E3BE4[i * 2];
            } else if (f & 4) {
                tbl = D_800E3BF4;
            } else if (f & 1) {
                tbl = &D_800E3BCC[i * 3];
            } else {
                tbl = D_800E3BF8;
            }
        } else {
            if (f & 0x202) {
                tbl = &D_800E3B64[i * 2];
            } else if (f & 4) {
                tbl = D_800E3B74;
            } else if (f & 1) {
                tbl = &D_800E3B14[tgt->f43][i * 2];
            } else {
                tbl = D_800E3B78;
            }
        }
    }
    r = func_800D4148();
    for (j = 0; j < 4; j++) {
        if (tbl[j] >= r) {
            break;
        }
        r -= tbl[j];
    }
    {
        u32 f = tgt->f30;
        if (f & 0x206) {
            j++;
        }
        switch (j) {
        case 0:
            tgt->f30 = f | 0x8000;
            break;
        case 1:
            tgt->f30 = f | 0x10000;
            func_800A6D80(tgt, 0x2F);
            return;
        case 2:
            if ((f & 0x1002) == 2) {
                tgt->f30 = f | 0x80000;
            } else {
                tgt->f30 = f | 0x20000;
            }
            break;
        }
    }
    func_800A6D80(tgt, 0x28);
}
