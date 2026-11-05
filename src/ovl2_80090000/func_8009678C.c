/* @header
 * func_8009678C
 * VRAM 0x8009678C | ROM 0x89C2C | size 0xC8
 * asm: asm/nonmatchings/ovl2_80090000/func_8009678C.s
 */
#include "common.h"

typedef struct { s32 flags; } St;

typedef struct {
    u8 pad0[0x14];
    St *st;
    u8 pad18[0xC4];
} Sprite;

void func_80097BB4(void);
extern u8 D_8007EF30[];
extern Sprite D_800E80C8[];
extern Sprite D_800E8280[];
extern s16 D_800E8B1A;
extern s16 D_800E8B20[];
extern s8 D_800F99B4;

void func_8009678C(void) {
    s32 n;
    u32 i;

    n = 10;
    if (D_8007EF30[0x1A1] == 1) {
        n = 20;
    }
    if (D_800E8B1A < n) {
        for (i = 0; i < 2; i++) {
            D_800E8B20[i] = -1;
            if (!(D_800E80C8[i].st->flags & 0x80)) {
                D_800E80C8[i].st->flags |= 0x80;
                D_800E8280[i].st->flags |= 0x80;
            }
        }
    }
    D_800E8B1A = 0;
    if (D_800F99B4 == 6) {
        func_80097BB4();
    }
}
