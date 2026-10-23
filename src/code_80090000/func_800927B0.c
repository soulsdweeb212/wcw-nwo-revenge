#include "common.h"

/* Emit a 4-digit decimal number as Gfx: set the font tile block, then for each
 * of four digit slots load the glyph and write the quad command, tinting the
 * digit when its low bits are clear. arg1 is the packed counter value. */
s32 loadResourceTexture4b(void *, void *, s32);
void accumulateColorChannels(s32,s32,s32);
extern u8 updateActionStateC5D48[];
typedef struct { s32 f0; u32 f4; u16 f8; } Desc927;
void func_800927B0(Nw2GfxCommand **arg0, s32 arg1, Desc927 *arg2) {
 Nw2GfxCommand *cmd; s32 digit,i;
 cmd=*arg0;
 { Nw2GfxCommand *g=cmd++; g->w0=0xDE000000; g->w1=(u32)(updateActionStateC5D48+0x48); }
 { Nw2GfxCommand *g=cmd++; g->w0=0x01000000|((arg2->f8&255)<<12)|((arg2->f8&127)*2); g->w1=arg2->f4; }
 i=0; do { digit=arg1; if(arg1>=10) digit=arg1%10+10;
 if(digit>=0) {
 if(loadResourceTexture4b(&cmd,arg2,digit)) {
 Nw2GfxCommand *g=cmd++;
 g->w0=(((i*8)&255)<<16)|(((i*8+2)&255)<<8)|((i*8+6)&255)|0x07000000;
 g->w1=(((i*8)&255)<<16)|(((i*8+6)&255)<<8)|((i*8+4)&255);
 }
 if(!(digit&3)) accumulateColorChannels(7,7,7);
 }
 i++; arg1-=8;
 }while(i<4);
 *arg0=cmd;
}
