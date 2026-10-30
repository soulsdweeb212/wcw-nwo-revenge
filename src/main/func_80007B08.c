/* @header
 * func_80007B08
 * VRAM 0x80007B08 | ROM 0x8708 | size 0x48
 * asm: asm/nonmatchings/main/func_80007B08.s
 */
#include "common.h"

s32 releaseHeapBlock(s32);

/* Reset two allocation groups in arg0: clear the s16 counters at +4/+6 and release
 * and clear the pointer at +0, then the same at +0xC/+0xE and +8. */
void func_80007B08(void *arg0) {
    *(s16 *)((s8 *)arg0 + 6) = 0;
    *(s16 *)((s8 *)arg0 + 4) = 0;
    releaseHeapBlock(*(s32 *)((s8 *)arg0 + 0));
    *(s32 *)((s8 *)arg0 + 0) = 0;
    *(s16 *)((s8 *)arg0 + 0xE) = 0;
    *(s16 *)((s8 *)arg0 + 0xC) = 0;
    releaseHeapBlock(*(s32 *)((s8 *)arg0 + 8));
    *(s32 *)((s8 *)arg0 + 8) = 0;
}
