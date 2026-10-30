/* @header
 * saveAudioRingBuffer  (originally func_8001FDEC)
 * VRAM 0x8001FDEC | ROM 0x209EC | size 0x170
 * asm: asm/nonmatchings/main/saveAudioRingBuffer.s
 */
#include "common.h"

typedef struct { u32 w0,w1; } CmdFD;
typedef struct {u8 pad[0x14];u16 *data;s32 x; s32 count;} BufferFD;
u32 func_8001CE80(void *);
#define SETFD(pkt,off,n) { CmdFD *c=(pkt); c->w0=0x08000000; c->w1=((off)<<16)|(((n)*2)&0xFFFF); }
#define SAVEFD(pkt,src) { CmdFD *c=(pkt); c->w0=0x06000000; c->w1=func_8001CE80(src); }
/* Emits the RSP commands to save `count` samples starting at `src` from the
 * audio ring buffer p at DMEM byte offset `offset`. A span wrapping past the
 * end of the ring is split into two SETBUFF/SAVEBUFF pairs (the second reads
 * back from p->data) and closes with a SETBUFF of the full count. Returns the
 * cursor past the written commands. */
CmdFD *saveAudioRingBuffer(BufferFD *p, u16 *src, s32 offset, s32 count, CmdFD *cmd) {
 CmdFD *initial=cmd;
 u16 *end=p->data+p->count;
 u16 *limit;
 s32 firstSpan, secondSpan;
 if(src<p->data) src+=p->count;
 limit=src+count;
 if(end<limit) {
  firstSpan=end-src;
  secondSpan=limit-end;
  cmd++;
  SETFD(initial,offset,firstSpan);
  SAVEFD(cmd++,src);
  SETFD(cmd++,offset+firstSpan*2,secondSpan);
  SAVEFD(cmd++,p->data);
  SETFD(cmd++,0,count);
 } else {
  cmd++;
  SETFD(initial,offset,count);
  SAVEFD(cmd++,src);
 }
 return cmd;
}
