/* @header
 * func_800B9ECC
 * VRAM 0x800B9ECC | ROM 0x6663C | size 0x4C
 * asm: asm/nonmatchings/code_80090000/func_800B9ECC.s
 */
#include "common.h"

s32 func_8000424C();                                /* extern */
s32 func_80004290();                                  /* extern */
s32 osPfsRepairId(s32 *);                             /* extern */
extern s8 D_80038AB0;
extern u8 D_800DCF50[];
extern s32 D_800DCFBC;
extern s32 D_800DCFC4;

s32 func_800B9ECC(void) {
    D_800DCFC4 = func_8000424C();
    D_800DCFBC = osPfsRepairId(&D_800DCF50);
    D_80038AB0 = 0;
    func_80004290();
    return D_800DCFBC;
}
