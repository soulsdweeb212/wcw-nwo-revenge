#include "common.h"

typedef struct {
    s32 f0;
    s16 f4, f6;
    s32 f8;
    s16 fC, fE;
    u8 pad10[0x10];
    u32 f20;
    u32 f24;
    u8 pad28[4];
    u32 f2C;
    u8 pad30[0x332];
    s8 f362;
    s8 f363;
} Nw2F408c;

s32 func_800D2BEC(void *, void *, void *, f32, u16, s32);
void func_800CE124(void *, s32, void *);
s32 func_800CE2C8(void *, s32, void *, void *, void *);
void func_800A7C40(void *, s8, s16);
void func_800A7F6C(void *, s32);
void func_800A837C(void *);
s16 func_800D5438(void *, s16);
void func_800D427C(void *, s16, s32);
void func_800D4AD0(void *);
void func_800A6C48(void *, s32);
extern s32 D_800EB40C;
extern void *D_800EB418;
extern u8 D_800F9B18[];
extern u8 D_800F9D10[];
extern s8 D_800FABE4;
extern s8 D_800FADB8;

#define P ((Nw2F408c *)D_800EB408)

void func_800A52CC(void) {
    s16 anim;
    s16 variant;
    u32 flags;
    u8 *m;

    switch (P->fC) {
    case 0:
        m = D_800F9B18 + D_800FADB8 * 16;
        func_800CE124(D_800EB408, D_800EB40C, m);
        flags = P->f2C;
        if (flags & 0x800) {
            anim = 0x8A;
        }
        if (flags & 0x1000) {
            anim = 0x8B;
        }
        if (flags & 0x2000) {
            anim = 0x8C;
        }
        func_800A7C40(D_800EB408, D_800FADB8, anim);
        flags = P->f2C;
        if (flags & 0x1800) {
            variant = (flags >> 14) & 1;
        }
        if (flags & 0x2000) {
            variant = (flags >> 6) & 1;
        }
        func_800D427C(D_800EB408, func_800D5438(D_800EB408, variant), 2);
        func_800A7F6C(D_800EB408, 0x41);
        func_800A837C(D_800EB408);
        P->fC = P->fC + 1;
    case 1:
        m = D_800F9B18 + D_800FADB8 * 16;
        if ((s8)func_800CE2C8(D_800EB408, D_800EB40C, D_800EB418,
                m, D_800F9B18 + D_800FABE4 * 16)) {
            P->fC = P->fC + 1;
        }
        break;
    case 2:
        func_800D2BEC(D_800EB408, D_800F9D10 + P->f362 * 0x3B0,
                D_800F9D10 + P->f363 * 0x3B0, 4.0f, 0, 0xFFFFE);
        if (P->f4 <= 0) {
            u64 *fp = (u64 *)((u8 *)D_800EB408 + 0x20);
            u64 flags2 = *fp;
            Nw2F408c *q;
            m = (u8 *)-1;
            P->f362 = (s32)m;
            q = P;
            flags2 &= 0xFFFFFFFFBFFFFFFFULL;
            flags2 |= (flags2 & ~flags2);
            *fp = flags2;
            q->f363 = (s32)m;
            func_800D4AD0(D_800EB408);
            func_800A6C48(D_800EB408, 0x2B);
        }
        break;
    }
}
