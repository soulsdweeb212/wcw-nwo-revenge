/* @header
 * func_8009F800
 * VRAM 0x8009F800 | ROM 0x4BF70 | size 0xBC
 * asm: asm/nonmatchings/code_80090000/func_8009F800.s
 */
#include "common.h"

void func_80099748(u32 **, s32, s32, s32, s32);

void func_8009F800(u32 **dl, s32 c, s16 *v) {
    s16 o[3];
    u32 *g = *dl;
    s32 i;
    for (i = 0; i < 3; i++) {
        if (v[i] < 0x20) {
            o[i] = 0;
        } else if (v[i] < 0x60) {
            o[i] = 0x3F;
        } else if (v[i] < 0xA0) {
            o[i] = 0x7F;
        } else if (v[i] < 0xE0) {
            o[i] = 0xBF;
        } else {
            o[i] = 0xFF;
        }
    }
    func_80099748(&g, o[0], o[1], o[2], c);
    *dl = g;
}
