#include "common.h"

typedef struct { s32 flags;u8 p4[0x14];s32 state;u8 p1C[0x14];s32 value;u8 p34[0x2C];s32 key;u8 p64[0xF4]; } VoiceCA4;
extern u32 D_800604C8;extern VoiceCA4 *D_800604D0;
/* Applies arg1 to every voice whose key matches arg0: voices already released
 * (state -1) are restarted, clearing their pending bit when set (value 1);
 * others get value=arg1 (minimum 1) and state=arg1. Returns the count changed. */
s32 func_80013CA4(s32 arg0,s32 arg1) {
 if(!arg0)return 0;
 {s32 amount=arg1;if(!arg1)amount=1;
 {u32 i=0;VoiceCA4 *p=D_800604D0;s32 n=0;
 while(i<D_800604C8){if(p->key==arg0){if(p->state==-1){if(p->flags&1){p->value=1;p->state=0;p->flags&=~1;}else{p->value=amount;p->state=arg1;}n++;}}i++;p++;}return n;}
 }
}
