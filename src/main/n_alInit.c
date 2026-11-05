/* @header
 * n_alInit  (originally func_80017510)
 * VRAM 0x80017510 | ROM 0x18110 | size 0x44
 * asm: asm/nonmatchings/main/n_alInit.s
 */
/* SDK: n_audio, libnaudio/src/n_sl.c (same code as the SDK source). */
#include "common.h"

s32 n_alSynNew(s32);
extern s32 D_80036F50;
extern s32 D_80036F54;

/* Register the root object arg0 and initialize the shared state pools only once. */
void n_alInit(s32 arg0, s32 arg1) {
    if (D_80036F50 == 0) {
        D_80036F50 = arg0;
        if (D_80036F54 == 0) {
            D_80036F54 = arg0;
            n_alSynNew(arg1);
        }
    }
}
