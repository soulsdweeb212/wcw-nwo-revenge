/* @header
 * func_80011764
 * VRAM 0x80011764 | ROM 0x12364 | size 0x3C0
 * asm: asm/nonmatchings/main/func_80011764.s
 */
#include "common.h"

typedef struct { u32 w0,w1; } Cmd117;
typedef struct { Cmd117 *buf[3]; u8 slot,type,frame; s8 timer; } Anim117;
typedef struct { s8 v; u8 pad[15]; } Byte117; typedef struct { u8 v; u8 pad[15]; } UByte117;
typedef struct { volatile s32 f0; u8 pad4[0x28]; volatile s16 f2C,f2E; volatile u32 f30,f34; } Sub117;
typedef struct { u8 pad0[12]; void *fC; u8 pad10[4]; Sub117 *f14; u8 pad18[2]; u8 f1A; u8 pad1B[0xC1]; } Desc117;
extern Anim117 D_8005AAA0[]; extern u8 D_8005AAAC[],D_8005AAAD[]; extern UByte117 D_8005AAAE[]; extern Byte117 D_8005AAAF[]; extern Desc117 D_8005A3C0[]; extern void *D_8005B218; extern u8 D_8005B220[],D_8007E010[]; extern s8 D_8007E013[]; extern u16 D_800307A0; extern u8 D_80036DEC[],D_80036DF4[],D_80036DFC[],D_80036E04[],D_80036E0C[],D_80036E14[];
Cmd117 *buildCi4TextureDisplayList(void *,void *,u16); u32 func_8001CE80(void *); void func_800015AC(void *,s32);
#define CMD117(a,b) { Cmd117 *g=p++; g->w0=(a); g->w1=(b); }
static inline void tail117(Desc117 *d, void *v, Cmd117 *p) { Sub117 *sub; d->f1A=0;d->fC=v;func_800015AC(d,4);sub=d->f14;sub->f0=1;sub->f2C=4;sub->f30=0;sub->f34=0;sub->f2E=0;sub->f30=(u32)v;sub->f34=(u32)p; }
void func_80011764(s16 arg0) { u16 slot,type; u8 frame; Cmd117 *p,*g; Desc117 *d; Anim117 *anim=&D_8005AAA0[arg0]; anim->timer=D_8005AAAF[arg0].v-1; if(D_8005AAAF[arg0].v<0) { slot=D_8005AAAC[arg0*16]; frame=D_8005AAAE[arg0].v; type=D_8005AAAD[arg0*16]; p=anim->buf[slot]; d=&D_8005A3C0[arg0]; if(frame<D_80036DEC[type]) { if(D_800307A0==1) { if(type==6) {CMD117(0xFA000000,0xFFFFFF7F);} else {CMD117(0xFA000000,0x7F7F7F7F);} } else {CMD117(0xFA000000,(D_80036DFC[type]<<24)|(D_80036E04[type]<<16)|(D_80036E0C[type]<<8)|D_80036E14[type]);} p=buildCi4TextureDisplayList(D_8005B220+(frame+D_80036DF4[type])*8,p,type); CMD117(0xD9DFFFFB,0); CMD117(0xE3001001,0xC000); g=p++;g->w0=0x01004008;g->w1=func_8001CE80(D_8005B218); CMD117(0x06000204,0x00040206); CMD117(0xE7000000,0); CMD117(0xD9FFFFFF,0x200004); CMD117(0xE2001E01,0); CMD117(0xE3001001,0x8000); CMD117(0xDF000000,0); D_8005AAAE[arg0].v++; } else { D_8007E010[arg0*92]=1; D_8007E013[arg0*92]=-1; p->w0=0xDF000000;p->w1=0; } tail117(d, D_8005B218, D_8005AAA0[arg0].buf[slot]); slot++; D_8005AAAF[arg0].v=1;D_8005AAAC[arg0*16]=slot%3; } }
