#include "common.h"

extern u16 D_800E4000[];
extern u16 D_800E4008[];
s16 findBoundaryQuadrant(void *, s32, s32);
s16 func_800D65D0(void *, u16);
s32 func_800DF924(void *, void *);
s32 func_800E07DC(void *);
void func_800E212C(void *);
void func_800A6C48(void *, s32);

typedef struct {
    u8 pad0[0xC];
    s16 fC;
    u8 padE[0x20 - 0xE];
    u64 flags;
    u8 pad28[0x3C - 0x28];
    s16 f3C;
    s16 f3E;
    u8 pad40[0x364 - 0x40];
    u8 *f364;
} Nw2EntDF5C4;

typedef struct {
    u8 pad0[0x38];
    u64 flags;
} Nw2AttDF5C4;

#define E ((Nw2EntDF5C4 *)e)
#define OTHER ((Nw2EntDF5C4 *)other)
#define ATT ((Nw2AttDF5C4 *)E->f364)

s8 func_800DF5C4(u8 *e, u8 *other, u16 mask, u16 val, u8 a4, u16 a5) {
    s16 idx;

    if (E->flags & 0x40) {
        idx = findBoundaryQuadrant(e, 0, 1);
        E->f3E = idx;
        if ((s16)idx == -1) {
            goto L7F4;
        }
        if ((mask & 4) && (D_800E4000[idx] & val) && (s8)func_800E07DC(e)) {
            if ((s8)func_800DF924(e, other)) {
                goto L8DC;
            }
            if (!(E->flags & 1)) {
                func_800A6C48(e, 0x18);
                return 1;
            }
        }
        if ((mask & 0x8000) && (val & 0xF00) == D_800E4000[E->f3E] && (OTHER->flags & 0x40) &&
            (OTHER->flags & 0x400000) && (ATT->flags & 0x400000)) {
            func_800E212C(e);
            func_800A6C48(e, 0x66);
            return 1;
        }
        if (a4 && (val & 0xF00) == D_800E4000[E->f3E] && (s8)func_800E07DC(e) && !(E->flags & 1)) {
            func_800E212C(e);
            func_800A6C48(e, 0x18);
            return 1;
        }
    }
L7F4:
    if ((mask & 4) && (E->flags & 0x80) && (s8)func_800DF924(e, other)) {
        if (val & (a5 & D_800E4008[E->f3C])) {
            u16 s1v;
            E->flags &= 0xFFFFFF7FFFFFFFFFULL;
            s1v = E->f3C;
            if ((s16)func_800D65D0(e, a5) == 1) {
                E->flags |= 0x8000000000ULL;
                s1v = (s1v - 1) & 3;
            }
            E->f3E = s1v;
            if ((s8)func_800E07DC(e)) {
            L8DC:
                func_800A6C48(e, 0xA);
                E->fC = 1;
                return 1;
            }
        }
    }
    return 0;
}
