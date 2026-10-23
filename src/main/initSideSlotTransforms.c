#include "common.h"

extern f64 D_8003B298;
extern f64 D_8003B2A0;
extern u8 D_80059D90[];
extern s16 D_8005A380[][3][2];
extern s16 D_8005A382[][3][2];
s32 func_80010200(s32, s16, f32);
s32 initializeTransformNode(void *, s32, f32, f32, f32);
s32 func_80007E14(void *, f32);
s32 nw2Mat4Mul(void *, void *, void *);
s32 func_8000FAF8(u32);
s32 func_80001DC4(void *);

/* Initializes the four side/slot transform records at D_80059D90: sets up each
 * node (offset 230 in Z), rotates it by a per-side angle, recomputes its world
 * matrix, and resets the three {s16,s16} side/slot pairs. */
void initSideSlotTransforms(void) {
    f32 mat[4][4];
    u32 i;
    u32 j;
    f64 d;

    for (i = 0; i < 4; i++) {
        func_80010200(0xB, i, 0.0f);
        initializeTransformNode(&D_80059D90[i * 0xDC], 4, 0.0f, 0.0f, 230.0f);
        d = (f64)(s32)i;
        if ((s32)i < 0) {
            d += D_8003B298;
        }
        func_80007E14(mat, (f32)(d * D_8003B2A0));
        nw2Mat4Mul(&D_80059D90[i * 0xDC + 0x1C], mat, &D_80059D90[i * 0xDC + 0x1C]);
        func_8000FAF8(i);
        func_80001DC4(&D_80059D90[i * 0xDC]);
        for (j = 0; j < 3; j++) {
            D_8005A380[i][j][0] = -1;
            D_8005A382[i][j][0] = 0;
        }
    }
}
