/* @header
 * func_80004BA8
 * VRAM 0x80004BA8 | ROM 0x57A8 | size 0xE8
 * asm: asm/nonmatchings/main/func_80004BA8.s
 */
#include "common.h"

extern void func_8000498C(void *, s16);
extern void func_800015AC(void *, s8);
extern void func_80001544(void *);

typedef struct {
    u8 pad0[2];
    s8 f2;
    s8 f3;
    u8 pad4[2];
    u8 f6;
    u8 pad7[5];
    s32 fC;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    s32 f20;
    s32 f24;
    s32 f28;
} Nw2Def;

typedef struct {
    s32 f0;
    u8 pad0[0x28];
    s16 f2C;
    s16 f2E;
    s32 f30;
    s32 f34;
} Nw2Sub;

/* Initialise entity arg0 from definition src: stash arg2 in the definition, run
 * func_8000498C, copy the appearance fields into arg0, reset it, fill the
 * sub-struct (at arg0+0x14) with the definition's state/frame/size values, then
 * stamp the three positional/behaviour parameters onto arg0. */
void func_80004BA8(u8 *arg0, Nw2Def *src, s32 arg2, s16 arg3, s32 arg4, s32 arg5, s32 arg6)
{
    Nw2Sub *p;

    src->f28 = arg2;
    func_8000498C(src, arg3);
    arg0[0x1A] = src->f6;
    *(s32 *)(arg0 + 0xC) = src->fC;
    func_800015AC(arg0, src->f2);
    p = *(Nw2Sub **)(arg0 + 0x14);
    p->f0 = 1;
    p->f30 = src->fC;
    p->f2C = src->f2;
    p->f2E = src->f3;
    if (src->f10 != 0) {
        p->f34 = src->f10;
    } else if (src->f14 != 0) {
        p->f34 = src->f14;
    }
    func_80001544(arg0);
    *(s32 *)(arg0 + 0) = arg4;
    *(s32 *)(arg0 + 4) = arg5;
    *(s32 *)(arg0 + 8) = arg6;
}
