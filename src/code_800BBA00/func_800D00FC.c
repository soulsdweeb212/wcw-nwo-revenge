#include "common.h"

void beginPairedEntityActions(void *source, s32 sourceAction, void *target, s32 targetAction);
void func_800A7C40(void *, s8, s16);
void func_800A7F6C(void *, s32);
s8 func_800D05E4(void *, void *);
extern u16 D_800E3C20[2][2][3];
extern u16 D_800E3C38[2][2][2];

#define W_(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define BY_(p, o) (*(s8 *)((u8 *)(p) + (o)))
#define F64_(p) (*(u64 *)((u8 *)(p) + 0x20))
#define FL W_(arg0, 0x2C)

s32 func_800D00FC(u8 *arg0, u8 *arg1, u16 arg2) {
    s32 s0;
    s8 i, j, k;

    if (FL & 0x40) {
        if (arg2 & 8) {
            beginPairedEntityActions(arg0, 0x74, arg1, 0x75);
            return 1;
        }
        if (arg2 & 0x20) {
            beginPairedEntityActions(arg0, 0x72, arg1, 0x73);
            return 1;
        }
    }
    if (FL & 0x300) {
        if (FL & 0x200000) {
            s0 = (FL & 0x100) ? 0x7E : 0x82;
            func_800A7C40(arg0, BY_(arg0, 0), (s16)s0);
            return 0;
        }
        if (arg2 & 0xC000) {
            if (FL & 0x100) {
                s0 = (FL & 2) ? 0x7D : 0x7C;
            } else {
                s0 = (FL & 2) ? 0x81 : 0x80;
            }
            func_800A7C40(arg0, BY_(arg0, 0), (s16)s0);
            func_800A7F6C(arg0, 0);
            if (func_800D05E4(arg0, arg1)) {
                return 3;
            }
            if (W_(arg0, 0x3AC) & 0x1800) {
                if ((F64_(arg0) & 0x80ULL)) {
                    beginPairedEntityActions(arg0, 0x4D, arg1, 0x4E);
                    return 1;
                }
            }
        ret0:
            return 0;
        }
        if (arg2 & 4) {
            if (FL & 0x100) {
                beginPairedEntityActions(arg0, 0xD, arg1, 0xE);
            } else {
                beginPairedEntityActions(arg0, 0xF, arg1, 0x10);
            }
            return 1;
        }
    }
    if (FL & 0x80) {
        if (FL & 0x200000) {
            func_800A7C40(arg0, BY_(arg0, 0), 0x6E);
            func_800A7F6C(arg0, 0);
            return 0;
        }
        if (arg2 & 0xC000) {
            if (FL & 2) {
                s0 = (arg2 & 0x8000) ? 0x64 : 0x69;
            } else {
                s0 = (arg2 & 0x8000) ? 0x5A : 0x5F;
            }
            func_800A7C40(arg0, BY_(arg0, 0), (s16)s0);
            func_800A7F6C(arg0, 0);
            return func_800D05E4(arg0, arg1) ? 3 : 0;
        }
    }
    if (arg2 & 4) {
        if (!(FL & 0x300)) {
            if (!(FL & 0x40)) {
                beginPairedEntityActions(arg0, 0xB, arg1, 0xC);
                return 1;
            }
        }
    }
    if (FL & 0x400) {
        if ((FL & 0x200003) == 0x200003) {
            s0 = (FL & 0x40) ? 0x41 : 0x3A;
            func_800A7C40(arg0, BY_(arg0, 0), (s16)s0);
            func_800A7F6C(arg0, 0);
            return 0;
        }
        if ((FL & 1) && (arg2 & 0xC000) == 0xC000 && !(F64_(arg1) & 9)) {
            s0 = (FL & 0x40) ? 0x43 : 0x3C;
            func_800A7C40(arg0, BY_(arg1, 0), (s16)s0);
            func_800A7F6C(arg0, 0);
            return 0;
        }
        if ((*(u64 *)(*(u8 **)(arg0 + 0x364) + 0x38) & 1) && ((FL & 0x42) == 2) && (arg2 & 0x4000)) {
            beginPairedEntityActions(arg0, 0x4B, arg1, 0x4C);
            return 1;
        }
        if (!(arg2 & 0xC000)) {
            return 2;
        }
        if (FL & 0x40) {
            u8 jj, kk;
            if (arg2 & 0x8000) {
                jj = 0;
            } else {
                jj = 1;
            }
            if (arg2 & 0xF00) {
                kk = 1;
            } else {
                kk = 0;
            }
            s0 = D_800E3C38[(FL >> 1) & 1][jj][kk];
        } else {
            i = (FL >> 1) & 1;
            if (arg2 & 0x8000) {
                j = 0;
            } else {
                j = 1;
            }
            if (arg2 & 0x800) {
                k = 1;
            } else {
                k = (arg2 >> 9) & 2;
            }
            s0 = D_800E3C20[i][j][k];
        }
        func_800A7C40(arg0, BY_(arg0, 0), (s16)s0);
        if (!(W_(arg0, 0x3AC) & 0x1800)) {
            goto L5A0;
        }
        if ((F64_(arg0) & 0x40ULL)) {
            func_800A7F6C(arg0, 0);
            if (func_800D05E4(arg0, arg1)) {
                return 3;
            }
            beginPairedEntityActions(arg0, 0x4D, arg1, 0x4E);
            return 1;
        }
        func_800A7C40(arg0, BY_(arg0, 0), (s16)(s0 + 5));
L5A0:
        func_800A7F6C(arg0, 0);
        if (!func_800D05E4(arg0, arg1)) {
            goto ret0;
        }
        return 3;
    }
    return 2;
}
