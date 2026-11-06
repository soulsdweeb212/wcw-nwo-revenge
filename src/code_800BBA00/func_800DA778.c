/* @header
 * func_800DA778
 * VRAM 0x800DA778 | ROM 0xCDC18 | size 0xD4
 * asm: asm/nonmatchings/code_800BBA00/func_800DA778.s
 */
#include "common.h"

/* When the wrestler has a tag partner, retargets its opponent from the partner's
 * state: in states 0x38/0x3C/0x3E/0x72/0x74 it takes the partner's opponent's
 * partner, in 0x39/0x3D/0x3F/0x73/0x75 the partner's opponent. */
s32 func_800DA778(Wrestler *arg0) {
    if (arg0->id != arg0->partnerId) {
        switch ((s16)((u16)D_800F9D10[arg0->partnerId].state - 0x38)) {
        case 0:
        case 4:
        case 6:
        case 58:
        case 60:
            arg0->opponentId = D_800F9D10[D_800F9D10[arg0->partnerId].opponentId].partnerId;
            break;
        case 1:
        case 5:
        case 7:
        case 61:
        case 59:
            arg0->opponentId = D_800F9D10[arg0->partnerId].opponentId;
            break;
        }
    }
}
