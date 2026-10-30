/* @header
 * func_800E2768
 * VRAM 0x800E2768 | ROM 0xD5C08 | size 0x4C
 * asm: asm/nonmatchings/code_800DE9C0/func_800E2768.s
 */
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
