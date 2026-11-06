/* @header
 * stepEntityXZQuadraticSpline  (originally func_800D732C)
 * VRAM 0x800D732C | ROM 0xCA7CC | size 0x140
 * asm: asm/nonmatchings/code_800BBA00/stepEntityXZQuadraticSpline.s
 */
#include "common.h"

extern f64 D_800E6D98;
extern f32 D_800F97F0[],D_800F9800[];
extern s8 D_800FADB8;
void func_800D4028(f32,f32 *);

/* Moves w along the 3-point curve pts (rows of 4 floats; x in [0], z in [2]) of slot D_800FADB8: the slot's
 * parameter D_800F97F0[slot] (clamped to 1.0 once it reaches D_800E6D98 = 1.0) gives the three quadratic B-spline
 * weights (func_800D4028), and w->x / w->z become the weighted sums of the points' x / z. Returns 1 when the
 * parameter had reached 1.0,
 * otherwise adds the slot's step D_800F9800[slot] to it and returns 0. */
s32 stepEntityXZQuadraticSpline(Wrestler *w,f32 pts[][4]) {
    f32 wt[3];
    f64 threshold=D_800E6D98;
    if(D_800F97F0[D_800FADB8]>=threshold) D_800F97F0[D_800FADB8]=1.0f;
    func_800D4028(D_800F97F0[D_800FADB8],wt);
    w->x=wt[0]*pts[0][0]+wt[1]*pts[1][0]+wt[2]*pts[2][0];
    w->z=wt[0]*pts[0][2]+wt[1]*pts[1][2]+wt[2]*pts[2][2];
    if(D_800F97F0[D_800FADB8]>=threshold) return 1;
    D_800F97F0[D_800FADB8]+=D_800F9800[D_800FADB8];
    return 0;
}
