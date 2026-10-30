/* @header
 * __osCheckId  (originally func_800227B4)
 * VRAM 0x800227B4 | ROM 0x233B4 | size 0xB8
 * asm: asm/nonmatchings/main/__osCheckId.s
 */
#include "common.h"

s32 __osContRamRead(s32, s32, s32, void *);
s32 func_80025480(void *, s32);
s32 bcmp(void *, void *, s32);

/* Reads the Controller Pak id block and compares it with the id stored in the
 * pfs header, retrying once on a transient error. Returns 2 when the ids differ. */
s32 __osCheckId(u8 *arg0) {
    s32 v;
    u8 buf[0x20];

    if (arg0[0x65] != 0) {
        v = func_80025480(arg0, 0);
        if (v == 2)
            v = func_80025480(arg0, 0);
        if (v != 0)
            return v;
    }
    v = __osContRamRead(*(s32 *)(arg0 + 4), *(s32 *)(arg0 + 8), 1, buf);
    if (v != 0) {
        if (v != 2)
            return v;
        v = __osContRamRead(*(s32 *)(arg0 + 4), *(s32 *)(arg0 + 8), 1, buf);
        if (v != 0)
            return v;
    }
    return (bcmp(arg0 + 0xC, buf, 0x20) != 0) << 1;
}

typedef struct {
    u8 b[8];
} Ent8;

extern Ent8 D_8006A260[];
