#include "common.h"

typedef struct{u8 type;s32 value;}Msg;void func_800160E8(s32,s32,s32);void func_80015EF8(void*,void*,s32);extern s32 D_80060504,D_80060508,D_8006050C;extern u8 *D_80060510;
/* Dispatch a queued audio message: type 0 starts, type 1 stops the voice; type 2 is
 * a no-op. */
void func_80014418(Msg *p){switch(p->type){case 0:func_800160E8(p->value,-2,1);break;case 1:func_800160E8(p->value,-2,0);break;case 2:break;}}
/* Enqueue an 8-byte message into the ring buffer; return 1 on success, 0 if full. */
s32 func_8001446C(void *arg0){s32 old=D_80060508; s32 next=(old+1)%D_8006050C;s32 r;if(next!=D_80060504){func_80015EF8(arg0,D_80060510+old*8,8);D_80060508=next;r=1;}else r=0;return r;}
