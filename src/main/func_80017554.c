/* @header
 * func_80017554
 * VRAM 0x80017554 | ROM 0x18154 | size 0x38
 * asm: asm/nonmatchings/main/func_80017554.s
 */
#include "common.h"

s32 func_800177C0();
extern s32 D_80036F50;
extern s32 D_80036F54;

/* Shut down the registered root object and clear the shared state pool pointers. */
void func_80017554(void) {
    if (D_80036F50 != 0) {
        func_800177C0();
        D_80036F50 = 0;
        D_80036F54 = 0;
    }
}
