/* @header
 * func_80096FE8
 * VRAM 0x80096FE8 | ROM 0x8A488 | size 0x884
 * asm: asm/nonmatchings/ovl2_80090000/func_80096FE8.s
 */
#include "common.h"

typedef struct { s32 flags; } St;

typedef struct {
    u8 pad0[0x10];
    void *dl;
    St *st;
    u8 pad18[0xC4];
} Sprite;

typedef struct {
    u8 b[0x2C];
} Frame;

typedef struct {
    void *meta;
    u32 addr;
} Tex;

void func_80006814(Sprite *, Tex *, f32, f32);
void func_800907A0(void *a, void *b, s16 x, s16 y, f32 f0, f32 f1, f32 sx, f32 sy, u8 r, u8 g, u8 bl, u8 al);
void func_80097BB4(void);
s8 func_800D633C(void);
extern s16 *D_800E2CF4[];
extern u8 *D_800E2D58[];
extern Sprite D_800E77C0;
extern void *D_800E789C[];
extern Tex D_800E78A8[];
extern s16 D_800E7940;
extern u16 D_800E7942;
extern Sprite D_800E8B28;
extern Sprite D_800E8C08;
extern Frame D_800E8CE8[];
extern Frame D_800E8D40[];
extern s16 D_800E8D98;
extern s16 D_800E8D9A;
extern s8 D_800F99B4;
extern s8 D_800F99B5;
extern s16 D_800F99B8;
extern s8 D_800F9A9E;
extern s16 D_800F9AA0;
extern s8 D_800F9AF8;

/* body of func_80096F64, inlined here */
static inline void setNote(void) {
    s32 v;

    v = (s8)(D_800E2CF4[D_800F99B4][D_800F9A9E] + 0x5C) / 2;
    D_800F9AF8 = v;
    D_800F99B5 = D_800E2D58[D_800F99B4][D_800F9A9E];
    if (v >= 5) {
        D_800F9AA0 = 0x6F;
    } else {
        D_800F9AA0 = 0x50;
    }
}

void func_80096FE8(void) {
    s32 d;

    if (!(D_800E7942 & 0x80) || D_800F99B8 > 0) {
        if (D_800F99B5 > 0) {
            D_800F99B5--;
            if (D_800F99B5 == 0) {
                D_800F9A9E++;
                if (D_800E2CF4[D_800F99B4][D_800F9A9E] == -1) {
                    D_800F9A9E = 0;
                }
                if (D_800E2CF4[D_800F99B4][D_800F9A9E] != 0) {
                    setNote();
                } else {
                    func_80097BB4();
                }
            }
        }
        if (func_800D633C()) {
            D_800E77C0.st->flags |= 0x80;
        } else {
            D_800E77C0.st->flags &= ~0x80;
        }
        if (D_800F99B4 != 0) {
            d = 0x80 - D_800F99B8;
            if (d >= 2) {
                D_800F99B8 += d / 2;
            } else {
                D_800F99B8 = 0x80;
            }
        } else if (D_800F99B8 >= 20) {
            D_800F99B8 -= 20;
        } else {
            D_800F99B8 = 0;
            D_800E7942 = 0x80;
            D_800E77C0.st->flags |= 0x80;
        }
        D_800E77C0.dl = D_800E789C[D_800E7940++];
        D_800E7940 %= 3;
        func_80006814(&D_800E77C0, &D_800E78A8[D_800F9AF8], 0x1E0 - D_800F99B8, D_800F9AA0);
    }
    if (D_800E8D9A >= 0) {
        D_800E8B28.st->flags &= ~0x80;
        D_800E8C08.st->flags &= ~0x80;
        if (D_800E8D9A < 12) {
            func_800907A0(&D_800E8B28, &D_800E8CE8[D_800E8D98], 0x21C - D_800E8D9A * 25, 0x82, 0.5f, -0.2f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0xFF);
            func_800907A0(&D_800E8C08, &D_800E8D40[D_800E8D98], 0x21C - D_800E8D9A * 25, 0x82, 0.5f, -0.2f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0xFF);
        } else if (D_800E8D9A < 15) {
            func_800907A0(&D_800E8B28, &D_800E8CE8[D_800E8D98], 0xF0, 0x82, 0.5f, -0.2f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0xFF);
            func_800907A0(&D_800E8C08, &D_800E8D40[D_800E8D98], 0xF0, 0x82, 0.5f, -0.2f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0xFF);
        } else if (D_800E8D9A < 24) {
            func_800907A0(&D_800E8B28, &D_800E8CE8[D_800E8D98], 0xF0, 0x82, 0.5f, -0.2f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0xFF);
            func_800907A0(&D_800E8C08, &D_800E8D40[D_800E8D98], 0xF0, 0x82, 0.5f, -0.2f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0xFF - (D_800E8D9A - 15) * 30);
        } else if (D_800E8D9A < 42) {
            func_800907A0(&D_800E8B28, &D_800E8CE8[D_800E8D98], 0xF0, 0x82, 0.5f, -0.2f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0xFF);
            func_800907A0(&D_800E8C08, &D_800E8D40[D_800E8D98], 0xF0, 0x82, 0.5f, -0.2f, 2.0f, 1.5f, 0, 0x57, 0xFF, 0);
        } else if (D_800E8D9A < 63) {
            func_800907A0(&D_800E8B28, &D_800E8CE8[D_800E8D98], 0xF0, 0x82, 0.5f, -0.2f, 2.0f, 1.5f, 0xFF, 0xFF, 0xFF, 0xFF - (D_800E8D9A - 42) * 12);
            func_800907A0(&D_800E8C08, &D_800E8D40[D_800E8D98], 0xF0, 0x82, 0.5f, -0.2f, 2.0f, 1.5f, 0, 0x57, 0xFF, 0);
        } else {
            D_800E8B28.st->flags |= 0x80;
            D_800E8C08.st->flags |= 0x80;
        }
        if (func_800D633C()) {
            D_800E8B28.st->flags |= 0x80;
            D_800E8C08.st->flags |= 0x80;
        } else {
            D_800E8D9A = (D_800E8B28.st->flags & 0x80) ? -1 : D_800E8D9A + 1;
        }
    }
}
