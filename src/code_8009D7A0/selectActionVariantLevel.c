/* @header
 * selectActionVariantLevel  (originally func_800ABD50)
 * VRAM 0x800ABD50 | ROM 0x9F1F0 | size 0xD0
 * asm: asm/nonmatchings/code_8009D7A0/func_800ABD50.s
 */
#include "common.h"

void func_800AD958(s32);
void func_800ADA38(void *);
s8 func_800D4198(s16);
extern u8 D_800E3610[], D_800E361C[], D_800E3634[], D_800E3640[];
extern f64 D_800E4E48;
extern u8 *D_800FABD0;

/* Select an action parameter set for D_800FABD0: a high +0x28 with a low +0x24
 * and a random check trigger action 0x22; above the f34 threshold pick
 * D_800E3634 or D_800E3640 by the f12 random check; otherwise pick D_800E3610
 * or D_800E361C by +0x28. */
void selectActionVariantLevel(void) {
    if (*(s16 *)(D_800FABD0 + 0x28) >= 0x5B && *(s16 *)(D_800FABD0 + 0x24) < 0x28 && func_800D4198(0x32)) {
        func_800AD958(0x22);
    } else if (D_800E4E48 < *(f32 *)(D_800FABD0 + 0x34)) {
        if (func_800D4198(*(s16 *)(D_800FABD0 + 0x12))) func_800ADA38(D_800E3634);
        else func_800ADA38(D_800E3640);
    } else {
        if (*(s16 *)(D_800FABD0 + 0x28) >= 0x1F) func_800ADA38(D_800E3610);
        else func_800ADA38(D_800E361C);
    }
}
