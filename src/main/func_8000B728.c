/* @header
 * func_8000B728
 * VRAM 0x8000B728 | ROM 0xC328 | size 0x15C
 * asm: asm/nonmatchings/main/func_8000B728.s
 */
#include "common.h"

/* func_8000B728: when the given entity has an active colour/graphics set,
 * copies its per-entity image (D_80073E90 entries) and its fixed 257-entry
 * palette from the source graphics buffers into the working buffers, then
 * optionally converts the copied image to grayscale when D_800307A0 is 1. */
typedef union { struct { s32 a, b; } words; u64 align; } CopyB728;
extern s8 D_800706A4[];
extern CopyB728 *D_80070458[][2], *D_8007045C[][2];
extern CopyB728 *D_80073FA4[][253], *D_80073FA8[][253];
extern s16 D_80073E90[];
extern u16 D_800307A0;
void convertRgba16ToGrayscale(void *, u16);

void func_8000B728(s16 arg0) {
    CopyB728 *src, *dst;
    u32 i;

    if (D_800706A4[arg0]) {
        src = D_8007045C[arg0][0];
        dst = D_80073FA8[arg0][0];
        for (i = 0; i < (u32)D_80073E90[arg0]; i++) {
            dst[i] = src[i];
        }
        dst = D_80073FA4[arg0][0];
        src = D_80070458[arg0][0];
        for (i = 0; i < 257; i++) {
            dst[i] = src[i];
        }
        if (D_800307A0 == 1) {
            convertRgba16ToGrayscale(D_80073FA8[arg0][0], D_80073E90[arg0]);
        }
    }
}
