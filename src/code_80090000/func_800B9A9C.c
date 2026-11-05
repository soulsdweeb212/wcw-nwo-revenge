/* @header
 * func_800B9A9C
 * VRAM 0x800B9A9C | ROM 0x6620C | size 0x8C
 * asm: asm/nonmatchings/code_80090000/func_800B9A9C.s
 */
#include "common.h"

s32 osPfsDeleteFile(s32 *, s32, s32, s32 *, s32 *);   /* extern */
s32 func_8000424C();                                /* extern */
s32 func_80004290();                                  /* extern */
s32 func_800B8C4C(s32);                               /* extern */
s32 func_800B9268(s32);                                 /* extern */
extern u8 D_800D2938[];
extern u8 D_800D2948[];
extern u8 D_800DCF50[];
extern s32 D_800DCFBC;
extern s32 D_800DCFC4;

s32 func_800B9A9C(void) {
    s32 var_s0;

    D_800DCFC4 = func_8000424C();
    D_800DCFBC = osPfsDeleteFile(&D_800DCF50, 0x4538, 0x4E56504A, &D_800D2938, &D_800D2948);
    var_s0 = 0;
    func_80004290();
    do {
        func_800B8C4C(var_s0);
        var_s0 += 1;
    } while (var_s0 < 4);
    func_800B9268(-1);
    return D_800DCFBC;
}
