/* @header
 * func_8001B980
 * VRAM 0x8001B980 | ROM 0x1C580 | size 0x1C8
 * asm: asm/nonmatchings/main/func_8001B980.s
 */
#include "common.h"

/* Build a perspective projection matrix (like glFrustum) from the given
 * field-of-view (degrees, converted to radians via D_8003B5D0), aspect, near
 * and far planes. The matrix is scaled uniformly, and perspNorm (when given)
 * receives the 16-bit perspective normalization factor (0xFFFF when
 * near+far <= D_8003B5D8, else D_8003B5E0/(near+far), clamped to at least 1).
 * The result is converted and written through out. */
f32 cosf(f32);
f32 sinf(f32);
extern const f64 D_8003B5D0, D_8003B5D8, D_8003B5E0, D_8003B5E8;
void func_8001B090(void *, void *);
void initIdentityMatrix4x4(void *);

void func_8001B980(void *out, u16 *perspNorm, f32 fovy, f32 aspect, f32 near, f32 far, f32 scale) {
    f32 mf[4][4];
    f32 (*m)[4] = mf;
    f32 angle;
    f32 cot;
    s32 i, j;

    initIdentityMatrix4x4(mf);
    angle = fovy * D_8003B5D0;
    angle = angle / 2.0f;
    cot = cosf(angle) / sinf(angle);
    mf[0][0] = cot / aspect;
    mf[1][1] = cot;
    mf[2][2] = (near + far) / (near - far);
    mf[2][3] = -1.0f;
    mf[3][2] = (2 * near * far) / (near - far);
    mf[3][3] = 0;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            m[i][j] *= scale;
    if (perspNorm) {
        if (near + far <= D_8003B5D8) {
            *perspNorm = 0xFFFF;
        } else {
            *perspNorm = (u16)(D_8003B5E0 / (near + far));
            if (*perspNorm == 0)
                *perspNorm = 1;
        }
    }
    func_8001B090(mf, out);
}
