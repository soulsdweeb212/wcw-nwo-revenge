/* @header
 * func_800C2CDC_ovl1  (originally func_800C2CDC)
 * VRAM 0x800C2CDC | ROM 0x6F44C | size 0xC4
 * asm: asm/nonmatchings/code_80090000/func_800C2CDC_ovl1.s
 */
#include "common.h"


typedef struct { f32 x, y, z; s32 a; } Cam;
typedef struct { u8 pad0[0x680]; Cam cam; u8 pad690[0x6D0 - 0x690]; } P;
typedef struct { u8 pad0[0x54]; f32 x; f32 y; f32 z; u8 pad60[0xB24 - 0x60]; } R;
extern P *D_800E79B8;
extern R D_80070CBC[];

void func_800C2CDC_ovl1(s32 a, f32 *o) {
    f32 *p = o;
    if (a & 4) {
        s32 i = a & 3;
#ifdef TARGET_PC
        /* PC: the records' address as a pointer-wide integer (port.h's uptr); an s32 would cut it in half. */
        uptr b = (uptr)D_800E79B8;
#else
        s32 b = (s32)D_800E79B8;
#endif
        P *q = (P *)(i * sizeof(P) + b);
        o[1] = q->cam.y + 140.0f;
        o[0] = q->cam.x;
        o[2] = q->cam.z;
    } else {
        p[1] = D_80070CBC[a].y + 50.0f;
        p[0] = D_80070CBC[a].x;
        p[2] = D_80070CBC[a].z;
    }
}
