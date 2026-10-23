#include "common.h"

s32 initObjectNodeLists();
extern s32 D_80037510;

/* Register the object-node heap arg0 on first use. */
void func_800201C0(s32 arg0) {
    if (D_80037510 == 0) {
        D_80037510 = arg0;
        initObjectNodeLists();
    }
}
