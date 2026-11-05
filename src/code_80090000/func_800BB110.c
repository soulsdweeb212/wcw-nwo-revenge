/* @header
 * func_800BB110
 * VRAM 0x800BB110 | ROM 0x67880 | size 0x190
 * asm: asm/nonmatchings/code_80090000/func_800BB110.s
 */
#include "common.h"

extern u8 D_800DCFD8[], D_800DCFF8[];
extern u8 D_800DCFDA;
extern u8 *D_800DCFDC, *D_800DCFE0, *D_800DCFB8;
extern s32 D_800DCFD4, D_800DCFE4, D_800DCFE8;

void func_800BB110(void) {
    u8 *b;
    u8 *q;
    s32 i;
    s32 j;
    s32 sp10;

    b = allocateHeap(0x100);
    bzero(b, 0x20);
    for (j = 0; j < 0x20; j += 4) {
        b[j] = 0x19;
        b[j + 1] = 0x97;
        b[j + 2] = 0x10;
        b[j + 3] = 0x21;
    }
    osWritebackDCache(b, 0x20);
    D_800DCFDC = D_800DCFF8;
    D_800DCFDA = 0;
    D_800DCFE4 = 0;
    D_800DCFE0 = b;
    D_800DCFE8 = 0x20;
    while (osEPiStartDma(D_800DCFD4, D_800DCFD8, 1) != 0) {
    }
    osRecvMesg(D_800DCFF8, &sp10, 1);
    func_8002BAB8();
    for (i = 0; i < 4; i++) {
        func_800B8C4C(i);
    }
    func_800B9268(-1);
    q = D_800DCFB8;
    osWritebackDCache(q, 0x2D80);
    D_800DCFDC = D_800DCFF8;
    D_800DCFE4 = 0x20;
    D_800DCFDA = 0;
    D_800DCFE0 = q;
    D_800DCFE8 = 0x2D80;
    while (osEPiStartDma(D_800DCFD4, D_800DCFD8, 1) != 0) {
    }
    osRecvMesg(D_800DCFF8, &sp10, 1);
    releaseHeapBlock(b);
}
