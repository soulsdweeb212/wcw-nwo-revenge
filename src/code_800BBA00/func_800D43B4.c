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
#ifdef TARGET_PC
/* PC definition. On the N64 this function passes func_800D427C its own third argument without naming it: every caller
 * puts a mode (0 to 3) in $a2 and declares this function with a third s32 parameter, and the N64 code leaves $a2
 * untouched on the way to func_800D427C, which stores it in D_800EB6B8. On PC an argument that is not named does not
 * travel on, so the PC version takes mode and hands it over. func_800D427C is declared with its definition's types. */
void func_800D427C(Wrestler *w, s16 animId, s32 mode);

/* Restart an animation: set animId to -1 so func_800D427C sees a change, then start animation action. */
void func_800D43B4(Wrestler *w, s16 action, s32 mode) {
    w->animId = -1;
    func_800D427C(w, action, mode);
}
#else
/* Declared with two arguments here: the mode argument of func_800D427C is left as whatever a2 holds. */
void func_800D427C(Wrestler *, s32);

/* Restart an animation: set animId to -1 so func_800D427C sees a change, then start animation action. */
void func_800D43B4(Wrestler *w, s16 action) {
    w->animId = -1;
    func_800D427C(w, action);
}
#endif
