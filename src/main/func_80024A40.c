/* @header
 * func_80024A40
 * VRAM 0x80024A40 | ROM 0x25640 | size 0xF8
 * asm: asm/nonmatchings/main/func_80024A40.s
 */
#include "common.h"

extern s32 __osCheckId(void *);
extern s32 __osContRamRead(void *, s32, s32, void *);
extern s32 func_80025480(u8 *, s32);

typedef struct {
    u32 value;
    u16 status;
    u16 dummy;
    u8 body[32];
} PakReadResult;

/* Read a range of Controller Pak blocks (count at +0x50, start at +0x5C) via
 * __osContRamRead and count those whose value word is non-zero. Stores the
 * non-zero count in *sumOut and the block count in *countOut. Returns 0 or a
 * Controller Pak error code (5 = no pak, plus __osCheckId / read errors). */
s32 func_80024A40(u8 *arg0, s32 *countOut, s32 *sumOut) {
    PakReadResult result;
    s32 status;
    s32 block;
    s32 nonZero = 0;

    if (!(*(u32 *)arg0 & 1)) {
        return 5;
    }
    status = __osCheckId(arg0);
    if (status != 0) {
        return status;
    }
    if (*(u8 *)(arg0 + 0x65) != 0) {
        status = func_80025480(arg0, 0);
        if (status != 0) {
            return status;
        }
    }
    block = 0;
    if (*(s32 *)(arg0 + 0x50) > 0) {
        do {
            status = __osContRamRead(*(void **)(arg0 + 4), *(s32 *)(arg0 + 8),
                                     (*(s32 *)(arg0 + 0x5C) + block) & 0xFFFF, &result);
            if (status != 0) {
                return status;
            }
            if (result.status != 0) {
                nonZero += (result.value != 0);
            }
            block++;
        } while (block < *(s32 *)(arg0 + 0x50));
    }
    *sumOut = nonZero;
    *countOut = *(s32 *)(arg0 + 0x50);
    return 0;
}
