/* @header
 * func_800D43B4
 * VRAM 0x800D43B4 | ROM 0xC7854 | size 0x28
 * asm: asm/nonmatchings/code_800BBA00/func_800D43B4.s
 */
#include "common.h"

extern s32 gRandSeed;
extern s32 D_800EB634;
extern u16 D_800EB638[];

s32 guRandom(void);
/* Declared with two arguments here: the mode argument of func_800D427C is left as whatever a2 holds. */
void func_800D427C(Wrestler *, s32);

/* Restart an animation: set animId to -1 so func_800D427C sees a change, then start animation action. */
void func_800D43B4(Wrestler *w, s16 action) {
    w->animId = -1;
    func_800D427C(w, action);
}
