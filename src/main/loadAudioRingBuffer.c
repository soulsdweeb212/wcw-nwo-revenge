/* @header
 * loadAudioRingBuffer  (originally func_8001FC7C)
 * VRAM 0x8001FC7C | ROM 0x2087C | size 0x170
 * asm: asm/nonmatchings/main/loadAudioRingBuffer.s
 */
#include "common.h"

typedef struct { u32 w0,w1; } CmdFC;
typedef struct {u8 pad[0x14];u16 *data;s32 x; s32 count;} BufferFC;
u32 func_8001CE80(void *);
#define SETFC(pkt,off,n) { CmdFC *c=(pkt); c->w0=0x08000000|((off)&0xFFFF); c->w1=((n)*2)&0xFFFF; }
#define LOADFC(pkt,src) { CmdFC *c=(pkt); c->w0=0x04000000; c->w1=func_8001CE80(src); }
/* Emits the RSP commands to load `count` samples starting at `src` into the
 * audio ring buffer p at DMEM byte offset `offset`. When the requested span
 * wraps past the end of the ring it is split into two SETBUFF/LOADBUFF pairs
 * (the second starting back at p->data). Always closes with a SETBUFF of the
 * full count. Returns the cursor past the written commands. */
CmdFC *loadAudioRingBuffer(BufferFC *p, u16 *src, s32 offset, s32 count, CmdFC *cmd) {
 CmdFC *initial=cmd;
 u16 *end=p->data+p->count;
 u16 *limit;
 s32 firstSpan, secondSpan;
 if(src<p->data) src+=p->count;
 limit=src+count;
 if(end<limit) {
  firstSpan=end-src;
  secondSpan=limit-end;
  cmd++;
  SETFC(initial,offset,firstSpan);
  LOADFC(cmd++,src);
  SETFC(cmd++,offset+firstSpan*2,secondSpan);
  LOADFC(cmd++,p->data);
 } else {
  cmd++;
  SETFC(initial,offset,count);
  LOADFC(cmd++,src);
 }
 SETFC(cmd++,0,count);
 return cmd;
}
