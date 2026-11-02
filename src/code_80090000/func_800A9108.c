/* @header
 * func_800A9108
 * VRAM 0x800A9108 | ROM 0x55878 | size 0x108
 * asm: asm/nonmatchings/code_80090000/func_800A9108.s
 */
#include "common.h"

typedef struct { u8 b[8]; u8 pad[8]; } X;
extern u8 D_8007EF30[];
extern s32 D_800EA31C;
void func_800A9E74(s32, s32, s32, s32, s32);
#define XX ((X *)(D_8007EF30 + 0x54))

void func_800A9108(void) {
    s32 i;
    for (i = 0; i < 8; i++) {
        func_800A9E74(i * 2, -1, -1, 0, 5);
        func_800A9E74(i * 2 + 1, -1, -1, 0, 5);
        XX[i * 2].b[0] = 0xFF;
        XX[i * 2].b[5] = 0x32;
        XX[i * 2].b[4] = 0x32;
        XX[i * 2].b[3] = 0x32;
        XX[i * 2].b[2] = 0x32;
        XX[i * 2].b[1] = 0x32;
        XX[i * 2].b[7] = 0;
        XX[i * 2].b[6] = 0;
        XX[i * 2 + 1].b[0] = 0xFF;
        XX[i * 2 + 1].b[5] = 0x32;
        XX[i * 2 + 1].b[4] = 0x32;
        XX[i * 2 + 1].b[3] = 0x32;
        XX[i * 2 + 1].b[2] = 0x32;
        XX[i * 2 + 1].b[1] = 0x32;
        XX[i * 2 + 1].b[7] = 0;
        XX[i * 2 + 1].b[6] = 0;
    }
    *(s32 *)(D_8007EF30 + 0xD00) = 0;
    D_800EA31C = 0;
}
