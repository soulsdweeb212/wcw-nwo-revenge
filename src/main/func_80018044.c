#include "common.h"

extern void *D_80036F54;
extern f64 D_8003B420;
extern f64 D_8003B428;

/* Scale arg0 by D_80036F54's +0x40 field, convert to fixed point, and round down to
 * a multiple of 16. */
s32 func_80018044(s32 arg0) {
    return (s32) (f32) (((f64) ((f32) arg0 * (f32) *(s32 *)((s8 *)D_80036F54 + 0x40)) / D_8003B420) + D_8003B428) & ~0xF;
}
