#include "common.h"

extern s8 D_800F99A0[];
extern u8 D_800F98E2[];

void applyEntityTextureMasks(s8, s8);

/* Re-applies the entity's texture masks when its +0x374 flag is set and the
 * +6 counter matches +0x375+7. */
void func_800E2768(u8 *arg0, s8 *arg1) {
    if (arg0[0x374] != 0 && *(s16 *)(arg0 + 6) == arg0[0x375] + 7) {
        applyEntityTextureMasks(*arg1, D_800F99A0[*(s8 *)arg0]);
    }
}
