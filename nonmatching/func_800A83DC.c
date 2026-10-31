#include "common.h"

typedef struct {
    u8 f0;
    u8 pad1[9];
    s16 fA;
    s16 fC;
    s16 fE;
    u8 pad10[6];
    s16 f16;
    u8 pad18[8];
    u64 flags;
    u8 pad28[4];
    u32 f2C;
    u8 pad30[0xA];
    s16 f3A;
    u8 pad3C[8];
    s16 f44;
    s16 f46;
    u8 pad48[0x318];
    u16 f360;
    s8 f362;
    u8 pad363[0xC];
    u8 f36F;
    u8 pad370[0x14];
    s8 f384;
    u8 pad385;
    s16 f386;
    u8 pad388[4];
    u8 f38C[2];
    u16 f38E;
    u8 pad390[0x13];
    u8 f3A3;
    u8 f3A4;
    u8 pad3A5[7];
    u32 f3AC;
} E83DC;

typedef struct {
    u8 hdr[0x10];
    u8 data[0x1A20];
} Anim83DC;

extern u8 D_80075468[];

void func_800D4AD0(void *);
void func_800D4B10(void *);
void func_800D427C(void *, s16, s32);
s16 func_800D5438(void *, s32);
void unpackAnimationParameters(void *, void *);

#define SETACT(e, act) \
    (e)->fA = (act); \
    (e)->fC = 0; \
    (e)->fE = 0; \
    (e)->f360 = 0; \
    (e)->flags = ((e)->flags & ~0x10810000000ULL) | 0x1000000000ULL; \
    func_800DECAC((e), 0, 0, 0);

static inline void load83(E83DC *a, s8 sel, s16 id)
{
    u8 *tbl;
    a->f384 = sel;
    a->f386 = id;
    tbl = &D_80075468[0x10] + a->f384 * 0x1A30;
    unpackAnimationParameters(a->f38C, tbl + id * 0x18);
    if (id < 0xEF) {
        if (a->f3AC & 0x8000) {
            a->flags |= 0x4000000000000000ULL;
        } else {
            a->flags &= ~0x4000000000000000ULL;
        }
    }
}

s32 func_800A83DC(E83DC *a, E83DC *b)
{
    s32 k;
    s16 m;

    a->flags &= ~0x3800000ULL;
    b->flags &= ~0x3800000ULL;
    if (a->f36F == 5 && a->f3A3 == 0) {
        func_800D4AD0(a);
        func_800D4AD0(b);
        SETACT(a, 0x45);
        a->fC = 2;
        a->f2C = (b->f2C & 2) | 0x440;
        do {
            if (a->f2C & 2) {
                a->f16 = 0x5A;
                break;
            }
            a->f16 = 0x3C;
        } while (0);
        func_800D427C(a, 0xE8E, 1);
        SETACT(b, 0x46);
        b->fC = 2;
        b->f16 = 0;
        b->f2C = 0;
        func_800D427C(b, 0xE8F, 1);
        goto done;
    }
    if (a->f3AC & 0x1E00) {
        func_800D4B10(a);
        func_800D4B10(b);
        b->f44 = a->f38E;
        b->f46 = (s8)a->f3A4;
        if (a->f3AC & 0x200) {
            SETACT(a, 0x3E);
            a->flags |= 0x10000000ULL;
            SETACT(b, 0x3F);
            b->flags |= 0x10000000ULL;
        } else {
            SETACT(a, 0x3C);
            a->flags |= 0x10000000ULL;
            SETACT(b, 0x3D);
            b->flags |= 0x10000000ULL;
        }
        goto done;
    }
    if (a->f3A3 != 0) {
        if (a->f3A3 == 0x9F || a->f3A3 == 0x9D) {
            a->f362 = -1;
            a->flags &= ~0x40000000ULL;
            func_800D4AD0(a);
            SETACT(a, 0x1F);
            a->fC = 1;
            a->flags |= 0x10000000ULL;
            goto done;
        }
        if (a->f3A3 == 0xA1 || a->f3A3 == 0xA3) {
            a->f362 = -1;
            a->flags &= ~0x40000000ULL;
            func_800D4AD0(a);
            SETACT(a, 7);
            a->fC = 1;
            a->flags |= 0x10000000ULL;
            goto done;
        }
        func_800D4AD0(a);
        func_800D4AD0(b);
        k = a->f3A3;
        if ((u8)(k - 0x99) < 14) {
            switch (k) {
            case 0x99: m = 0; break;
            case 0x9A: m = 1; break;
            case 0x9B: m = 2; break;
            case 0x9C: m = 4; break;
            case 0x9D: m = 8; break;
            case 0x9E: m = 0x10; break;
            case 0xA6: m = 0x20; break;
            }
            a->f3A = m;
            SETACT(a, 0x58);
            a->flags |= 0x10000000ULL;
            SETACT(b, 0x59);
            b->flags |= 0x10000000ULL;
        } else if ((u32)(k - 0x5A) < 0x10) {
            load83(a, a->f0, (u8)k);
    func_800D427C(a, func_800D5438(a, 0), 1);
    func_800D427C(b, func_800D5438(a, 1), 1);

            a->f2C |= 0x80;
            SETACT(a, 0x49);
            a->flags |= 0x10000000ULL;
            SETACT(b, 0x4A);
            b->flags |= 0x10000000ULL;
        } else {
            load83(a, a->f0, (u8)k);
    func_800D427C(a, func_800D5438(a, 0), 1);
    func_800D427C(b, func_800D5438(a, 1), 1);

            SETACT(a, 0x53);
            a->flags |= 0x10000000ULL;
            SETACT(b, 0x54);
            b->flags |= 0x10000000ULL;
        }
        goto done;
    }
    return 0;
done:
    return 1;
}
