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
#ifndef TARGET_PC /* on PC, port_decls.h declares D_80070458 (picture pairs); its label D_8007045C has no PC symbol */
extern CopyB728 *D_80070458[][2], *D_8007045C[][2];
#endif
#ifndef TARGET_PC /* on PC these labels inside D_80073EB0 (port_decls.h) have no symbol: the code reads its fields */
extern CopyB728 *D_80073FA4[][253], *D_80073FA8[][253];
#endif
extern s16 D_80073E90[];
extern u16 D_800307A0;
#ifndef TARGET_PC /* on PC, port_decls.h declares convertRgba16ToGrayscale, which takes the u16 colours */
void convertRgba16ToGrayscale(void *, u16);
#endif

void func_8000B728(s16 arg0) {
    CopyB728 *src, *dst;
    u32 i;

    if (D_800706A4[arg0]) {
#ifdef TARGET_PC
        /* PC: the N64 reads player arg0's picture pair through the label D_8007045C (the pair's +0x4) and its display
         * record 5's +0x1C through the label D_80073FA8, both stepped by the N64 sizes. On PC the pair is
         * Nw2TexPair and the record Nw2Descr4BA8 (common.h), read by field name: the pair's palette and the
         * record's palette buffer. */
        src = D_80070458[arg0].pal;
        dst = D_80073EB0[arg0][5].f1C;
#else
        src = D_8007045C[arg0][0];
        dst = D_80073FA8[arg0][0];
#endif
        for (i = 0; i < (u32)D_80073E90[arg0]; i++) {
            dst[i] = src[i];
        }
#ifdef TARGET_PC
        /* PC: as above, the record's +0x18 (the label D_80073FA4 on the N64) and the pair's image. */
        dst = D_80073EB0[arg0][5].f18;
        src = D_80070458[arg0].img;
#else
        dst = D_80073FA4[arg0][0];
        src = D_80070458[arg0][0];
#endif
        for (i = 0; i < 257; i++) {
            dst[i] = src[i];
        }
        if (D_800307A0 == 1) {
#ifdef TARGET_PC
            /* PC: the buffer just copied (display record 5's f1C, the label D_80073FA8 on the N64) holds
             * u16 colours, as the definition takes them; this file's view of it, CopyB728, is only the 8-byte unit
             * the copy loops move. */
            convertRgba16ToGrayscale((u16 *)D_80073EB0[arg0][5].f1C, D_80073E90[arg0]);
#else
            convertRgba16ToGrayscale(D_80073FA8[arg0][0], D_80073E90[arg0]);
#endif
        }
    }
}
