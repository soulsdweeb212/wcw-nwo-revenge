/* @header
 * n_alInit  (originally func_80017510)
 * VRAM 0x80017510 | ROM 0x18110 | size 0x44
 * asm: asm/nonmatchings/main/n_alInit.s
 */
/* SDK: n_audio, libnaudio/src/n_sl.c (same code as the SDK source). */
#include "common.h"

s32 n_alSynNew(s32);
extern s32 n_alGlobals;
extern s32 n_syn;

/* Register the root object arg0 and initialize the shared state pools only once. */
void n_alInit(s32 arg0, s32 arg1) {
    if (n_alGlobals == 0) {
        n_alGlobals = arg0;
        if (n_syn == 0) {
            n_syn = arg0;
            n_alSynNew(arg1);
        }
    }
}
