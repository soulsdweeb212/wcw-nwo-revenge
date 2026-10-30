/* @header
 * readPiHandleWord  (originally func_80028210)
 * VRAM 0x80028210 | ROM 0x28E10 | size 0x190
 * asm: asm/nonmatchings/main/readPiHandleWord.s
 */
#include "common.h"

extern Nw2PiHandle *D_80037620[];
extern char D_8003B9D8[],D_8003B9DC[];
void func_8001CEE0(char *,char *,s32);
s32 readPiHandleWord(Nw2PiHandle *h,u32 addr,u32 *value) {
 Nw2PiHandle *old; u32 domain;
 if(value==NULL) func_8001CEE0(D_8003B9D8,D_8003B9DC,43);
 while(*(vu32 *)0xa4600010 & 3) {}
 domain=h->domain;old=D_80037620[domain];
 if(old!=h){
 if(domain==0){
 if(old->latency!=h->latency) *(vu32 *)0xa4600014=h->latency;
 if(old->pulse!=h->pulse) *(vu32 *)0xa460001c=h->pulse;
 if(old->page!=h->page) *(vu32 *)0xa4600020=h->page;
 if(old->release!=h->release) *(vu32 *)0xa4600018=h->release;
 }else{
 if(old->latency!=h->latency) *(vu32 *)0xa4600024=h->latency;
 if(old->pulse!=h->pulse) *(vu32 *)0xa460002c=h->pulse;
 if(old->page!=h->page) *(vu32 *)0xa4600030=h->page;
 if(old->release!=h->release) *(vu32 *)0xa4600028=h->release;
 }
 D_80037620[domain]=h;
 }
 *value=*(vu32 *)(h->base|addr|0xa0000000);
 return 0;
}
