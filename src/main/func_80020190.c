/* @header
 * func_80020190
 * VRAM 0x80020190 | ROM 0x20D90 | size 0x28
 * asm: asm/nonmatchings/main/func_80020190.s
 */
#include "common.h"

typedef struct NwNode2 {
    struct NwNode2 *f0;
    struct NwNode2 *f4;
} NwNode2;

/* Node callback: handle messages 1 and 6 by storing arg2. */
s32 func_80020190(void *arg0, s32 arg1, s32 arg2) {
    switch (arg1) {
    case 1:
        *(s32 *)arg0 = arg2;
        break;
    case 6:
        *(s32 *)((u8 *)arg0 + 0x14) = arg2;
        break;
    }
    return 0;
}

typedef struct {
    s32 f0;
    u32 f4;
    s32 f8;
} NwAllocHdr;
