#include "common.h"

/* cosf: single-precision cosine. For exponents below 310 it reduces x to a
 * small argument around a multiple n of pi/2 (constants D_8003B558..D_8003B580),
 * evaluates the minimax polynomial (D_8003B538..D_8003B550) and flips the sign
 * for odd n. Larger-magnitude inputs lose precision through the reduction, so
 * it returns D_8003B960 for NaN and D_8003B570 otherwise. */
extern f64 D_8003B538;
extern f64 D_8003B540;
extern f64 D_8003B548;
extern f64 D_8003B550;
extern f64 D_8003B558;
extern f64 D_8003B560;
extern f64 D_8003B568;
extern f64 D_8003B578;
extern f64 D_8003B580;
extern f32 D_8003B570;
extern f32 D_8003B960;

f32 cosf(f32 x) {
    double dx;
    double xsq;
    double poly;
    double dn;
    float xabs;
    int n;
    double result;
    int ix;
    int xpt;

    ix = *(int *)&x;
    xpt = (ix >> 22) & 0x1FF;

    if (xpt < 310) {
        xabs = (0 < x) ? x : -x;
        dx = xabs;

        dn = dx * D_8003B558 + D_8003B578;
        if (0 <= dn)
            n = dn + D_8003B578;
        else
            n = dn - D_8003B578;
        dn = n;

        dn -= D_8003B580;
        dx -= dn * D_8003B560;
        dx -= dn * D_8003B568;

        xsq = dx * dx;

        poly = (((D_8003B550 * xsq) + D_8003B548) * xsq + D_8003B540) * xsq + D_8003B538;

        result = dx + ((dx * xsq) * poly);

        if ((n & 0x1) == 0)
            return result;
        else
            return -(float)result;
    }

    if (x != x)
        return D_8003B960;
    return D_8003B570;
}
