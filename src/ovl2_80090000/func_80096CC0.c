/* @header
 * func_80096CC0
 * VRAM 0x80096CC0 | ROM 0x8A160 | size 0x16C
 * asm: asm/nonmatchings/ovl2_80090000/func_80096CC0.s
 */
#include "common.h"

typedef struct { s32 flags; } St;

typedef struct {
    u8 pad0[0x14];
    St *st;
    u8 pad18[0xC4];
} Sprite;

void func_8009786C(s32);
extern u8 D_8007E228[];
extern Sprite D_800E7950[];
extern s16 D_800E91CC;
extern s16 D_800E91CE;
extern s16 D_800E91D0;
extern s16 D_800F99B6;
extern s16 D_800F9A9C;

void func_80096CC0(s32 btn) {
    s16 s;
    u32 i;

    if (D_800F99B6 == 0) {
        D_800E91CE = 0x1E;
        D_800E91D0 = 0;
        s = -1;
        if (btn & 0x4000) {
            D_800E91CC = 4;
            s = 10;
        } else if (btn & 0x800) {
            D_800E91CC = 6;
            D_800E91CE = 0;
            s = 10;
        } else if (btn & 0x2000) {
            D_800E91CC = 0;
            s = 3;
        } else if (btn & 0x1000) {
            D_800E91CC = 1;
            s = 5;
        } else if (btn & 0x8000) {
            D_800E91CC = 3;
            s = 10;
        } else if (btn & 0xD0000) {
            D_800E91CC = 2;
            s = 7;
        } else if (btn & 0x20000) {
            D_800E91CC = 5;
            s = 7;
        }
        if (s >= 0) {
            func_8009786C(s);
        }
        if (*(u32 *)(D_8007E228 + 0x620) & 0x100000) {
            D_800F99B6 = 1;
            D_800F9A9C = 1;
            if (!(D_800E7950[0].st->flags & 0x80)) {
                for (i = 0; i < 5; i++) {
                    D_800E7950[i].st->flags |= 0x80;
                }
            }
        }
    }
}
