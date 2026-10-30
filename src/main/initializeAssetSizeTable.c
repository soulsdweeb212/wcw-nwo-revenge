/* @header
 * initializeAssetSizeTable  (originally func_800034A0)
 * VRAM 0x800034A0 | ROM 0x40A0 | size 0x114
 * asm: asm/nonmatchings/main/initializeAssetSizeTable.s
 */
#include "common.h"

void *allocateHeap(u32);
void readRomSynchronousChunks(void *, void *, u32);
void releaseHeapBlock(void *);
extern u32 *D_800482E0, *D_800482E4;
extern u8 D_00CE2752[], D_000DAC50[];
/* Loads the packed asset size table from ROM (0x77A8 bytes), then walks its
 * 0x1DE9 entries: each entry's end is the next entry's start, and entries whose
 * low bit is set hold an explicit size loaded from ROM. Fills D_800482E4 with
 * each asset's size and frees the scratch word. */
void initializeAssetSizeTable(void) {
 u32 *p, *tmp; u32 i; u32 start, end, flag;
 D_800482E0 = allocateHeap(0x77A8);
 readRomSynchronousChunks(D_00CE2752, D_800482E0, 0x77A8);
 D_800482E4 = allocateHeap(0x77A4);
 tmp = allocateHeap(4);
 p = D_800482E0;
 for(i=0; i<0x1DE9; i++) {
 start = *p++;
 end = *p;
 flag = start;
 start &= ~1;
 end &= ~1;
 start += (u32)D_000DAC50;
 end += (u32)D_000DAC50;
 if(flag & 1) {
 readRomSynchronousChunks((void *)start,tmp,4);
 D_800482E4[i] = *tmp;
 } else D_800482E4[i] = end-start;
 }
 releaseHeapBlock(tmp);
}
