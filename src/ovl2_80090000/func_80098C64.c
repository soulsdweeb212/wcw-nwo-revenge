/* @header
 * func_80098C64
 * VRAM 0x80098C64 | ROM 0x8C104 | size 0x84
 * asm: asm/nonmatchings/ovl2_80090000/func_80098C64.s
 */
#include "common.h"

/* Resource-indexed tables: entry k belongs to resource id 0x2CA + k. */
#define RES_BASE 0x2CA

extern void *D_800EB2B8[]; /* loaded textures, D_800EB2B8[id - RES_BASE] */
extern u16 D_800E2EA0[];   /* screen x per resource (new symbol) */
extern u16 D_800E2EE8[];   /* screen y per resource (new symbol) */
void func_80099E2C(void *gp, void *tex, void *pal, f32 x, f32 y);

void func_80098C64(void *gp, s16 id, s16 pal) {
    func_80099E2C(gp, D_800EB2B8[id - RES_BASE], D_800EB2B8[pal - RES_BASE], (f32)D_800E2EA0[id - RES_BASE],
                  (f32)D_800E2EE8[id - RES_BASE]);
}
