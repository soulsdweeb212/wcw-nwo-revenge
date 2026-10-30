/* @header
 * func_8001656C
 * VRAM 0x8001656C | ROM 0x1716C | size 0x58
 * asm: asm/nonmatchings/main/func_8001656C.s
 */
#include "common.h"

extern u8 D_80062520;
extern s32 D_80062524;
extern s32 D_80062528;
extern s32 D_8006255C;
extern s32 D_80036F38;
extern f64 D_8003B3E8;
extern void *D_80036F54;
void func_800171B4(void);
s32 func_8001C740(s32);

/* Decode a signed delta into the float at arg0+0xAC and advance the float at
 * arg0+0x44 by it. */
u8 *func_8001656C(void *arg0, u8 *arg1) {
    s32 v = *arg1++;
    f32 f, d;

    if (v & 0x80) {
        v |= 0xFFFFFF00;
    }
    f = (f32)v / D_8003B3E8;
    d = *(f32 *)((u8 *)arg0 + 0x44) - *(f32 *)((u8 *)arg0 + 0xAC);
    d += f;
    *(f32 *)((u8 *)arg0 + 0xAC) = f;
    *(f32 *)((u8 *)arg0 + 0x44) = d;
    return arg1;
}
