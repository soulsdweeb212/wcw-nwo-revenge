/* @header
 * func_800B9A28
 * VRAM 0x800B9A28 | ROM 0x66198 | size 0x74
 * asm: asm/nonmatchings/code_80090000/func_800B9A28.s
 */
#include "common.h"

s32 func_8000424C();                                /* extern */
s32 func_80004290();                                  /* extern */
s32 osPfsAllocateFile(s32 *, s32, s32, s32 *, s32 *, s32, s32 *); /* extern */
extern u8 D_800D2938[];
extern u8 D_800D2948[];
extern u8 D_800DCF50[];
extern s32 D_800DCFBC;
extern u8 D_800DCFC0[];
extern s32 D_800DCFC4;

s32 func_800B9A28(void) {
    D_800DCFC4 = func_8000424C();
    D_800DCFBC = osPfsAllocateFile(&D_800DCF50, 0x4538, 0x4E56504A, &D_800D2938, &D_800D2948, 0, &D_800DCFC0);
    func_80004290();
    return D_800DCFBC;
}
