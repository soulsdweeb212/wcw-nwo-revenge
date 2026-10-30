/* @header
 * writePiHandleWord  (originally func_800283A0)
 * VRAM 0x800283A0 | ROM 0x28FA0 | size 0x144
 * asm: asm/nonmatchings/main/writePiHandleWord.s
 */
#include "common.h"

typedef struct {u32 f0; u8 f4,latency,pulse,page,release,domain; u16 pad; u32 base;} PiHandle283A0;
extern PiHandle283A0 *D_80037620[];
s32 writePiHandleWord(PiHandle283A0 *h,u32 addr,u32 value) {
 PiHandle283A0 *old; u32 domain;
 while(*(vu32 *)0xa4600010 & 3) {}
 domain=h->domain; old=D_80037620[domain];
 if(old!=h) {
 if(domain==0) {
 if(old->latency!=h->latency) *(vu32 *)0xa4600014=h->latency;
 if(old->pulse!=h->pulse) *(vu32 *)0xa460001c=h->pulse;
 if(old->page!=h->page) *(vu32 *)0xa4600020=h->page;
 if(old->release!=h->release) *(vu32 *)0xa4600018=h->release;
 } else {
 if(old->latency!=h->latency) *(vu32 *)0xa4600024=h->latency;
 if(old->pulse!=h->pulse) *(vu32 *)0xa460002c=h->pulse;
 if(old->page!=h->page) *(vu32 *)0xa4600030=h->page;
 if(old->release!=h->release) *(vu32 *)0xa4600028=h->release;
 }
 D_80037620[domain]=h;
 }
 *(vu32 *)(h->base|addr|0xa0000000)=value;
 return 0;
}
