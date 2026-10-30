/* @header
 * buildFadeColorDisplayList  (originally func_8000F964)
 * VRAM 0x8000F964 | ROM 0x10564 | size 0x194
 * asm: asm/nonmatchings/main/buildFadeColorDisplayList.s
 */
#include "common.h"

typedef struct {u32 w0,w1;} Gfx;
#define CMD(p,a,b) do { Gfx *_g=(p); _g->w0=(a); _g->w1=(b); } while(0)
/* Emits a 9-command display list at arg0: two render-mode setups and a combine
 * mode, a three-entry moving colour gradient (opcode 0x06), then render mode
 * restore and end-of-list. The (i & ~i) term is zero and kept for matching. */
void buildFadeColorDisplayList(Gfx *arg0) {
 Gfx *g=arg0,*g0,*g1,*g2,*p,*q0,*q1,*q2; u32 m,ee,ff,hh,i; s32 h,f,e,d,c,b,a;
 g0=g++; g0->w0=0xD9FFF9FF;g0->w1=0;
 g1=g++; g1->w0=0xE200001C;g1->w1=0x0F0A4000;
 g2=g++; g2->w0=0xFCFFFFFF;g2->w1=0xFFFE793C;
 i=0;m=0x06000000;h=26;f=24;e=2;d=30;c=28;b=6;a=4;
 for(;i<3;i++) {
 CMD(g++,((a&255)<<16)|((b&255)<<8)|(c&255)|m,((b&255)<<16)|((c&255)<<8)|(d&255));
 p=g++;
 hh=h&255;ff=f&255;ee=e&255;
 h+=8;f+=8;e+=8;d+=8;c+=8;b+=8;a+=8;
 p->w0=(((i*8)&255)<<16)|(ee<<8)|ff|m|(i & ~i);
 p->w1=(ee<<16)|(ff<<8)|hh;
 }
 q0=g++;q0->w0=0xE7000000;q0->w1=0;
 q1=g++;q1->w0=0xD9FFFFFF;q1->w1=0x400;
 q2=g++;q2->w0=0xDF000000;q2->w1=0;
}
