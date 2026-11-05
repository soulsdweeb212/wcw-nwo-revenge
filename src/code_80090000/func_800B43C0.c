/* @header
 * func_800B43C0
 * VRAM 0x800B43C0 | ROM 0x60B30 | size 0x2DC
 * asm: asm/nonmatchings/code_80090000/func_800B43C0.s
 */
#include "common.h"

typedef struct {
    u8 pad0[6];
    u16 unk6;
    u8 pad8[4];
} Pad43C0;

extern Pad43C0 D_8006E178[];
extern u16 D_8007EF30[];
extern s32 D_800E79A0[];
extern s32 D_800E7BF0[];
extern u8 D_800E7C60[][8];
extern u16 D_800EA0C8[];
extern s32 D_800EA318;
s32 func_800996A0(s32, s32);
void func_800B3BCC(s32, s32);
void func_800B3D58(void);
void func_8000DEE4(s32);

#define STEP(n)                                    \
    c = D_800E7BF0[i];                             \
    if (n < 0) {                                   \
        v = c ? 0x2F : 0x2D;                       \
    } else if (n >= 0x30) {                        \
        v = (c == 3) ? 0x2E : 0;                   \
    } else if (c == 0 && n >= 0x2E) {              \
        v = 0;                                     \
    } else {                                       \
        v = n;                                     \
        if (c == 3 && n < 0x2E) {                  \
            v = 0x2F;                              \
        }                                          \
    }

s32 func_800B43C0(void) {
    s32 i, s, c, n, k, v;
    u16 t;
    s32 r = 0xC;

    for (i = 0; i < 4; i++) {
        k = D_800E7BF0[i];
        s = -1;
        if (k < 0) {
            goto next;
        }
        t = D_8006E178[i].unk6;
        if (t & 0x8000) {
            switch (func_800996A0(D_800E79A0[i], i * 2) & 0xFF) {
            case 0xC6:
                if (D_800E7BF0[i] != 0) {
                    D_800E7C60[i][D_800E7BF0[i]] = 0;
                    if (--D_800E7BF0[i] == 0) {
                        D_800E79A0[i] = 0;
                    }
                }
                s = 0x403;
                break;
            case 0xC7:
                D_800E7C60[i][D_800E7BF0[i]] = 0;
                D_800E7BF0[i] = s;
                s = 0x408;
                break;
            default:
                func_800B3BCC(i, 0);
                if (++D_800E7BF0[i] == 3) {
                    D_800E79A0[i] = 0x2F;
                }
                s = 0x408;
                break;
            }
        } else if (t & 0x4000) {
            if (k != 0) {
                D_800E7C60[i][k] = 0;
                if (--D_800E7BF0[i] == 0) {
                    D_800E79A0[i] = 0;
                }
            }
            s = 0x403;
        } else {
            t = D_800EA0C8[i];
            if (t & 0xA00) {
                n = D_800E79A0[i] - 1;
                D_800E79A0[i] = n;
                STEP(n);
                D_800E79A0[i] = v;
                s = 0x409;
            } else if (t & 0x500) {
                n = D_800E79A0[i] + 1;
                D_800E79A0[i] = n;
                STEP(n);
                D_800E79A0[i] = v;
                s = 0x409;
            }
            func_800B3BCC(i, D_8007EF30[5] & 8);
        }
next:
        if (s >= 0) {
            func_8000DEE4(s);
        }
    }
    if (D_800E7BF0[0] < 0 && D_800E7BF0[1] < 0 && D_800E7BF0[2] < 0 && D_800E7BF0[3] < 0) {
        func_800B3D58();
        r = 0xD;
        D_800EA318 = 0x42A;
    }
    return r << 8;
}
