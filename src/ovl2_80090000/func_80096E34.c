/* @header
 * func_80096E34
 * VRAM 0x80096E34 | ROM 0x8A2D4 | size 0x130
 * asm: asm/nonmatchings/ovl2_80090000/func_80096E34.s
 */
#include "common.h"

typedef struct { s32 flags; } St;

typedef struct {
    u8 pad0[0x14];
    St *st;
    u8 pad18[0xC4];
} Sprite;

typedef struct {
    u8 b[0x2C];
} Frame;

void func_800907A0(void *a, void *b, s16 x, s16 y, f32 f0, f32 f1, f32 sx, f32 sy, u8 r, u8 g, u8 bl, u8 al);
extern Sprite D_800E8B28;
extern Sprite D_800E8C08;
extern Frame D_800E8CE8[];
extern Frame D_800E8D40[];
extern s16 D_800E8D98;
extern s16 D_800E8D9A;

void func_80096E34(s16 arg0) {
    if (arg0 < 2) {
        D_800E8D98 = arg0;
        if (D_800E8B28.st->flags & 0x80) {
            D_800E8D9A = 0;
            func_800907A0(&D_800E8B28, &D_800E8CE8[arg0], 0xF0, 0xA, 0.5f, 0.0f, 1.0f, 1.0f, 0xFF, 0xFF, 0xFF, 0xF);
            func_800907A0(&D_800E8C08, &D_800E8D40[D_800E8D98], 0xF0, 0xA, 0.5f, 0.0f, 1.0f, 1.0f, 0, 0x57, 0xFF, 0);
        }
    }
}
