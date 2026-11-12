/* @header
 * func_800BB110
 * VRAM 0x800BB110 | ROM 0x67880 | size 0x190
 * asm: asm/nonmatchings/code_80090000/func_800BB110.s
 */
#include "common.h"

#ifdef TARGET_PC
/* PC: D_800DCFD8 is the cartridge request (libultra's OSIoMesg) of the save-memory transfers, which the N64 code fills
 * through labels of its fields (D_800DCFDA its priority, D_800DCFDC its queue, D_800DCFE0 the RAM address, D_800DCFE4
 * the device address, D_800DCFE8 the size). Those labels have no PC symbol, and on PC the request is port.h's
 * PortIoMesg, whose addresses are pointers, so the code fills it by field name. D_800DCFD4 holds the address of the
 * PI handle that func_80000A40 returns, so it is a pointer. The SDK and game functions are declared with the port's
 * and their definitions' types (the message pointers as void *, as func_80009990 and initializeResourceStream declare
 * them; bzero, allocateHeap and releaseHeapBlock as src/main defines them). */
extern PortIoMesg D_800DCFD8;
extern u8 D_800DCFF8[];
extern u8 *D_800DCFB8;
extern void *D_800DCFD4;
void *allocateHeap(u32 bytes);
void releaseHeapBlock(u8 *arg0);
void bzero(void *dst, s32 len);
void osWritebackDCache(void *, s32);
s32 osEPiStartDma(void *, void *, s32);
s32 osRecvMesg(void *, void *, s32);
void func_8002BAB8(void);
void func_800B8C4C(s32 mode);
void func_800B9268(s32 id);

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
    D_800DCFD8.retQueue = D_800DCFF8;
    D_800DCFD8.pri = 0;
    D_800DCFD8.devAddr = 0;
    D_800DCFD8.dramAddr = b;
    D_800DCFD8.size = 0x20;
    while (osEPiStartDma(D_800DCFD4, &D_800DCFD8, 1) != 0) {
    }
    osRecvMesg(D_800DCFF8, &sp10, 1);
    func_8002BAB8();
    for (i = 0; i < 4; i++) {
        func_800B8C4C(i);
    }
    func_800B9268(-1);
    q = D_800DCFB8;
    osWritebackDCache(q, 0x2D80);
    D_800DCFD8.retQueue = D_800DCFF8;
    D_800DCFD8.devAddr = 0x20;
    D_800DCFD8.pri = 0;
    D_800DCFD8.dramAddr = q;
    D_800DCFD8.size = 0x2D80;
    while (osEPiStartDma(D_800DCFD4, &D_800DCFD8, 1) != 0) {
    }
    osRecvMesg(D_800DCFF8, &sp10, 1);
    releaseHeapBlock(b);
}
#else
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
#endif
