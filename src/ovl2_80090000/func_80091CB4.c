/* @header
 * func_80091CB4
 * VRAM 0x80091CB4 | ROM 0x85154 | size 0x140
 * asm: asm/nonmatchings/ovl2_80090000/func_80091CB4.s
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

extern Spr D_800E9450[2];
extern Spr D_800E9608[2];
extern SprTex D_800E97C0[2];
extern SprTex D_800E9818[2];
extern s16 D_800E9870;

void func_80091CB4(void) {
    u32 i;

    for (i = 0; i < 2; i++) {
        D_800E9450[i].node->flags &= ~0x80;
        D_800E9608[i].node->flags &= ~0x80;
        func_800907A0(&D_800E9450[i], &D_800E97C0[i], 0xF0, 0x64, 0.5f, 0.5f, 0.5f, 0.5f, 0xFF, 0xFF, 0xFF, 0);
        func_800907A0(&D_800E9608[i], &D_800E9818[i], 0xF0, 0x64, 0.5f, 0.5f, 0.5f, 0.5f, 0xFF, 0, 0, 0);
    }
    D_800E9870 = 0;
}
