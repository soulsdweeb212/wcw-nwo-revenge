/* @header
 * func_800C72DC
 * VRAM 0x800C72DC | ROM 0xBA77C | size 0x4B0
 * asm: asm/nonmatchings/code_800BBA00/func_800C72DC.s
 */
#include "common.h"

typedef struct {
    u8 pad0[4];
    s16 f4;
    s16 f6;
    u8 pad8[4];
    s16 fC;
    u8 padE[8];
    s16 f16;
    u8 pad18[8];
    u64 flags;
    u8 pad28[8];
    u32 f30;
    u8 pad34[8];
    s16 f3C;
    u8 pad3E[0x1A];
    s32 f58;
} Nw2F5C;

typedef struct {
    u8 pad0[0x386];
    u16 f386;
    u8 pad388[0x13];
    s8 f39B;
    u8 pad39C[5];
    s8 f3A1;
    u8 pad3A2[0xA];
    u32 f3AC;
} Nw2F9B64;

extern Nw2F5C *D_800FAF5C;
extern Nw2F9B64 *D_800F9B64;
extern s32 D_800E3CA0[];

void func_800B68A0(void *, void *, void *);
void func_800A6C48(void *, s32);
void func_800A7364(void *);
void beginEntityActionA8D8C(void *);
void func_800D427C(void *, s16, s32);
void func_800D4AD0(void *);
void func_800D25D0(void *, f32);
s32 func_800D2B64(void *, f32, u16, s32);
s8 func_800C2634(void *, u16);
s8 func_800B71F8(void *, s32, s32);
s16 func_800B6DEC(void *, s32, s32);
s16 func_800C778C(void *);

void func_800C72DC(void) {
    s16 s0;
    u32 flags;
    u16 r;
    s32 b;

    switch (D_800FAF5C->fC) {
    case 0:
        if ((s32)D_800FAF5C->f30 >= 0) {
            func_800B68A0(D_800F9B64, D_800F9B64, D_800FAF5C);
        }
        flags = D_800FAF5C->f30;
        if (flags & 0x800) {
            switch ((s16)(D_800F9B64->f386 - 0xD1)) {
            case 0:
            case 1:
            case 7:
            case 12:
            case 13:
            case 15:
            case 16:
            case 17:
            case 19:
            case 22:
            case 23:
            case 24:
            case 25:
                flags = D_800FAF5C->f30 | 0x20000;
                D_800FAF5C->f30 = flags;
                if (D_800F9B64->f3AC & 0x40) {
                    D_800FAF5C->f30 = flags | 0x20000000;
                    s0 = 0x1058;
                } else {
                    D_800FAF5C->f30 = flags | 0x10000000;
                    s0 = 0x1049;
                }
                break;
            case 9:
            case 10:
                s0 = 0x1058;
                D_800FAF5C->f30 |= 0x20020000;
                break;
            case 4:
            case 5:
            case 6:
            case 8:
            case 18:
                D_800FAF5C->f30 |= 0x90010000;
                func_800A6C48(D_800FAF5C, 0x2F);
                return;
            }
            if (D_800FAF5C->f30 & 0x1000) {
                s0++;
            }
            func_800D427C(D_800FAF5C, s0, 3);
            D_800FAF5C->fC++;
            return;
        }
        if (flags & 0x8000) {
            switch (D_800F9B64->f39B) {
            case 0:
                s0 = 0x102E;
                break;
            case 1:
                s0 = 0x1030;
                break;
            case 2:
                s0 = 0x1032;
                break;
            case 3:
                s0 = 0x1034;
                break;
            case 4:
                s0 = 0x1063;
                break;
            case 5:
                s0 = 0x1036;
                break;
            }
        }
        if (D_800FAF5C->f30 & 0x20000) {
            s0 = func_800C778C(D_800FAF5C);
        }
        if (D_800FAF5C->f30 & 0x80000) {
            b = D_800F9B64->f3A1;
            s0 = b + 0x106D;
            if (b == 0) {
                s0 = func_800C778C(D_800FAF5C);
            }
        }
        flags = D_800FAF5C->f30;
        if (flags & 0x40000) {
            s0 = (s8)*(u8 *)&D_800F9B64->f3A1 + 0x1055;
        }
        if (flags & 0x100000) {
            s0 = 0xF00;
        }
        if (flags & 0x200000) {
            s0 = 0xEFE;
        }
        if (flags & 0x4000000) {
            if (func_800B71F8(D_800FAF5C, 0, 0x12)) {
                s0 = 0xEFE;
            } else {
                s0 = 0xF03;
            }
        }
        flags = D_800FAF5C->f30;
        if (flags & 0x8000000) {
            s0 = 0x1056;
        }
        if (flags & 0x2400000) {
            D_800FAF5C->f58 = D_800E3CA0[D_800FAF5C->f3C];
            if (D_800FAF5C->f30 & 0x2000000) {
                D_800FAF5C->f16 = func_800B6DEC(D_800FAF5C, 0, 0);
                s0 = 0x10B2;
            } else {
                s0 = 0x10AB;
            }
            func_800A7364(D_800FAF5C);
            func_800D427C(D_800FAF5C, s0, 2);
        } else {
            if (flags & 0x1800000) {
                func_800A6C48(D_800FAF5C, 0x62);
                return;
            }
            if (!(flags & 0xE7E0000)) {
                if (flags & 0x1000) {
                    s0++;
                }
            }
            if (s0 == 0xF03) {
                func_800D427C(D_800FAF5C, 0xF03, 0);
            } else {
                func_800D427C(D_800FAF5C, s0, 3);
            }
        }
        D_800FAF5C->fC++;
        break;
    case 1:
        if (D_800FAF5C->f30 & 0x4000000) {
            goto l7754;
        }
        func_800D25D0(D_800FAF5C, 4.0f);
        if (D_800FAF5C->f30 & 0x4000000) {
            goto l7754;
        }
        r = func_800D2B64(D_800FAF5C, 2.0f, 0, 0xFFFFE);
        if (r == 0) {
            goto l7754;
        }
        if (!(D_800FAF5C->flags & 0x40)) {
            goto l7754;
        }
        if (!(D_800FAF5C->f30 & 0x80E0000)) {
            goto l7754;
        }
        if (D_800FAF5C->f6 >= 5) {
            goto l7754;
        }
        if (!func_800C2634(D_800FAF5C, r)) {
            goto l7754;
        }
        func_800A6C48(D_800FAF5C, 0x62);
        break;
    l7754:
        if (D_800FAF5C->f4 > 0) {
            break;
        }
        func_800D4AD0(D_800FAF5C);
        beginEntityActionA8D8C(D_800FAF5C);
        break;
    }
}
