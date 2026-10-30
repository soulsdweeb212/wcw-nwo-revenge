/* @header
 * func_80027950
 * VRAM 0x80027950 | ROM 0x28550 | size 0x20
 * asm: asm/nonmatchings/main/func_80027950.s
 */
#include "common.h"

extern s32 D_80037600;
extern s32 D_80037608;

/* Returns the active controller/Pak queue handle, or 0 when uninitialized. */
s32 func_80027950(void) {
    switch (D_80037600) {
    case 0:
        return 0;
    default:
        return D_80037608;
    }
}
