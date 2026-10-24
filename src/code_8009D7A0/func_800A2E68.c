#include "common.h"

typedef struct {
    u8 pad0[4];
    s16 f4;
    u8 pad1[6];
    s16 fC;
    u8 pad2[8];
    u16 f16;
    u8 pad3[8];
    u64 flags;
} Nw2Action800A2E68;

#define ACT800A2E68 ((Nw2Action800A2E68 *)D_800EB408)
#define FLAGS (*(u64 *)((u8 *)D_800EB408 + 0x20))

extern s32 D_800F9B14;
extern s32 D_800F9B0C;
extern u16 D_800FABE6;
s32 func_800D4D44(void *, s32, s32);
void func_800D427C(void *, s32, s32);
void func_800A7240(void *, s32, s32, u64);
s8 func_800A93C0(void);
void func_800A7D1C(void *, s32);
void func_800B68A0(void *, void *, void *);
void func_800D4AD0(void *);
void func_800D25D0(void *, f32);
s32 func_800D2B64(void *, f32, u16, s32);

void func_800A2E68(void) {
    func_800D25D0(D_800EB408, 4.0f);
    func_800D2B64(D_800EB408, 1.0f, 0, 2);
    switch (ACT800A2E68->fC) {
    case 0:
        func_800D427C(D_800EB408, (s16)func_800D4D44(D_800EB408, 2, 0), 3);
        ACT800A2E68->f16 = 0;
        ACT800A2E68->fC = ACT800A2E68->fC + 1;
        return;
    case 1:
        FLAGS |= 0x100000000000ULL;
        func_800A7240(D_800EB408, D_800F9B14, 0x155, 0x100000000ULL);
        ACT800A2E68->f16 = ACT800A2E68->f16 + 1;
        if ((s16)ACT800A2E68->f16 < 5) return;
        if ((s16)ACT800A2E68->f16 >= 100) ACT800A2E68->f16 = 100;
        if (D_800FABE6 & 0x10) {
            if (func_800A93C0() == 0) return;
        }
        func_800D427C(D_800EB408, (s16)func_800D4D44(D_800EB408, 1, D_800F9B0C), 3);
        ACT800A2E68->f16 = 100;
        ACT800A2E68->fC = ACT800A2E68->fC + 1;
        return;
    case 2:
        FLAGS |= 0x100000000000ULL;
        func_800A7240(D_800EB408, D_800F9B14, 0x155, 0x100000000ULL);
        ACT800A2E68->f16 = ACT800A2E68->f16 + 1;
        if ((s16)ACT800A2E68->f16 < 0x6A) return;
        func_800A6C48(D_800EB408, 1);
        return;
    case 3:
        func_800D427C(D_800EB408, 0xEC0, 3);
        ACT800A2E68->fC = ACT800A2E68->fC + 1;
        return;
    case 4:
        if (ACT800A2E68->f4 > 0) return;
        func_800A7D1C(D_800EB408, 2);
        func_800B68A0(D_800EB408, D_800EB408, D_800EB408);
        func_800D4AD0(D_800EB408);
        func_800A6C48(D_800EB408, 0x2B);
        return;
    }
}
