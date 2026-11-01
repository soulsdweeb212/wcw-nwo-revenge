/* @header
 * func_800A9FA0
 * VRAM 0x800A9FA0 | ROM 0x56710 | size 0xBC
 * asm: asm/nonmatchings/code_80090000/func_800A9FA0.s
 */
#include "common.h"

extern u8 D_8007EF30[];
s32 func_8002AD34(s32, s32);
s32 func_8002AD04(s32, s32);
s32 lookupPlayerNameById(s32, s32);
#define F(t, o, i) (*(t *)(D_8007EF30 + (o) + (i)))

s32 func_800A9FA0(s32 i) {
    s32 r;
    if ((*(u16 *)(D_8007EF30 + 8) & 0xF0) == 0x20) {
        r = func_8002AD34(F(s16, 0x4E, (i * 2) << 4), F(u8, 0x50, (i * 2) << 4));
        r = lookupPlayerNameById(r, func_8002AD34(F(s16, 0x4E, (i * 2 + 1) << 4), F(u8, 0x50, (i * 2 + 1) << 4)));
    } else {
        r = func_8002AD04(F(s16, 0x4E, i << 4), F(u8, 0x50, i << 4));
    }
    return r;
}
