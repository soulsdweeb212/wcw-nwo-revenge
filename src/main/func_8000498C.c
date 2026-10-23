#include "common.h"

/*
 * Initialize a display object `p` from resource `id`: load the raw resource,
 * copy the small header fields out of it (bit 7 of byte 1 is stored in f6,
 * the rest of the header bytes fill f2 and the two nibbles at +4/+5), then
 * allocate/attach the vertex and texture buffers and build the display lists.
 * Buffers come from an existing arena when p->f28 is set, otherwise from the
 * heap.  The temporary resource buffer is freed at the end.
 */
void lookupResourceDescriptor(void *, u16);
void func_80003684(void *, u16, void *);
void *allocateHeap(u32);
void releaseHeapBlock(void *);
void *func_80007B50(s32, u8);
void *func_80007B84(s32, u16);
void func_8000486C(void *, void *);
void buildVertexDisplayList(void *, void *);
void buildObjectDisplayListTail(void *);
void func_8000498C(Nw2Descr4BA8 *p, u16 id) {
 s32 descriptor[4];
 s32 scratch[4];
 u8 *raw;
 lookupResourceDescriptor(descriptor, id);
 raw = allocateHeap(descriptor[2]);
 func_80003684(scratch, id, raw);
 p->f6 = raw[1] & 0x80;
 raw[1] &= 0x7F;
 ((u8 *)p)[0] = 1;
 p->f2 = raw[1];
 ((u8 *)p)[1] = raw[2];
 ((u8 *)p)[4] = raw[3] >> 4;
 ((u8 *)p)[5] = raw[3] & 15;
 if (p->f2 > 0) {
  if (p->f28) p->fC = (s32)func_80007B50(p->f28, raw[1]);
  else p->fC = (s32)allocateHeap(raw[1] * 16);
  func_8000486C((void *)p->fC, raw);
 }
 if (((s8 *)p)[1] > 0) {
  if (p->f28) {
   p->f14 = (s32)func_80007B84(p->f28, ((s8 *)p)[1] / 2 + 5);
   p->f10 = (s32)func_80007B84(p->f28, 24);
  } else {
   p->f14 = (s32)allocateHeap((((s8 *)p)[1] / 2 + 5) * 8);
   p->f10 = (s32)allocateHeap(256);
  }
  buildVertexDisplayList(p, raw);
  buildObjectDisplayListTail(p);
 }
 releaseHeapBlock(raw);
}
