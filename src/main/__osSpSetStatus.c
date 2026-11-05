/* @header
 * __osSpSetStatus  (originally func_80027390)
 * VRAM 0x80027390 | ROM 0x27F90 | size 0x10
 * asm: asm/nonmatchings/main/__osSpSetStatus.s
 */
/* SDK: libultra 2.0I, ultralib src/io/spsetstat.c (same code as the SDK source). */
#include "common.h"

extern s32 D_800388A0;
extern u8 D_80064AB0[];
extern u8 D_8007E210[];
extern s32 D_80037600;
extern s32 D_80037608;
extern s32 D_A4080000;

s32 osCreateMesgQueue(void *, void *, s32);
s32 osRecvMesg(void *, void *, s32);
s32 osSendMesg(void *, s32, s32);

void __osSpSetStatus(s32 arg0) {
    *(vu32 *)0xA4040010 = arg0;
}
