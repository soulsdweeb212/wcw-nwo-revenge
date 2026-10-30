/* @header
 * setCameraView  (originally func_800055AC)
 * VRAM 0x800055AC | ROM 0x61AC | size 0x120
 * asm: asm/nonmatchings/main/func_800055AC.s
 */
#include "common.h"

extern f32 D_80048500[4][4], D_80048540[4][4];   /* perspective / view matrices */
extern f32 D_80048580, D_80048584, D_80048588;   /* cached eye position (x/y/z) */
void buildPerspectiveMatrixFloat(void *, u16 *, f32, f32, f32, f32, f32);
void func_8001A980(void *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
void func_800014AC(s32, void *, void *);
void func_800014D0(s32, u16);

/* Build the perspective projection from (fov, aspect, zNear, zFar, scale) and a
 * camera-view matrix from the eye position (eyeX/Y/Z) and rotation
 * (rotX/Y/Z, with up = (0,1,0)), then install both plus the computed viewport
 * norm on display-list arg0. */
void setCameraView(s32 gfx, f32 fov, f32 aspect, f32 zNear, f32 zFar, f32 scale,
                   f32 eyeX, f32 eyeY, f32 eyeZ, f32 rotX, f32 rotY, f32 rotZ) {
    u16 norm;
    D_80048580 = eyeX; D_80048584 = eyeY; D_80048588 = eyeZ;
    buildPerspectiveMatrixFloat(D_80048500, &norm, fov, aspect, zNear, zFar, scale);
    func_8001A980(D_80048540, eyeX, eyeY, eyeZ, rotX, rotY, rotZ, 0.0f, 1.0f, 0.0f);
    func_800014AC(gfx, D_80048500, D_80048540);
    func_800014D0(gfx, norm);
}
