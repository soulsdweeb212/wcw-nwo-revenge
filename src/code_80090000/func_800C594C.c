/* @header
 * func_800C594C
 * VRAM 0x800C594C | ROM 0x720BC | size 0x184
 * asm: asm/nonmatchings/code_80090000/func_800C594C.s
 */
#include "common.h"

extern s32 D_80038A98, D_800D5F18, D_800E7C8C, D_800E8208;
extern u8 D_8007E228[], D_8007EF30[], D_800DF3E0[], D_800DF4C0[];

s32 func_800C594C(void) {
    s32 m = D_80038A98;
    s32 r;

    D_800E8208 = 3;
    D_800E7C8C = 2;
    func_800C5718();
    if (D_80038A98 != 1) {
        r = func_800C1C70();
    } else {
        r = func_800A171C();
    }
    if (D_80038A98 < 0) {
        r = -1;
        D_80038A98 = 0;
        *(s32 *)(D_8007E228 + 0x60C) = 0;
    }
    if (r != 0) {
        func_80002C74();
        func_800C54FC(0);
        if (m != 1) {
            func_800C1C4C();
        } else {
            func_800A16E0();
        }
        func_800B6278();
        releaseResourcePool();
        func_800BB358();
        func_80098EC8();
        func_80094054();
        releaseAllResources1211C();
        if (r > 0) {
            if (D_8007EF30[1] == 0) {
                D_8007E228[0x608] = 0x7F;
            } else {
                D_8007E228[0x608] = 0;
            }
        }
    } else {
        func_80094AE4(D_800DF4C0, D_800DF3E0, D_800D5F18);
        func_800B7C9C(0);
        func_800C5214(m, 0);
    }
    D_800D5F18++;
    return r;
}
