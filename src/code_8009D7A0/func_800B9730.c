#include "common.h"

typedef struct {
    u16 f0;
    u8 pad2[0xE];
    u64 flags;
    u8 pad18[0x1C];
    u16 f34;
    u8 pad36[0x37A];
} Rec9730;

typedef struct {
    s32 v;
    u8 pad[8];
} Slot9730;

typedef struct {
    u8 pad0[0x18];
    u16 f18;
    u16 f1A;
    s16 f1C;
    u8 pad1E[2];
    Slot9730 slots[6];
    u8 pad68[4];
    s16 f6C;
} Blk9730;

extern Rec9730 D_800F9D20[];
extern u8 D_8007E228[];
extern Blk9730 D_8007E8C0;
extern u16 D_8007E92C;
extern u16 D_800E3984[];
extern u16 D_800E398C[];
extern u8 D_800E39A4[];
extern s16 D_800EB470;
extern u16 D_800FAF84;
extern u16 D_800FAF86;
extern s8 D_800FABDC;
extern f64 D_800E5698;

void func_800B9D60(s8 *, s8 *, s32);
s32 func_800BA6A8(s8);
void func_800BC7D0(s32);
void func_80096CC0(s32);

void func_800B9730(s8 *arg0, s8 *arg1, s32 arg2, s32 arg3) {
    s16 cnt0;
    s16 sum0;
    s16 sum1;
    s16 cnt1;
    s16 i;

    if (arg3 << 24) {
        func_800B9D60(arg0, arg1, arg2);
    }
    D_8007E8C0.f6C = 0;
    D_8007E8C0.f18 = D_800FAF84;
    D_8007E8C0.f1A = D_800FAF86;
    if (*arg1 == -1) {
        D_8007E8C0.f1C = -1;
    } else {
        D_8007E8C0.f1C = D_800F9D20[*arg1].f34;
    }
    D_800FABDC = *arg0;
    D_8007E848 = arg2;
    if ((D_8007E280 & 0x200) && *arg0 != -1 && *arg1 != -1) {
        if (D_800F9D20[*arg0].flags & 0x200000000ULL) {
            D_8007E848 = arg2 | 0x100;
        } else {
            D_8007E848 = arg2 | 0x200;
        }
    }
    D_800F9D20[0].flags &= ~0x4000ULL;
    D_800F9D20[1].flags &= ~0x4000ULL;
    D_800F9D20[2].flags &= ~0x4000ULL;
    D_800F9D20[3].flags &= ~0x4000ULL;

    cnt0 = 0;
    sum0 = 0;
    for (i = 0; i < 2; i++) {
        if (*arg0 != -1) {
            D_8007E848 |= D_800E3984[*arg0];
            D_800F9D20[*arg0].flags |= 0x4000ULL;
            cnt0++;
            sum0 += D_800F9D20[*arg0].f0;
            arg0++;
        }
    }
    if (cnt0 != 0) {
        sum0 /= cnt0;
    }

    cnt1 = 0;
    sum1 = 0;
    for (i = 0; i < 3; i++) {
        if (*arg1 != -1) {
            D_8007E848 |= D_800E398C[*arg1];
            D_800F9D20[*arg1].flags |= 0x8000ULL;
            if ((func_800BA6A8(*arg1) << 24) == 0) {
                D_800F9D20[*arg1].flags &= ~0x200ULL;
            } else if (D_8007E280 & 0x400) {
                D_800F9D20[*arg1].flags |= 0x10ULL;
            }
            cnt1++;
            sum1 += D_800F9D20[*arg1].f0;
            arg1++;
        }
    }
    if (cnt1 != 0) {
        sum1 /= cnt1;
    }

    D_8007E8C0.slots[D_8007E8C0.f6C].v = D_8007E848;
    func_800BC7D0(D_8007E848);
    D_800EB470 = sum0 - sum1;
    if (D_800EB470 < 0) {
        D_800EB470 = 0;
    }
    D_800EB470 = (s16)(s32)((f64)D_800EB470 * D_800E5698);
    if (arg2 & 0x100000) {
        D_8007E228[0x8C] = 0;
        if ((arg2 & 0xB000) && (D_800F9D20[D_800FABDC].flags & 0x4000000000000000ULL)) {
            D_8007E228[0x8C] = D_800E39A4[D_800FABDC];
        }
    }
    D_8007E92C++;
    func_80096CC0(D_8007E848);
}
