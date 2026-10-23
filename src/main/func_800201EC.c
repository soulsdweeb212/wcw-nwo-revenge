#include "common.h"

typedef s32 M2C_UNK;
M2C_UNK func_800209D0(void);
extern s32 D_80037510;

/* Shuts down the audio stream subsystem once and clears the active flag. */
void func_800201EC(void) {
    if (D_80037510 != 0) {
        func_800209D0();
        D_80037510 = 0;
    }
}
