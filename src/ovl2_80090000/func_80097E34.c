/* @header
 * func_80097E34
 * VRAM 0x80097E34 | ROM 0x8B2D4 | size 0xC0
 * asm: asm/nonmatchings/ovl2_80090000/func_80097E34.s
 */
#include "common.h"

extern s16 D_800EB19C;
extern void *D_800EB1A4;
extern s16 D_800EB1A8;
extern s16 D_800EB1AA;

s16 func_8000B3C4(s32);
s32 func_8002AD04(s32, s32);
void *func_8002A2FC(u32 key, u16 flags);
void func_8002A5F4(void *entry);

void func_80097E34(s16 id, s16 var) {
    if (D_800EB1A8 != id) {
        D_800EB19C = -1;
        D_800EB1AA = 0;
        if (D_800EB1A4 != NULL) {
            D_800EB1A8 = 4;
            func_8002A5F4(D_800EB1A4);
            D_800EB1A4 = NULL;
        } else {
            D_800EB1A8 = id;
            D_800EB1A4 = func_8002A2FC(func_8002AD04(func_8000B3C4(id), var), 0x8008);
        }
    } else if (D_800EB1A8 >= 0) {
        D_800EB1AA = 1;
    }
}
