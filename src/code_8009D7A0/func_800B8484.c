/* @header
 * func_800B8484
 * VRAM 0x800B8484 | ROM 0xAB924 | size 0x810
 * asm: asm/nonmatchings/code_8009D7A0/func_800B8484.s
 */
#include "common.h"

typedef struct {
    u8 p0[2];
    s16 f2;
    u8 p4[6];
    s16 fA;
    u8 pC[4];
    u16 f10;
    u8 p12[2];
    u16 f14;
    u8 p16[0xA];
    u64 flags;
    u8 p28[0x329];
    u8 f351;
    u8 p352[0x1C];
    u8 f36E;
    u8 p36F[0x41];
} Rec8484;

extern Rec8484 D_800F9D10[];
extern u16 D_8007E280;
extern u16 D_800E397C[];

void playEntitySound(s16, s16);
s8 func_800D4198(s16);
void func_800B9730(void *, void *, s32, s32);
void func_800B9D60(void *, void *, s32);

s32 func_800B8484(s32 mode) {
    s8 a[4];
    s8 b[4];
    s8 c[4];
    s8 d[4];
    s8 e[4];
    s8 buf1[8];
    s8 buf2[8];
    s16 sumA;
    s16 na;
    s16 cntA;
    s16 sumB;
    s16 nb;
    s16 cntB;
    s16 i;
    u16 fw;

    sumA = 0;
    na = 0;
    cntA = 0;
    sumB = 0;
    nb = 0;
    cntB = 0;
    for (i = 0; i < 4; i++) {
        a[i] = -1;
        b[i] = -1;
        c[i] = -1;
        d[i] = -1;
        e[i] = -1;
    }
    for (i = 0; i < 4; i++) {
        if (D_800F9D10[i].f2 == -1) {
            continue;
        }
        if (!(D_800F9D10[i].flags & 0x200)) {
            continue;
        }
        if (D_8007E280 & 0x400) {
            if (D_800F9D10[i].flags & 0x100) {
                if (D_800F9D10[i].fA == 0x8F) {
                    return 0;
                }
                b[nb] = i;
                nb++;
            } else {
                if (D_800F9D10[i].f36E == 2) {
                    return 0;
                }
                a[na] = i;
                na++;
            }
        }
        if (D_8007E280 & 0x100) {
            if (a[0] == -1) {
                a[0] = i;
                sumA = D_800F9D10[i].f10 + D_800F9D10[i].f14;
                if (D_800F9D10[i].flags & 0x100) {
                    na++;
                }
            } else {
                b[0] = i;
                sumB = D_800F9D10[i].f10 + D_800F9D10[i].f14;
                if (D_800F9D10[i].flags & 0x100) {
                    nb++;
                }
            }
        }
        if (D_8007E280 & 0x200) {
            if (D_8007E280 & D_800E397C[i]) {
                a[cntA] = i;
                sumA += D_800F9D10[i].f10 + D_800F9D10[i].f14;
                cntA++;
                if ((D_800F9D10[i].flags & 0x200) && (D_800F9D10[i].flags & 0x100)) {
                    d[na] = i;
                    na++;
                }
            } else {
                b[cntB] = i;
                sumB += D_800F9D10[i].f10 + D_800F9D10[i].f14;
                cntB++;
                if ((D_800F9D10[i].flags & 0x200) && (D_800F9D10[i].flags & 0x100)) {
                    e[nb] = i;
                    nb++;
                }
            }
        }
    }
    fw = D_8007E280;
    if (fw & 0x200) {
        sumA = sumA / cntA;
        sumB = sumB / cntB;
    }
    if (mode == 0x10000) {
        if (fw & 0x400) {
            playEntitySound(0, 2);
            i = 0;
            while (b[i] != -1 && i < 4) {
                buf1[0] = D_800F9D10[b[i]].f351;
                buf1[1] = -1;
                buf2[0] = b[i];
                buf2[1] = -1;
                buf2[2] = -1;
                func_800B9D60(buf1, buf2, 0x10000);
                i++;
            }
            switch (na) {
            case 0:
                func_800B9730(c, c, mode | 0x100800, 0);
                return 1;
            case 1:
                func_800B9730(a, b, mode | 0x100000, 0);
                return 1;
            default:
                func_800B9730(c, b, mode, 0);
                return 0;
            }
        }
        if (fw & 0x100) {
            if (na == nb) {
                if (fw & 0x800) {
                    if (sumA > sumB || (sumA == sumB && func_800D4198(500))) {
                        func_800B9730(a, b, 0x120400, 1);
                    } else {
                        func_800B9730(b, a, 0x120400, 1);
                    }
                } else {
                    func_800B9730(c, c, 0x120800, 1);
                }
            } else if (na < nb) {
                func_800B9730(a, b, 0x110000, 1);
            } else {
                func_800B9730(b, a, 0x110000, 1);
            }
            return 1;
        }
        if (fw & 0x200) {
            if (na != 0 && nb != 0) {
                if (fw & 0x800) {
                    if (sumA > sumB || (sumA == sumB && func_800D4198(500))) {
                        func_800B9730(a, b, 0x120400, 1);
                    } else {
                        func_800B9730(b, a, 0x120400, 1);
                    }
                } else {
                    func_800B9730(c, c, 0x120800, 1);
                }
                return 1;
            }
            if (na == 0) {
                func_800B9730(a, b, 0x110000, 1);
            }
            if (nb == 0) {
                func_800B9730(b, a, 0x110000, 1);
            }
            return 1;
        }
    }
    if (mode == 0x4000) {
        if ((D_8007E280 & 0xC00) != 0x800) {
            func_800B9730(c, c, 0x104800, 1);
        } else if (sumA > sumB || (sumA == sumB && func_800D4198(500))) {
            func_800B9730(a, b, 0x104400, 1);
        } else {
            func_800B9730(b, a, mode | 0x100400, 1);
        }
        return 1;
    }
    return 1;
}
