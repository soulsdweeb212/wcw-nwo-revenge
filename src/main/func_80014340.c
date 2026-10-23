#include "common.h"

typedef struct{u8 type;s32 value;}Msg;
void func_800160E8(s32,s32,s32);void func_80015EF8(void*,void*,s32);
extern s32 D_80060504,D_80060508,D_8006050C;extern u8 *D_80060510;
extern s32 D_800604F8,D_800604FC;
extern u32 D_800604C8;extern u8 *D_800604D0;
/* Dispatch a queued audio message: type 0 starts, type 1 stops the voice. */
void func_80014418(Msg *p){switch(p->type){case 0:func_800160E8(p->value,-2,1);break;case 1:func_800160E8(p->value,-2,0);break;}}
/* Enqueue an 8-byte message into the ring buffer; return 1 on success, 0 if full. */
s32 func_8001446C(void *arg0){s32 old=D_80060508; s32 next=(old+1)%D_8006050C;if(next!=D_80060504){func_80015EF8(arg0,D_80060510+old*8,8);D_80060508=next;return 1;}return 0;}
/* When arg0 is zero, queue a type-2 message carrying the current sequence value,
 * then latch arg0 into D_800604F8 if the enqueue succeeded. */
void func_80014340(s32 arg0){Msg msg;s32 r=1;if(arg0==0){msg.type=2;msg.value=D_800604FC;D_800604FC=msg.value;r=func_8001446C(&msg);}if(r)D_800604F8=arg0;}
/* On every voice record whose key (+0x60) matches arg0, set +0xD0 to arg1 and mark
 * +0xDE = 255; return the number of records updated. */
s32 func_80013E10(s32 arg0,s32 arg1){u32 i;s32 n;u8 *p;if(arg0==0)return 0;n=0;p=D_800604D0;for(i=0;i<D_800604C8;i++){if(*(s32*)(p+0x60)==arg0){n++;*(s16*)(p+0xD0)=arg1;p[0xDE]=255;}p+=0x158;}return n;}
