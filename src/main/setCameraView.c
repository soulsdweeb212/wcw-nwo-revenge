/* @header
 * setCameraView  (originally func_800055AC)
 * VRAM 0x800055AC | ROM 0x61AC | size 0x120
 * asm: asm/nonmatchings/main/setCameraView.s
 */
#include "common.h"

extern f32 D_80048500[4][4], D_80048540[4][4];   /* perspective / view matrices */
extern f32 D_80048580, D_80048584, D_80048588;   /* cached eye position (x/y/z) */
void guPerspectiveF(void *, u16 *, f32, f32, f32, f32, f32);
void guLookAtF(void *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
#ifndef TARGET_PC /* on PC, port_decls.h declares func_800014AC and func_800014D0 */
void func_800014AC(s32, void *, void *);
void func_800014D0(s32, u16);
#endif

/* Build the perspective projection from (fov, aspect, zNear, zFar, scale) and a
 * camera-view matrix from the eye position (eyeX/Y/Z) and rotation
 * (rotX/Y/Z, with up = (0,1,0)), then install both plus the computed viewport
 * norm on display-list arg0. */
#ifdef TARGET_PC
/* PC: gfx is the camera's record (func_800B83D0 passes its id, the record's address), which this function only passes
 * on to func_800014AC and func_800014D0, as func_80005304 and setupTiltedPerspectiveCamera do. The N64 definition
 * takes it as an s32, which on PC would cut the address in half, so the PC definition takes a pointer. */
void setCameraView(void *gfx, f32 fov, f32 aspect, f32 zNear, f32 zFar, f32 scale,
                   f32 eyeX, f32 eyeY, f32 eyeZ, f32 rotX, f32 rotY, f32 rotZ) {
#else
void setCameraView(s32 gfx, f32 fov, f32 aspect, f32 zNear, f32 zFar, f32 scale,
                   f32 eyeX, f32 eyeY, f32 eyeZ, f32 rotX, f32 rotY, f32 rotZ) {
#endif
    u16 norm;
    D_80048580 = eyeX; D_80048584 = eyeY; D_80048588 = eyeZ;
    guPerspectiveF(D_80048500, &norm, fov, aspect, zNear, zFar, scale);
    guLookAtF(D_80048540, eyeX, eyeY, eyeZ, rotX, rotY, rotZ, 0.0f, 1.0f, 0.0f);
    func_800014AC(gfx, D_80048500, D_80048540);
    func_800014D0(gfx, norm);
}
