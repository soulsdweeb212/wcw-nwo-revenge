#include "common.h"

extern u32 D_800604C8;
extern u8 *D_800604D0;

/* Parses a 16-bit envelope value (with a 0x80 high-bit escape) into +0xCE. */
void *func_80016168(void *arg0, u8 *arg1) {
    s32 v = *arg1++;

    if (v & 0x80) {
        v = *arg1++ | ((v & 0x7F) << 8);
    }
    *(u16 *)((u8 *)arg0 + 0xCE) = v;
    return arg1;
}
