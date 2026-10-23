#include "common.h"

typedef struct {
    s32 f0;
    s16 f4;
    s16 f6;
    s32 f8;
    s16 fC;
    s16 fE;
    u8 pad10[0x10];
    u64 flags;
    u16 f28;
    u8 pad2A[6];
} Nw2Act13DC;

#define P ((Nw2Act13DC *)D_800EB408)

extern void *D_800EB408;
extern void *D_800EB40C;
extern u16 D_800F9D08[];
extern u16 D_800FADC6[];
extern s8 D_800FADB8;
extern u16 D_800FABE6;
s16 func_800D4D44(void *, s32, s32);
void func_800D427C(void *, s32, s32);
s8 func_800B4C60(void *, void *, u16, s32);

void func_800A13DC(void) {
    u16 flags;

    switch (P->fC) {
    case 0:
        if (P->f28 & 0x200) {
            func_800D427C(D_800EB408, (s16)func_800D4D44(D_800EB408, 0xA, 0), 1);
        } else {
            func_800D427C(D_800EB408, 0xE71, 2);
        }
        P->f28 = P->f28 | 0x1A0;
        P->fC++;
    case 1:
        func_800B4C60(D_800EB408, D_800EB40C, D_800FABE6, 1);
        if (P->f4 > 0) {
            return;
        }
        flags = P->f28;
        P->f28 = flags & 0xFCFF;
        if ((s16)D_800F9D08[D_800FADB8] <= 0) {
            D_800FADC6[D_800FADB8] = 0;
        } else {
            P->f28 = flags & 0xFC7F;
        }
        D_800F9D08[D_800FADB8]++;
        func_800A6C48(D_800EB408, 3);
        P->fC = 2;
        P->flags = P->flags & 0xFFFFFFFFFEFFFFFFULL;
        break;
    }
}
