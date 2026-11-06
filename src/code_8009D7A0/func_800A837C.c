/* @header
 * func_800A837C
 * VRAM 0x800A837C | ROM 0x9B81C | size 0x60
 * asm: asm/nonmatchings/code_8009D7A0/func_800A837C.s
 */
#include "common.h"

extern u8 D_8007EF30[];

/* Count the current move in the second word of its row of the per-player statistics table (D_8007EF30 + 0x1B4 +
 * (w->id * 87 + w->moveStatKind) * 8; func_800A7F6C counts the first word), saturating at 0xFFFFFFFF. Does nothing
 * when moveStatKind is 0x57 (not counted). */
void func_800A837C(Wrestler *w) {
    s16 t = w->moveStatKind;
    s32 idx;

    if (t != 0x57) {
        idx = (w->id * 0x57 + t) * 8;
        if (*(u32 *)(D_8007EF30 + 0x1B4 + idx) < 0xFFFFFFFFU) {
            *(u32 *)(D_8007EF30 + 0x1B4 + idx) += 1;
        }
    }
}
