#include "common.h"

extern s16 D_800E6B78;
extern s16 D_800E73B0;
extern s16 D_800E74DC;
extern s16 D_800E7540;
extern s16 D_800E7C88;
extern s16 D_800E821C;

/* Reset the six match/score counters to their defaults. */
void func_800969E8(void) {
    D_800E821C = 0;
    D_800E74DC = 0;
    D_800E6B78 = 0xF0;
    D_800E7C88 = 0xF0;
    D_800E7540 = 0;
    D_800E73B0 = 0;
}
