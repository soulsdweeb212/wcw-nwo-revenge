/* @header
 * alInit  (originally func_800201C0)
 * VRAM 0x800201C0 | ROM 0x20DC0 | size 0x2C
 * asm: asm/nonmatchings/main/alInit.s
 */
/* SDK: libultra 2.0I, ultralib src/audio/sl.c (same code as the SDK source). */
#include "common.h"

s32 alSynNew();
extern s32 alGlobals;

/* Register the object-node heap arg0 on first use. */
void alInit(s32 arg0) {
    if (alGlobals == 0) {
        alGlobals = arg0;
        alSynNew();
    }
}
