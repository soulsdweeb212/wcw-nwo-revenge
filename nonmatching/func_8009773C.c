#include "common.h"

typedef struct { u32 w0, w1; } G773;
extern u8 D_C95B8[];
void func_8009773C(G773 **arg0, s32 a1, s32 a2, s32 a3, s32 x, s32 w, s32 h, s32 tw, s32 th) {
    G773 *g = *arg0;
    f32 sx, sy;
    sx = (f64)th / w;
    sy = (f64)tw / h;
    g->w0 = 0xDE000000;
    g->w1 = (u32)D_C95B8;
    g++;
    *arg0 = g;
}
