/* @header
 * func_80091DF4
 * VRAM 0x80091DF4 | ROM 0x85294 | size 0x4CC
 * asm: asm/nonmatchings/ovl2_80090000/func_80091DF4.s
 */
#include "common.h"

typedef struct {
    s32 flags;
} Node;

typedef struct {
    u8 pad0[0x14];
    Node *node;
    u8 pad18[0xDC - 0x18];
} Spr;

typedef struct {
    u8 pad0[0x2C];
} SprTex;

void func_800907A0(Spr *s, SprTex *t, s16 x, s16 y, f32 a, f32 b, f32 c, f32 d, u8 r, u8 g, u8 bl, u8 al);
s32 func_8000DEE4(s32 arg0);

extern Spr D_800E9450[2];
extern Spr D_800E9608[2];
extern SprTex D_800E97C0[2];
extern SprTex D_800E9818[2];
extern s16 D_800E9870;
extern s16 D_800F9A9C;
extern s16 D_800F9AFA;

void func_80091DF4(void) {
    u32 x;
    s32 n;

    if (D_800E9870 < 0) {
        return;
    }
    if (D_800E9870 == 0x10) {
        func_8000DEE4(2);
        func_8000DEE4(0x4C);
    }
    if (D_800E9870 < 4) {
        x = D_800E9870 * 63;
        func_800907A0(&D_800E9608[0], &D_800E9818[0], 0xF0, 0x64, 0.5f, 0.5f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, x);
        func_800907A0(&D_800E9608[1], &D_800E9818[1], 0xF0, 0x64, 0.5f, 0.5f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0);
    } else if (D_800E9870 < 6) {
        x = (D_800E9870 - 4) * 127;
        func_800907A0(&D_800E9608[0], &D_800E9818[0], 0xF0, 0x64, 0.5f, 0.5f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0xFF - x);
        func_800907A0(&D_800E9608[1], &D_800E9818[1], 0xF0, 0x64, 0.5f, 0.5f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, x);
    } else if (D_800E9870 < 8) {
        x = (D_800E9870 - 6) * 127;
        func_800907A0(&D_800E9608[0], &D_800E9818[0], 0xF0, 0x64, 0.5f, 0.5f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0);
        func_800907A0(&D_800E9608[1], &D_800E9818[1], 0xF0, 0x64, 0.5f, 0.5f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0xFF - x);
        func_800907A0(&D_800E9450[0], &D_800E97C0[0], 0xF0, 0x64, 0.5f, 0.5f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, x);
    } else if (D_800E9870 < 10) {
        x = (D_800E9870 - 8) * 127;
        func_800907A0(&D_800E9608[1], &D_800E9818[1], 0xF0, 0x64, 0.5f, 0.5f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0);
        func_800907A0(&D_800E9450[0], &D_800E97C0[0], 0xF0, 0x64, 0.5f, 0.5f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0xFF - x);
        func_800907A0(&D_800E9450[1], &D_800E97C0[1], 0xF0, 0x64, 0.5f, 0.5f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, x);
    } else if (D_800E9870 < 0x14) {
        func_800907A0(&D_800E9450[1], &D_800E97C0[1], 0xF0, 0x64, 0.5f, 0.5f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0xFF);
        func_800907A0(&D_800E9450[0], &D_800E97C0[0], 0xF0, 0x64, 0.5f, 0.5f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0);
    } else if (D_800E9870 < 0x18) {
        /* placeholder: a condition only cse1 folds; it keeps a label inside this arm
           through jump1 so "if (foo) bar; else break;" does not swap it with the
           else arm below (the ROM keeps this arm first and all arms jump to the ++) */
        n = 0;
        if (n == 0) {
            x = (D_800E9870 - 0x14) * 63;
        }
        func_800907A0(&D_800E9450[1], &D_800E97C0[1], 0xF0, 0x64, 0.5f, 0.5f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0xFF - x);
        func_800907A0(&D_800E9450[0], &D_800E97C0[0], 0xF0, 0x64, 0.5f, 0.5f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0);
    } else {
        D_800E9450[0].node->flags |= 0x80;
        D_800E9608[0].node->flags |= 0x80;
        D_800E9450[1].node->flags |= 0x80;
        D_800E9608[1].node->flags |= 0x80;
        D_800F9A9C = 0;
        D_800E9870 = -1;
        D_800F9AFA = 1;
        return;
    }
    D_800E9870++;
}
