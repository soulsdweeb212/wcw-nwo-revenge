#include "common.h"

extern f32 D_80048500[4][4], D_80048540[4][4];
extern f32 D_80048580, D_80048584, D_80048588;
void buildPerspectiveMatrixFloat(void *, u16 *, f32, f32, f32, f32, f32);
void func_8001A980(void *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
void func_800014AC(s32, void *, void *);
void func_800014D0(s32, u16);
/* Build and apply the camera matrices for the render object arg0: cache the eye
 * position (D_80048580/584/588), build the perspective projection
 * (FOV 33 deg, aspect 4/3, near 100, far 4000) into D_80048500, build the
 * look-at view into D_80048540, then submit both matrices and the projection's
 * near/far scale to the object. */
void func_80005304(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    u16 norm;
    D_80048580 = arg1; D_80048584 = arg2; D_80048588 = arg3;
    buildPerspectiveMatrixFloat(D_80048500, &norm, 33.0f, 1.3333334f, 100.0f, 4000.0f, 1.0f);
    func_8001A980(D_80048540, arg1, arg2, arg3, arg4, arg5, arg6, 0.0f, 1.0f, 0.0f);
    func_800014AC(arg0, D_80048500, D_80048540);
    func_800014D0(arg0, norm);
}
