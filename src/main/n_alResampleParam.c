/* @header
 * n_alResampleParam  (originally func_8001994C)
 * VRAM 0x8001994C | ROM 0x1A54C | size 0x20
 * asm: asm/nonmatchings/main/n_alResampleParam.s
 */
/* SDK: n_audio, libnaudio/src/n_resample.c (same code as the SDK source). */
#include "common.h"

typedef s32 M2C_UNK;
M2C_UNK n_alLoadParam(void);

/* Resets the entity state and returns 0. */
s32 n_alResampleParam(void) {
    n_alLoadParam();
    return 0;
}
