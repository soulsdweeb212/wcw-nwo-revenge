/* @header
 * func_800B6114
 * VRAM 0x800B6114 | ROM 0xA95B4 | size 0xD8
 * asm: asm/nonmatchings/code_8009D7A0/func_800B6114.s
 */
#include "common.h"

extern f32 D_800E3C50[];
extern f32 D_800E3C54[];
extern f64 D_800E5508;
s8 func_800B4C60(void *, void *, s32, s32);
f32 func_800D3890(void *, void *, void *);
void func_800D37C0(void *, f32, void *);
void translateEntityXZ(void *, void *);

typedef struct {
    f32 x, y, z;
    s32 angle;
} DirResult;

s32 func_800B6114(void *arg0, void *arg1) {
    f32 v[3];
    DirResult dir;
    f32 tmp[4];

    if (func_800B4C60(arg0, arg1, 0, 1)) {
        return 0;
    }
    v[0] = D_800E3C50[*(s16 *)((u8 *)arg0 + 0x3E) * 2];
    v[2] = D_800E3C54[*(s16 *)((u8 *)arg0 + 0x3E) * 2];
    func_800D3890(v, (u8 *)arg0 + 0x6C, &dir);
    if ((f64)dir.y <= D_800E5508) {
        func_800D37C0((void *)dir.angle, (f32)(D_800E5508 - (f64)dir.y), tmp);
        translateEntityXZ(arg0, tmp);
        return 1;
    }
    return 0;
}
