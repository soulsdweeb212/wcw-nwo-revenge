/* @header
 * func_80098CE8
 * VRAM 0x80098CE8 | ROM 0x8C188 | size 0x6C
 * asm: asm/nonmatchings/ovl2_80090000/func_80098CE8.s
 */
#include "common.h"

/* Resource-indexed tables: entry k belongs to resource id 0x2CA + k. */
#define RES_BASE 0x2CA

extern void *D_800EB2B8[]; /* loaded textures, D_800EB2B8[id - RES_BASE] */
extern u16 D_800E2EA0[];   /* screen x per resource (new symbol) */
extern u16 D_800E2EE8[];   /* screen y per resource (new symbol) */
void func_80099E2C(void *gp, void *tex, void *pal, f32 x, f32 y);

void func_80098CE8(void *gp, s16 id) {
    func_80099E2C(gp, D_800EB2B8[0x2D5 - RES_BASE], D_800EB2B8[0x2CA - RES_BASE], (f32)(D_800E2EA0[id - RES_BASE] - 16),
                  (f32)D_800E2EE8[id - RES_BASE]);
}
