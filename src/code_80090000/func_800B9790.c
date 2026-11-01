/* @header
 * func_800B9790
 * VRAM 0x800B9790 | ROM 0x65F00 | size 0x3C
 * asm: asm/nonmatchings/code_80090000/func_800B9790.s
 */
#include "common.h"

s32 func_8000424C();                                /* extern */
s32 func_80004290();                                  /* extern */
s32 func_800B947C();                                /* extern */
extern s32 D_800DCFBC;
extern s32 D_800DCFC4;

s32 func_800B9790(void) {
    D_800DCFC4 = func_8000424C();
    D_800DCFBC = func_800B947C();
    func_80004290();
    return D_800DCFBC;
}
