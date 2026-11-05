/* @header
 * alClose  (originally func_800201EC)
 * VRAM 0x800201EC | ROM 0x20DEC | size 0x30
 * asm: asm/nonmatchings/main/alClose.s
 */
/* SDK: libultra 2.0I, ultralib src/audio/sl.c (same code as the SDK source). */
#include "common.h"

typedef s32 M2C_UNK;
M2C_UNK alSynDelete(void);
extern s32 alGlobals;

/* Shuts down the audio stream subsystem once and clears the active flag. */
void alClose(void) {
    if (alGlobals != 0) {
        alSynDelete();
        alGlobals = 0;
    }
}
