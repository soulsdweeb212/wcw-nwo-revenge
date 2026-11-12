/* @header
 * func_800C5010
 * VRAM 0x800C5010 | ROM 0x71780 | size 0x190
 * asm: asm/nonmatchings/code_80090000/func_800C5010.s
 */
#include "common.h"

extern u8 *D_800E79B8;
extern s16 D_8006E440;
extern s32 D_80038A98, D_800DF3C0;
#ifdef TARGET_PC
/* PC: the game functions this file calls, declared with their definitions' types (each in the src/main file of its
 * name). */
void func_80008810(void);
void *allocateHeap(u32 bytes);
void initializeMatchResources(void);
void func_8000C91C(s16 arg0, u16 arg1, s16 arg2, s16 arg3, s32 arg4, s8 arg5, s8 arg6);
void func_8000D238(s16 arg0, s8 arg1);
void func_80012B38(s16 arg0, s16 arg1, s16 arg2);
void initSideSlotTransforms(void);
void func_8000E920(void *unused, s16 arg1);
void func_8000DE40(s32 arg0);
void func_8000F620(s16 arg0);
#endif

void func_800C5010(void) {
    s32 i;
    s32 n;
    s16 x;
    u8 *p;

    func_80008810();
    D_8006E440 = 0;
    D_800E79B8 = allocateHeap(0x1B40);
    if (D_80038A98 == 0) {
        D_800DF3C0 = 4;
    } else {
        D_800DF3C0 = 2;
    }
    initializeMatchResources();
    for (i = 0; i < D_800DF3C0; i++) {
        x = i;
        func_8000C91C(x, 1, 0, 0, 0, 0, 0);
        func_8000D238(x, 0x80);
        func_80012B38(x, -1, 2);
    }
    p = D_800E79B8;
    for (i = 0; i < 4; i++, p += 0x6D0) {
        *(s16 *)(p + 0x68C + 8) = -1;
        *(s16 *)(p + 0x68C + 6) = -1;
        *(s16 *)(p + 0x68C + 4) = -1;
        *(s16 *)(p + 0x68C + 0xE) = -1;
        *(s16 *)(p + 0x68C + 0xC) = -1;
        *(s16 *)(p + 0x68C + 0xA) = -1;
        *(s16 *)(p + 0x68C + 0x22) = -1;
        *(s16 *)(p + 0x68C + 0x1E) = -1;
        *(s16 *)(p + 0x68C + 0x20) = -1;
        *(s16 *)(p + 0x68C + 0x1C) = -1;
        *(s16 *)(p + 0x68C + 0x1A) = -1;
        *(s16 *)(p + 0x68C + 0x18) = -1;
        *(s16 *)(p + 0x68C + 0x16) = -1;
        *(s16 *)(p + 0x68C + 0x14) = -1;
        *(s16 *)(p + 0x68C + 0x12) = -1;
        *(s16 *)(p + 0x68C + 0x10) = -1;
        *(s16 *)(p + 0x68C + 0x30) = -1;
        *(s16 *)(p + 0x68C + 0x32) = 0;
        *(s16 *)(p + 0x68C + 0x2A) = 0;
        *(s16 *)(p + 0x68C + 0x28) = 0;
        *(s16 *)(p + 0x68C + 0x26) = 0;
        *(s16 *)(p + 0x68C + 0x24) = 0;
        *(s16 *)(p + 0x68C + 0x2E) = 0;
        *(s32 *)(p + 0x68C + 0x38) = 0x80;
        *(s32 *)(p + 0x68C - 0xC) = 0;
        *(s32 *)(p + 0x68C - 8) = 0;
        *(s32 *)(p + 0x68C - 4) = 0;
        *(s32 *)(p + 0x68C) = 0x800;
    }
    initSideSlotTransforms();
#ifdef TARGET_PC
    /* PC: func_8000E920's first parameter is a pointer that it never reads (func_8000E920.c), so the PC passes NULL
     * where the N64 passes 2. */
    func_8000E920(NULL, 0);
#else
    func_8000E920(2, 0);
#endif
    func_8000DE40(1);
    func_8000F620(0);
}
