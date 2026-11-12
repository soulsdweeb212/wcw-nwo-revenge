/* @header
 * func_8000B550
 * VRAM 0x8000B550 | ROM 0xC150 | size 0xE0
 * asm: asm/nonmatchings/main/func_8000B550.s
 */
#include "common.h"

/* Choose the highest category id available to character/state `charId`.
 *
 * For each of the 23 attribute rows of D_8007C438[charId] (a row is skipped
 * when the pointer is null or its length D_8007C318[charId][row] is < 17),
 * the 16 category ids stored at [16..31] are tested against the permission
 * mask D_80030860[maskIndex]: an id is usable when none of its bits fall
 * outside the mask (`id & ~mask` == 0). Among usable ids >= 2, the largest id
 * wins; its key byte (the row's entry at that index) is returned. Returns 0
 * when nothing is usable. */
extern u16 D_80030860[];
extern u16 D_8007C318[][23];
#ifndef TARGET_PC /* on PC, port_decls.h declares D_8007C438 */
extern u16 *D_8007C438[][23];
#endif

u16 func_8000B550(s16 charId, s32 maskIndex)
{
    u16 bestId = 0;
    u16 bestKey = 0;
    u32 row, k;
    u16 candidate;
    u32 id;
    for (row = 0; row < 23; row++) {
        if (D_8007C438[charId][row] && (D_8007C318[charId][row] >= 17U)) {
            for (k = 0; k < 16; k++) {
#ifdef TARGET_PC
                /* PC: a row is a block of u16 that stays in the N64's byte order (palette colours, then category
                 * ids; docs/port.md, "Byte order on PC"), so the value is read big-endian, as func_8000B884 reads the
                 * same rows. */
                candidate = READ_BE16(&((u16 *)D_8007C438[charId][row])[16 + k]);
#else
                candidate = D_8007C438[charId][row][16 + k];
#endif
                id = candidate & 0xFFFF;
                if (!(id & ~D_80030860[maskIndex & 0xFFFF])) {
                    if (id >= 2U) {
                        if (bestId < id) {
                            bestId = candidate;
#ifdef TARGET_PC
                            /* PC: the colour as a number (big-endian, as above): func_800C4140 hands it to
                             * func_800A73AC, which takes it apart into its red, green and blue. */
                            bestKey = READ_BE16(&((u16 *)D_8007C438[charId][row])[k]);
#else
                            bestKey = D_8007C438[charId][row][k];
#endif
                        }
                    }
                }
            }
        }
    }
    return bestKey;
}
