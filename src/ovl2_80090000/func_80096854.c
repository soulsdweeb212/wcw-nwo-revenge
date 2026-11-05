/* @header
 * func_80096854
 * VRAM 0x80096854 | ROM 0x89CF4 | size 0x46C
 * asm: asm/nonmatchings/ovl2_80090000/func_80096854.s
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

s32 func_8000DEE4(s32);
void func_800907A0(void *a, void *b, s16 x, s16 y, f32 f0, f32 f1, f32 sx, f32 sy, u8 r, u8 g, u8 bl, u8 al);
void func_8009786C(s32);
extern u16 D_800E2B1C[];
extern s16 D_800E2D96[];
extern Sprite D_800E80C8[];
extern Sprite D_800E8280[];
extern Frame D_800E8438[][10];
extern Frame D_800E87A8[][10];
extern s16 D_800E8B18;
extern s16 D_800E8B1A;
extern s16 D_800E8B1C[];
extern s16 D_800E8B20[];
extern s16 D_800F99B6;

void func_80096854(s16 n) {
    s8 d[2];
    u32 i;

    if (D_800F99B6 == 0) {
        if (n >= 1 && n <= 20) {
            if (D_800E8B1A != n) {
                func_8000DEE4(D_800E2D96[n]);
            }
            D_800E8B1A = n;
            D_800E8B18 = 0;
            d[0] = n / 10;
            d[1] = n % 10;
            if (d[0] > 0) {
                for (i = 0; i < 2; i++) {
                    if (D_800E8B20[i] != d[i]) {
                        D_800E8B20[i] = d[i];
                        D_800E8B1C[i] = i;
                        func_800907A0(&D_800E80C8[i], &D_800E8438[i][D_800E8B20[i]], (f32)D_800E2B1C[D_800E8B1C[i]], 0xC,
                                      0.5f, 0.0f, 1.0f, 1.0f, 0xFF, 0xFF, 0xFF, 0);
                        func_800907A0(&D_800E8280[i], &D_800E87A8[i][D_800E8B20[i]], (f32)D_800E2B1C[D_800E8B1C[i]], 0xC,
                                      0.5f, 0.0f, 1.0f, 1.0f, 0xFF, 0, 0, 0);
                    }
                    D_800E80C8[i].st->flags &= ~0x80;
                    D_800E8280[i].st->flags &= ~0x80;
                }
            } else {
                D_800E80C8[0].st->flags |= 0x80;
                D_800E8280[0].st->flags |= 0x80;
                if (D_800E8B20[1] != d[1]) {
                    D_800E8B20[1] = d[1];
                    D_800E8B1C[1] = 2;
                    func_800907A0(&D_800E80C8[1], &D_800E8438[1][D_800E8B20[1]], (f32)D_800E2B1C[D_800E8B1C[1]], 0xC,
                                  0.5f, 0.0f, 1.0f, 1.0f, 0xFF, 0xFF, 0xFF, 0);
                    func_800907A0(&D_800E8280[1], &D_800E87A8[1][D_800E8B20[1]], (f32)D_800E2B1C[D_800E8B1C[1]], 0xC,
                                  0.5f, 0.0f, 1.0f, 1.0f, 0xFF, 0, 0, 0);
                    D_800E80C8[1].st->flags &= ~0x80;
                    D_800E8280[1].st->flags &= ~0x80;
                }
            }
        }
        func_8009786C(6);
    }
}
