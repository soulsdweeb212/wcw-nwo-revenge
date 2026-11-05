/* @header
 * n_alClose  (originally func_80017554)
 * VRAM 0x80017554 | ROM 0x18154 | size 0x38
 * asm: asm/nonmatchings/main/n_alClose.s
 */
/* SDK: n_audio, libnaudio/src/n_sl.c (same code as the SDK source). */
#include "common.h"

s32 n_alSynDelete();
extern s32 n_alGlobals;
extern s32 n_syn;

/* Shut down the registered root object and clear the shared state pool pointers. */
void n_alClose(void) {
    if (n_alGlobals != 0) {
        n_alSynDelete();
        n_alGlobals = 0;
        n_syn = 0;
    }
}
