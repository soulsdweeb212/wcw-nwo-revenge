/* @header
 * func_800C0BDC
 * VRAM 0x800C0BDC | ROM 0x6D34C | size 0x55C
 * asm: asm/nonmatchings/code_80090000/func_800C0BDC.s
 */
#include "common.h"

typedef struct { u8 pad0[2]; u16 flags; u16 n; } Scene;
typedef struct { u16 n; u16 pad2; s16 v[6]; } Key;
typedef struct { u8 pad0[0x20]; } Shot;

extern Shot D_800D4930[];
extern s32 D_800E79C4, D_800DF3AC, D_800DF3B0, D_80038A8C, D_800E74C8;
extern Scene *D_800DF31C;
extern s32 D_800DF314, D_800DF308, D_800DF310;
extern s32 D_800E9F70, D_800DF328, D_800DF324, D_800E74E8;
extern Key **D_800DF320;
extern f32 D_800E74F8[7];
extern f64 D_800D6C58;
void func_800BF9B8(Shot *);

void func_800C0BDC(void) {
    s32 k;
    Key *e;

    func_800BF9B8(&D_800D4930[D_800E79C4]);
    if (D_800DF3AC != 0) {
        if (D_800DF3AC < 0) {
            D_800DF3AC += D_800DF3B0;
            if (D_800DF3AC > 0) {
                D_800DF3AC = 0;
            }
        } else {
            D_800DF3AC -= D_800DF3B0;
            if (D_800DF3AC < 0) {
                D_800DF3AC = 0;
            }
        }
        if (D_800DF3AC == 0 && D_80038A8C == 0) {
            D_800E74C8 = 0;
        }
    }
    if (D_800DF31C->n != 0) {
        switch (D_800DF31C->flags & 0xF) {
        case 7:
        case 8:
            k = 4;
            break;
        case 1:
        case 2:
            k = 8;
            break;
        case 3:
        case 4:
            k = 0x10;
            break;
        case 5:
        case 6:
            k = 0x20;
            break;
        default:
            k = 0;
            break;
        }
        if (k != 0 && D_800DF31C->n - k < D_800DF314) {
            D_800DF3B0 = 0x100 / k;
            D_800DF3AC = ((D_800DF314 - (D_800DF31C->n - k)) << 8) / k;
            if (D_800DF31C->flags & 1) {
                D_800DF3AC = -D_800DF3AC;
            }
        }
        if (D_800DF314 == D_800DF31C->n) {
            if (D_800DF31C->flags & 0x40) {
                D_80038A8C = -1;
            } else {
                D_800DF308++;
            }
        }
        if (D_800DF314 + 1 == D_800DF31C->n) {
            D_800DF310 = D_800DF308 + 1;
        }
    }
    if (D_800DF3AC != 0 && D_80038A8C == 0) {
        D_800E74C8 = D_800DF3AC;
    }
    if ((u32)D_800E9F70 < 9) {
        e = &(*D_800DF320)[D_800DF328];
        if (e->n != 0) {
            D_800E74F8[0] = e[0].v[0] + (f64)((e[1].v[0] - e[0].v[0]) * D_800DF324) / e->n;
            D_800E74F8[1] = e[0].v[1] + (f64)((e[1].v[1] - e[0].v[1]) * D_800DF324) / e->n;
            D_800E74F8[2] = e[0].v[2] + (f64)((e[1].v[2] - e[0].v[2]) * D_800DF324) / e->n;
            D_800E74F8[4] = e[0].v[3] + (f64)((e[1].v[3] - e[0].v[3]) * D_800DF324) / e->n;
            D_800E74F8[5] = e[0].v[4] + (f64)((e[1].v[4] - e[0].v[4]) * D_800DF324) / e->n;
            D_800E74F8[6] = e[0].v[5] + (f64)((e[1].v[5] - e[0].v[5]) * D_800DF324) / e->n;
        } else {
            D_800E74F8[0] = e->v[0];
            D_800E74F8[1] = e->v[1];
            D_800E74F8[2] = e->v[2];
            D_800E74F8[4] = e->v[3];
            D_800E74F8[5] = e->v[4];
            D_800E74F8[6] = e->v[5];
        }
        D_800E74F8[3] = D_800E74E8 * D_800D6C58;
    }
    D_800DF314++;
}
