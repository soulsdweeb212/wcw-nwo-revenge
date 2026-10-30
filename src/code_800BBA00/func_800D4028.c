/* @header
 * func_800D4028
 * VRAM 0x800D4028 | ROM 0xC74C8 | size 0x60
 * asm: asm/nonmatchings/code_800BBA00/func_800D4028.s
 */
#include "common.h"

extern f64 D_800E6C00, D_800E6C08, D_800E6BD0, D_800E6BB0;
f32 cosf(f32);
f32 sinf(f32);
f32 func_80003A3C(f32,f32);
f32 nw2Sqrtf(f32);
s32 func_8001C580(void);
s16 func_800D4204(void);
extern s32 gRandSeed, D_800EB634;
extern s16 D_800EB638[];
typedef union { f32 f; s32 i; } NwFI;
typedef struct { NwFI e[4]; } NwV4;

/* Evaluate the three quadratic spline basis weights at t. */
void func_800D4028(f32 t, f32 *out) {
 f32 a,b,c;
 f64 u = D_800E6C00 - (f64)t;
 a = u*u*D_800E6C08;
 b = u*(f64)t+D_800E6C08;
 c = (f64)(t*t)*D_800E6C08;
 *out++ = a; *out++ = b; *out = c;
}
