/* @header
 * buildAudioLoadBufferCommands  (originally func_8001E0AC)
 * VRAM 0x8001E0AC | ROM 0x1ECAC | size 0x178
 * asm: asm/nonmatchings/main/buildAudioLoadBufferCommands.s
 */
#include "common.h"

typedef struct {u32 w0,w1;} CmdE0;
typedef struct {u8 pad[0x14]; u32 buffer; u32 state; u8 pad1c[0x14]; s32 (*dma)(s32,s32,s32); s32 dmaState; u8 pad38[8]; s32 f40; s32 f44;} VoiceE0;
/* Builds the RSP audio command list for loading `count` samples from `src`:
 * a LOADBUFF pair (with DMA alignment adjustment) when len>0, an optional
 * SETSTATE command when flags bit1 is set, then the SETBUFF and the
 * ADDMIXER/opcode-0x01 command referencing v->buffer. Clears v->f40 and
 * returns the cursor past the written commands. */
CmdE0 *buildAudioLoadBufferCommands(CmdE0 *out, VoiceE0 *v, s32 count, s32 len, u16 dest, s32 src, s32 flags) {
 s16 base=src; s32 align; s32 addr; CmdE0 *p,*q; s32 round;
 if(len>0){addr=v->dma(v->f44,len,v->dmaState); align=addr&7; len+=align; p=out++; q=out++; p->w0=0x08000000|(src&0xffff); round=(len&7)-8; p->w1=(len-round)&0xffff; q->w0=0x04000000; q->w1=addr-align;} else align=0;
 if(flags&2){CmdE0 *r=out++; r->w0=0x0f000000; r->w1=v->state&0x1fffffff;}
 {CmdE0 *r=out++; r->w0=0x08000000|((base+align)&0xffff); r->w1=(dest<<16)|((count*2)&0xffff);}
 {CmdE0 *r=out++; r->w0=0x01000000|((flags&0xff)<<16); r->w1=v->buffer&0x1fffffff;} v->f40=0; return out;
}
