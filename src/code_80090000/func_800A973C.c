/* @header
 * func_800A973C
 * VRAM 0x800A973C | ROM 0x55EAC | size 0x44
 * asm: asm/nonmatchings/code_80090000/func_800A973C.s
 */
#include "common.h"

typedef struct { u16 y; u8 p[0x136]; } S;
extern S D_800E8234[];
extern u16 D_80038A90, D_80038A92, D_80038A94;

void func_800A973C(void) {
    s16 a = D_80038A90;
    D_80038A92 = a;
    D_80038A94 = D_800E8234[a].y;
}
