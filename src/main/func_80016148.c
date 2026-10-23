#include "common.h"

/* Reset the voice's envelope/timer fields. */
s32 func_80016148(void *arg0) {
    *(s32 *)((u8 *)arg0 + 0x4C) = 0;
    *(s32 *)((u8 *)arg0 + 0x48) = 0;
    *(s32 *)((u8 *)arg0 + 0x94) = 0;
    *(s16 *)((u8 *)arg0 + 0xC6) = 0;
    *(s32 *)((u8 *)arg0 + 0x60) = 0;
    *(s32 *)((u8 *)arg0 + 8) = 0;
    return 0;
}
