/* @header
 * func_80014020
 * VRAM 0x80014020 | ROM 0x14C20 | size 0x44
 * asm: asm/nonmatchings/main/func_80014020.s
 */
#include "common.h"

extern s32 D_800604F0;
extern s32 D_800604F4;
extern u32 D_800604C8;
extern u8 *D_800604D0;
s32 func_8001381C(s32);

/* Select arg0 as the current voice owner when it is stopping, run the loader, then
 * restore the default owner. */
s32 func_80014020(s32 arg0, s32 arg1) {
    s32 r;

    if (arg0 != 0 && *(s32 *)((u8 *)arg0 + 0x10) < 0) {
        D_800604F0 = arg0;
    }
    r = func_8001381C(arg1);
    D_800604F0 = D_800604F4;
    return r;
}
