/* @header
 * checkFacingProximity  (originally func_800D24C8)
 * VRAM 0x800D24C8 | ROM 0xC5968 | size 0x100
 * asm: asm/nonmatchings/code_800BBA00/func_800D24C8.s
 */
#include "common.h"

typedef struct {
    u8 pad0[0x20];
    u64 flags;
    u8 pad28[0x30];
    s32 f58;
    u8 pad5C[0x10];
    f32 f6C;
    u8 pad70[4];
    f32 f74;
} Nw2ObjD24C8;

extern f64 D_800E6B08;
extern f64 D_800E6B10;

/* Returns 1 when arg1 (flagged 0x40) is within a 0x400 heading of arg0
 * (flagged 0x100) and arg0's X (f6C) and Z (f74) both lie strictly inside
 * (D_800E6B08, D_800E6B10). */
s32 checkFacingProximity(Nw2ObjD24C8 *arg0, Nw2ObjD24C8 *arg1, s32 arg2) {
    f64 f, g;
    if (!(arg0->flags & 0x100))
        return 0;
    if (!(arg1->flags & 0x40))
        return 0;
    if (func_800D3550(func_800D3684(arg2, arg0->f58)) >= 0x400)
        return 0;
    f = arg0->f6C;
    if (!(D_800E6B08 < f))
        return 0;
    if (!(f < D_800E6B10))
        return 0;
    g = arg0->f74;
    if (!(D_800E6B08 < g))
        return 0;
    if (g < D_800E6B10)
        return 1;
    return 0;
}
