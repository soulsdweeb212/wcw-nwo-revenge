/* @header
 * func_800169D4
 * VRAM 0x800169D4 | ROM 0x175D4 | size 0x3C
 * asm: asm/nonmatchings/main/func_800169D4.s
 */
#include "common.h"

extern f64 D_8003B3F0; /* byte-to-value scale, 100/4096 = 0.0244140625 */

/* Consume one encoded byte from `cursor` and update `obj`:
 *   obj+0x8C = byte * D_8003B3F0   (byte widened through f32/f64)
 *   obj+0x38 = (obj+0x90)^2
 * Returns the advanced stream cursor. */
void *func_800169D4(void *obj, u8 *cursor) {
    f32 value = *(f32 *)((u8 *)obj + 0x90);
    f32 valueSquared = value * value;

    *(f32 *)((u8 *)obj + 0x8C) = (f32)((f64)(f32)*cursor * D_8003B3F0);
    *(f32 *)((u8 *)obj + 0x38) = valueSquared;
    return cursor + 1;
}
