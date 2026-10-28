#include "common.h"

typedef struct{u8 type;s32 value;}Msg;void func_800160E8(s32,s32,s32);void func_80015EF8(void*,void*,s32);extern s32 D_80060504,D_80060508,D_8006050C;extern u8 *D_80060510;
/* Dispatch a queued audio message: type 0 starts, type 1 stops the voice; type 2 is
 * a no-op. */
void func_80014418(Msg *p){switch(p->type){case 0:func_800160E8(p->value,-2,1);break;case 1:func_800160E8(p->value,-2,0);break;case 2:break;}}
