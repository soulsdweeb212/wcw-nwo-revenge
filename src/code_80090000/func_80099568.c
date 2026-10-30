/* @header
 * func_80099568
 * VRAM 0x80099568 | ROM 0x45CD8 | size 0x84
 * asm: asm/nonmatchings/code_80090000/func_80099568.s
 */
#include "common.h"

extern s16 D_800E74DC;
extern s16 D_800E7C88;

extern u8 updateEntityReactionState[];
u8 *func_80028B5C(u8 *, u8 *);
u8 *func_80028D18(s32, s32);

extern void *D_800E7518;
extern u8 D_800E7CE0[];
extern u8 D_800E7CE4[];
extern u8 D_800E7CE8[];
extern u8 D_800E7CF0[];
extern s32 D_800E7BE8;
extern s32 D_800E7BEC;
extern s32 D_800E8220;

void *allocateHeap(s32);

/* Looks up (or builds) the name string for entity arg0, prefixed with the
 * default string; returns the default string when the id is empty or the lookup
 * fails. */
u8 *func_80099568(u8 *arg0) {
    u8 *r;
    u8 *p;

    if (*arg0 == 0) {
        return updateEntityReactionState + 0x64;
    }
    r = func_80028D18(arg0, 3);
    if (r == NULL) {
        return updateEntityReactionState + 0x64;
    }
    if (*r == 0) {
        p = func_80028B5C(r, updateEntityReactionState + 0x1F4);
        p = func_80028B5C(p, arg0);
        *p = 0;
    }
    return r;
}
