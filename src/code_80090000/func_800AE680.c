/* @header
 * func_800AE680
 * VRAM 0x800AE680 | ROM 0x5ADF0 | size 0x3FC
 * asm: asm/nonmatchings/code_80090000/func_800AE680.s
 */
#include "common.h"

typedef struct { u8 pad0[0x22]; u16 f22; u8 pad24[0x148 - 0x24]; } El;
typedef struct { u8 pad0[0x48]; u8 name[4][9]; } Names;
typedef struct { u8 pad0[6]; u16 btn; u8 pad8[4]; } Pad;
extern El *D_800E8E74;
extern s16 D_80038A90;
extern s32 D_800E9F98[4][16];
extern Names D_8007E8C0;
extern s32 D_800E79A0[];
extern s32 D_800E7BF0[];
extern s32 D_800D5F1C;
extern u16 D_800EA0C8[];
extern volatile Pad D_8006E178[]; /* controller state, read fresh each time */
void func_8000DEE4(s32);
void func_800A8F98(s32);
void func_800BAC58(u8 *, s32);
void func_800B9F18(void);

s32 func_800AE680(void) {
    s32 ret;
    El *e;
    s32 left = 4;
    s32 i, k, n, m, snd, ch, old;
    s32 ok[4];
    s32 pad[4]; /* placeholder: the ROM has 16 unused bytes above ok[] */
    s32 *p;
    u16 b;

    e = D_800E8E74;
    ret = D_80038A90;
    for (i = 0; i < 4; i++, e++) {
        ok[i] = 0;
        k = D_800E7BF0[i];
        snd = -1;
        if (i >= D_800D5F1C) {
            left--;
            D_800E7BF0[i] = 1;
            D_800E79A0[i] = 0;
            ok[i] = 1;
            continue;
        }
        b = D_800EA0C8[i];
        if (b & 0xC00) {
            if (b & 0x400) {
                D_800E7BF0[i] = k + 1;
            } else {
                D_800E7BF0[i] = k - 1;
            }
            if (D_800E7BF0[i] < 0) {
                D_800E7BF0[i] = 9;
            }
            if (D_800E7BF0[i] >= 10) {
                D_800E7BF0[i] = 0;
            }
            if (k == D_800E7BF0[i]) {
                goto done;
            }
            snd = 0x401;
            ok[i] = 1;
        } else {
            b = D_8006E178[i].btn;
            if ((b & 0x1000) || (k <= 0 && (b & 0x4000))) {
                if (k == 1) {
                    left -= 2;
                } else {
                    snd = 0x401;
                    D_800E7BF0[i] = 1;
                    D_800E79A0[i] = 0;
                    ok[i] = 1;
                }
            } else {
                switch (D_800E7BF0[i]) {
                case 0:
                    if (D_8006E178[i].btn & 0x8000) {
                        func_800A8F98(i);
                        snd = 0x403;
                        ok[i] = 1;
                    }
                    break;
                case 1:
                    left--;
                    /* the do-while's loop notes keep `left--` ahead of the pad read (it goes in the beql slot) */
                    do {
                        if (D_8006E178[i].btn & 0xD000) {
                            left--;
                        }
                    } while (0);
                    break;
                default:
                    b = D_8006E178[i].btn;
                    if (b & 0x8000) {
                        ch = 0;
                    } else if (b & 0x4000) {
                        ch = 1;
                    } else if (b & 0x20) {
                        ch = 2;
                    } else if (b & 0x10) {
                        ch = 3;
                    } else if (b & 8) {
                        ch = 4;
                    } else if (b & 2) {
                        ch = 6;
                    } else if (b & 1) {
                        ch = 7;
                    } else {
                        ch = (b & 4) ? 5 : -1;
                    }
                    if (ch >= 0) {
                        n = D_800E7BF0[i] - 2;
                        old = D_8007E8C0.name[i][n];
                        D_8007E8C0.name[i][n] = ch;
                        for (m = 0; m < 8; m++) {
                            if (m != n && D_8007E8C0.name[i][m] == ch) {
                                D_8007E8C0.name[i][m] = old;
                                break;
                            }
                        }
                        ok[i] = 1;
                        snd = 0x408;
                    }
                    break;
                }
            }
        }
    done:
        e->f22 = D_800E7BF0[i] - D_800E79A0[i];
        if (snd >= 0) {
            func_8000DEE4(snd);
        }
    }
    for (i = 0; i < 4; i++) {
        if (ok[i]) {
            s32 c, d;
            p = D_800E9F98[i];
            for (c = 0, d = D_800E79A0[i]; c < 11; c++, d++, p++) {
                *p = d << 4;
                if (d >= 2) {
                    *p = (d << 4) | D_8007E8C0.name[i][d - 2];
                }
            }
        }
    }
    if (left < 0) {
        func_8000DEE4(0x42A);
        func_800BAC58(D_8007E8C0.name[0], 0);
        func_800BAC58(D_8007E8C0.name[1], 1);
        func_800BAC58(D_8007E8C0.name[2], 2);
        func_800BAC58(D_8007E8C0.name[3], 3);
        func_800B9F18();
        ret = 0x200;
    }
    return ret;
}
