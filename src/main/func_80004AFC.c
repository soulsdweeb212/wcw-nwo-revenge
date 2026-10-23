#include "common.h"

/* Clear the six leading bytes and the seven word fields of arg0's descriptor. */
void func_80004AFC(void *arg0) {
    *(s8 *)((s8 *)arg0 + 0) = 0;
    *(s8 *)((s8 *)arg0 + 1) = 0;
    *(s8 *)((s8 *)arg0 + 2) = 0;
    *(s8 *)((s8 *)arg0 + 3) = 0;
    *(s8 *)((s8 *)arg0 + 4) = 0;
    *(s8 *)((s8 *)arg0 + 5) = 0;
    *(s32 *)((s8 *)arg0 + 0xC) = 0;
    *(s32 *)((s8 *)arg0 + 0x10) = 0;
    *(s32 *)((s8 *)arg0 + 0x14) = 0;
    *(s32 *)((s8 *)arg0 + 0x18) = 0;
    *(s32 *)((s8 *)arg0 + 0x1C) = 0;
    *(s32 *)((s8 *)arg0 + 0x20) = 0;
    *(s32 *)((s8 *)arg0 + 0x24) = 0;
}
