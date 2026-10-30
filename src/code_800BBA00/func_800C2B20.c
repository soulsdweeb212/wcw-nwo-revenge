/* @header
 * func_800C2B20
 * VRAM 0x800C2B20 | ROM 0xB5FC0 | size 0x6C
 * asm: asm/nonmatchings/code_800BBA00/func_800C2B20.s
 */
#include "common.h"

extern u8 D_8007EF30[];
extern u8 D_800FABE8[], D_800FABEC[], D_800FABEE[];
/* Initialises the 8 animation frames of entity-type arg0 to 150.0f / 15 / 0. */
void func_800C2B20(s8 arg0) {
    s16 i;
    for (i = 0; i < 8; i++) {
        s32 offset = i * 8 + arg0 * 64;
        *(f32 *)(D_800FABE8 + offset) = 150.0f;
        *(s16 *)(D_800FABEC + offset) = 15;
        *(s16 *)(D_800FABEE + offset) = 0;
    }
}
