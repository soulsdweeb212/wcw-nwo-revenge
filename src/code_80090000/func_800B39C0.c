/* @header
 * func_800B39C0
 * VRAM 0x800B39C0 | ROM 0x60130 | size 0x20C
 * asm: asm/nonmatchings/code_80090000/func_800B39C0.s
 */
#include "common.h"

typedef struct { u8 pad0[0x20]; u16 f20; u8 pad22[0x148 - 0x22]; } El;

extern s32 D_8007E8C0[], D_800DC830[], D_800DC840[], D_800DC850[], D_800E7BF0[], D_800E79A0[], D_800EA098[];
extern u8 D_8007EF30[], D_800E7C60[][8];
extern u8 *D_800E948C;
void func_80021F60(void *, s32);
void func_800B3640(void);
void func_800B5300(s32);

s32 func_800B39C0(void) {
    u8 *p = D_800E948C + 0xCD0;
    s32 r = 0xD;
    s32 i;
    s32 v;
    s32 pad[4];
    El *w;

    for (i = 0; i < 4; i++) {
        D_800E7BF0[i] = -1;
        D_800DC850[i] = -1;
        D_800DC840[i] = -1;
        D_800DC830[i] = -1;
        D_800EA098[i] = -1;
        func_80021F60(D_800E7C60[i], 8);
    }
    for (i = 0, w = (El *)p; i < 4; i++, w += 2) {
        v = w->f20;
        if (!(v & 0xC)) {
            D_800DC850[i] = v & 3;
            D_800DC830[i] = D_8007E8C0[v & 3] - 1;
            D_800DC840[D_800DC830[i]] = i;
            w->f20 |= 0x10;
            D_800E7BF0[D_800DC830[i]] = 0;
            D_800E79A0[D_800DC830[i]] = 0;
        }
    }
    if ((*(s32 *)(D_8007EF30 + 8) & 0x88000000) != 0x80000000) {
        func_800B3640();
        for (i = 0; i < 4; i++) {
            if (D_800E7BF0[i] >= 0) {
                r = 0xB;
                func_800B5300(D_800DC840[i] + 0x436);
            }
        }
    }
    return r << 8;
}
