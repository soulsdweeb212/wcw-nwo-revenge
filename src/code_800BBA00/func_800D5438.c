#include "common.h"

extern u8 D_80030560[];
extern u8 D_8007C438[];

/* Looks up the entity's animation id: indexes the D_80030560 table by its
 * +0x386 anim and the +0x384 row, offsets by arg1 and adds the base 0x110B. */
s16 func_800D5438(u8 *arg0, s32 arg1) {
    s32 idx = *(s16 *)(arg0 + 0x386);
    s32 row = *(s8 *)(arg0 + 0x384);
    u16 t = ((u16 *)(D_80030560 + 0x10))[0 + idx];
    s32 off = (s16)(t + arg1);
    u16 *p = (u16 *)(D_8007C438 + 0x180 + row * 0x600);
    return p[off] + 0x110B;
}
