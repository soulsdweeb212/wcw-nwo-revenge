/* @header
 * func_800D90E8
 * VRAM 0x800D90E8 | ROM 0xCC588 | size 0xD8
 * asm: asm/nonmatchings/code_800BBA00/func_800D90E8.s
 */
#include "common.h"

extern s8 D_8007EF30[];
extern s16 D_800E3FA8[];
extern u16 D_800F9840[];

/* Per-wrestler counter that arms a flag once it passes a threshold.
 * While flags bit 0x0008000000000000 is set, bump D_800F9840[w->id]; once the count
 * exceeds D_800E3FA8[D_8007EF30[0xCFC]] set flags bit 0x0010000000000000. Otherwise
 * clear that bit and reset the wrestler's counter to zero. */
void func_800D90E8(Wrestler *w)
{
    if (w->flags & 0x0008000000000000ULL) {
        D_800F9840[w->id]++;
        if ((s16)D_800F9840[w->id] > D_800E3FA8[D_8007EF30[0xCFC]]) {
            w->flags |= 0x0010000000000000ULL;
        }
    } else {
        w->flags &= ~0x0010000000000000ULL;
        D_800F9840[w->id] = 0;
    }
}
