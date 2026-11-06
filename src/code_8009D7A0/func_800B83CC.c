/* @header
 * func_800B83CC
 * VRAM 0x800B83CC | ROM 0xAB86C | size 0xB8
 * asm: asm/nonmatchings/code_8009D7A0/func_800B83CC.s
 */
#include "common.h"

extern s16 func_800BF2FC(void *);
/* Returns 1 when wrestler arg0's damage is low: in state 0x3D it checks that its
 * bodyPart hit by the opponent's current move (opponent's move.targetPart) is
 * below 10; otherwise that the func_800BF2FC damage value is below 25. */
s32 func_800B83CC(s16 arg0) {
    if (D_800F9D10[arg0].state == 0x3D) {
        if (D_800F9D10[arg0].bodyPart[D_800F9D10[D_800F9D10[arg0].opponentId].move.targetPart] < 10) return 1;
    } else {
        if (func_800BF2FC(&D_800F9D10[arg0]) < 25) return 1;
    }
    return 0;
}
