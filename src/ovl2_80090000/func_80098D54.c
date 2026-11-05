/* @header
 * func_80098D54
 * VRAM 0x80098D54 | ROM 0x8C1F4 | size 0x8D4
 * asm: asm/nonmatchings/ovl2_80090000/func_80098D54.s
 */
#include "common.h"

typedef struct {
    u32 w0, w1;
} G;

/* Resource-indexed tables: entry k belongs to resource id 0x2CA + k. */
#define RES_BASE 0x2CA

extern void *D_800EB2B8[]; /* loaded textures, D_800EB2B8[id - RES_BASE] */
extern u16 D_800E2EA0[];   /* screen x per resource (new symbol) */
extern u16 D_800E2EE8[];   /* screen y per resource (new symbol) */
extern s16 D_800E2F30[];
extern s16 D_800E2F3C[];
extern s16 D_800EB2A8;
extern s16 D_800EB2AA;
extern s16 D_800EB2B2;
extern u16 D_800EB2B6;
extern s16 D_800F9AA2;
extern u8 D_8007EF30[];
extern u8 D_8007E8C0[];
void func_80099E2C(G **gp, void *tex, void *pal, f32 x, f32 y);

static inline void drawRes(G **gp, s16 id, s16 pal) {
    func_80099E2C(gp, D_800EB2B8[id - RES_BASE], D_800EB2B8[pal - RES_BASE], (f32)D_800E2EA0[id - RES_BASE],
                  (f32)D_800E2EE8[id - RES_BASE]);
}

static inline void drawResL(G **gp, s16 id) {
    func_80099E2C(gp, D_800EB2B8[0x2D5 - RES_BASE], D_800EB2B8[0x2CA - RES_BASE], (f32)(D_800E2EA0[id - RES_BASE] - 16),
                  (f32)D_800E2EE8[id - RES_BASE]);
}

#define EMIT(a, b) { G *_g = g++; _g->w0 = (a); _g->w1 = (b); }

s32 func_80098D54(G **gp, s16 mode) {
    G *g;

    if (mode == 1) {
        g = *gp;
        EMIT(0xE200001C, 0x0F0A7008);
        EMIT(0xFCFFFFFF, 0xFFFCF279);
        EMIT(0xE3001201, 0);
        EMIT(0xE3000C00, 0);
        *gp = g;
        if (D_800EB2A8 == 0) {
            drawRes(gp, 0x2D6, 0x2CA);
            if ((D_8007E280 & 0x1000) && D_800EB2B2 > 0) {
                drawRes(gp, 0x2D8, 0x2CB);
            } else {
                drawRes(gp, 0x2D8, 0x2CA);
            }
            drawRes(gp, 0x2D7, 0x2CA);
            if (D_8007E8C0[0x66F] == 0) {
                drawRes(gp, 0x2DC, 0x2CA);
            } else {
                drawRes(gp, 0x2DB, 0x2CA);
            }
            if (D_8007E280 & 0x100) {
                if (D_800F9AA2 != 0) {
                    drawRes(gp, 0x2DA, 0x2CA);
                } else {
                    drawRes(gp, 0x2D9, 0x2CA);
                }
            } else {
                drawRes(gp, 0x2D9, 0x2CB);
            }
            if (!(D_8007E280 & 0x200)) {
                if (D_8007EF30[3] == 0) {
                    drawRes(gp, 0x2DE, 0x2CA);
                } else {
                    drawRes(gp, 0x2DD, 0x2CA);
                }
            } else {
                drawRes(gp, 0x2DD, 0x2CB);
            }
            drawRes(gp, D_800E2F30[D_800EB2AA], 0x2CA);
            drawResL(gp, D_800E2F3C[D_800EB2AA]);
        } else {
            drawRes(gp, 0x2E5, 0x2CA);
            drawRes(gp, 0x2E6, 0x2CA);
            if (D_800EB2AA == 1) {
                drawRes(gp, 0x2E3, 0x2CA);
            } else {
                drawRes(gp, 0x2E4, 0x2CA);
            }
            if (D_800EB2A8 == 1) {
                drawResL(gp, 0x2E5);
            } else {
                drawResL(gp, 0x2E6);
            }
            drawRes(gp, 0x2E1, 0x2CA);
        }
        drawRes(gp, 0x2EA, 0x2E9);
        drawRes(gp, 0x2EC, 0x2EB);
        drawRes(gp, 0x2E8, 0x2E7);
        drawRes(gp, 0x2DF, 0x2CA);
        drawRes(gp, 0x2E0, 0x2CA);
        drawRes(gp, 0x2D0, D_800EB2B6 + 0x2CC);
        drawRes(gp, D_800EB2B6 + 0x2D1, D_800EB2B6 + 0x2CC);
        g = *gp;
        EMIT(0xE3000C00, 0x80000);
        EMIT(0xE3001201, 0x2000);
        *gp = g;
    }
    return 1;
}
