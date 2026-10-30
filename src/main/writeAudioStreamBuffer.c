/* @header
 * writeAudioStreamBuffer  (originally func_80017DB0)
 * VRAM 0x80017DB0 | ROM 0x189B0 | size 0x168
 * asm: asm/nonmatchings/main/func_80017DB0.s
 */
#include "common.h"

typedef struct { u8 pad0[8]; s32 (*refill)(void*); u8 padC[4]; s32 fillLimit; } Node;
typedef struct { Node *head; u8 pad4[0x18]; s32 writePos; s32 cursor; u8 pad24[0x20]; s32 chunkSize; s32 srcAddr; } Ctx;
extern Ctx *D_80036F54;
void func_80017F5C(void);
s32 func_80017FF4(s32);
s32 *func_8001A360(s32,s32*);
/* Writes `arg3` audio samples from arg2 into the stream buffer at arg0,
 * refilling DMA nodes whose fill limit is below the requested length and
 * copying in chunkSize pieces via func_8001A360. Stores the number of samples
 * written into *arg1 and returns the advanced destination cursor. */
s32 *writeAudioStreamBuffer(s32 *arg0,s32 *arg1,s32 *arg2,s32 arg3){
  Node *node,*head; s32 len; s32 *dst,*src; s32 chunk;
  head=D_80036F54->head; len=arg3; dst=arg0; src=arg2;
  if(head==NULL){ *arg1=0; } else {
    node=head;
    while(node->fillLimit-D_80036F54->cursor<len){ D_80036F54->writePos=node->fillLimit&~0xF; node->fillLimit+=func_80017FF4(node->refill(node)); }
    D_80036F54->writePos&=~0xF;
    while(len>0){ chunk=D_80036F54->chunkSize; if(len<chunk) chunk=len; D_80036F54->srcAddr=(s32)src; dst=func_8001A360(D_80036F54->cursor,dst); len-=chunk; src+=chunk; D_80036F54->cursor+=chunk; }
    {s32 *end=dst; *arg1=(s32)(end-arg0)>>1; func_80017F5C(); return end;}
  }
  return dst;
}
