/* @header
 * func_800B4BC8
 * VRAM 0x800B4BC8 | ROM 0x61338 | size 0x2C
 * asm: asm/nonmatchings/code_80090000/func_800B4BC8.s
 */
#include "common.h"

typedef struct { u8 x[16]; } S;
extern S D_800CD270[][10];

S *func_800B4BC8(s32 a) {
    return &D_800CD270[a >> 4][a & 0xF];
}
