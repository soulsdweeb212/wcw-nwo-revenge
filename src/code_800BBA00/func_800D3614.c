#include "common.h"

s16 func_800D3638(s32);

/* Quadrant (0..7) of the angle arg0 rotated by 0x800. */
s16 func_800D3614(s32 arg0) {
    return func_800D3638(arg0 + 0x800);
}
