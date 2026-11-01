/* @header
 * func_800B0408
 * VRAM 0x800B0408 | ROM 0x5CB78 | size 0xB4
 * asm: asm/nonmatchings/code_80090000/func_800B0408.s
 */
#include "common.h"

extern u8 D_8007EF30[];
extern u8 *D_800E8724;
extern f64 D_800D66D8, D_800D66E0;

void func_800B0408(void) {
    u8 *e = D_800E8724;
    s32 n = 3;
    f64 x;
    if (D_8007EF30[0x14D] & 1) {
        *(u16 *)(e + 0x3E2) &= ~1;
        *(f32 *)(e + 0x3DC) = 65.0f;
        n = 4;
    } else {
        *(u16 *)(e + 0x3E2) |= 1;
    }
    e = D_800E8724;
    if (D_8007EF30[0x14D] & 2) {
        x = (n - D_800D66D8) * D_800D66E0;
        *(u16 *)(e + 0x52A) &= ~1;
        *(f32 *)(e + 0x524) = x;
    } else {
        *(u16 *)(e + 0x52A) |= 1;
    }
}
