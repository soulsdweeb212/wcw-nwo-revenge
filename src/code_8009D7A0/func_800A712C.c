/* @header
 * func_800A712C
 * VRAM 0x800A712C | ROM 0x9A5CC | size 0x5C
 * asm: asm/nonmatchings/code_8009D7A0/func_800A712C.s
 */
#include "common.h"

s32 func_800D36E8(f32, f32);
void unpackAnimationParameters(void *, void *);
extern u8 D_8007BD64[];
void func_800D4AD0(void *);
void func_800D3890(void *, void *, void *);
/* Measures from a's pelvis joint (jointA[1]) to b's with func_800D3890 (XZ only): optionally returns the heading
 * from a to b through outHeading and the XZ distance through outDist. */
void func_800A712C(Wrestler *a, Wrestler *b, s32 *outHeading, f32 *outDist) {
    struct { f32 dx, dist, dz; s32 heading; } result;
    func_800D3890(&a->jointA[1], &b->jointA[1], &result);
    if (outHeading != NULL) *outHeading = result.heading;
    if (outDist != NULL) *outDist = result.dist;
}
