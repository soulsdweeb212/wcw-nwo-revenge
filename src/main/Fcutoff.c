/* @header
 * Fcutoff  (originally func_800163E4)
 * VRAM 0x800163E4 | ROM 0x16FE4 | size 0x24
 * asm: asm/nonmatchings/main/Fcutoff.s
 */
/* SDK: libmus, libmus/src/playerinc/player_commands.inc.c (same code as the SDK source). */
#include "common.h"

extern f64 D_8003B3C8;
extern f64 D_8003B3D0;
extern f64 D_8003B3D8;
extern f64 D_8003B3E0;

/* Decode a two-byte (big-endian) release rate into +0xD2. */
u8 *Fcutoff(u8 *arg0, u8 *arg1) {
    u8 hi;
    u8 lo;

    hi = *arg1;
    arg1++;
    lo = *arg1;
    *(s16 *)(arg0 + 0xD4) = 0;
    *(s16 *)(arg0 + 0xD2) = lo | (hi << 8);
    return arg1 + 1;
}
