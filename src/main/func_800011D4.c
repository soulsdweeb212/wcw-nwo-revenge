/* @header
 * func_800011D4
 * VRAM 0x800011D4 | ROM 0x1DD4 | size 0x84
 * asm: asm/nonmatchings/main/func_800011D4.s
 */
#include "common.h"

extern void func_80090000(void);

extern void bzero(void *, s32);
extern void osEPiLinkHandle(void *);
extern u8 D_8003DDB8[];
extern u8 D_8003DDBC, D_8003DDBD, D_8003DDBE, D_8003DDBF, D_8003DDC0, D_8003DDC1;
extern s32 D_8003DDC4, D_8003DDC8;

extern s32 osSetIntMask(s32);

extern s32 osRecvMesg(u8 *, s32, s32);
extern s32 osViGetCurrentFramebuffer(void);
extern s32 osViGetNextFramebuffer(void);
extern u8 D_800441D8[];

/* Blocks until the RSP queue is empty and neither of the two task ids equals the
 * object's +0xC value. */
void func_800011D4(u8 *arg0) {
    s32 v = *(s32 *)(arg0 + 0xC);
    while (osRecvMesg(D_800441D8, 0, 0) != -1) { }
    for (;;) {
        if (osViGetCurrentFramebuffer() == v || osViGetNextFramebuffer() == v) {
            osRecvMesg(D_800441D8, 0, 1);
        } else break;
    }
}
