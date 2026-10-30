/* @header
 * func_800084AC
 * VRAM 0x800084AC | ROM 0x90AC | size 0xC8
 * asm: asm/nonmatchings/main/func_800084AC.s
 */
#include "common.h"

extern u8 D_8006A2B0[];
extern u8 D_8006A2B2[];
extern s32 D_80030830;

void readRomSynchronousChunks(s32, void *, s32);
void *allocateHeap(s32);
void releaseHeapBlock(void *);
void lookupResourceDescriptor(s32 *, s32);
s16 func_80008574(s32);

void func_800084AC(void)
{
    s32 tmp[4];
    u32 i;
    s32 fix;
    s32 off;
    u8 *buf;

    if (D_80030830 != 0) {
        buf = allocateHeap(4);
        i = 0;
        fix = 0xE390000;
        off = 0;
loop:
        lookupResourceDescriptor(tmp, (i + 0xE39) & 0xFFFF);
        readRomSynchronousChunks(tmp[0], buf, 4);
        *(u16 *)(D_8006A2B0 + off) = *(u16 *)(buf + 0);
        i++;
        *(u16 *)(D_8006A2B2 + off) = *(u16 *)(buf + 2);
        func_80008574(fix >> 16);
        fix += 0x10000;
        off += 4;
        if (i < 0xFB1) {
            goto loop;
        }
        releaseHeapBlock(buf);
        D_80030830 = 0;
    }
}
