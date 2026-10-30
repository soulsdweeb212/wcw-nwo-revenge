/* @header
 * func_80096A48
 * VRAM 0x80096A48 | ROM 0x431B8 | size 0x24
 * asm: asm/nonmatchings/code_80090000/func_80096A48.s
 */
#include "common.h"

extern s16 D_800E74DC;
extern s16 D_800E7C88;

extern void *D_800E7518;
extern u8 D_800E7CE0[];
extern u8 D_800E7CE4[];
extern u8 D_800E7CE8[];
extern u8 D_800E7CF0[];
extern s32 D_800E7BE8;
extern s32 D_800E7BEC;
extern s32 D_800E8220;

void *allocateHeap(s32);

/* Return one of the two cached values selected by arg0. */
s16 func_80096A48(s32 arg0) {
    if (arg0 != 0) {
        return D_800E7C88;
    }
    return D_800E74DC;
}
