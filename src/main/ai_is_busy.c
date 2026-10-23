#include "common.h"

s32 ai_is_busy(void) {
    s32 value;
    s32 zero;
    value = *(vs32 *)0xA450000C;
    zero = 0;
    return value < zero;
}
