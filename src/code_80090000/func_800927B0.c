/* @header
 * func_800927B0
 * VRAM 0x800927B0 | ROM 0x3EF20 | size 0x1B0
 * asm: asm/nonmatchings/code_80090000/func_800927B0.s
 */
#include "common.h"

/* Emit a 4-digit decimal number as Gfx: set the font tile block, then for each
 * of four digit slots load the glyph and write the quad command, tinting the
 * digit when its low bits are clear. arg1 is the packed counter value. */
s32 loadResourceTexture4b(void *, void *, s32);
void accumulateColorChannels(s32,s32,s32);
extern u8 D_800C5D48[];
typedef struct { s32 f0; u32 f4; u16 f8; } Desc927;
#ifdef TARGET_PC
/* PC: a command is port.h's 16-byte Gfx (common.h's Nw2GfxCommand is the N64's 8 bytes), and the branch target goes
 * into the command as the whole pointer (port.h's DL_ADDR). arg2->f4, the digits' vertices, is still the record's
 * 32-bit word: arg2 is D_800C6588, overlay 1 data whose PC layout is not decided yet. */
void func_800927B0(Gfx **arg0, s32 arg1, Desc927 *arg2) {
    Gfx *cmd; s32 digit,i;
    cmd=*arg0;
    { Gfx *g=cmd++; g->w0=0xDE000000; g->w1=DL_ADDR(D_800C5D48+0x48); }
    { Gfx *g=cmd++; g->w0=0x01000000|((arg2->f8&255)<<12)|((arg2->f8&127)*2); g->w1=arg2->f4; }
    i=0; do { digit=arg1; if(arg1>=10) digit=arg1%10+10;
        if(digit>=0) {
            if(loadResourceTexture4b(&cmd,arg2,digit)) {
                Gfx *g=cmd++;
                g->w0=(((i*8)&255)<<16)|(((i*8+2)&255)<<8)|((i*8+6)&255)|0x07000000;
                g->w1=(((i*8)&255)<<16)|(((i*8+6)&255)<<8)|((i*8+4)&255);
            }
            if(!(digit&3)) accumulateColorChannels(7,7,7);
        }
        i++; arg1-=8;
    }while(i<4);
    *arg0=cmd;
}
#else
void func_800927B0(Nw2GfxCommand **arg0, s32 arg1, Desc927 *arg2) {
    Nw2GfxCommand *cmd; s32 digit,i;
    cmd=*arg0;
    { Nw2GfxCommand *g=cmd++; g->w0=0xDE000000; g->w1=(u32)(D_800C5D48+0x48); }
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
#endif
