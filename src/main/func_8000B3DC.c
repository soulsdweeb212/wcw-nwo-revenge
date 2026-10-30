/* @header
 * func_8000B3DC
 * VRAM 0x8000B3DC | ROM 0xBFDC | size 0x40
 * asm: asm/nonmatchings/main/func_8000B3DC.s
 */
#include "common.h"

extern u16 *D_80031998[];
extern s16 D_8003673C[];
extern s32 *D_80032B44[];

/* Decode part arg0 into an index into D_8003673C (masked to 7 bits). */
s16 func_8000B3DC(u32 arg0) {
    u32 g = (arg0 >> 8) & 0x1F;
    u32 n = (arg0 & 0x1F) - 1;
    return D_8003673C[D_80031998[g][n] & 0x7F];
}
