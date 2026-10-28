#include "common.h"

extern u16 D_800EB4B8[];

/* Add `delta` to the signed-byte part value at entity+index+0x34C, wrapping as
 * a byte and clamping to 0 on underflow. */
void func_800BF228(s32 entity, s16 index, s32 delta) {
    u8 *value = (u8 *)(entity + index + 0x34C);
    u8 sum = *value + delta;

    *value = sum;
    if ((s8)sum < 0) {
        *value = 0;
    }
}
