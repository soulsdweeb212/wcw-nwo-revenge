#include "common.h"

typedef struct{u8 type;s32 value;}Msg;
void func_800160E8(s32,s32,s32);void func_80015EF8(void*,void*,s32);
extern s32 D_80060504,D_80060508,D_8006050C;extern u8 *D_80060510;
extern s32 D_800604F8,D_800604FC;
extern u32 D_800604C8;extern u8 *D_800604D0;
/* Consumes an audio message: types 0/1 start/stop the sound at p->value. */
void func_80014418(Msg *p){switch(p->type){case 0:func_800160E8(p->value,-2,1);break;case 1:func_800160E8(p->value,-2,0);break;}}
/* Copies an 8-byte message into the audio command queue at the write index,
 * advancing it (wrapping) and failing when the queue is full. Returns 1 on
 * success. */
s32 func_8001446C(void *arg0){s32 old=D_80060508; s32 next=(old+1)%D_8006050C;if(next!=D_80060504){func_80015EF8(arg0,D_80060510+old*8,8);D_80060508=next;return 1;}return 0;}
/* Enqueues a no-op (type 2) audio message and updates the shared sound handle. */
void func_80014340(s32 arg0){Msg msg;s32 r=1;if(arg0==0){msg.type=2;msg.value=D_800604FC;D_800604FC=msg.value;r=func_8001446C(&msg);}if(r)D_800604F8=arg0;}
/* Sets the pan (clamped 0..0xFF) of every voice whose key matches arg0. Returns
 * the number updated. */
s32 func_80013E10(s32 arg0,s32 arg1){u32 i;s32 n;u8 *p;if(arg0==0)return 0;n=0;p=D_800604D0;for(i=0;i<D_800604C8;i++){if(*(s32*)(p+0x60)==arg0){n++;*(s16*)(p+0xD0)=arg1;p[0xDE]=255;}p+=0x158;}return n;}
