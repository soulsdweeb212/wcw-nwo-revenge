/* @header
 * sinf  (originally func_8001BF50)
 * VRAM 0x8001BF50 | ROM 0x1CB50 | size 0x1A0
 * asm: asm/nonmatchings/main/sinf.s
 */
#include "common.h"

extern f64 D_8003B5F8, D_8003B600, D_8003B608, D_8003B610, D_8003B618, D_8003B620, D_8003B628, D_8003B638, D_8003B640;
extern f32 D_8003B630, D_8003B960;
/* f32 sinf(f32 x): fdlibm-style sine on the raw float bits.
 * xpt = biased exponent field (bits 22..30).
 *   < 255 : |x| finite; for tiny |x| (==230..254) return x, else polynomial.
 *   < 310 : large |x| -> Cody-Waite argument reduction by n*(pi/2).
 *   else  : NaN -> D_8003B960, otherwise the pole value D_8003B630. */
f32 sinf(f32 x) {
 double dx, xsq, poly, dn, result;
 int n, ix, xpt;
 ix=*(int *)&x;
 xpt=ix>>22;
 xpt &=0x1ff;
 if(xpt<255) {
 dx=x;
 if(xpt>=230) {
 xsq=dx*dx;
 poly=(((D_8003B610*xsq+D_8003B608)*xsq+D_8003B600)*xsq+D_8003B5F8);
 result=dx+((dx*xsq)*poly);
 return result;
 }
 return x;
 }
 if(xpt<310) {
 dx=x;
 dn=dx*D_8003B618;
 if(0<=dn) n=dn+D_8003B638; else n=dn-D_8003B640;
 dn=n;
 dx-=dn*D_8003B620;
 dx-=dn*D_8003B628;
 xsq=dx*dx;
 poly=(((D_8003B610*xsq+D_8003B608)*xsq+D_8003B600)*xsq+D_8003B5F8);
 result=dx+((dx*xsq)*poly);
 if((n&1)==0) return result; else return -(float)result;
 }
 if(x!=x) return D_8003B960;
 return D_8003B630;
}
