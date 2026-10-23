#include "common.h"

extern f64 D_8003B8B0;
extern f64 D_8003B8B8;

/* Scales arg1 by the object's +0x44 rate and applies the D_8003B8B0/B8B8 bias. */
s32 func_80020894(void *arg0, s32 arg1) {
    return (s32) (f32) (((f64) ((f32) arg1 * (f32) *(s32 *)((u8 *)arg0 + 0x44)) / D_8003B8B0) + D_8003B8B8);
}
