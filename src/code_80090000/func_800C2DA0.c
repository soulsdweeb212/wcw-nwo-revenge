/* @header
 * func_800C2DA0
 * VRAM 0x800C2DA0 | ROM 0x6F510 | size 0xB0
 * asm: asm/nonmatchings/code_80090000/func_800C2DA0.s
 */
#include "common.h"

typedef struct { u8 p[0x54]; f32 x; f32 y; f32 z; u8 q[0xAC4]; } S;
extern S D_80070CBC[];

void func_800C2DA0(s32 i, f32 *o, s32 flag) {
    S *s = &D_80070CBC[i];
    o[0] = s->x;
    o[2] = s->z;
    if (flag) {
        if (-300.0f < o[0] && o[0] < 300.0f && -300.0f < o[2] && o[2] < 300.0f) {
            o[1] = 90.0f;
        }
    }
}
