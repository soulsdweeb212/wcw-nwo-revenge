/* @header
 * allocateHeap  (originally func_80000854)
 * VRAM 0x80000854 | ROM 0x1454 | size 0x104
 * asm: asm/nonmatchings/main/func_80000854.s
 */
#include "common.h"

typedef struct HeapBlock { struct HeapBlock *next; u32 size; u64 magic; } HeapBlock;
extern HeapBlock *D_8002EE94;
extern HeapBlock D_801F0000;
extern u32 D_801F0004;
extern s32 D_8007C430;
void func_80021F60(void *, s32);
/* Allocates at least `bytes` from the circular 16-byte-unit free list,
 * initializing the 0x21000-unit heap on first use. Splits a block when it is
 * larger than needed, stamps the 0xCAFE4ABE magic and returns the payload. */
void *allocateHeap(u32 bytes) {
 HeapBlock *prev = D_8002EE94;
 HeapBlock *p;
 u32 units = ((bytes + 15) >> 4) + 1;
 u32 size;
 if (prev == NULL) {
  prev = &D_801F0000;
  func_80021F60(prev, 0x210000);
  D_8002EE94 = prev;
  D_801F0000.next = prev;
  D_801F0004 = 0x21000;
  D_8007C430 = 0;
 }
 p = prev->next;
 for (;;) {
  size = p->size;
  if (size >= units) {
   if (size == units) prev->next = p->next;
   else { p->size = size - units; p += p->size; p->size = units; }
   p->magic = 0xCAFE4ABE;
   D_8002EE94 = prev;
   D_8007C430++;
   return p + 1;
  }
  if (p == D_8002EE94) break;
  prev = p;
  p = p->next;
 }
 return NULL;
}
