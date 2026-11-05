/* @header
 * osPiGetCmdQueue  (originally func_80027950)
 * VRAM 0x80027950 | ROM 0x28550 | size 0x20
 * asm: asm/nonmatchings/main/osPiGetCmdQueue.s
 */
/* SDK: libultra 2.0I, ultralib src/io/pigetcmdq.c (same code as the SDK source). */
#include "common.h"

extern s32 D_80037600;
extern s32 D_80037608;

/* Returns the active controller/Pak queue handle, or 0 when uninitialized. */
s32 osPiGetCmdQueue(void) {
    switch (D_80037600) {
    case 0:
        return 0;
    default:
        return D_80037608;
    }
}
