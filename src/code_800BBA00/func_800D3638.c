#include "common.h"

s32 func_800D3638(s32 arg0) {
    s32 v = arg0;
    v += 0x1100;
    if (v < 0) {
        v += 0x1FF;
    }
    return (v >> 9) & 7;
}
