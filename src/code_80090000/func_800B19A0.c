/* @header
 * func_800B19A0
 * VRAM 0x800B19A0 | ROM 0x5E110 | size 0x90
 * asm: asm/nonmatchings/code_80090000/func_800B19A0.s
 */
#include "common.h"

typedef struct { u32 a; u32 b; } P;
extern struct { u8 p[8]; u16 f; u8 q[0x1A6]; P m[4][0x57]; } D_8007EF30;
void func_800B16F0(void);

void func_800B19A0(void) {
    s32 i, j;
    if (D_8007EF30.f & 0x80) {
        func_800B16F0();
    } else {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 0x57; j++) {
                if (D_8007EF30.m[i][j].a < D_8007EF30.m[i][j].b) {
                    D_8007EF30.m[i][j].a = D_8007EF30.m[i][j].b;
                }
            }
        }
    }
}
