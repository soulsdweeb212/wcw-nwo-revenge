/* @header
 * func_8009A69C
 * VRAM 0x8009A69C | ROM 0x8DB3C | size 0x78
 * asm: asm/nonmatchings/ovl2_80090000/func_8009A69C.s
 */
#include "common.h"

typedef struct {
    f32 x, y, z;
    f32 rot;
} Pos;

s16 func_8000CF64(f32, f32);
void func_80007E14(void *, f32);
void func_80007E04(void *, f32, f32, f32);

void func_8009A69C(u8 *obj, Pos *p) {
    if (func_8000CF64(p->x, p->z)) {
        p->y = 90.0f;
    } else {
        p->y = 0.0f;
    }
    func_80007E14(obj + 0x1C, p->rot);
    func_80007E04(obj + 0x1C, p->x, p->y, p->z);
}
