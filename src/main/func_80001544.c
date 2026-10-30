/* @header
 * func_80001544
 * VRAM 0x80001544 | ROM 0x2144 | size 0x68
 * asm: asm/nonmatchings/main/func_80001544.s
 */
#include "common.h"

extern s32 D_80046860[];
extern s16 D_80047062;
extern u8 *D_80046858;
extern s16 D_80047060;

void func_8001C0F0(void *, s32, s32, f32);
void initIdentityMatrix4x4(void *);

/* Registers the transform node's +0x14 value in the D_80046860 table (no-op if
 * already present). */
void func_80001544(void *arg0) {
    s32 v = *(s32 *)((u8 *)arg0 + 0x14);
    u32 i;

    for (i = 0; i < D_80047062; i++) {
        if (D_80046860[i] == v) {
            return;
        }
    }
    D_80046860[D_80047062] = v;
    D_80047062++;
}
