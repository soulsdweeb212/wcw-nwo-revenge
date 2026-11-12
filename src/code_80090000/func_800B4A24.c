/* @header
 * func_800B4A24
 * VRAM 0x800B4A24 | ROM 0x61194 | size 0x1A4
 * asm: asm/nonmatchings/code_80090000/func_800B4A24.s
 */
#include "common.h"

extern s16 D_80038A90;
extern u8 *D_800E95C4[], *D_800E96FC[];
extern u8 D_8007EF30[];
extern s16 D_800E96EC, D_800E95B4;
extern s32 D_800EA0B8;
extern s32 D_800DC830[], D_800DC840[], D_800EA098[];
extern u16 D_800CD89C[];
#ifdef TARGET_PC
/* PC: func_800B48CC declared with its definition's types (func_800B48CC.c); C99 has no implicit declarations. */
s32 func_800B48CC(s32 k);
#endif

s32 func_800B4A24(void) {
    u8 *p = D_800E95C4[0];
    s32 r, i, n;
    u16 f;

    if (D_80038A90 == 0xF) {
        f = *(u16 *)(D_8007EF30 + 8);
        if (f & 0x8000) {
#ifdef TARGET_PC
            /* PC: D_8007EF30 keeps its N64 layout, so its +0x30, the address of the cup record, is 4 bytes and holds
             * a handle (port.h's PTR_TO_SLOT), as func_800AA1E0 reads it. */
            n = *(u16 *)((u8 *)SLOT_TO_PTR(*(u32 *)(D_8007EF30 + 0x30)) + 8);
#else
            n = *(u16 *)(*(u8 **)(D_8007EF30 + 0x30) + 8);
#endif
        } else {
            switch (f & 0xF0) {
            case 0x20:
                n = 1;
                break;
            case 0x40:
                n = 7;
                break;
            case 0x80:
                n = 8;
                break;
            default:
                n = 0;
                break;
            }
        }
        D_800EA0B8 = n;
        r = func_800B48CC(n);
        for (i = 0; i < 4; i++) {
            if (D_800EA098[i] >= 0) {
                *(u16 *)(p + D_800EA098[i] * 0x148 + 0x22) = D_800CD89C[D_800DC830[D_800DC840[i]]];
            }
        }
    } else {
        D_800EA0B8 = 0;
        r = func_800B48CC(0);
    }
    D_800E96EC = 0xA;
    D_800E95B4 = 0xA;
    *(u16 *)(D_800E95C4[0] + 0xF6A) |= 1;
    *(u16 *)(D_800E95C4[0] + 0x10B2) |= 1;
    *(u16 *)(D_800E96FC[0] + 0xF6A) |= 1;
    *(u16 *)(D_800E96FC[0] + 0x10B2) |= 1;
    return r;
}
