#include "common.h"

void *allocateHeap(u32); void func_800015AC(void *,s32);void func_80001544(void *);
void buildColorOverlayDisplayList(u8 *obj,u8 red,u8 green,u8 blue,u8 alpha){
 Nw2GfxCommand *dl;u32 i;u32 r=red,g=green,b=blue,a=alpha;
 if(!*(void **)(obj+0x10)){
 *(void **)(obj+0x10)=allocateHeap(0x300);func_800015AC(obj,0);func_80001544(obj);*(f32 *)(*(u8 **)(obj+0x14)+0x24)=-15000.0f;obj[0x19]=1;
 }
 dl=*(Nw2GfxCommand **)(obj+0x10);
 {Nw2GfxCommand *q=dl++;q->w0=0xe7000000;q->w1=0;}
 {Nw2GfxCommand *q=dl++;q->w0=0xfa000000;q->w1=(r<<24)|(g<<16)|(b<<8)|a;}
 {Nw2GfxCommand *q=dl++;q->w0=0xe200001c;q->w1=0x504240;}
 {Nw2GfxCommand *q=dl++;q->w0=0xfcffffff;q->w1=0xfffdf6fb;}
 for(i=0;i<8;i++){
 Nw2GfxCommand *q=dl++;q->w0=0xf677c000|(((i+1)*120)&0xff8);q->w1=(i*120)&0xff8;
 }
 {Nw2GfxCommand *q=dl++;q->w0=0xe7000000;q->w1=0;}
 {Nw2GfxCommand *q=dl++;q->w0=0xdf000000;q->w1=0;}
}
