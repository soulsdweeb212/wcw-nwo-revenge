/* @header
 * func_800B3640
 * VRAM 0x800B3640 | ROM 0x5FDB0 | size 0x380
 * asm: asm/nonmatchings/code_80090000/func_800B3640.s
 */
#include "common.h"

typedef struct { s32 f0; u8 pad4[0xC]; } Ent;
typedef struct { s32 w[10]; s32 f28; } Sc;
extern struct { u8 pad0[8]; u16 mode; u8 padA[0x26]; u16 *p30; } D_8007EF30;
extern Ent D_800EA0D8[2][10];
extern s32 D_800DC830[];
extern s32 D_800DC850[];
extern s32 D_800E7BF0[];
extern Sc D_800EA220[];
extern s32 D_800EA098[];
void func_800BA940(Ent *, s32);
void func_80021C40(void *, void *, s32);

void func_800B3640(void) {
    s32 score[14];
    s32 order[14];
    s32 i, j, k, n, v, t;

    if (D_8007EF30.mode & 0x8000) {
        n = D_8007EF30.p30[4];
    } else {
        switch (D_8007EF30.mode & 0xF0) {
        case 0x40:
            n = 7;
            break;
        case 0x20:
            n = 1;
            break;
        case 0x80:
            n = 8;
            break;
        default:
            n = 0;
            break;
        }
    }
    func_800BA940(D_800EA0D8[0], (n << 4) | 0xF);
    for (i = 0; i < 10; i++) {
        score[i] = D_800EA0D8[0][i].f0;
        order[i] = i;
    }
    for (k = 0; k < 4; k++) {
        v = D_800DC850[k];
        if (v >= 0 && D_800DC830[k] >= 0 && D_800E7BF0[D_800DC830[k]] >= 0 && !(v == 3 && (D_8007EF30.mode & 0x20)) &&
            !(v == 1 && (D_8007EF30.mode & 0x60))) {
            score[10 + k] = D_800EA220[v].f28;
            order[10 + k] = D_800DC830[k] | 0x80;
        } else {
            score[10 + k] = 0;
        }
    }
    for (i = 0; i < 14; i++) {
        for (j = i; j < 14; j++) {
            if (score[j] > score[i]) {
                t = score[j];
                score[j] = score[i];
                score[i] = t;
                t = order[j];
                order[j] = order[i];
                order[i] = t;
            }
        }
    }
    func_80021C40(D_800EA0D8[0], D_800EA0D8[1], 0xA0);
    for (i = 0; i < 10; i++) {
        if (order[i] & 0x80) {
            D_800EA098[order[i] & 0x7F] = i;
        } else {
            func_80021C40(&D_800EA0D8[1][order[i]], &D_800EA0D8[0][i], 0x10);
        }
    }
    if ((D_8007EF30.mode & 0x60) && D_800DC830[0] != D_800DC830[1] && D_800EA098[D_800DC830[0]] >= 0) {
        D_800EA098[D_800DC830[1]] = D_800EA098[D_800DC830[0]];
    }
    if ((D_8007EF30.mode & 0x20) && D_800DC830[2] != D_800DC830[3] && D_800EA098[D_800DC830[2]] >= 0) {
        D_800EA098[D_800DC830[3]] = D_800EA098[D_800DC830[2]];
    }
    for (i = 0; i < 4; i++) {
        if (D_800EA098[i] < 0) {
            D_800E7BF0[i] = -1;
        }
    }
}
