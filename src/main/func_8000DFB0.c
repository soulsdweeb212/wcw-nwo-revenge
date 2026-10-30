/* @header
 * func_8000DFB0
 * VRAM 0x8000DFB0 | ROM 0xEBB0 | size 0x20
 * asm: asm/nonmatchings/main/func_8000DFB0.s
 */
#include "common.h"

typedef s32 M2C_UNK;
M2C_UNK func_80013B58(M2C_UNK, M2C_UNK);

/* Convenience wrapper: plays sound group 1 with parameter 4. */
void func_8000DFB0(void) {
    func_80013B58(1, 4);
}
