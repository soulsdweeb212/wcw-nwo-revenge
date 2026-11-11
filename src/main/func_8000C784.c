/* @header
 * func_8000C784
 * VRAM 0x8000C784 | ROM 0xD384 | size 0xC4
 * asm: asm/nonmatchings/main/func_8000C784.s
 */
#include "common.h"

extern u8 D_8007EF30;
extern u8 D_80070450[];
extern u8 D_8003090C[], D_80030A0C[], D_80030B0C[], D_80030C0C[];
void applyTextureTransparencyMask(void *, void *, s32);

#ifndef TARGET_PC /* on PC the label D_80073F34 (record 3 of D_80073EB0's first row) has no symbol: see below */
typedef struct {
    u8 f00[0x2C];
    u8 f2C[0x2C];
    u8 f58[0x3F4 - 0x58];
} Rec;

extern Rec D_80073F34[];
#endif

/* Apply the transparency masks to character record arg0's three texture layers
 * (the +0x58 and +0x2C layers always, the +0x00 layer with the high-bit mask or
 * the normal one depending on D_80070450). Does nothing while D_8007EF30 is set. */
void func_8000C784(s16 arg0) {
    if (D_8007EF30 == 0) {
#ifdef TARGET_PC
        /* PC: the N64 reaches records 3, 4 and 5 of player arg0's row of D_80073EB0 through the label D_80073F34
         * (record 3) and the view Rec (f00, f2C and f58 are records 3, 4 and 5). On PC the row is 23 Nw2Descr4BA8
         * (common.h), 0x50 bytes each, so the records are reached by index. */
        applyTextureTransparencyMask(&D_80073EB0[arg0][5], D_8003090C, 0xF801);
        applyTextureTransparencyMask(&D_80073EB0[arg0][4], D_80030A0C, 0xF801);
        if (D_80070450[arg0] & 0x80) {
            applyTextureTransparencyMask(&D_80073EB0[arg0][3], D_80030C0C, 0xF801);
        } else {
            applyTextureTransparencyMask(&D_80073EB0[arg0][3], D_80030B0C, 0xF801);
        }
#else
        applyTextureTransparencyMask(D_80073F34[arg0].f58, D_8003090C, 0xF801);
        applyTextureTransparencyMask(D_80073F34[arg0].f2C, D_80030A0C, 0xF801);
        if (D_80070450[arg0] & 0x80) {
            applyTextureTransparencyMask(D_80073F34[arg0].f00, D_80030C0C, 0xF801);
        } else {
            applyTextureTransparencyMask(D_80073F34[arg0].f00, D_80030B0C, 0xF801);
        }
#endif
    }
}
