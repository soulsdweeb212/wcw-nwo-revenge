/* @header
 * func_800B83CC
 * VRAM 0x800B83CC | ROM 0xAB86C | size 0xB8
 * asm: asm/nonmatchings/code_8009D7A0/func_800B83CC.s
 */
#include "common.h"

extern s16 func_800BF2FC(void *);
extern u8 D_800F9D10[][0x3B0];
extern s16 D_800F9D1A[][0x1D8];
extern s8 D_800FA05C[][0x3B0], D_800FA063[][0x3B0], D_800FA0A6[][0x3B0];
/* Returns 1 when entity arg0's damage is low: for state 0x3D it checks the
 * part value indexed through D_800FA063/FA0A6 is below 10; otherwise the
 * func_800BF2FC damage value is below 25. */
s32 func_800B83CC(s16 arg0) {
    if (D_800F9D1A[arg0][0] == 0x3D) {
        if (D_800FA05C[arg0][D_800FA0A6[D_800FA063[arg0][0]][0]] < 10) return 1;
    } else {
        if (func_800BF2FC(D_800F9D10[arg0]) < 25) return 1;
    }
    return 0;
}
