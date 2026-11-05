/* @header
 * n_alAudioFrame  (originally func_80017DB0)
 * VRAM 0x80017DB0 | ROM 0x189B0 | size 0x168
 * asm: asm/nonmatchings/main/n_alAudioFrame.s
 */
/* SDK: n_audio, libnaudio/src/n_synthesizer.c (same code as the SDK source). */
#include "common.h"

typedef struct { u8 pad0[8]; s32 (*refill)(void*); u8 padC[4]; s32 fillLimit; } Node;
typedef struct { Node *head; u8 pad4[0x18]; s32 writePos; s32 cursor; u8 pad24[0x20]; s32 chunkSize; s32 srcAddr; } Ctx;
extern Ctx *D_80036F54;
void _n_collectPVoices(void);
s32 _n_timeToSamplesNoRound(s32);
s32 *n_alSavePull(s32,s32*);
/* Writes `arg3` audio samples from arg2 into the stream buffer at arg0,
 * refilling DMA nodes whose fill limit is below the requested length and
 * copying in chunkSize pieces via n_alSavePull. Stores the number of samples
 * written into *arg1 and returns the advanced destination cursor. */
s32 *n_alAudioFrame(s32 *arg0,s32 *arg1,s32 *arg2,s32 arg3){
    Node *node,*head; s32 len; s32 *dst,*src; s32 chunk;
    head=D_80036F54->head; len=arg3; dst=arg0; src=arg2;
    if(head==NULL){ *arg1=0; } else {
        node=head;
        while(node->fillLimit-D_80036F54->cursor<len){ D_80036F54->writePos=node->fillLimit&~0xF; node->fillLimit+=_n_timeToSamplesNoRound(node->refill(node)); }
        D_80036F54->writePos&=~0xF;
        while(len>0){ chunk=D_80036F54->chunkSize; if(len<chunk) chunk=len; D_80036F54->srcAddr=(s32)src; dst=n_alSavePull(D_80036F54->cursor,dst); len-=chunk; src+=chunk; D_80036F54->cursor+=chunk; }
        {s32 *end=dst; *arg1=(s32)(end-arg0)>>1; _n_collectPVoices(); return end;}
    }
    return dst;
}
