#include "common.h"

/* Allocate a DMA transfer block of `size` bytes for physical address `addr`.
 *
 * Addresses in the 0xFF000000 KSEG range are remapped (addr &= 0xFFFFFF,
 * addr += 0x140000) and use the alternate queue D_80062574; otherwise the
 * primary queue D_80062570 is used (unless the D_8007BD64&1 path validates
 * `addr` directly through func_8001CE80).
 *
 * The active block list D_80062524 is searched for a block that already covers
 * [addr, addr+size) within D_80062568 bytes of its base. If found, its stamp is
 * refreshed and the mapped offset is returned through func_8001CE80. Otherwise
 * the head of the free list D_80062528 is popped, linked into the active list
 * (before `prev`, or at the head), its address/extent are filled in, and a
 * transfer message is posted to `queue` via func_800219B0.
 *
 * Returns the mapped offset plus the low-bit alignment. */
typedef struct Nw2DmaBlock
{
  struct Nw2DmaBlock *next;
  struct Nw2DmaBlock *prev;
  s32 addr;
  s32 stamp;
  u32 offset;
} Nw2DmaBlock;
typedef struct
{
  u8 f0;
  u8 f1;
  u8 f2;
  u8 f3;
  void *f4;
  u32 f8;
  u32 fC;
  u32 f10;
  u8 pad14[4];
} Nw2DmaMsg;
s32 func_8001CE80(void *);
s32 func_8002023C(Nw2DmaBlock *, s32);
void func_8002021C(Nw2DmaBlock *, Nw2DmaBlock *);
s32 func_800219B0(void *, void *, s32);
extern Nw2DmaBlock *D_80062524;
extern Nw2DmaBlock *D_80062528;
extern u8 D_80062540[];
extern u8 *D_80062560;
extern s32 D_80062568;
extern void *D_80062570;
extern void *D_80062574;
extern s32 D_80036F30;
extern s32 D_80036F38;
extern u32 D_8007BD64;
s32 func_800171B4(u32 addr, s32 size)
{
  Nw2DmaBlock *prev;
  Nw2DmaBlock *cur;
  Nw2DmaBlock **headp;
  void *queue;
  s32 end;
  s32 top;
  u32 new_var;
  u32 align;
  u32 offset;
  Nw2DmaMsg *msg;
  if ((addr & 0xFF000000) == 0xFF000000)
  {
    queue = D_80062574;
    addr &= 0xFFFFFF;
    addr += 0x140000;
  }
  else
    if (D_8007BD64 & 1)
  {
    return func_8001CE80(addr);
  }
  else
  {
    queue = D_80062570;
  }
  cur = D_80062524;
  prev = NULL;
  end = addr + size;
  while (cur != NULL)
  {
    top = cur->addr + D_80062568;
    if (addr < cur->addr)
    {
      break;
    }
    prev = cur;
    if (top >= end)
    {
      new_var = cur->offset;
      cur->stamp = D_80036F30;
      offset = new_var;
      return func_8001CE80((offset + addr) - cur->addr);
    }
    cur = cur->next;
  }

  headp = &D_80062528;
  cur = *headp;
  if (cur == NULL)
  {
    return func_8001CE80(D_80062524);
  }
  *headp = cur->next;
  func_8002023C(cur, end);
  if (prev != NULL)
  {
    func_8002021C(cur, prev);
  }
  else
  {
    if (D_80062524 != NULL)
    {
      prev = D_80062524;
      D_80062524 = cur;
      cur->next = prev;
      cur->prev = NULL;
      prev->prev = cur;
    }
    else
    {
      D_80062524 = cur;
      cur->next = NULL;
      cur->prev = NULL;
    }
  }
  align = addr & 1;
  addr -= align;
  cur->addr = addr;
  cur->stamp = D_80036F30;
  offset = cur->offset;
  msg = (Nw2DmaMsg *) (D_80062560 + (D_80036F38 * 0x18));
  msg->f2 = 0;
  msg->f4 = D_80062540;
  msg->fC = addr;
  msg->f8 = offset;
  msg->f10 = D_80062568;
  func_800219B0(queue, msg, 0);
  D_80036F38++;
  return func_8001CE80(offset) + align;
}
