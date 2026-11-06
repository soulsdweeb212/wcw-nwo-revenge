/* @header
 * func_800B10B8
 * VRAM 0x800B10B8 | ROM 0xA4558 | size 0x84
 * asm: asm/nonmatchings/code_8009D7A0/func_800B10B8.s
 */
#include "common.h"

extern u8 *D_800FABD0;
s8 func_800D4198(s16);
f32 func_800B3AD8(void *);
/* Returns the frames left until the opponent's hit window opens when it is in
 * state 0x44 (and the chance roll passes): anim.hitStart - animFrame - 1,
 * clamped at 0. */
s16 func_800B10B8(void) {
    s16 result = 0;
    if (D_800F9B60->state == 0x44) {
        if (func_800D4198(*(s16 *)(D_800FABD0 + 0x12))) {
            result = D_800F9B60->anim.hitStart - (u16)D_800F9B60->animFrame - 1;
            if (result < 0) result = 0;
        }
    }
    return result;
}
